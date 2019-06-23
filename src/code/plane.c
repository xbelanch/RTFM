#include <stdlib.h>
#include <stdio.h>
#include "common.h"
#include "vector.h"
#include "ray.h"
#include "trace.h"
#include "object.h"
#include "hitable.h"
#include "material.h"


void logPlane(Object* self)
{
  printf("Plane:: normal={%f, %f, %f}; distance=%f\n",
         self->is.plane.normal.x,
         self->is.plane.normal.y,
         self->is.plane.normal.z,
         self->is.plane.distance);
}


bool hitPlane(Object* self, Ray* ray, double t_min, double t_max, hit_record* rec)
{

  double Vd, Vo, T;

  // Calculate the dot product of the plane's normal and the
  // ray's direction

  Vd = v3Dot(&self->is.plane.normal, &ray->direction);

  if (Vd <= 0.000001) // ray is parallel to plane. No intersection. No hit
    return false;

  Vo = v3Dot(&self->is.plane.normal, &ray->origin);
  Vo += self->is.plane.distance;
  Vo *= -1.0;

  T = Vo/Vd;
  if (T < 0.0)
    return false; // intersection behind ray origin

  if (T < t_max && T > t_min) // there's a intersection... need to recorded in hit_record!
    {
      rec->t = T;
      rec->p = point_at_parameter(ray, rec->t);
      rec->normal.x = -self->is.plane.normal.x;
      rec->normal.y = -self->is.plane.normal.y;
      rec->normal.z = -self->is.plane.normal.z;
      return true;
    }
  return false;
}


Object* newPlane(v3* normal, double distance, Material* material)
{
  Object* object = NEWTYPE(Object);
  if (object != NULL)
    {
      object->type = aPlane;
      object->log = logPlane;
      object->hit = hitPlane;
      object->material = material;
      v3Normalize(normal);
      object->is.plane.normal = *normal;
      object->is.plane.distance = distance;
      return object;
    } else {
    return NULL;
  }
}
