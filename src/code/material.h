#ifndef MATERIALH
#define MATERIALH 1

#include "color.h"

typedef struct _material
{
  Color albedo;
  double fuzz;
  double ref_idx;
  bool (*scatter) (struct _material* self, Ray* ray_in, struct _hit_record rec, Color* attenuation,  Ray* scattered);
} Material;

Material* Lambertian(Color albedo);
Material* Metal(Color albedo, double fuzz);
Material* Dielectric(double);

#endif
