#ifndef VECTORH
#define VECTORH 1


// Declare a two-dimensional vector
typedef struct { double x, y; } v2;
// Declare a three-dimensional vector
typedef struct { double x, y, z; } v3;
// Declare a fourth-dimensional vector
typedef struct { double x, y, z, w; } v4;

typedef v2 Point2;
typedef v3 Point3;

// macros debug log
#define v3log(info, id, v) { printf("%s %s={%f, %f, %f}\n", info, id, v->x, v->y, v->z); }
#define dlog(info, d) {printf("%s: %f\n", info, d); }

// v2 operations

// v3 operations
extern double v3SquaredLength(), v3Length();
extern double v3Dot(), v3DistanceBetween2Points();
extern v3* v3Negate(),* v3Normalize(),* v3Scale(),* v3Add(),* v3Sub();
extern v3* v3Mul(),* v3Cross();
extern v3* v3New();
extern v3* v3Duplicate();

// not implemented yet
extern v3* v3Lerp(),* v3Combine();

#endif
