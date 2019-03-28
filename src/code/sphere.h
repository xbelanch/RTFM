// sphere

#ifndef HSPHERE
#define HSPHERE

#include "vec3.h"
#include "ray.h"

typedef struct { vec3 center; float radius; } Sphere;

float hit_sphere(Sphere sphere, const ray r)
{
  vec3 oc = {
          r.origin.x - sphere.center.x,
          r.origin.y - sphere.center.y,
          r.origin.z - sphere.center.z
  };

  float a = dot_vec3(r.direction, r.direction);
  float b = 2.0 * dot_vec3(oc, r.direction);
  float c = dot_vec3(oc, oc) - sphere.radius * sphere.radius;
  float discriminant = b*b - 4*a*c;
  return (discriminant < 0) ? -1.0 :
    ( -b - sqrt(discriminant) ) / (2.0 * a)
    ;
}


#endif
