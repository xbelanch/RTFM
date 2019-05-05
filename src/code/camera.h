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
Camera* newCamera(Vector lookFrom, Vector lookAt, Vector Up, double fov, double aspect)
{
  Camera* cam = malloc(sizeof(Camera));
  if (cam != NULL)
    {
      Vector u, v, w;
      double theta = fov*M_PI/180;
      double half_height = tan(theta/2);
      double half_width = aspect * half_height;
      cam->origin = lookFrom;
      w = vectorUnitary(vectorSubtract(lookFrom, lookAt));
      u = vectorUnitary(vectorCross(Up, w));
      v = vectorCross(w, u);

      cam->lower_left_corner = newVector(-half_width, -half_height, -1.0);
      Vector _half_width_u = vectorScale(u, half_width);
      Vector _half_height_v = vectorScale(v, half_height);
      Vector a = vectorSubtract(cam->origin, _half_width_u);
      Vector b = vectorSubtract(a, _half_height_v);
      cam->lower_left_corner = vectorSubtract(b, w);

      cam->horizontal = vectorScale(_half_width_u, 2);
      cam->vertical = vectorScale(_half_height_v, 2);


      cam->get_ray = getRay;
      return cam;
    }

  return NULL;

}
#endif
