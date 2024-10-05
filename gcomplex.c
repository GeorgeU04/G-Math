#include "gcomplex.h"
#include <stdio.h>

/**
 * Prints a complex number in the format "a + bi".
 * Handles both positive and negative imaginary values.
 */
void gPrintComplex(gcomplex_num complex_num) {
  if (complex_num.imaginary >= 0)
    printf("%f + %fi\n", complex_num.real, complex_num.imaginary);
  else
    printf("%f - %fi\n", complex_num.real, -complex_num.imaginary);
}

/**
 * Adds two complex numbers and returns the result.
 * The real and imaginary parts are added separately.
 *
 */
gcomplex_num gAddComplex(gcomplex_num complex_num1, gcomplex_num complex_num2) {
  gcomplex_num new_num = {.real = complex_num1.real + complex_num2.real,
                          .imaginary =
                              complex_num1.imaginary + complex_num2.imaginary};
  return new_num;
}

/**
 * Multiplies two complex numbers and returns the result.
 * Uses the formula (a + bi) * (c + di) = (ac - bd) + (ad + bc)i.
 *
 */
gcomplex_num gMultiplyComplex(gcomplex_num complex_num1,
                              gcomplex_num complex_num2) {
  gcomplex_num new_num = {
      .real = (complex_num1.real * complex_num2.real -
               complex_num1.imaginary * complex_num2.imaginary),
      .imaginary = complex_num1.imaginary * complex_num2.real +
                   complex_num1.real * complex_num2.imaginary};
  return new_num;
}

/**
 * Adds a real number to the real part of a complex number.
 * This function modifies the original complex number in place.
 *
 */
void gAddComplexWithReal(gcomplex_num *complex_num, double real_num) {
  complex_num->real += real_num;
}

/**
 * Multiplies a complex number by a real number.
 * This function modifies the original complex number in place.
 *
 */
void gMultiplyComplexWithReal(gcomplex_num *complex_num, double real_num) {
  complex_num->real *= real_num;
  complex_num->imaginary *= real_num;
}
