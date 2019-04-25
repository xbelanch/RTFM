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


// NOTE: this is the old getColor Function. Needs to fit with the new hitable code
/* Color getColor(Sphere* sphere, Ray* ray) */
/* { */
/*   // paint sphere if there's a collision */
/*   float hit  = sphere->hit(sphere, ray); */

/*   // hit the sphere, return the normal color from the hit point */
/*   if (hit > 0.0) */
/*     { */
/*       Vector pp = point_at_parameter(hit, ray); */
/*       Vector pp_c = { */
/*                      pp.x - sphere->center.x, */
/*                      pp.y - sphere->center.y, */
/*                      pp.z - sphere->center.z */
/*       }; */

/*       Vector U, S; */
/*       Vsubtract(pp_c, sphere->center, S); */
/*       Vunitary(S, U) */
/*         Vector normals = {(U.x + 1.0), */
/*                           (U.y + 1.0), */
/*                           (U.z + 1.0)}; */
/*       Vscale(normals, 1.5); // the book says 1.0 but renders a blue sphere */
/*       Color csphere = { */
/*                        normals.x, */
/*                        normals.y, */
/*                        normals.z */
/*       }; */
/*       return csphere; */
/*     } */

/*   // paint background sky */
/*   Vector unit_direction; */
/*   Vunitary(ray->direction, unit_direction); */
/*   double t = 0.5 * (unit_direction.y + 1.0); */
/*   Color background = { */
/*                       (1.0 - t) * 1.0 + t * 0.5 , */
/*                       (1.0 - t) * 1.0 + t * 0.7 , */
/*                       (1.0 - t) * 1.0 + t * 1.0 */
/*   }; */
/*   return background; */
/* } */


// NOTE: This is the second version of getColor (chapter 5)
// It's the "same" code of the book (or very similar), but it's
// not working properly.

/* Color getColor(Ray* ray, Hitable_Linked_List* world) */
/* { */
/*   hit_record rec; */
/*   if (world->hit(world, ray, 0.0, 100.0, &rec)) */
/*     { */

/*       Vector color_normals =  { */
/*                                (rec.normal.x + 1.0), */
/*                                (rec.normal.y + 1.0), */
/*                                (rec.normal.z + 1.0)}; */
/*       Vscale(color_normals, .5); */
/*       Color c = { */
/*                  color_normals.x, */
/*                  color_normals.y, */
/*                  color_normals.z */
/*       }; */
/*       return c; */
/*     } else { */
/*     // paint background sky */
/*     Vector unit_direction; */
/*     Vunitary(ray->direction, unit_direction); */
/*     double t = 0.5 * (unit_direction.y + 1.0); */
/*     Color background = { */
/*                         (1.0 - t) * 1.0 + t * 0.5 , */
/*                         (1.0 - t) * 1.0 + t * 0.7 , */
/*                         (1.0 - t) * 1.0 + t * 1.0 */
/*     }; */
/*     return background; */
/*   } */
/* } */

