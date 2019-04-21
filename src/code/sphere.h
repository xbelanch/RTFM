// sphere

#ifndef SPHEREH
#define SPHEREH

bool hitSphere(Hitable* hitable, Ray* ray, float t_min, float t_max, hit_record* rec)
{

  double a, b, c;
  double discriminant;

  Vector oc = {
               ray->origin.x - hitable->Object.sphere.center.x,
               ray->origin.y - hitable->Object.sphere.center.y,
               ray->origin.z - hitable->Object.sphere.center.z
  };

  Vdot(ray->direction, ray->direction, a); // set a
  Vdot(oc,  ray->direction, b); // set b
  Vdot(oc, oc, c); // set c
  c -=  (hitable->Object.sphere.radius * hitable->Object.sphere.radius);
  discriminant = b*b - a*c;

  if (discriminant > 0)
    {
      double temp = (-b - sqrt(b*b-a*c))/a;
      if (temp < t_max && temp > t_min)
        {
          rec->t = temp;
          rec->p = ray->point_at_parameter(ray, rec->t);
          rec->normal = (Vector) {
                                  (rec->p.x - hitable->Object.sphere.center.x) /  hitable->Object.sphere.radius,
                                  (rec->p.y - hitable->Object.sphere.center.y) / hitable->Object.sphere.radius,
                                  (rec->p.z - hitable->Object.sphere.center.z) / hitable->Object.sphere.radius };
          return true;
        }
      temp = (-b + sqrt(b*b-a*c))/a;
      if (temp < t_max && temp > t_min)
        {
          rec->t = temp;
          rec->p = ray->point_at_parameter(ray, rec->t);
          rec->normal = (Vector) {
                                  (rec->p.x - hitable->Object.sphere.center.x) / hitable->Object.sphere.radius,
                                  (rec->p.y - hitable->Object.sphere.center.y) / hitable->Object.sphere.radius,
                                  (rec->p.z - hitable->Object.sphere.center.z) / hitable->Object.sphere.radius
          };
          return true;
        }

    }

  return false;

}

Hitable* newSphere(Vector center, float radius)
{
  Hitable* hitable = NULL;

  hitable = malloc(sizeof(Hitable));

  if (hitable != NULL){
    memset(hitable, '\0', sizeof(Hitable));
    hitable->next = NULL;
    hitable->type = Sphere;
    hitable->hit = hitSphere;
    hitable->Object.sphere.center = center;
    hitable->Object.sphere.radius = radius;
  }

  return hitable;
}

#endif
