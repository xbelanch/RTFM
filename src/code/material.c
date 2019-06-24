/* NOTE:
   must split in files for every material: lambertian.c, metal.c, dielectric.c...
*/
#define _XOPEN_SOURCE    /* ALWAYS BEFORE the include statement */
// https://cs50.stackexchange.com/questions/6061/implicit-declaration-of-function-drand48-is-invalid-in-c99-generating-rand
#define _CRT_RAND_S

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "common.h"
#include "vector.h"
#include "ray.h"
#include "color.h"
#include "hitable.h"
#include "material.h"
// private functions


v3 random_in_unit_sphere()
{
  v3 p;
  double t;
  do {
    p.x = 2.0 * drand48() - 1.0;
    p.y = 2.0 * drand48() - 1.0;
    p.z = 2.0 * drand48() - 1.0;
    t = v3SquaredLength(p);
  } while (t >= 1.0);
  return p;
}


// Lambertian material definition

bool scatter_lambertian (Material* self, Ray* ray_in, hit_record rec, Color* attenuation,  Ray* scattered)
{

  v3 rand = random_in_unit_sphere();
  v3 target = {
               rec.p.x + rec.normal.x + rand.x,
               rec.p.y + rec.normal.y + rand.y,
               rec.p.z + rec.normal.z + rand.z
  };
  v3 rdir = {
             target.x - rec.p.x,
             target.y - rec.p.y,
             target.z - rec.p.z
  };


  scattered->origin = rec.p;
  scattered->direction = rdir;

  attenuation->r = self->albedo.r;
  attenuation->g = self->albedo.g;
  attenuation->b = self->albedo.b;

  return true;

}

Material* Lambertian(Color albedo)
{
  Material* mat = NEWTYPE(Material);

  if (mat != NULL)
    {
      mat->albedo = albedo;
      mat->scatter = scatter_lambertian;
      return mat;
    }

  return NULL;
}

// METAL

v3 reflect(v3 v, v3 n)
{
  v3 reflected = {.0, .0, .0};
  reflected.x -= 2 * v3Dot(&v, &n) * n.x;
  reflected.y -= 2 * v3Dot(&v, &n) * n.y;
  reflected.z -= 2 * v3Dot(&v, &n) * n.z;
  return reflected;
}

bool scatter_metal (Material* self, Ray* ray_in, hit_record rec, Color* attenuation, Ray* scattered)
{
  v3Normalize(ray_in->direction);
  v3 reflected = reflect(ray_in->direction, rec.normal);
  v3 rand = random_in_unit_sphere();

  scattered->origin = rec.p;
  scattered->direction.x = reflected.x + (rand.x * self->fuzz);
  scattered->direction.y = reflected.y + (rand.y * self->fuzz);
  scattered->direction.z = reflected.z + (rand.z * self->fuzz),

  attenuation->r = self->albedo.r;
  attenuation->g = self->albedo.g;
  attenuation->b = self->albedo.b;

  if (v3Dot(&scattered->direction, &rec.normal ) > 0)
    {
      return true;
        } else {
    return false;
  }
}


Material* Metal(Color albedo, double fuzz)
{
  Material *mat;
  mat = malloc(sizeof(Material));
  if (mat != NULL)
    {
      mat->albedo = albedo;
      if (fuzz < 1.0)
        {
          mat->fuzz = fuzz;
        } else {
        mat->fuzz = 1.0;
      }
      mat->scatter = scatter_metal;
      return mat;
    }
  return NULL;
}

/* Dielectric Material */

bool refract(v3 v, v3 n, double ni_over_nt, v3* refracted)
{
  v3 uv = v;
  v3Normalize(&uv);
  double dt = v3Dot(&uv, &n);
  double discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);
  if (discriminant > 0)
    {
      refracted->x = ni_over_nt * (uv.x - n.x * dt) - n.x * sqrt(discriminant);
      refracted->y = ni_over_nt * (uv.y - n.y * dt) - n.y * sqrt(discriminant);
      refracted->z = ni_over_nt * (uv.z - n.z * dt) - n.z * sqrt(discriminant);
      return true;
    }
  else
    return false;
}


// Real glass has reflectivity that varies with angle. This is a
// big ugly equation for that, but almost everybody uses a simple
// and surprisingly polynomial approximation by Christophe Schlick
double schlick(double cosine, double ref_idx)
{
  double r0 = (1 - ref_idx) / (1 + ref_idx);
  r0 = r0 * r0;
  return r0 + (1 - r0) * pow((1 - cosine), 5);
}

bool scatter_dielectric (Material*self, Ray* ray_in, hit_record rec, Color* attenuation, Ray* scattered)
{
  v3 outward_normal;
  v3 reflected = reflect(ray_in->direction, rec.normal);
  double ni_over_nt;
  attenuation->r = attenuation->g = attenuation->b = 1.0;
  v3 refracted;
  double reflect_prob;
  double cosine;
  double _first_check = v3Dot(&ray_in->direction, &rec.normal);

  if (_first_check > 0)
    {
      outward_normal.x = -rec.normal.x;
      outward_normal.y = -rec.normal.y;
      outward_normal.z = -rec.normal.z;
      ni_over_nt = self->ref_idx;
      cosine = self->ref_idx * v3Dot(&ray_in->direction, &rec.normal) / v3Length(&ray_in->direction);
    }
  else
    {
      outward_normal = rec.normal;
      ni_over_nt = 1.0 / self->ref_idx;
      cosine = -(v3Dot(&ray_in->direction, &rec.normal) / v3Length(&ray_in->direction));
    }

  // check refract
  bool _refract = refract(ray_in->direction, outward_normal, ni_over_nt, &refracted);
  if (_refract)
    {
      scattered->origin = rec.p;
      scattered->direction = refracted;
      reflect_prob = schlick(cosine, self->ref_idx);
    }
  else
    {
      scattered->origin = rec.p;
      scattered->direction = reflected;
      reflect_prob = 1.0;
    }

  // randomness
  if (drand48() < reflect_prob)
    {
      scattered->origin = rec.p;
      scattered->direction = reflected;
    }
  else
    {
      scattered->origin = rec.p;
      scattered->direction = refracted;

    }

  return true;
}

Material* Dielectric(double ri)
{
  Material *mat;
  mat = malloc(sizeof(Material));
  if (mat != NULL)
    {
      mat->ref_idx = ri;
      mat->scatter = scatter_dielectric;
      return mat;
    }
  return NULL;
}
