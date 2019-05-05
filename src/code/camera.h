#ifndef CAMERAH
#define CAMERAH


Vector random_in_unit_disk()
{
  Vector p;
  Vector rnd;
  do {
    rnd.x = drand48() - 1.0;
    rnd.y = drand48() - 1.0;
    rnd.z = 0;
    p = vectorScale(rnd, 2);
  } while (vectorDot(p, p) >= 1.0);
  return rnd;
}

// from the book:
// ray get_ray (float u, float v) { return ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);}
Ray* getRay(Camera* camera, double s, double t)
{
  Vector rd = vectorScale(random_in_unit_disk(), camera->lens_radius);
  Vector offset = vectorAdd(vectorScale(camera->u, rd.x), vectorScale(camera->v, rd.y));

  Vector a = vectorAdd(camera->lower_left_corner, vectorScale(camera->horizontal, s));
  Vector b = vectorAdd(a, vectorScale(camera->vertical, t));
  Vector c = vectorSubtract(b, camera->origin);
  Vector d = vectorSubtract(c, offset);
  return newRay(vectorAdd(camera->origin, offset), d);

}

// Camera variables is hardcoded
Camera* newCamera(Vector lookFrom, Vector lookAt, Vector Up, double fov, double aspect, double aperture, double focus_dist)
{
  Camera* cam = malloc(sizeof(Camera));
  if (cam != NULL)
    {

      cam->lens_radius = aperture / 2;

      double theta = fov*M_PI/180;
      double half_height = tan(theta/2);
      double half_width = aspect * half_height;
      cam->origin = lookFrom;
      cam->w = vectorUnitary(vectorSubtract(lookFrom, lookAt));
      cam->u = vectorUnitary(vectorCross(Up, cam->w));
      cam->v = vectorCross(cam->w, cam->u);

      Vector _half_width_u = vectorScale(cam->u, half_width * focus_dist);
      Vector _half_height_v = vectorScale(cam->v, half_height * focus_dist);

      Vector a = vectorSubtract(cam->origin, _half_width_u);
      Vector b = vectorSubtract(a, _half_height_v);
      cam->lower_left_corner = vectorSubtract(b, vectorScale(cam->w, focus_dist));

      cam->horizontal = vectorScale(cam->u, focus_dist * half_width * 2);
      cam->vertical = vectorScale(cam->v, focus_dist * half_height * 2);


      cam->get_ray = getRay;
      return cam;
    }

  return NULL;

}
#endif
