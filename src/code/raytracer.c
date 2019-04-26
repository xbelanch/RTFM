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


//
Color getColor(Ray* ray, Scene* scene)
{
  Object* pt = scene->objects;
  Object* object;
  bool hit_anything = false;
  double t_min = 0.0;
  double closest_so_far = 1000.0;
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
      // return color of the object intersected by ray
      Vector col = newVector(scene->rec->normal.x + 1,
                             scene->rec->normal.y + 1,
                             scene->rec->normal.z + 1);
      col = vectorScale(col, 0.5);
      return (Color) {col.x, col.y, col.z};

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

  // Create the ppm file
  // FILE* ppm;
  // ppm = fopen("picture.ppm", "w+");
  // fprintf(ppm, "P3\n%d %d\n255\n", nx, ny);

  Scene* scene = newScene();
  Object* sphere;

  sphere = newSphere( location(.0, -100.5, -1), 100 );
  scene->add(scene, sphere);

  sphere = newSphere( location(.25, .25, .0), .25 );
  scene->add(scene, sphere);

  sphere = newSphere( location(.0, .0, -1.0), .5 );
  scene->add(scene, sphere);


  scene->print(scene);

  Camera* camera = newCamera(
                             cam_lower_left_corner(-2.0, -1.0, -1.0),
                             cam_horizontal(4.0, .0, .0),
                             cam_vertical(.0, 2.0, .0),
                             cam_origin(.0, .0, .0)
                             );


  // Create a basic SDL infrastructure:
  // a window, a renderer and a texture.
  SDL_Window* window = SDL_CreateWindow(argv[1], SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W*wscale,H*hscale, SDL_WINDOW_RESIZABLE);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
  SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, W,H);

  // NOTE This is another way of create a pixels of the screen as a pointer
  // Uint32* pixels;
  // pixels = (Uint32*) malloc(sizeof(Uint32) * W * H);
  // also you must add this on a simple struct instead of a chaotic variables

  Uint32 pixels[W * H];
  // reset pixels
  SDL_memset(&pixels, 0x0, W * H * sizeof(Uint32));
  int pitch;


  // NOTE: This is the game loop ;)
  bool interrupted = false;
  while(!interrupted)
    {

      // Process events
      for(SDL_Event ev; SDL_PollEvent(&ev) != 0; )
        {

          // Process keyboard input
          // ESC : shutdown
          // W: Camera forward
          // S: Camera backward
          // A: Camera left
          // D: Camera right
          if (ev.type == SDL_KEYDOWN)
            {
              switch (ev.key.keysym.sym) {
              case SDLK_ESCAPE: // escape the raytracer
                printf("Exit the program\n");
                interrupted = true;
                break;

              case SDLK_a: // left camera movement
                camera->origin.x += 0.1;
                break;

              case SDLK_d: // right camera movement
                camera->origin.x -= 0.1;
                break;

              case SDLK_w: // forward camera movement
                camera->origin.z -= 0.1;
                break;

              case SDLK_s: // backward camera movement
                               camera->origin.z += 0.1;
                break;

              }
            }

        }

  /*     // Render a frame */

   for (int j = H-1; j>= 0; j--)
    {
      for (int i = 0; i < W; i++)
        {
          double u = (double)(i) / (double)(W);
          double v = (double)(j) / (double)(H);
          // ray = origin, lower_left_corner + u*horizontal + v*vertical
          Ray* ray = newRay(camera->origin,
                            vectorAdd(
                                      vectorAdd(
                                                vectorScale(camera->horizontal, u),
                                                vectorScale(camera->vertical, v)
                                                ),
                                      camera->lower_left_corner));
          ray->point_at_parameter(ray, 2.0);
          Color col = getColor(ray, scene);

          //createPPM(ppm, col);
            int ir = (int)(255.99 * col.r);
  int ig = (int)(255.99 * col.g);
  int ib = (int)(255.99 * col.b);

              j = (H - 1) - j; // solve the problem of put the pixels correctly
              pixels[(j * W) + i] = (0xff << 24) | (ir << 16) | (ig << 8) | ib;


        }
    }

      // pitch = four bytes: (Alpha | Red | Green | Blue ) * Row
      SDL_UpdateTexture(texture, NULL, pixels, W*4);
      SDL_RenderCopy(renderer, texture, NULL, NULL);
      SDL_RenderPresent(renderer);

      // Basic delay
      SDL_Delay(1000/60);

    }

  SDL_DestroyTexture(texture);
  SDL_Quit();
  // remove scene from memory

  scene->free(scene);

  // close the ppm file
  // fclose(ppm);

  return 0;
}
