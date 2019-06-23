#include <stdlib.h>
#include <stdio.h>
#include "common.h"
#include "vector.h"
#include "ray.h"
#include "object.h"
#include "hitable.h"


bool hit(Hitable* self, Ray* ray, double t_min, double t_max, hit_record* rec)
{
  Object* ptr = self->list_of_hitable_objects;
  Object* obj = ptr;
  hit_record temp_rec;
  bool hit_anything = false;
  double closest_so_far = t_max;

  while (obj)
    {
      if(obj->hit(
                  obj,
                  ray,
                  t_min,
                  closest_so_far,
                  &temp_rec))
        {
          hit_anything = true;
          closest_so_far = temp_rec.t;
          rec->t = temp_rec.t;
          rec->p = temp_rec.p;
          rec->normal = temp_rec.normal;
          rec->material = obj->material;
          rec->object = obj->type;
        }
      obj = obj->next;
    }
  self->list_of_hitable_objects = ptr;
  return hit_anything;

}


void addObjectToList(Hitable* self, Object* object)
{
  if(self->list_of_hitable_objects == NULL) // ooh, empty list
    {
      self->list_of_hitable_objects = object;
      object->next = NULL;
    } else {
    object->next = self->list_of_hitable_objects;
    self->list_of_hitable_objects = object;
  }
  self->list_size++;
}

void printListOfObjects(Hitable* self)
{
  Object* objectLast = self->list_of_hitable_objects;
  while (self->list_of_hitable_objects)
    {
      self->list_of_hitable_objects->log(self->list_of_hitable_objects);
      self->list_of_hitable_objects = self->list_of_hitable_objects->next;
    }
  self->list_of_hitable_objects = objectLast;
}

Hitable* newHitable()
{
  Hitable* hitable = NEWTYPE(Hitable);

  if (hitable != NULL)
    {
      hitable->list_size = 0;
      hitable->addObject = addObjectToList;
      hitable->log = printListOfObjects;
      hitable->list_of_hitable_objects = NULL;
      hitable->hit = hit;
      return hitable;
    } else {
    return NULL;
  }
}
