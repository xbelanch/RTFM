#include <stdlib.h>
#include <math.h>
#include "common.h"
#include "color.h"


Color* colorSQRT(Color* c)
{
  c->r = sqrt(c->r);
  c->g = sqrt(c->g);
  c->b = sqrt(c->b);
  return c;
}

Color* colorNew(double r, double g, double b)
{
  Color* col = NEWTYPE(Color);
  if (col != NULL) { col->r = r; col->g = g; col->b = b; };
  return col;
}

Color* colorDuplicate(Color* a)
{
  Color* col = NEWTYPE(Color);
  if (col != NULL) { col->r = a->r; col->g = a->g; col->b = a->b; };
  return col;
}

Color* colorNegate(Color* a)
{
  a->r = -(a->r);  a->g = -(a->g);  a->b = -(a->b);
  return a;
}

Color* colorAdd(Color* a, Color* b, Color* c)
{
  c->r = a->r + b->r; c->g = a->g + b->g; c->b = a->b + b->b;
  return c;
}

Color* colorSub(Color* a, Color* b, Color* c)
{
  c->r = a->r - b->r; c->g = a->g - b->g; c->b = a->b - b->b;
  return c;
}

Color* colorMul(Color* a, Color* b, Color* c)
{
  c->r = a->r * b->r; c->g = a->g * b->g; c->b = a->b * b->b;
  return c;
}

Color* colorDiv(Color* c, double f)
{
  c->r /= f; c->g /= f; c->b /= f;
  return c;
}

Color* colorScalar(Color* a, double scalar)
{
  a->r *= scalar; a->g *= scalar; a->b *= scalar;
  return a;
}
