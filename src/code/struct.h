#ifndef STRUCTH
#define STRUCTH

// Define a three-dimensional vector
typedef struct
{
  double x;
  double y;
  double z;
} Vector;

// Define a RGB Color structure
typedef struct
{
  double r;
  double g;
  double b;
} Color;

// Define a ray
typedef struct _ray
{
  Vector origin;
  Vector direction;
  Vector (*point_at_parameter) (struct _ray* ray, double t);
} Ray;

// Objects
typedef struct
{
  Vector center;
  float radius;
} aSphere;

// Define a camera
typedef struct _camera
{
  Vector lower_left_corner;
  Vector horizontal;
  Vector vertical;
  Vector origin;
  Ray* (*get_ray) (struct _camera* camera, double u, double v);
} Camera;


typedef struct
{
  double t;
  Vector p;
  Vector normal;
} hit_record;


typedef struct _anObject
{
  struct _anObject* next;
  ObjectType type;

  // function pointers for operations on objects
  // hit -> deal with intersections between objects and rays
  // print -> print simple info of the object
  bool (*hit) (struct _anObject* self, Ray* ray, float t_min, float t_max, hit_record* rec);
  void (*print) (struct _anObject* self);

  // Object specific related
  union
  {
    aSphere sphere;
  } is;

} Object;


// Define a 3D scene as a linked list of objects ;)
typedef struct _scene
{
  Object* objects;
  int size;
  hit_record* rec;
  void (*print) (struct _scene* self);
  void (*add) (struct _scene* self, Object* object);
  void (*free) (struct _scene* scene);

} Scene;


// Define the Screen environment
typedef struct {
  unsigned int width;
  unsigned int height;
} Screen;

#endif
