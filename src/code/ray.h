// Ray.h

#ifndef RAYH
#define RAYH


Vector point_at_parameter(struct _ray* ray, double t)
{
  return vectorAdd(ray->origin, vectorScale(ray->direction, t));
}

Ray* newRay(Vector o, Vector direction)
{
  Ray* ray = malloc(sizeof(Ray));
  if (ray != NULL)
    {
      ray->origin = o;
      ray->direction = direction;
      ray->point_at_parameter = point_at_parameter;

      return ray;
    }

  return NULL;
};


#endif
