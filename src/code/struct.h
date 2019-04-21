#ifndef STRUCTH
#define STRUCTH

// Define a three-dimensional vector
typedef struct
{
  double x;
  double y;
  double z;
} Vector;

// Define a RGB Color structure
typedef struct
{
  double r;
  double g;
  double b;
} Color;

// Define a ray
typedef struct _ray
{
  Vector origin;
  Vector direction;
  Vector (*point_at_parameter) (struct _ray* ray, double t);
} Ray;

// Objects
typedef struct
{
  Vector center;
  float radius;
} aSphere;

// Define a camera
typedef struct
{
  Vector lower_left_corner;
  Vector horizontal;
  Vector vertical;
  Vector origin;
} Camera;

// Define the Screen environment
typedef struct {
  unsigned int width;
  unsigned int height;
} Screen;

#endif
