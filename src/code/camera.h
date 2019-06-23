#ifndef CAMERAH
#define CAMERAH 1

#include "vector.h"
#include "ray.h"

typedef struct _camera
{
  Point3 origin;
  Point3 lower_left_corner;
  Point3 horizontal;
  Point3 vertical;
  double lens_radius;
  v3 u, v, w;
} Camera;

Camera* newCamera(v3 lookFrom, v3 lookAt, v3 vUp, double vfov, double aspect, double aperture, double focus_dist);


#endif
