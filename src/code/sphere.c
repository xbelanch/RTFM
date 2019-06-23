#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "common.h"
#include "ray.h"
#include "trace.h"
#include "object.h"
#include "hitable.h"
#include "material.h"

void logSphere(Object* self)
{
  printf("Sphere:: center={%f, %f, %f}; radius=%f\n",
         self->is.sphere.center.x,
         self->is.sphere.center.y,
         self->is.sphere.center.z,
         self->is.sphere.radius
         );
}


bool hitSphere(Object* self, Ray* ray, double t_min, double t_max, hit_record* rec)
{
  v3 oc, vv;
  v3Sub(&ray->origin, &self->is.sphere.center, &oc);
  double a = v3Dot(&ray->direction, &ray->direction);
  double b = 2.0 * v3Dot(&oc, &ray->direction);
  double c = v3Dot(&oc, &oc) - self->is.sphere.radius * self->is.sphere.radius;
  double discriminant = b * b - 4 * a * c;
  double t0;
  if (discriminant >= 0.0001)
    {
      t0 = (-b - sqrt(discriminant)) / (2.0 * a);
      if (t0 < t_max && t0 > t_min)
        {
          rec->t = t0;
          rec->p = point_at_parameter(ray, rec->t);
          rec->normal.x = (rec->p.x - self->is.sphere.center.x) / self->is.sphere.radius;
          rec->normal.y = (rec->p.y - self->is.sphere.center.y) / self->is.sphere.radius;
          rec->normal.z = (rec->p.z - self->is.sphere.center.z) / self->is.sphere.radius;
          return true;
        }
      t0 = (-b + sqrt(discriminant)) / (2.0 * a);
      if (t0 < t_max && t0 > t_min)
        {
          rec->t = t0;
          rec->p = point_at_parameter(ray, rec->t);
          rec->normal.x = (rec->p.x - self->is.sphere.center.x) / self->is.sphere.radius;
          rec->normal.y = (rec->p.y - self->is.sphere.center.y) / self->is.sphere.radius;
          rec->normal.z = (rec->p.z - self->is.sphere.center.z) / self->is.sphere.radius;

          return true;
        }
    }
  return false;
}

Object* newSphere(v3* center, double radius, Material* material)
{
  Object* object = NULL;

  object = NEWTYPE(Object);

  if (object != NULL){
    object->type = aSphere;
    object->material = material;
    object->next = NULL;
    object->hit = hitSphere;
    object->log = logSphere;
    object->is.sphere.center = *center;
    object->is.sphere.radius = radius;
    return object;
  } else {
    return NULL;
  }
}
