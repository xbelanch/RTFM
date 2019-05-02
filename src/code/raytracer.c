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
#include "material.h"
#include "sphere.h"

// https://docs.microsoft.com/en-us/previous-versions/sxtz2fa8(v=vs.140)
#define _CRT_RAND_S

// drand48() returns a random double in the range [0.0, 1.0). You can mimic with rand() by the expression (rand() / (RAND_MAX + 1.0)).
double drand48()
{
  return rand() / (RAND_MAX + 1.0);
}


// The main tracer recursive function
Color getColor(Ray* ray, Scene* scene, int depth)
{
  hit_record rec;
  if (scene->hitable(scene, ray, 0.001, 1000.0, &rec))
    {

      Color attenuation = {0.35, 0.35, 0.35};
      Ray scattered;


      if (depth < 50 && rec.material->scatter(ray, &scattered, rec.material, rec, &attenuation))
        {
          Color col = getColor(&scattered, scene, depth + 1);

          return (Color) {
            col.r * attenuation.r,
              col.g * attenuation.g,
              col.b * attenuation.b
              };
        } else {
        return (Color) {0.0, 0.0, 0.0};
      }
    } else {

    // else paint background
    Vector unit_direction = vectorUnitary(ray->direction);
    double t = 0.5 * (unit_direction.y + 1.0);
    return (Color) { (1.0 - t) * 1.0 + t * 0.5 , (1.0 - t) * 1.0 + t * 0.7 ,  (1.0 - t) * 1.0 + t * 1.0  };
  }

}

void createPPM(FILE* file, int r, int g, int b)
{
  fprintf(file, "%d %d %d\n", r, g, b);
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


  sphere = newSphere( location(.0, .0, -1), .5 );
  sphere->material = Lambertian((Color) {0.8, 0.3, 0.3});
  scene->add(scene, sphere);

  sphere = newSphere( location(.0, -100.5, -1.0), 100 );
  sphere->material = Lambertian((Color) {0.8, .8, .0});
  scene->add(scene, sphere);

  sphere = newSphere( location(1, 0, -1.0), .5 );
  sphere->material = Metal((Color) {.8, .6, .2}, 0.3);
  scene->add(scene, sphere);

  sphere = newSphere( location(-1, 0, -1.0), .5 );
  sphere->material = Metal((Color) {.8, .8, .8}, 0.95);
  scene->add(scene, sphere);


  sphere = newSphere( location(0, 0.85, -1.0), .35 );
  sphere->material = Lambertian((Color) {0.2, 0.2, .65});
  scene->add(scene, sphere);



  scene->print(scene);

  Camera* camera = newCamera();


  // Create a basic SDL infrastructure:
  // a window, a renderer and a texture.
  SDL_Window* window = SDL_CreateWindow(argv[1], SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W ,H , SDL_WINDOW_RESIZABLE);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
  SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, W,H);

  // NOTE This is another way of create a pixels of the screen as a pointer
  // Uint32* pixels;
  // pixels = (Uint32*) malloc(sizeof(Uint32) * W * H);
  // also you must add this on a simple struct instead of a chaotic variables

  Uint32* pixels;
  pixels = (Uint32*) malloc(sizeof(Uint32) * W * H);
  int pitch;

  // reset pixels
  /* SDL_memset(&pixels, 0x0, W * H * sizeof(Uint32)); */
  /* int pitch; */


  // NOTE: This is the game SDL loop ;)
  bool interrupted = false;
  while(!interrupted)
    {



      // Render a frame

      for (int j = H-1; j>= 0; j--)
        {
          if (interrupted) break;
          for (int i = 0; i < W; i++)
            {

              Color col = {0.0, 0.0, 0.0};

              // Antialiasing
              for (int s = 0; s < samples; s++)
                {

                  double u = (double)(i + drand48()) / (double)(W);
                  double v = (double)(j + drand48()) / (double)(H);

                  Ray* ray = camera->get_ray(camera, u, v);

                  point_at_parameter(ray, 2.0);

                  int depth = 16;
                  Color t = getColor(ray, scene, depth);
                  col.r += t.r;
                  col.g += t.g;
                  col.b += t.b;

                }

              col.r /= (double)(samples);
              col.g /= (double)(samples);
              col.b /= (double)(samples);

              // using a "gamma 2" which means raising the color to the power 1/gamma, or
              // in our simple case 1/2 which is just squared-root
              col.r = sqrt(col.r);
              col.g = sqrt(col.g);
              col.b = sqrt(col.b);

              int ir = (int)(255.99 * col.r);
              int ig = (int)(255.99 * col.g);
              int ib = (int)(255.99 * col.b);

              // save color to ppm file
              createPPM(ppm, ir, ig, ib);


              // Update SDL window for every line
              // Process events
              for(SDL_Event ev; SDL_PollEvent(&ev) != 0; )
                {

                  // Process keyboard input
                  // ESC : shutdown
                  if (ev.type == SDL_KEYDOWN)
                    {
                      switch (ev.key.keysym.sym) {
                      case SDLK_ESCAPE: // escape the raytracer
                        printf("Stop the render process\n");
                        interrupted = true;
                        break;

                      }
                    }

                }

              int _j = (H - 1) - j; // solve the problem of put the pixels correctly
              pixels[(_j * W) + i] = 0xff << 24 | ir  << 16 | ig << 8 | ib;

              if (((_j * W) + i) % W == 0)
                {
                  // pitch = four bytes: (Alpha | Red | Green | Blue ) * Row
                  SDL_UpdateTexture(texture, NULL, pixels, W*4);
                  SDL_RenderCopy(renderer, texture, NULL, NULL);
                  SDL_RenderPresent(renderer);

                }

            }
        }
      // update last line of screen
      SDL_UpdateTexture(texture, NULL, pixels, W*4);
                  SDL_RenderCopy(renderer, texture, NULL, NULL);
                  SDL_RenderPresent(renderer);
      interrupted = true;
    }



  bool exit  = false;
  while(!exit)
    {
              for(SDL_Event ev; SDL_PollEvent(&ev) != 0; )
                {

                  // Process keyboard input
                  // ESC : shutdown
                  if (ev.type == SDL_KEYDOWN)
                    {
                      switch (ev.key.keysym.sym) {
                      case SDLK_ESCAPE: // escape the raytracer
                        printf("Exit the program\n");
                        exit = true;
                        break;

                      }
                    }

                }


    }
  SDL_DestroyTexture(texture);
  SDL_Quit();

  // remove scene from memory
  scene->free(scene);

  // close the ppm file
  fclose(ppm);

  return 0;
}
