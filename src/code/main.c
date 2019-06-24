// Ray Tracing in One Year in C

#define _XOPEN_SOURCE    /* ALWAYS BEFORE the include statement */
// https://cs50.stackexchange.com/questions/6061/implicit-declaration-of-function-drand48-is-invalid-in-c99-generating-rand
// Standard headers
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#ifdef __CYGWIN__
#include <string.h>
#endif


#include "common.h"
#include "color.h"
#include "vector.h"
#include "ray.h"
#include "object.h"
#include "camera.h"
#include "texture.h"
#include "hitable.h"
#include "material.h"
#include "trace.h"

/* TODO, FIXME, ALERT

   TODO: Create a simple parser for the scene instead of hardcoding
   TODO: Rewrite trace.h to include a struct to handle with global variables like Ray, Color and ir, ig, ib
   TODO: Implement a png write?
   TODO: matrix.h
   TODO:
   FIXME: vector.h Dont like some operations like add, sub and others :-
   FIXME: material.c Seems that rand48() in random_in_unit_sphere() compile with Visual Studio is a mess
*/


int main(int argc, char** argv)
{
  srand(time(0));
  printf("%s - %s - %s\n", TITLE, VERSION, YEAR );

  if (argc > 0)
    printf("Pass arguments is not supported on this version\n");

  // Trace initialization
  int width = 800;
  int height = 200;

  // Create the ppm file */
  FILE* ppm;
  ppm = fopen("../../renders/picture.ppm", "w+");
  fprintf(ppm, "P3\n%d %d\n255\n", width, height);

  int samples = 32;
  // Scene creation
  Hitable* scene = random_scene();

  Camera* camera = newCamera(
                             (v3){13.0, 2.0, 3.0}, // look From
                             (v3){.0, .0, 0},   // look At
                             (v3){0.0, 1.0, 0.0 }, // Up vector
                             20, // fov
                             (double)(width)/(double)(height), // aspect ratio
                             1.0, // aperture
                             v3Length((v3){13.0, 2.0, 3.0})// dist_to_focus
                             );


  Ray ray;
  Color color;
  int ir, ig, ib;
  // initialize the picture buffer
  Buffer* buffer = newBuffer(width,  height);


  // paint the canvas
  printf("Render process...\n");
  for (int j = height-1; j >= 0; j--)
    {
      for (int i = 0; i < width ; i++)
        {
          // antialiasing
          color.r = color.g = color.b = 0.0;
          for (int s = 0; s < samples; s++)
            {
              double u = (double)(i + drand48()) / (double)(width);
              double v = (double)(j + drand48()) / (double)(height);

              // calculate ray direction
              getRayfromCamera(&ray, camera, u, v);

              // get the color for every ray
              Color tcol =  getColor(&ray, scene, 5);
              colorAdd(&color, &tcol, &color);
            }

          // sample color
          color.r /= samples; color.g /= samples; color.b /= samples;

          // Gamma?
          color.r = sqrt(color.r); color.g = sqrt(color.g); color.b = sqrt(color.b);

          // transform the color values to 0..255
          ir = (int)(255.99 * color.r);
          ig = (int)(255.99 * color.g);
          ib = (int)(255.99 * color.b);

          // store color to the buffer
          buffer[j * width + i].red = ir;
          buffer[j * width + i].green = ig;
          buffer[j * width + i].blue = ib;

        }
    }
  // save color to ppm file */
  printf("Save render to a PPM\n");
  createPPM(ppm, buffer, width, height);
  free(buffer);

  return 0;
}
