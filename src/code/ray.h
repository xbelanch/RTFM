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

Ray* newRay(Vector o, Vector direction)
{
  Ray* ray = malloc(sizeof(Ray));
  if (ray != NULL)
    {
      ray->origin = o;
      ray->direction = direction;

      return ray;
    }

  return NULL;
};





#endif RAYH
