#ifndef OBJECTH
#define OBJECTH 1

#include "hitable.h"

typedef struct { Point3 center;  double radius;} Sphere;
typedef struct { v3 normal; double distance; } Plane;
typedef struct { Point3 a, b, c; } Triangle;


typedef struct _anObject
{
  ObjectType type;
  struct _anObject* next;
  struct _material* material;
  /* TODO: Material* material; */
  void (*log) (struct _anObject* self);
  bool (*hit) (struct _anObject* self, Ray* ray, double t_min, double t_max, struct _hit_record* rec);

  // Object specific related
  union
  {
    Sphere sphere;
    Plane plane;
    Triangle triangle;
  } is;

} Object;


Object* newPlane();
Object* newSphere();
Object* newTriangle();


#endif
