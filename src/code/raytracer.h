//
//
// Ray Tracing for the Masses in C and SDL
//
//
// raytracer.h:
// Data structures definitions


typedef enum _objectType {
                          ASphere,
                          APlane
} ObjectType;

// Define a three-dimensional vector
typedef struct {
  double x;
  double y;
  double z;
} Vector;

// Define a RGB Color structure
typedef struct {
  double r;
  double g;
  double b;
} Color;

// Define a ray
typedef struct {
  Vector origin;
  Vector direction;
} Ray;

// Define a camera
typedef struct {
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
