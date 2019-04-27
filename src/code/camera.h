#ifndef CAMERAH
#define CAMERAH

// from the book:
// ray get_ray (float u, float v) { return ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);}
Ray* getRay(Camera* camera, double u, double v)
{
  Vector a = vectorAdd(camera->lower_left_corner, vectorScale(camera->horizontal, u));
  Vector b = vectorAdd(a, vectorScale(camera->vertical, v));
  Vector c = vectorSubtract(b, camera->origin);
  return newRay(camera->origin, c);

}

// Camera variables is hardcoded
Camera* newCamera()
{
  Camera* cam = malloc(sizeof(Camera));
  if (cam != NULL)
    {
      cam->lower_left_corner = newVector(-2.0, -1.0, -1.0);
      cam->horizontal = newVector(4.0, .0, .0);
      cam->vertical = newVector(.0, 2.0, .0);
      cam->origin = newVector(.0, .0, .0);

      cam->get_ray = getRay;
      return cam;
    }

  return NULL;

}
#endif
