#ifndef HITABLEH
#define HITABLEH


typedef struct
{
  double t;
  Vector p;
  Vector normal;
} hit_record;


typedef struct _hitable
{
  struct _hitable* next;
  ObjectType type;

  // function pointers for operations on objects
   bool (*hit) (struct _hitable* hitable, Ray* r, float t_min, float t_max, hit_record* rec);

  // Object specific related
  union
  {
    aSphere sphere;
  } Object;

} Hitable;

typedef struct _hitable_linked_list
{
  Hitable** list;
  int list_size;
  bool (*hit) (struct _hitable_linked_list* list, Ray* r, float t_min, float t_max, hit_record* rec);

} Hitable_Linked_List;



bool hit (Hitable_Linked_List* hitable_linked_list, Ray* r, float t_min, float t_max, hit_record* rec)
{
  hit_record temp_rec;
  bool hit_anything = false;
  double closest_so_far = t_max;
  for (int i = 0; i < hitable_linked_list->list_size; i++ )
    {

      if (hitable_linked_list->list[i]->hit(hitable_linked_list->list[i], r, t_min, closest_so_far, &temp_rec))
        {
          hit_anything = true;

          closest_so_far = temp_rec.t;
          rec = &temp_rec;
        }
    }
  return hit_anything;
}


Hitable_Linked_List* newHitableList(Hitable** list, int size)
{
  Hitable_Linked_List* hitable_linked_list = malloc(sizeof(Hitable_Linked_List));

  if (hitable_linked_list != NULL)
    {
      hitable_linked_list->list = list;
      hitable_linked_list->list_size = size;
      hitable_linked_list->hit = hit;
      return hitable_linked_list;

    } else {

    return NULL;
  }
}

#endif
