#define _XOPEN_SOURCE    /* ALWAYS BEFORE the include statement */
#include <stdlib.h>
#include "common.h"
#include "vector.h"
#include "ray.h"
#include "camera.h"

Point3 point_at_parameter(Ray* ray, double t)
{
  Point3 p =
    {
     ray->origin.x + (ray->direction.x * t),
     ray->origin.y + (ray->direction.y * t),
     ray->origin.z + (ray->direction.z * t)
    };

  return p;
}

void getDirection(Ray* ray, Camera* camera, double u, double v)
{
  ray->direction.x = camera->lower_left_corner.x + (u * camera->horizontal.x) + (v * camera->vertical.x);
  ray->direction.y = camera->lower_left_corner.y + (u * camera->horizontal.y) + (v * camera->vertical.y);
  ray->direction.z = camera->lower_left_corner.z + (u * camera->horizontal.z) + (v * camera->vertical.z);
}

v3 random_in_unit_disk()
{
  v3 p, rnd;
  do {
    rnd.x = drand48() - 1.0;
    rnd.y = drand48() - 1.0;
    rnd.z = 0;
    p.x = rnd.x * 2;
    p.y = rnd.y * 2;
    p.z = rnd.z * 2;
  } while (v3Dot(&p, &p) >= 1.0);
  return rnd;
}

void getRayfromCamera(Ray* ray, Camera* camera, double s, double t)
{
  v3 rnd = random_in_unit_disk();
  v3 rd = {
           rnd.x * camera->lens_radius,
           rnd.y * camera->lens_radius,
           rnd.z * camera->lens_radius
  };
  v3 offset = {
               camera->u.x * rd.x + camera->v.x * rd.y,
               camera->u.y * rd.x + camera->v.y * rd.y,
               camera->u.z * rd.x + camera->v.z * rd.y
  };

  ray->origin.x = camera->origin.x + offset.x;
  ray->origin.y = camera->origin.y + offset.y;
  ray->origin.z = camera->origin.z + offset.z;

  v3 direction = {
                  camera->lower_left_corner.x + s * camera->horizontal.x + t * camera->vertical.x- camera->origin.x - offset.x,
                  camera->lower_left_corner.y + s * camera->horizontal.y + t * camera->vertical.y- camera->origin.y - offset.y,
                  camera->lower_left_corner.z + s * camera->horizontal.z + t * camera->vertical.z- camera->origin.z - offset.z
  };
  ray->direction = direction;
}


Ray* newRay(Point3 o, v3 direction)
{
  Ray* ray = NEWTYPE(Ray);
  if (ray != NULL)
    {
      ray->origin = o;
      ray->direction = direction;
      return ray;
    }
  return NULL;
};
