#include <stdlib.h>
#include <math.h>
#include "common.h"
#include "vector.h"
#include "ray.h"
#include "camera.h"



Camera* newCamera(v3 lookFrom, v3 lookAt, v3 vUp, double vfov, double aspect, double aperture, double focus_dist)
{
  Camera* camera = NEWTYPE(Camera);
  if (camera != NULL)
    {
      camera->lens_radius = aperture / 2;

      double theta = vfov * M_PI / 180;
      double half_height = tan(theta/2);
      double half_width = aspect * half_height;
      camera->origin = lookFrom;
      v3 w = { lookFrom.x - lookAt.x, lookFrom.y - lookAt.y, lookFrom.z - lookAt.z }; v3Normalize(&w);
      v3 u; v3Cross(&vUp, &w, &u); v3Normalize(&u);
      v3 v; v3Cross(&w, &u, &v);

      camera->w = w;
      camera->u = u;
      camera->v = v;

      camera->lower_left_corner.x = camera->origin.x - half_width * focus_dist * u.x - half_height * focus_dist * v.x - focus_dist * w.x;
      camera->lower_left_corner.y = camera->origin.y - half_width * focus_dist * u.y - half_height * focus_dist * v.y - focus_dist * w.y;
      camera->lower_left_corner.z = camera->origin.z - half_width * focus_dist * u.z - half_height * focus_dist * v.z - focus_dist * w.z;

      camera->horizontal.x = 2 * half_width * focus_dist * u.x;
      camera->horizontal.y = 2 * half_width * focus_dist * u.y;
      camera->horizontal.z = 2 * half_width * focus_dist * u.z;

      camera->vertical.x = 2 * half_height * focus_dist * v.x;
      camera->vertical.y = 2 * half_height * focus_dist * v.y;
      camera->vertical.z = 2 * half_height * focus_dist * v.z;

      return camera;
    } else {
    return NULL;
  }
}
