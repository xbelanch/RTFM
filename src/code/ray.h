// Ray.h

#ifndef RAYH
#define RAYH

Ray newRay(Vector origin, Vector direction)
{
  Ray r = {
           origin,
           direction
  };

  return r;
}

inline Vector point_at_parameter(float t, Ray* ray)
{
  Vector v =
  {
    ray->origin.x + (ray->direction.x * t),
    ray->origin.y + (ray->direction.y * t),
    ray->origin.z + (ray->direction.z * t)
  };

  return v;
}

#endif
