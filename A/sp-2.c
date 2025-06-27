#include <stdio.h>

double integral(double a, double b);
double f(double x);

double main()
{
  double a = 0, b = 2;

  printf("integral from 0 to 2 of x^3 dx = %f\n", integral(a, b));
}

double integral(double a, double b)
{
  int n = 100000;
  double h = (b - a) / n;
  double sum = 0.0;

  for (int i = 0; i < n; i++)
  {
    double x_1 = a + i * h;
    double x_2 = a + (i + 1) * h;

    sum += (f(x_1) + f(x_2)) * h / 2;
  }
  return sum;
}

double f(double x)
{
  return x * x * x;
}