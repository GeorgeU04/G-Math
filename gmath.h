#ifndef GMATH_H
#define GMATH_H
#include "gcomplex.h"
#include <stdint.h>
#define PI 3.14159265358979323
#define e 2.718281828459045235
#define LN2 0.6931471805599453
// simple exponents
double gsqrt(double num);
double gpow(double num, int64_t power);
double gexp(double power);
double gln(double num);

// misc
void gQuadraticEquation(double a, double b, double c, gcomplex_num *root1,
                        gcomplex_num *root2);
uint64_t gFactorial(uint64_t num);
double gabs(double num);
int64_t gceil(double num);
int64_t gfloor(double num);
double gmodf(double num, int64_t *integer);

// trig in degrees
double gcos(double degrees);
double gsin(double degrees);
double gtan(double degrees);

// trig in radians
double gcosr(double radians);
double gsinr(double radians);
double gtanr(double radians);

// inverse trig funtions; return radians
double gatan(double num);
double gasin(double num);
double gacos(double num);

#endif
