#ifndef COMMON
#define COMMON 1

typedef unsigned int bool;
typedef bool flag;

#define true 1
#define false 0

#ifdef __CYGWIN__
#define min(a,b) (a < b ? a : b)
#define max(a,b) (a > b ? a : b)
#endif

#define swap(a,b) (a^=b; b^=a; a^=b)
#define lerp(a,l,h) ((l)+(((h)-(l))*(a)))
#define clamp(v,l,h) (v < l : l : v > h ? h : v)

// macros allocation memory
#define NEWTYPE(x) (x*) (malloc((unsigned)sizeof(x)))

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define _XOPEN_SOURCE    /* ALWAYS BEFORE the include statement */
#if defined _WIN32
// https://docs.microsoft.com/en-us/previous-versions/sxtz2fa8(v=vs.140)
#define _CRT_RAND_S
// drand48() returns a random double in the range [0.0, 1.0). You can mimic with rand() by the expression (rand() / (RAND_MAX + 1.0)).

#define drand48() (rand() / (RAND_MAX + 1.0))
#endif


#endif
