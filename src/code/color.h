#ifndef COLORH
#define COLORH 1

// Your output image will be in a "red-green-blue" color space, referred to for the
// rest of the source code as RGB
typedef struct { double r, g, b; } Color;

// Aritmethic operations with RGBs
extern Color* colorNew(),* colorDuplicate();
extern Color* colorNegate(),* colorAdd(),* colorSub(),* colorMul(), * colorDiv(),* colorScalar();
extern Color* colorSQRT();
#endif
