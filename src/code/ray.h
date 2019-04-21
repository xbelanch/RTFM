// Ray.h

#ifndef RAYH
#define RAYH


Vector point_at_parameter(struct _ray* ray, double t)
{
  Vector v =
  {
    ray->origin.x + (ray->direction.x * t),
    ray->origin.y + (ray->direction.y * t),
    ray->origin.z + (ray->direction.z * t)
  };

  return v;
}



Ray* newRay(Vector origin, Vector direction)
{
  Ray* ray = malloc(sizeof(Ray));
  if (ray != NULL)
    {
      ray->origin = origin;
      ray->direction = direction;
      ray->point_at_parameter = point_at_parameter;

      return ray;
    }

  return NULL;
};


#endif
