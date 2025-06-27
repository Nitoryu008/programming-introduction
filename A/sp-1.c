#include <stdio.h>

int factorial(int n);

int main()
{
  for (int i = 1; i < 11; i++)
  {
    printf("%d! = %d\n", i, factorial(i));
  }
}

int factorial(int n)
{
  if (n <= 1)
  {
    return 1;
  }

  return n * factorial(n - 1);
}