#include <stdio.h>
#include <math.h>

void calculate_eigenvalues(double matrix[2][2]);

int main()
{
  double matrix[2][2];
  scanf("%lf %lf", &matrix[0][0], &matrix[0][1]);
  scanf("%lf %lf", &matrix[1][0], &matrix[1][1]);

  calculate_eigenvalues(matrix);
}

void calculate_eigenvalues(double matrix[2][2])
{
  double a = matrix[0][0];
  double b = matrix[0][1];
  double c = matrix[1][0];
  double d = matrix[1][1];
  double trace = a + d;
  double determinant = a * d - b * c;
  double discriminant = trace * trace - 4 * determinant;

  if (discriminant < 0)
  {
    printf("Eigenvalues are complex.\n");
    return;
  }

  double sqrt_discriminant = sqrt(discriminant);
  double eigenvalue1 = (trace + sqrt_discriminant) / 2;
  double eigenvalue2 = (trace - sqrt_discriminant) / 2;

  printf("Eigenvalues are real:\n");
  printf("Eigenvalue 1: %lf\n", eigenvalue1);
  printf("Eigenvalue 2: %lf\n", eigenvalue2);
}