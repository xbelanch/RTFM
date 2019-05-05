#ifndef MATERIALH
#define MATERIALH


Vector random_in_unit_sphere()
{
  Vector p;
  do {

    p = vectorScale(
                    vectorSubtract(
                                   newVector(drand48(), drand48(), drand48()),
                                   newVector(1.0, 1.0, 1.0)
                                   ),
                    2.0);
  } while (vectorSquaredLength(p) >= 1.0);
  return p;
}

// LAMBERTIAN

bool scatter_lambertian (Ray* ray_in, Ray* scattered, Material* self, hit_record rec, Color* attenuation)
{

  Vector v = vectorAdd(rec.p, rec.normal);
  Vector target = vectorAdd(v, random_in_unit_sphere() );
   scattered->origin = rec.p;
   scattered->direction = vectorSubtract(target, rec.p);

  attenuation->r = self->albedo.r;
  attenuation->g = self->albedo.g;
  attenuation->b = self->albedo.b;
  return true;

}

Material* Lambertian(Color albedo)
{
  Material* mat;
  mat = malloc(sizeof(Material));

  if (mat != NULL)
    {
      mat->albedo = albedo;
      mat->scatter = scatter_lambertian;
      return mat;
    }

  return NULL;
}

// METAL

Vector reflect(Vector v, Vector n)
{
  double a = vectorDot(v, n) * 2;
  Vector b = vectorScale(n, a);
  Vector d = vectorSubtract(v, b);
  return d;
}

bool scatter_metal (Ray* ray_in, Ray* scattered, Material* self, hit_record rec, Color* attenuation)
{
  Vector reflected = reflect(vectorUnitary(ray_in->direction), rec.normal);
  scattered->origin = rec.p;
  scattered->direction = vectorAdd(reflected, vectorScale(random_in_unit_sphere(), self->fuzz));

  attenuation->r = self->albedo.r;
  attenuation->g = self->albedo.g;
  attenuation->b = self->albedo.b;

  if (vectorDot(scattered->direction, rec.normal ) > 0)
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
      mat->fuzz = fuzz;
      mat->scatter = scatter_metal;
      return mat;
    }
  return NULL;
}

// DIALECTRICS

bool refract(Vector v, Vector n, double ni_over_nt, Vector* refracted)
{
  Vector uv = vectorUnitary(v);
  double dt = vectorDot(uv, n);
  double discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);
  if (discriminant > 0)
    {
      Vector n_dt = vectorScale(n, dt);
      Vector uv_n_dt = vectorSubtract(uv, n_dt);
      Vector ni_over_nt_uv_ndt = vectorScale(uv_n_dt, ni_over_nt);
      Vector n_disc = vectorScale(n, sqrt(discriminant));
      Vector result = vectorSubtract(ni_over_nt_uv_ndt, n_disc);
      refracted->x = result.x;
      refracted->y = result.y;
      refracted->z = result.z;
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

bool scatter_dialectric (Ray* ray_in, Ray* scattered, Material* self, hit_record rec, Color* attenuation)
{
  Vector outward_normal;
  Vector reflected = reflect(ray_in->direction, rec.normal);
  double ni_over_nt;
  *attenuation = (Color){1.0, 1.0, 1.0};
  Vector refracted;
  double reflect_prob;
  double cosine;
  double _first_check = vectorDot(ray_in->direction, rec.normal);


  if (_first_check > 0)
    {
      outward_normal = vectorNegate(rec.normal);
      ni_over_nt = self->ref_idx;
      cosine = self->ref_idx * vectorDot(ray_in->direction, rec.normal) / vectorLength(ray_in->direction);
    }
  else
    {
      outward_normal = rec.normal;
      ni_over_nt = 1.0 / self->ref_idx;
      cosine = -(vectorDot(ray_in->direction, rec.normal) / vectorLength(ray_in->direction));
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
      mat->albedo = (Color) {.0, .0, .0}; // @alert: need to initialize, otherwise the result is impredictible
      mat->ref_idx = ri;
      mat->scatter = scatter_dialectric;
      return mat;
    }
  return NULL;
}


#endif
