/*
  NOTE: This is a simply file to save all the procedural texture functions.
  At the moment blue sky is functional as a background
*/

#include "color.h"
#include "vector.h"
#include "ray.h"

Color skydome(Ray* ray)
{
  v3Normalize(&ray->direction);
  v3 unit_direction = ray->direction;
  double t = 0.5 * (unit_direction.y + 1.0);
  Color color = {
                 1.0 - t * 1.0 + t * 0.5,
                 1.0 - t * 1.0 + t * 0.7,
                 1.0 - t * 1.0 + t * 1.0
  };
  return color;
}


int textureTest0(int x, int y) {
  int ir = x ^ y % 64;
  int ig = x ^ y % 128;
  int ib = x ^ y % 256;
  return ir << 16 | ig << 8 | ib;
}

              /* int blue = 0x3; */
              /* int tilesize = 64; */
              /* int green = (int) (((float) i / (float) W ) * 256 + tilesize); */
              /* int red = (int) (((float) j / (float) H ) * 256 + tilesize); */
              // pixels[j * W + i] = red % tilesize << 16 | green % tilesize << 8  | blue % tilesize;
              //
              // NOTE: screen -> [0, 1]



// paint texture normals
          /* v3 N= { rec.p.x, rec.p.y, rec.p.z + 1.0}; */
          /* v3Normalize(&N); */
          /* color.r = 0.5 * (N.x + 1); */
          /* color.g = 0.5 * (N.y + 1); */
          /* color.b = 0.5 * (N.z + 1); */
