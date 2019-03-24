// vec3.h

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct { float x; float y; float z;} vec3;


inline void log_vec3(char* id, vec3 v)
{
  printf("%s = {%f, %f, %f}\n", id,  v.x, v.y, v.z);
}


// give vec3 make unitary
inline void make_unit_vec3(vec3* v)
{
  float k = 1.0 / sqrt(
                       v->x * v->x +
                       v->y * v->y +
                       v->z * v->z);

  v->x *= k;
  v->y *= k;
  v->z *= k;
}

// vector add operation: v1 + v2
// return new vec3
inline vec3 add_vec3(vec3 v1, vec3 v2)
{
  vec3 v3 = {
    v1.x + v2.x,
    v1.y + v2.y,
    v1.z + v2.z
  };

  return v3;
}

// vector substract operation: v1 - v2
// return new vec3
inline vec3 substract_vec3(vec3 v1, vec3 v2)
{
  vec3 v3 = {
    v1.x - v2.x,
    v1.y - v2.y,
    v1.z - v2.z
  };

  return v3;
}

// vector multiply operation: v1 * v2
// return new vec3
inline vec3 multiply_vec3(vec3 v1, vec3 v2)
{
  vec3 v3 = {
    v1.x * v2.x,
    v1.y * v2.y,
    v1.z * v2.z
  };

  return v3;
}

// vector division operation: v1 / v2
// return new vec3
inline vec3 division_vec3(vec3 v1, vec3 v2)
{
  vec3 v3 = {
    v1.x / v2.x,
    v1.y / v2.y,
    v1.z / v2.z
  };

  return v3;
}

// vector multiply by scalar  operation: v * scalar
// return new vec3
inline vec3 mult_scalar_vec3(vec3 v, float scalar)
{
  vec3 v3 = {
    v.x * scalar,
    v.y * scalar,
    v.z * scalar
  };

  return v3;
}

// dot vector operation
inline float dot_vec3(vec3 v1, vec3 v2)
{
  return
    v1.x * v2.x +
    v1.y * v2.y +
    v1.z * v2.z;
}

inline vec3 cross_vec3(vec3 v1, vec3 v2)
{
  vec3 v3 = {
          v1.y * v2.z - v1.z * v2.y,
          -(v1.x * v2.z - v1.z * v2.x),
          v1.x * v2.y - v1.y * v2.x
  };

  return v3;
}

inline float length_vec3(vec3 v)
{
  return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

inline float squared_length_vec3(vec3 v)
{
  return v.x * v.x + v.y * v.y + v.z * v.z;
}

inline vec3 unit_vec3(vec3 v)
{
  float length = length_vec3(v);
  vec3 v3 = {
             v.x / length,
             v.y / length,
             v.z / length
  };

  return v3;
}
