#include <stdio.h>
#include <math.h>
#include <complex.h>

#define EPSILON 1e-9

void calculate_eigenvalues(double matrix[3][3]);

int main()
{
  double matrix[3][3];
  for (int i = 0; i < 3; i++)
  {
    scanf("%lf %lf %lf", &matrix[i][0], &matrix[i][1], &matrix[i][2]);
  }

  calculate_eigenvalues(matrix);
}

void calculate_eigenvalues(double matrix[3][3])
{
  double a = matrix[0][0];
  double b = matrix[0][1];
  double c = matrix[0][2];
  double d = matrix[1][0];
  double e = matrix[1][1];
  double f = matrix[1][2];
  double g = matrix[2][0];
  double h = matrix[2][1];
  double i = matrix[2][2];

  // Unique polynomial coefficients for a 3x3 matrix
  double c1 = -(a + e + i);
  double c2 = a * e - b * d + e * i - f * h + a * i - c * g;
  double c3 = -(a * e * i + b * f * g + c * d * h - a * f * h - b * d * i - c * e * g);

  // cardano's formula for eigenvalues
  double p = (-c1 * c1 + 3.0 * c2) / 3.0;
  double q = (2.0 * c1 * c1 * c1 - 9.0 * c1 * c2 + 27.0 * c3) / 27.0;
  double complex r = 3.0 * sqrt(3.0) * q;
  double complex s = cpow(27.0 * q * q + 4.0 * p * p * p, 1.0 / 2.0);
  double t = 6.0 * sqrt(3.0);
  double complex A = (r + s) / t;
  double complex B = (r - s) / t;
  double complex omega = (-1.0 + sqrt(3.0) * I) / 2.0;

  double complex cpowA = cpow(A, 1.0 / 3.0);
  double complex cpowB = cpow(B, 1.0 / 3.0);

  double complex x1 = -c1 / 3.0 - cpowA - cpowB;
  double complex x2 = -c1 / 3.0 - omega * cpowA - omega * omega * cpowB;
  double complex x3 = -c1 / 3.0 - omega * omega * cpowA - omega * cpowB;

  if (cimag(x1) < EPSILON && cimag(x2) < EPSILON && cimag(x3) < EPSILON)
  {
    printf("Eigenvalues are all real:\n");
    printf("Eigenvalue 1: %lf\n", creal(x1));
    printf("Eigenvalue 2: %lf\n", creal(x2));
    printf("Eigenvalue 3: %lf\n", creal(x3));
  }
  else
  {
    printf("Eigenvalues has complex values.\n");
  }
}