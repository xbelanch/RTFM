// sphere

#ifndef HSPHERE
#define HSPHERE


typedef struct _sphere {
  Vector center;
  float radius;
  struct _sphere* next;
  float (*hit)(struct _sphere*, Ray*); // pointer to a function
} Sphere;


float hit_sphere(struct _sphere* sphere, Ray* ray)
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

Sphere* sphere_new(double x, double y, double z, float radius)
{
  Sphere* sphere = NULL;

  sphere = malloc(sizeof(Sphere));

  if (sphere != NULL){
    memset(sphere, '\0', sizeof(Sphere));
    sphere->center.x = x;
    sphere->center.y = y;
    sphere->center.z = z;
    sphere->radius = radius;
    sphere->hit = hit_sphere;

  }

  return sphere;
}

#endif
