#include <stdio.h>
#define SDL_MAIN_HANDLED
#include "SDL.h"

typedef unsigned int bool;

#define W 20
#define H 10
#define true 1
#define false 0
#define hscale 10
#define wscale 10




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
              float r =(float) i / (float) W;
              float g =(float) j / (float) H;
              float b = .2;

              Uint8 ir = (int)(255.99 * r);
              Uint8 ig = (int)(255.99 * g);
              Uint8 ib = (int)(255.99 * b);

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


