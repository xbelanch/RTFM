// sphere

#ifndef SPHEREH
#define SPHEREH

void printSphere(Object* self)
{
  printf("Sphere at [%f, %f, %f] with radius: %f\n",
         self->is.sphere.center.x,
         self->is.sphere.center.y,
         self->is.sphere.center.z,
         self->is.sphere.radius
         );
}

bool hitSphere(Object* self, Ray* ray, float t_min, float t_max, hit_record* rec)
{

  double a, b, c;
  double discriminant;

  Vector oc = {
               ray->origin.x - self->is.sphere.center.x,
               ray->origin.y - self->is.sphere.center.y,
               ray->origin.z - self->is.sphere.center.z
  };

  Vdot(ray->direction, ray->direction, a); // set a
  Vdot(oc,  ray->direction, b); // set b
  Vdot(oc, oc, c); // set c
  c -=  (self->is.sphere.radius * self->is.sphere.radius);
  discriminant = b*b - a*c;

  if (discriminant > 0)
    {
      double temp = (-b - sqrt(b*b-a*c))/a;
      if (temp < t_max && temp > t_min)
        {
          rec->t = temp;
          rec->p = ray->point_at_parameter(ray, rec->t);
          rec->normal = (Vector) {
                                  (rec->p.x - self->is.sphere.center.x) / self->is.sphere.radius,
                                  (rec->p.y - self->is.sphere.center.y) / self->is.sphere.radius,
                                  (rec->p.z - self->is.sphere.center.z) / self->is.sphere.radius };
          return true;
        }
      temp = (-b + sqrt(b*b-a*c))/a;
      if (temp < t_max && temp > t_min)
        {
          rec->t = temp;
          rec->p = ray->point_at_parameter(ray, rec->t);
          rec->normal = (Vector) {
                                  (rec->p.x - self->is.sphere.center.x) / self->is.sphere.radius,
                                  (rec->p.y - self->is.sphere.center.y) / self->is.sphere.radius,
                                  (rec->p.z - self->is.sphere.center.z) / self->is.sphere.radius
          };
          return true;
        }

    }

  return false;

}


Object* newSphere(Vector center, float radius)
{
  Object* object = NULL;

  object = malloc(sizeof(Object));

  if (object != NULL){
    memset(object, '\0', sizeof(Object));
    object->next = NULL;
    object->type = Sphere;
    object->hit = hitSphere;
    object->print = printSphere;
    object->is.sphere.center = center;
    object->is.sphere.radius = radius;
    return object;

  } else {
    return NULL;
  }


}

#endif