Color getColor(Ray* ray, Scene* scene)
{
  Object* pt = scene->objects;
  Object* object;
  bool hit_anything = false;
  while(scene->objects)
    {
      object = scene->objects;
      if (object->hit(object, ray, 0.0, 1000.0, scene->rec))
        {
          hit_anything = true;
        }
      scene->objects = object->next;
    }

  scene->objects = pt;

  if (hit_anything)
    {
      Vector col = newVector(scene->rec->normal.x + 1,
                             scene->rec->normal.y + 1,
                             scene->rec->normal.z + 1);
      col = vectorScale(col, 0.5);
      return (Color) {col.x, col.y, col.z};

    } else {
    // paint background
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
  FILE* ppm;
  ppm = fopen("picture.ppm", "w+");
  // extract from the book to generate the ppm file
  int nx = 400;
  int ny = 200;
  fprintf(ppm, "P3\n%d %d\n255\n", nx, ny);

  Scene* scene = newScene();
  Object* sphere;

  sphere = newSphere( location(.0, .0, -1.0), .5 );
  scene->add(scene, sphere);

  sphere = newSphere( location(.0, -100.5, -1), 100 );
  scene->add(scene, sphere);
  /*
  sphere = newSphere( location(.0, .20, -1.0), .5 );
  scene->add(scene, sphere);
  */

  scene->print(scene);

  Camera* camera = newCamera(
                             cam_lower_left_corner(-2.0, -1.0, -1.0),
                             cam_horizontal(4.0, .0, .0),
                             cam_vertical(.0, 2.0, .0),
                             cam_origin(.0, .0, .0)
                             );




  for (int j = ny-1; j>= 0; j--)
    {
      for (int i = 0; i < nx; i++)
        {
          double u = (double)(i) / (double)(nx);
          double v = (double)(j) / (double)(ny);
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

          createPPM(ppm, col);

        }
    }


  // remove scene from memory
  scene->free(scene);

  // close the ppm file
  fclose(ppm);
  exit(0);

  /* // Create a basic SDL infrastructure: */
  /* // a window, a renderer and a texture. */
  /* SDL_Window* window = SDL_CreateWindow(argv[1], SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W*wscale,H*hscale, SDL_WINDOW_RESIZABLE); */
  /* SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0); */
  /* SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, W,H); */

  /* // NOTE This is another way of create a pixels of the screen as a pointer */
  /* // Uint32* pixels; */
  /* // pixels = (Uint32*) malloc(sizeof(Uint32) * W * H); */
  /* // also you must add this on a simple struct instead of a chaotic variables  */

  /* Uint32 pixels[W * H]; */
  /* // reset pixels */
  /* SDL_memset(&pixels, 0x0, H * W * sizeof(Uint32)); */
  /* int pitch; */


  /* // NOTE: This is the game loop ;) */
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
  /*               camera.origin.x += 0.1; */
  /*               break; */

  /*             case SDLK_d: // right camera movement */
  /*               camera.origin.x -= 0.1; */
  /*               break; */

  /*             case SDLK_w: // forward camera movement */
  /*               camera.origin.z -= 0.1; */
  /*               break; */

  /*             case SDLK_s: // backward camera movement */
  /*                              camera.origin.z += 0.1; */
  /*               break; */

  /*             } */
  /*           } */

  /*       } */

  /*     // Render a frame */
  /*     for (int j = H - 1; j >= 0; j--) */
  /*       { */
  /*         for (int i = 0 ; i < W; i++) */
  /*           { */
  /*             // UV screen */
  /*             float u = (float) i / (float) W; */
  /*             float v = (float) j / (float) H; */

  /*             Vector direction =  { */
  /*                         camera.lower_left_corner.x + u * camera.horizontal.x + v * camera.vertical.x, */
  /*                         camera.lower_left_corner.y + u * camera.horizontal.y + v * camera.vertical.y, */
  /*                         camera.lower_left_corner.z + u * camera.horizontal.z + v * camera.vertical.z */
  /*             }; */
  /*             Ray* ray = newRay( camera.origin, direction                                 ); */

  /*             //              Vector p = ray->point_at_parameter(ray, 1.0); // interesting to see how it change the pattern if you add more value */
  /*             ray->point_at_parameter(ray, 2.0); // the book says 2.0 :?  */
  /*            Color color = getColor(ray, world); */
  /*             Uint8 ir = (int)(255.99 * color.r); */
  /*             Uint8 ig = (int)(255.99 * color.g); */
  /*             Uint8 ib = (int)(255.99 * color.b); */

  /*             j = (H - 1) - j; // solve the problem of put the pixels correctly */
  /*             pixels[(j * W) + i] = (0xff << 24) | (ir << 16) | (ig << 8) | ib; */


  /*           } */
  /*       } */

  /*     // pitch = four bytes: (Alpha | Red | Green | Blue ) * Row */
  /*     SDL_UpdateTexture(texture, NULL, pixels, W*4); */
  /*     SDL_RenderCopy(renderer, texture, NULL, NULL); */
  /*     SDL_RenderPresent(renderer); */

  /*     // Basic delay */
  /*     SDL_Delay(1000/60); */

  /*   } */

  /* SDL_DestroyTexture(texture); */
  /* SDL_Quit(); */
  return 0;
}
