#include <stdio.h>
#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "ray.h"

typedef unsigned int bool;

#define W 200
#define H 100
#define true 1
#define false 0
#define hscale 5
#define wscale 5


vec3 color(const ray ray)
{
  vec3 unit_direction = make_unit_vec3(ray.direction);
  float t = 0.5 * (unit_direction.y + 1.0);
  vec3 color = {
            (1.0 - t) * 1.0 + t * 0.5 ,
            (1.0 - t) * 1.0 + t * 0.7 ,
            (1.0 - t) * 1.0 + t * 1.0
  };
  return color;
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

  /* Uint32* pixels; */
  /* pixels = (Uint32*) malloc(sizeof(Uint32) * W * H); */
  /* // reset pixels */
  Uint32 pixels[W * H];
  SDL_memset(&pixels, 0x0, H * W * sizeof(Uint32));
  int pitch;

  // Raytracer camera values
  vec3 lower_left_corner = {-2.0, -1.0, -1.0};
  vec3 horizontal = {4.0, .0, .0};
  vec3 vertical = {.0, 2.0, .0};
  vec3 origin = {.0, .0, .0};
  
 
  bool interrupted = false;
  while(!interrupted)
    {

      // Process events
      for(SDL_Event ev; SDL_PollEvent(&ev) != 0; )
        {

          if (ev.type == SDL_KEYDOWN)
            {
              switch (ev.key.keysym.sym) {
              case SDLK_ESCAPE:
                printf("Exit the program\n");
                interrupted = true;
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

              ray r = {
                       origin,
                       {
                        lower_left_corner.x + u * horizontal.x + v * vertical.x,
                        lower_left_corner.y + u * horizontal.y + v * vertical.y,
                        lower_left_corner.z + u * horizontal.z + v * vertical.z
                       }
              };

              vec3 c = color(r);
              
              Uint8 ir = (int)(255.99 * c.x);
              Uint8 ig = (int)(255.99 * c.y);
              Uint8 ib = (int)(255.99 * c.z);

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


