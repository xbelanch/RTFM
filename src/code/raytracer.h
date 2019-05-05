//
//
// Ray Tracing for the Masses in C and SDL
//
//
// raytracer.h:
// Data structures definitions

#ifndef RAYTRACERH
#define RAYTRACERH

#define W 1024
#define H 768
#define true 1
#define false 0
#define samples 100



typedef unsigned int bool;

typedef enum _objectType {
                          Sphere,
                          Plane
} ObjectType;

// this is a shit, but maybe now works
double drand48();

#endif
