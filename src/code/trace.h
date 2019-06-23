#ifndef RAYTRACERH
#define RAYTRACERH 1
#define VERSION "0.0.1"
#define TITLE "Ray Tracing in One Year in C"
#define YEAR "2019"

#include "color.h"
#include "hitable.h"

typedef struct _canvas
{
  int width;
  int height;
} Canvas;

void createPPM(FILE* file, int r, int g, int b);
Color getColor(Ray* ray, Hitable* scene, int depth);
Hitable* random_scene();

#endif
