#ifndef HSCENE
#define HSCENE

#include "sphere.h"


// This is a implementation of a simple linked list
// By now, only support spheres... or need to say
// a scene of spheres

typedef struct {
  Sphere* spheres;
  int count;
} Scene;

Scene* Scene_new(void)
{
  Scene* scene = malloc(sizeof(Scene));
  scene->spheres = NULL;
  scene->count = 0;

  return scene;
}

void Scene_add_sphere(Scene* scene, Sphere* sphere)
{

  if (scene->spheres == NULL)
    {
      scene->spheres = sphere;
      sphere->next = NULL;
    } else {

    sphere->next = scene->spheres;
    scene->spheres = sphere;
  }

  scene->count++;

}


void Scene_print(Scene* scene)
{
  printf("How many spheres at the scene? %d\n", scene->count);

  Sphere* last = scene->spheres;
  int total = scene->count;

  while(scene->spheres)

    {
      scene->count--;
      printf("Sphere %d with radius %f at (%f, %f, %f)\n",
             scene->count,
             scene->spheres->radius,
             scene->spheres->center.x,
             scene->spheres->center.y,
             scene->spheres->center.z);
      scene->spheres = scene->spheres->next;
    }

  scene->spheres = last;
  scene->count = total;

}




#endif
