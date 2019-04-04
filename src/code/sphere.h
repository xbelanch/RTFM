// sphere

#ifndef HSPHERE
#define HSPHERE


float hit_sphere(Sphere* sphere, Ray* ray)
{
  double a, b, c;
  double discriminant;

  Vector oc = {
             ray->origin.x - sphere->center.x,
             ray->origin.y - sphere->center.y,
             ray->origin.z - sphere->center.z
  };

  Vdot(ray->direction, ray->direction, a);
  Vdot(oc,  ray->direction, b);
  Vdot(oc, oc, c);

  b *= 2.0;
  c -= sphere->radius * sphere->radius;

  discriminant = b*b - 4*a*c;
  return (discriminant < 0) ? -1.0 :
    ( -b - sqrt(discriminant) ) / (2.0 * a)
    ;
}


#endif
