#ifndef SCENEH
#define SCENEH


/* bool hit (Hitable_Linked_List* hitable_linked_list, Ray* r, float t_min, float t_max, hit_record* rec) */
/* { */
/*   hit_record temp_rec; */
/*   bool hit_anything = false; */
/*   double closest_so_far = t_max; */
/*   for (int i = 0; i < hitable_linked_list->list_size; i++ ) */
/*     { */

/*       if (hitable_linked_list->list[i]->hit(hitable_linked_list->list[i], r, t_min, closest_so_far, &temp_rec)) */
/*         { */
/*           hit_anything = true; */

/*           closest_so_far = temp_rec.t; */
/*           rec = &temp_rec; */
/*         } */
/*     } */
/*   return hit_anything; */
/* } */

void addObjectToScene(Scene* self, Object* object)
{
  if(self->objects == NULL) // empty scene
    {
      self->objects = object;
      object->next = NULL; // first enter points to NULL
    } else {

    object->next = self->objects; // point to the last object added
    self->objects = object; // update list pointing
  }

  self->size += 1;
}

void printInfo(Scene* scene)
{
  printf("This is a simple print info debug of the scene\n");
  Object* objectPTR = scene->objects; // conserve the original linked list
  while (scene->objects)
    {
      scene->objects->print(scene->objects);
      scene->objects = scene->objects->next;
    }
  scene->objects = objectPTR;
}


void freeScene(Scene* scene)
{
  Object* objectPTR;
  while(scene->objects)
    {
      objectPTR = scene->objects;
      scene->objects = scene->objects->next;
      free(objectPTR);
    }
  scene->objects = NULL;
}


Scene* newScene()
{
  Scene* scene = malloc(sizeof(Scene));

  if (scene != NULL)
    {
      scene->objects = NULL;
      scene->size = 0;
      scene->rec = malloc(sizeof(hit_record));
      scene->rec->t = .0;
      scene->rec->p = (Vector) {.0, .0, .0};
      scene->rec->normal = (Vector) {.0, .0, .0};
      // pointer functions
      scene->add = addObjectToScene;
      scene->print = printInfo;
      scene->free = freeScene;
      return scene;

    } else {

    return NULL;
  }
}

#endif
