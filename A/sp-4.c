#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 100

void integral(char f[STR_SIZE]);

int main()
{
  char input[STR_SIZE];
  char output[STR_SIZE];

  printf("f(x) = \n");
  scanf("%s", input);
  integral(input);
}

void integral(char f[STR_SIZE])
{
  double coefficients[100];
  int exponents[100];
  int term_index = 0;
  char err_msg[] = "<Invalid Input>\n";
  char *p = strtok(f, "+");

  // input
  while (p != NULL)
  {
    while (isspace(*p))
    {
      p++;
    }

    char *num_end;
    double current_coeff = strtod(p, &num_end);

    if (num_end == p)
    {
      coefficients[term_index] = 1;
    }
    else
    {
      coefficients[term_index] = current_coeff;
      p = num_end;
    }

    char *x_pos = strstr(p, "x");
    if (x_pos != NULL)
    {
      if (*(x_pos + 1) == '\0' || strncmp(x_pos + 1, "**", 2) != 0)
      {
        exponents[term_index] = 1;
      }
      else
      {
        exponents[term_index] = (int)strtod(x_pos + 3, NULL);
      }
    }
    else
    {
      exponents[term_index] = 0;
    }

    term_index++;
    p = strtok(NULL, "+");
  }

  // integral
  for (int i = 0; i < term_index; i++)
  {
    exponents[i] += 1;
    coefficients[i] /= exponents[i];
  }

  // output
  double sum = 0;

  for (int j = 0; j < term_index; j++)
  {
    sum += coefficients[j];
  }

  printf("%f\n", sum);
}