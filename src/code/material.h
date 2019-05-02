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

#endif
