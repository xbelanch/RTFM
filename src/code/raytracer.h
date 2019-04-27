//
//
// Ray Tracing for the Masses in C and SDL
//
//
// raytracer.h:
// Data structures definitions

#ifndef RAYTRACERH
#define RAYTRACERH

#define W 800
#define H 400
#define true 1
#define false 0
#define hscale 2
#define wscale 2
#define samples 256

typedef unsigned int bool;

typedef enum _objectType {
                          Sphere,
                          Plane
} ObjectType;


#endif
