#ifndef RAYH
#define RAYH 1

#include "vector.h"
#include "camera.h"

typedef struct _ray
{
  Point3 origin;
  v3 direction;
  /* Point3 (*point_at_parameter)(struct _ray*, double); */
  /* void (*getDirection)(struct _ray*, struct _camera*, double, double); */
} Ray;

Ray* newRay(Point3, v3);
Point3 point_at_parameter(Ray* ray, double t);
void getDirection(Ray* ray, Camera* camera, double u, double v);
void getRayfromCamera(Ray* ray, Camera* camera, double s, double t);
#endif
