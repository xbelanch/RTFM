//
//
// Ray Tracing for the Masses in C and SDL
//
//
// vector.h:
// Data structures definitions

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define Vlog(a) { printf("{%f, %f, %f}\n", a.x, a.y, a.z); }

#define Vadd(a, b, c) {                         \
    c.x = a.x + b.x;                            \
    c.y = a.y + b.y;                            \
    c.z = a.z + b.z;                            \
  }

#define Vsubtract(a, b, c) {                    \
    c.x = a.x - b.x;                            \
    c.y = a.y - b.y;                            \
    c.z = a.z - b.z;                            \
  }


#define Vunitary(a, u) {                                        \
    double k = 1.0 / sqrt(a.x * a.x + a.y * a.y + a.z * a.z);   \
    u.x = a.x * k;                                              \
    u.y = a.y * k;                                              \
    u.z = a.z * k;                                              \
  }

// Vector negate: b = -a
#define Vnegate(a, b) {                         \
    b.x = -a.x;                                 \
    b.y = -a.y;                                 \
    b.x = -a.z;                                 \
  }

// Vector scale: a = k * a
#define Vscale(a, k) {                          \
    a.x *= k;                                   \
    a.y *= k;                                   \
    a.z *= k;                                   \
  }

// Vector length of a
inline float Vlength(Vector a) {
  return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

// Vector squared length of a
inline float Vsquaredlength(Vector a) {
  return a.x * a.x + a.y * a.y + a.z * a.z;
}

// Vector normalize u = |a|
#define Vnormalize(a, u) {                      \
    double length = Vlength(a);                 \
    u.x = a.x / length;                         \
    u.y = a.y / length;                         \
    u.z = a.z / length;                         \
  }

// Vector dot product: double d = a dot b
#define Vdot(a, b, d) {                         \
    d = a.x * b.x + a.y * b.y + a.z * b.z;      \
  }

// Vector cross product: c = a cross b
#define Vcross(a, b, c) {                       \
    c.x = a.y * b.z - a.z * b.y;                \
    c.y = a.z * b.x - a.x * b.z;                \
    c.z = a.x * b.y - a.y * b.x;                \
  }
