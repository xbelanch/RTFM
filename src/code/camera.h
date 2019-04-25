#ifndef CAMERAH
#define CAMERAH

Camera* newCamera(Vector _lower_left_corner, Vector _horizontal, Vector _vertical, Vector _origin )
{
  Camera* cam = malloc(sizeof(Camera));
  if (cam != NULL)
    {
      cam->lower_left_corner = _lower_left_corner;
      cam->horizontal = _horizontal;
      cam->vertical = _vertical;
      cam->origin = _origin;
      return cam;

    }

  return NULL;

}

#endif
