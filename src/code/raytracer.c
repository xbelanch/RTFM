#include <stdio.h>
#define SDL_MAIN_HANDLED
#include "SDL.h"

#include "raytracer.h"
#include "vector.h"
#include "ray.h"
#include "sphere.h"

typedef unsigned int bool;

#define W 200
#define H 100
#define true 1
#define false 0
#define hscale 5
#define wscale 5


Color getColor(Ray* ray)
{
  // paint sphere if there's a collision
  Sphere sphere = {
                   {0, 0, -1}, // center of the sphere
                   0.5 // radius of the sphere
  };

  float hit  = hit_sphere(&sphere, ray);
  // hit the sphere, return the normal color from the hit point
  if (hit > 0.0)
    {
      Vector pp = point_at_parameter(hit, ray);
      Vector pp_c = {
                   pp.x - sphere.center.x,
                   pp.y - sphere.center.y,
                   pp.z - sphere.center.z
      };

      Vector U, S;
      Vsubtract(pp_c, sphere.center, S);
      Vunitary(S, U)
      Vector normals = {(U.x + 1.0),
                       (U.y + 1.0),
                       (U.z + 1.0)};
      Vscale(normals, 1.5); // the book says 1.0 but renders a blue sphere
      Color csphere = {
                       normals.x,
                       normals.y,
                       normals.z
      };
      return csphere;
    }

  // paint background sky
  Vector unit_direction;
  Vunitary(ray->direction, unit_direction);
  double t = 0.5 * (unit_direction.y + 1.0);
  Color background = {
            (1.0 - t) * 1.0 + t * 0.5 ,
            (1.0 - t) * 1.0 + t * 0.7 ,
            (1.0 - t) * 1.0 + t * 1.0
  };
  return background;
}


int main(int argc, char** argv)
{
  char* message = "Raytracer for the masses";
  printf("%s\n", message);

  // Create a basic SDL infrastructure:
  // a window, a renderer and a texture.
  SDL_Window* window = SDL_CreateWindow(argv[1], SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W*wscale,H*hscale, SDL_WINDOW_RESIZABLE);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
  SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, W,H);

  // TODO This is another way of create a pixels of the screen as a pointer
  // IS A INFO!
  // Uint32* pixels;
  // pixels = (Uint32*) malloc(sizeof(Uint32) * W * H);

  
  Uint32 pixels[W * H];
  // reset pixels
  SDL_memset(&pixels, 0x0, H * W * sizeof(Uint32));
  int pitch;

  /* // Raytracer camera values */
  Camera camera = {
                   {-2.0, -1.0, -1.0}, // lower_left_corner
                   {4.0, .0, .0}, // horizontal
                   {.0, 2.0, .0}, // vertical
                   {.0, .0, .0} // origin
  };
  
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
                camera.origin.x += 0.1;
                break;
              
              case SDLK_d: // right camera movement
                camera.origin.x -= 0.1;
                break;
              
              case SDLK_w: // forward camera movement
                camera.origin.z -= 0.1;
                break;
              
              case SDLK_s: // backward camera movement
                camera.origin.z += 0.1;
                break;
              
              
              }

              
            }

        }

      // Render a frame
      for (int j = H - 1; j >= 0; j--)
        {
          for (int i = 0 ; i < W; i++)
            {
              // UV screen
              float u = (float) i / (float) W;
              float v = (float) j / (float) H;

              Ray ray = {
                       camera.origin,
                       {
                        camera.lower_left_corner.x + u * camera.horizontal.x + v * camera.vertical.x,
                        camera.lower_left_corner.y + u * camera.horizontal.y + v * camera.vertical.y,
                        camera.lower_left_corner.z + u * camera.horizontal.z + v * camera.vertical.z
                       }
              };

              // Color color = {1.0, 0, 1.0};
              Color color = getColor(&ray);
              
              Uint8 ir = (int)(255.99 * color.r);
              Uint8 ig = (int)(255.99 * color.g);
              Uint8 ib = (int)(255.99 * color.b);

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
  return 0;
}


