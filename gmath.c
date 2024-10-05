
#include "gmath.h"
#include "gcomplex.h"
#include <stdint.h>

// Simple Exponents

/**
 * Computes the square root of a number using the Babylonian method
 * (Newton-Raphson method for square roots).
 * Returns -1 for negative input as sqrt is undefined for negative numbers.
 * The algorithm iterates until the difference between successive guesses
 * is smaller than a specified tolerance value.
 */
double gsqrt(double num) {
  if (num < 0) {
    return -1;
  }
  if (num == 0 || num == 1) {
    return num;
  }
  double guess = num / 2;
  double tolerance = 0.000001;
  double diff;

  do {
    double new_guess = 0.5 * (guess + num / guess);
    diff = new_guess - guess;
    guess = new_guess;
  } while (diff > tolerance || diff < -tolerance);

  return guess;
}

/**
 * Computes the power of a number (num^power) using exponentiation by squaring.
 * Handles negative powers by computing the reciprocal.
 * For negative base and non-integer power, the result is undefined.
 */
double gpow(double num, int64_t power) {
  if (power == 0) {
    return 1;
  }

  double result = 1;
  double current_base = num;
  int64_t current_exp = gabs(power);

  while (current_exp > 0) {
    if (current_exp % 2 == 1) {
      result *= current_base;
    }
    current_base *= current_base;
    current_exp /= 2;
  }
  return (power < 0) ? 1 / result : result;
}

/**
 * Computes e^power using the gpow function with base e.
 */
double gexp(double power) { return gpow(e, power); }

/**
 * Computes the natural logarithm of a number using a series approximation.
 * Returns -1 for invalid inputs (num <= 0). The function divides the input
 * until it is reduced to a number close to 1, and then uses a series expansion
 * for accuracy.
 */
double gln(double num) {
  if (num <= 0) {
    return -1;
  }
  if (num == 1) {
    return 0;
  }

  uint32_t count = 0;
  while (num > 2) {
    num /= 2;
    count++;
  }

  double result = count * LN2;

  double z = (num - 1) / (num + 1);
  double term = z;
  double series_sum = 0;

  for (int i = 1; i <= 10; i += 2) {
    series_sum += term / i;
    term *= z * z;
  }

  result += 2 * series_sum;

  return result;
}

// Miscellaneous Functions

/**
 * Solves the quadratic equation ax^2 + bx + c = 0.
 * Uses the quadratic formula and stores the two roots in root1 and root2.
 * The roots can be complex if the discriminant (b^2 - 4ac) is negative.
 */
void gQuadraticEquation(double a, double b, double c, gcomplex_num *root1,
                        gcomplex_num *root2) {
  if (a != 1) { // Normalize coefficients if a is not 1
    b /= a;
    c /= a;
    a = 1;
  }
  double discriminant = b * b - 4 * a * c;

  if (discriminant < 0) { // Complex roots
    root1->real = (-b) / (2 * a);
    root1->imaginary = gsqrt(gabs(discriminant)) / (2 * a);
    root2->real = (-b) / (2 * a);
    root2->imaginary = -1 * gsqrt(gabs(discriminant)) / (2 * a);
  } else { // Real roots
    root1->real = (-b + gsqrt(discriminant)) / (2 * a);
    root2->real = (-b - gsqrt(discriminant)) / (2 * a);
    root1->imaginary = 0;
    root2->imaginary = 0;
  }
}

/**
 * Computes the factorial of a number.
 * Uses a loop-based implementation for performance, especially with large
 * numbers.
 */
uint64_t gFactorial(uint64_t num) {
  if (num == 0 || num == 1) {
    return 1;
  }

  uint64_t val = 1;
  for (uint64_t i = 2; i <= num; ++i) {
    val *= i;
  }
  return val;
}

/**
 * Returns the absolute value of a number.
 */
double gabs(double num) { return (num < 0) ? -num : num; }

/**
 * Rounds a number up to the nearest integer.
 */
int64_t gceil(double num) {
  int64_t int_part = (int64_t)num;
  if (num == (double)int_part)
    return int_part;
  return (num > 0) ? int_part + 1 : int_part;
}

