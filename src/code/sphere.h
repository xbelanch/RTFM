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
  Vector oc = vectorSubtract(ray->origin, self->is.sphere.center);
  double a = vectorDot(ray->direction, ray->direction);
  double b = vectorDot(oc, ray->direction);
  double c = vectorDot(oc, oc) - (self->is.sphere.radius * self->is.sphere.radius);
  double discriminant = b*b - a*c;

  if (discriminant > 0)
    {
      double temp = (-b - sqrt(b*b-a*c))/a;
      if (temp < t_max && temp > t_min)
        {
          rec->t = temp;
          rec->p = ray->point_at_parameter(ray, rec->t);
          rec->normal = vectorDivide(vectorSubtract(rec->p, self->is.sphere.center), self->is.sphere.radius);
          return true;
        }
      temp = (-b + sqrt(b*b-a*c))/a;
      if (temp < t_max && temp > t_min)
        {
          rec->t = temp;
          rec->p = ray->point_at_parameter(ray, rec->t);
          rec->normal = vectorDivide(vectorSubtract(rec->p, self->is.sphere.center), self->is.sphere.radius);
          return true;
        };
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
