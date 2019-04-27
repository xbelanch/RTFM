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

Vector newVector(double x, double y, double z)
{
  Vector v3 = {x, y, z};
  return v3;
}

// macro to log output
#define Vlog(a) { printf("{%f, %f, %f}\n", a.x, a.y, a.z); }

//
// instead of newVector(a, b, c) better say location(a, b, c)
//
#define location newVector

// add two vectors c = a + b
inline Vector vectorAdd (Vector a, Vector b)
{
  Vector c;
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    c.z = a.z + b.z;
  return c;
}

// substract two vectors c = a - b
inline Vector vectorSubtract (Vector a, Vector b)
{
  Vector c;
    c.x = a.x - b.x;
    c.y = a.y - b.y;
    c.z = a.z - b.z;
  return c;
}

inline Vector vectorMultiply (Vector a, Vector b)
{
  a.x *= b.x;
  a.y *= b.y;
  a.z *= b.z;
  return a;
}

inline Vector vectorDivide (Vector a, double b)
{
  a.x /= b;
  a.y /= b;
  a.z /= b;
  return a;
}

// vector unitary
inline Vector vectorUnitary(Vector a)
{
  Vector u;
  double k = 1.0 / sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
  u.x = a.x * k;
  u.y = a.y * k;
  u.z = a.z * k;
  return u;
}

// Vector negate: b = -a
inline Vector vectorNegate(Vector a)
{
  Vector n;
    n.x = -a.x;
    n.y = -a.y;
    n.x = -a.z;
    return n;
}

// Vector scale: b = k * a
inline Vector vectorScale(Vector a, double k)
{
    a.x *= k;
    a.y *= k;
    a.z *= k;
    return a;
}

// Vector length of a
inline double vectorLength(Vector a) {
  return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

// Vector squared length of a
inline double vectorSquaredLength(Vector a) {
  return a.x * a.x + a.y * a.y + a.z * a.z;
}

// Vector normalize u = |a|
inline Vector Vnormalize(Vector a)
{
  Vector u;
  double length = Vlength(a);
  u.x = a.x / length;
  u.y = a.y / length;
  u.z = a.z / length;
  return u;
}

// Vector dot product: double d = a dot b
inline double vectorDot(Vector a, Vector b)
{
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Vector cross product: c = a cross b
inline Vector vectorCross(Vector a, Vector b)
{
  Vector c;
  c.x = a.y * b.z - a.z * b.y;
  c.y = a.z * b.x - a.x * b.z;
  c.z = a.x * b.y - a.y * b.x;
  return c;
}
