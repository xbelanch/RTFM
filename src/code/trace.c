#define _XOPEN_SOURCE    /* ALWAYS BEFORE the include statement */
#include <stdlib.h>
#include <stdio.h>
#include "vector.h"
#include "color.h"
#include "ray.h"
#include "hitable.h"
#include "material.h"
#include "object.h"
#include "texture.h"
#include "trace.h"

Buffer* newBuffer(int width, int height)
{
  Buffer* buffer = malloc(sizeof(Buffer) * width * height);
  if (buffer != NULL)
    {
      int i;
      for (i = 0; i < width * height; i++)
        {
          buffer[i].red = 0; buffer[i].green = 0; buffer[i].blue = 0;
        }

      return buffer;
    }
  else {
    return NULL;
  }
}

void createPPM(FILE* file, Buffer* buffer, int width, int height)
{
  int r, g, b;
  for (int j = height - 1; j >= 0; j--)
    {
      for (int i = 0; i < width; i++)
        {
          r = buffer[j * width + i].red;
          g = buffer[j * width + i].green;
          b = buffer[j * width + i].blue;
          fprintf(file, "%d %d %d\n", r, g, b);
        }
    }
}


Color getColor(Ray* ray, Hitable* scene, int depth)
{
  hit_record rec;
  if (scene->hit(scene, ray, 0.00001, 10000.0, &rec))
    {
      // NOTE: after two days of segfaults, I found myself stupid!
      // you can initialize a Ray as a struct, but function pointers
      // are at this moment a black hole
      // for this you need to initialize it as a whole!
      // ALERT: if you do that, memory increase a lot! because every getColor call
      // is reserving space memory for the pointer of the struct of RAY!
      // TODO: Time to organize better this function!
      //Ray* scattered =  newRay((v3){.0, .0, .0}, (v3){.0, .0, -1});
      // DONE: remove function pointers from ray struct
      Ray scattered;
      // This not happens with Color struct
      Color attenuation;

      if (depth < 50 && rec.material->scatter(rec.material, ray, rec, &attenuation, &scattered ))
        {
          Color color = getColor(&scattered, scene, depth + 1);
          return (Color) {color.r * attenuation.r, color.g * attenuation.g, color.b * attenuation.b };
        } else {
        return (Color) {.0, .0, .0};
      }
    } else {
    return skydome(ray);
  }
}



Hitable* random_scene()
{
  int n = 500; // number of spheres into the scene
  Hitable* scene = newHitable();
  // ground sphere
  scene->addObject(scene, newSphere(v3New(.0, -1000.5, -1.0), 1000.0, Lambertian((Color) {.5, .5, .5})));

  for (int a = -11; a < 11; a++)
    {
      for (int b = -11; b < 11; b++)
        {
          double choose_mat = drand48();
          v3 center = { a + 0.9 * drand48(), 0.0, b + 0.9 * drand48() };
          if (v3Length(v3Sub(&center,v3New(4.0, 0.2, 0.0), &center)) > 0.9)
            {
              if (choose_mat < 0.8) // diffuse
                {
                  scene->addObject(scene, newSphere(center, 0.2, Lambertian((Color){drand48() * drand48(),  drand48() * drand48(), drand48() * drand48()})));
                }
              else if (choose_mat < 0.9) // metal
                {
                  scene->addObject(scene, newSphere(center, 0.2, Metal((Color){ 0.5 * (1 + drand48()), 0.5 * (1 + drand48()), 0.5 * (1 + drand48()) }, 0.5 * (1 + drand48()))));
                }
              else { // glasss
                scene->addObject(scene, newSphere(center, 0.2, Dielectric(1.5)));
              }
            }
        }
    }

  // add the three large spheres
  scene->addObject(scene, newSphere(v3New(-4.0, 1.0, .0), 1.0, Lambertian((Color){.4, .2, .1})));
  scene->addObject(scene, newSphere(v3New(.0, 1.0, .0), 1.0, Dielectric(1.5)));
  scene->addObject(scene, newSphere(v3New(4.0, 1.0, .0), 1.0, Metal((Color){.7, .6, .5}, .0)));
  // print scene info
  //  scene->log(scene);
  return scene;
}
