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
  Vector u, v, w;
  double lens_radius;
  Ray* (*get_ray) (struct _camera* camera, double u, double v);
} Camera;


typedef struct _material
{
  Color albedo;
  double fuzz;
  double ref_idx;
  bool (*scatter) (Ray* ray_in, Ray* scattered, struct _material* self, struct _hit_record rec, Color* attenuation);
} Material;

typedef struct _hit_record
{
  double t;
  Vector p;
  Vector normal;
  Material* material;


} hit_record;


typedef struct _anObject
{
  struct _anObject* next;
  ObjectType type;
  Material* material;

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
  void (*print) (struct _scene* self);
  void (*add) (struct _scene* self, Object* object);
  void (*free) (struct _scene* self);
  bool (*hitable) (struct _scene* self, Ray* ray, double t_min, double t_max, hit_record* rec);
} Scene;


// Define the Screen environment
typedef struct {
  unsigned int width;
  unsigned int height;
} Screen;

#endif
