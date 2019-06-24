#ifndef RAYTRACERH
#define RAYTRACERH 1
#define VERSION "0.0.1"
#define TITLE "Ray Tracing in One Year in C"
#define YEAR "2019"

#include "color.h"
#include "hitable.h"


typedef struct _buffer
{
  int red; int green; int blue;
} Buffer;

Buffer* newBuffer(int width, int height);
void createPPM(FILE* file, Buffer* buffer, int width, int height);
Color getColor(Ray* ray, Hitable* scene, int depth);
Hitable* random_scene();

#endif
