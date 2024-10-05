#ifndef GCOMPLEX_H
#define GCOMPLEX_H

typedef struct gcomplex_num {
  double real;
  double imaginary;
} gcomplex_num;

void gPrintComplex(gcomplex_num complex_num);
gcomplex_num gAddComplex(gcomplex_num complex_num1, gcomplex_num complex_num2);
gcomplex_num gMultiplyComplex(gcomplex_num complex_num1,
                              gcomplex_num complex_num2);
void gAddComplexWithReal(gcomplex_num *complex_num, double real_num);
void gMultiplyComplexWithReal(gcomplex_num *complex_num, double real_num);
#endif
