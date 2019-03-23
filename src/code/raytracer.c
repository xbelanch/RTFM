#include <stdio.h>
#define SDL_MAIN_HANDLED
#include "SDL.h"

typedef unsigned int bool;

#define W 64
#define H 32
#define true 1
#define false 0




int main(int argc, char** argv)
{
  char* message = "Raytracer for the masses";
  printf("%s\n", message);


   // Create a screen.
   SDL_Window* window = SDL_CreateWindow(argv[1], SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W*4,H*6, SDL_WINDOW_RESIZABLE);
   SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
   SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, W,H);

   bool interrupted = false;

  while(!interrupted)
     {

       // Process events
       for(SDL_Event ev; SDL_PollEvent(&ev) != 0; )
	 {

               if (ev.type == SDL_KEYDOWN) { 
                 switch (ev.key.keysym.sym) {
                 case SDLK_ESCAPE:
                   printf("Exit the program\n");
                   interrupted = true;
                   break;
                 }
               }

	 }

     }

   SDL_Quit();
  return 0;
}


