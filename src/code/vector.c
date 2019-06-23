#include <stdlib.h>
#include <math.h>
#include "common.h"
#include "vector.h"


double v3SquaredLength(v3* v)
{
  return ((v->x * v->x) + (v->y * v->y) + (v->z * v->z));
}

double v3Length(v3* v)
{
  return sqrt(v3SquaredLength(v));
}

double v3Dot(v3* a, v3* b)
{
  return ((a->x * b->x) + (a->y * b->y) + (a->z * b->z));
}

double v3DistanceBetween2Points(v3* a, v3* b)
{
  double dx = a->x - b->x;
  double dy = a->y - b->y;
  double dz = a->z - b->z;
  return sqrt((dx * dx) + (dy * dy) + (dz * dz));
}

v3* v3Negate(v3* v)
{
  v->x = -v->x; v->y = -v->y; v->z = -v->z;
  return v;
}

v3* v3Normalize(v3* v)
{
  double len = v3Length(v);
  if (len != 0.0) { v->x /= len; v->y /= len; v->z /= len; }
  return v;
}

v3* v3Scale(v3* v, double newlen)
{
  double len = v3Length(v);
  if (len != 0.0) {v->x *= newlen/len; v->y *= newlen/len; v->z *= newlen/len; }
  return v;
}

// c = a + b
v3* v3Add(v3* a, v3* b, v3* c)
{
  c->x = a->x + b->x; c->y = a->y + b->y; c->z = a->z + b->z;
  return c;
}

// c = a - b
v3* v3Sub(v3* a, v3* b, v3* c)
{
  c->x = a->x - b->x; c->y = a->y - b->y; c->z = a->z - b->z;
  return c;
}

// c = a * b
v3* v3Mul(v3* a, v3* b, v3* c)
{
  c->x = a->x * b->x; c->y = a->y * b->y; c->z = a->z * b->z;
  return c;
}

v3* v3Cross(v3* a, v3* b, v3* c)
{
  c->x = ((a->y * b->z) - (a->z * b->y));
  c->y = ((a->z * b->x) - (a->x * b->z));
  c->z = ((a->x * b->y) - (a->y * b->x));
  return c;
}

v3* v3New(double x, double y, double z){
  v3* v = NEWTYPE(v3);
  v->x = x; v->y = y; v->z = z;
  return v;
}


v3* v3Duplicate(v3* a)
{
  v3* v = NEWTYPE(v3);
  v->x = a->x; v->y = a->y; v->z = v->z;
  return v;
}
