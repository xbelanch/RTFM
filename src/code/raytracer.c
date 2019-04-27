#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define SDL_MAIN_HANDLED
#include "SDL.h"

#include "raytracer.h"
#include "struct.h"
#include "scene.h"
#include "vector.h"
#include "ray.h"
#include "camera.h"
#include "sphere.h"

// https://docs.microsoft.com/en-us/previous-versions/sxtz2fa8(v=vs.140)
#define _CRT_RAND_S

// drand48() returns a random double in the range [0.0, 1.0). You can mimic with rand() by the expression (rand() / (RAND_MAX + 1.0)).
double drand48()
{
  return rand() / (RAND_MAX + 1.0);
}

Vector random_in_unit_sphere()
{
  Vector p;
  do {
    p = vectorScale(
                    vectorSubtract(
                                   newVector(drand48(), drand48(), drand48()),
                                   newVector(1.0, 1.0, 1.0)
                                   ),
                    2.0);
  } while (vectorSquaredLength(p) >= 1.0);
  return p;
}

//
Color getColor(Ray* ray, Scene* scene)
{
  Object* pt = scene->objects;
  Object* object;
  bool hit_anything = false;
  double t_min = 0.00001; // min distance
  double closest_so_far = 1000.0; // max distance
  while(scene->objects)
    {
      object = scene->objects;
      if (object->hit(object, ray, t_min, closest_so_far, scene->rec))
        {
          hit_anything = true;
          closest_so_far = scene->rec->t;
        }
      scene->objects = object->next;
    }

  scene->objects = pt;

  if (hit_anything)
    {

      // diffuse material
      Vector _v = vectorAdd(scene->rec->p, scene->rec->normal);
      Vector target = vectorAdd(_v, random_in_unit_sphere());
      Ray* ray = newRay(scene->rec->p,
                        vectorSubtract(target, scene->rec->p)
                        );

      // Recursive!
      Color col = getColor(ray, scene);
      return (Color) {col.r * 0.5, col.g * 0.5, col.b * 0.5};

    } else {
    // else paint background
    Vector unit_direction = vectorUnitary(ray->direction);
    double t = 0.5 * (unit_direction.y + 1.0);
    return (Color) { (1.0 - t) * 1.0 + t * 0.5 , (1.0 - t) * 1.0 + t * 0.7 ,  (1.0 - t) * 1.0 + t * 1.0  };
  }

}

void createPPM(FILE* file, Color col)
{
  int ir = (int)(255.99 * col.r);
  int ig = (int)(255.99 * col.g);
  int ib = (int)(255.99 * col.b);

  fprintf(file, "%d %d %d\n", ir, ig, ib);
}

int main(int argc, char** argv)
{
  char* message = "Raytracer for the masses";
  printf("%s\n", message);


  // Rand stuff
  // Seed the random-number generator with the current time so that
  // the numbers will be different every time we run.
  srand( (unsigned)time( NULL ) );

  // Create the ppm file
  FILE* ppm;
  ppm = fopen("picture.ppm", "w+");
  fprintf(ppm, "P3\n%d %d\n255\n", W, H);

  Scene* scene = newScene();
  Object* sphere;

  sphere = newSphere( location(.0, -100.5, -1.0), 100 );
  scene->add(scene, sphere);

  sphere = newSphere( location(.15, -0.25, -0.65), .15 );
  scene->add(scene, sphere);

  sphere = newSphere( location(.0, .0, -1.35), .5 );
  scene->add(scene, sphere);

  sphere = newSphere( location(-0.85, -0.25, -1.0), .25 );
  scene->add(scene, sphere);


  scene->print(scene);

  Camera* camera = newCamera();


  // Create a basic SDL infrastructure:
  // a window, a renderer and a texture.
  /* SDL_Window* window = SDL_CreateWindow(argv[1], SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W*wscale,H*hscale, SDL_WINDOW_RESIZABLE); */
  /* SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0); */
  /* SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, W,H); */

  // NOTE This is another way of create a pixels of the screen as a pointer
  // Uint32* pixels;
  // pixels = (Uint32*) malloc(sizeof(Uint32) * W * H);
  // also you must add this on a simple struct instead of a chaotic variables

  /* Uint32 pixels[W * H]; */
  // reset pixels
  /* SDL_memset(&pixels, 0x0, W * H * sizeof(Uint32)); */
  /* int pitch; */


  // NOTE: This is the game SDL loop ;)
  /* bool interrupted = false; */
  /* while(!interrupted) */
  /*   { */

  /*     // Process events */
  /*     for(SDL_Event ev; SDL_PollEvent(&ev) != 0; ) */
  /*       { */

  /*         // Process keyboard input */
  /*         // ESC : shutdown */
  /*         // W: Camera forward */
  /*         // S: Camera backward */
  /*         // A: Camera left */
  /*         // D: Camera right */
  /*         if (ev.type == SDL_KEYDOWN) */
  /*           { */
  /*             switch (ev.key.keysym.sym) { */
  /*             case SDLK_ESCAPE: // escape the raytracer */
  /*               printf("Exit the program\n"); */
  /*               interrupted = true; */
  /*               break; */

  /*             case SDLK_a: // left camera movement */
  /*               camera->origin.x += 0.1; */
  /*               break; */

  /*             case SDLK_d: // right camera movement */
  /*               camera->origin.x -= 0.1; */
  /*               break; */

  /*             case SDLK_w: // forward camera movement */
  /*               camera->origin.z -= 0.1; */
  /*               break; */

  /*             case SDLK_s: // backward camera movement */
  /*                              camera->origin.z += 0.1; */
  /*               break; */

  /*             } */
  /*           } */

  /*       } */

  /*     // Render a frame */

  for (int j = H-1; j>= 0; j--)
    {
      for (int i = 0; i < W; i++)
        {

          Color col = {0.0, 0.0, 0.0};

          // Antialiasing
          for (int s = 0; s < samples; s++)
            {

              double u = (double)(i + drand48()) / (double)(W);
              double v = (double)(j + drand48()) / (double)(H);

              Ray* ray = camera->get_ray(camera, u, v);

              ray->point_at_parameter(ray, 2.0);

              Color t = getColor(ray, scene);
              col.r += t.r;
              col.g += t.g;
              col.b += t.b;

            }

          col.r /= (float)(samples);
          col.g /= (float)(samples);
          col.b /= (float)(samples);
          createPPM(ppm, col);

          // SDL Stuff
          /* int ir = (int)(255.99 * col.r); */
          /* int ig = (int)(255.99 * col.g); */
          /* int ib = (int)(255.99 * col.b); */

          /* j = (H - 1) - j; // solve the problem of put the pixels correctly */
          /* pixels[(j * W) + i] = (0xff << 24) | (ir << 16) | (ig << 8) | ib; */


        }
    }

  // pitch = four bytes: (Alpha | Red | Green | Blue ) * Row
  /* SDL_UpdateTexture(texture, NULL, pixels, W*4); */
  /* SDL_RenderCopy(renderer, texture, NULL, NULL); */
  /* SDL_RenderPresent(renderer); */

  /* // Basic delay */
  /* SDL_Delay(1000/60); */

  //}

  /* SDL_DestroyTexture(texture); */
  /* SDL_Quit(); */

  // remove scene from memory
  scene->free(scene);

  // close the ppm file
  fclose(ppm);

  return 0;
}