/**
 * Rounds a number down to the nearest integer.
 */
int64_t gfloor(double num) {
  int64_t int_part = (int64_t)num;
  if (num == (double)int_part)
    return int_part;
  return (num > 0) ? int_part : int_part - 1;
}

/**
 * Separates the integer and fractional part of a number.
 * The integer part is stored in the provided pointer.
 */
double gmodf(double num, int64_t *integer) {
  *integer = (int64_t)num;
  return num - *integer;
}

// Trig Functions in Degrees

/**
 * Converts degrees to radians and computes the cosine using gcosr (radians).
 */
double gcos(double degrees) {
  double radians = degrees * PI / 180;
  return gcosr(radians);
}

/**
 * Converts degrees to radians and computes the sine using gsinr (radians).
 */
double gsin(double degrees) {
  double radians = degrees * PI / 180;
  return gsinr(radians);
}

/**
 * Converts degrees to radians and computes the tangent using gtanr (radians).
 */
double gtan(double degrees) {
  double radians = degrees * PI / 180;
  return gtanr(radians);
}

// Trig Functions in Radians

/**
 * Computes the cosine of an angle given in radians using the Taylor series.
 * Handles periodicity by reducing angles larger than 2*PI and negative angles.
 */
double gcosr(double radians) {
  while (radians > (2 * PI)) {
    radians -= 2 * PI;
  }
  while (radians < 0) {
    radians += 2 * PI;
  }

  if (radians == 0 || radians == 2 * PI)
    return 1;
  else if (radians == PI / 2 || radians == 3 * PI / 2)
    return 0;
  else if (radians == PI)
    return -1;

  double val = 0;
  for (uint32_t i = 0; i < 10; ++i) {
    val += (gpow(-1, i) * gpow(radians, 2 * i) / gFactorial(2 * i));
  }
  return val;
}

/**
 * Computes the sine of an angle given in radians using the Taylor series.
 * Handles periodicity by reducing angles larger than 2*PI and negative angles.
 */
double gsinr(double radians) {
  while (radians > (2 * PI)) {
    radians -= 2 * PI;
  }
  while (radians < 0) {
    radians += 2 * PI;
  }

  if (radians == 0 || radians == 2 * PI || radians == PI)
    return 0;
  else if (radians == PI / 2)
    return 1;
  else if (radians == 3 * PI / 2)
    return -1;

  double val = 0;
  for (uint32_t i = 0; i < 10; ++i) {
    val += (gpow(-1, i) * gpow(radians, 2 * i + 1) / gFactorial(2 * i + 1));
  }
  return val;
}

/**
 * Computes the tangent of an angle given in radians by dividing sine by cosine.
 */
double gtanr(double radians) { return gsinr(radians) / gcosr(radians); }

// Inverse Trig Functions

/**
 * Approximates the arctangent of a number using a series expansion.
 * Handles values greater than 1 by using the identity atan(x) = PI/2 -
 * atan(1/x).
 */
double gatan(double num) {
  if (num == 0) {
    return 0;
  }

  if (num > 1) {
    return PI / 2.0 - gatan(1.0 / num);
  } else if (num < -1) {
    return -PI / 2.0 - gatan(1.0 / num);
  }

  double val = 0;

  for (uint32_t i = 0; i < 10; i++) {
    double term = gpow(-1, i) * gpow(num, 2 * i + 1) / (2 * i + 1);
    val += term;
  }

  return val;
}

/**
 * Approximates the arcsine of a number using a series expansion.
 * Only valid for inputs in the range [-1, 1].
 */
double gasin(double num) {
  if (num < -1 || num > 1) {
    return -1;
  }
  double val = 0;
  for (uint32_t i = 0; i < 10; ++i) {
    val += (gFactorial(2 * i) * gpow(num, 2 * i + 1)) /
           (gpow(4, i) * gpow(gFactorial(i), 2) * (2 * i + 1));
  }
  return val;
}

/**
 * Approximates the arccosine of a number by computing PI/2 - arcsin(x).
 * Only valid for inputs in the range [-1, 1].
 */
double gacos(double num) {
  if (num < -1 || num > 1) {
    return -1;
  }
  return PI / 2 - gasin(num);
}
