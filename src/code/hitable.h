#ifndef HITABLEH
#define HITABLEH 1

#include "common.h" // need for boolean

typedef enum  {
                 aPlane,
                 aSphere
} ObjectType;


typedef struct _hit_record
{
  double t;
  Point3 p;
  v3 normal;
  struct _material* material;
  ObjectType object;
} hit_record;

typedef struct _hitable
{
  int list_size;
  struct _anObject* list_of_hitable_objects;
  bool (*hit)(struct _hitable* self,  Ray* ray, double t_min, double t_max, hit_record* rec);
  void (*log) (struct _hitable* self);
  void (*addObject) (struct _hitable* self, struct _anObject* object);
} Hitable;

Hitable* newHitable();

#endif
