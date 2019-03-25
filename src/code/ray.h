// ray.h

#ifndef RAYH
#define RAYH
#include "vec3.h"

typedef struct { vec3 origin; vec3 direction; } ray;


ray newRay(vec3 origin, vec3 direction)
{
  ray r = {
           origin,
           direction
  };

  return r;
}

inline vec3 point_at_parameter(float t, ray ray)
{
  vec3 v =
  {
    ray.origin.x + (ray.direction.x * t),
    ray.origin.y + (ray.direction.y * t),
    ray.origin.z + (ray.direction.z * t)
  };

  return v;
}

#endif
