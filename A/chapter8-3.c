#include <stdio.h>

int main()
{
  int m[2][2] = {{6, 1}, {5, 1}};
  int u[2][2] = {{1, -1}, {2, -2}};
  int v[2][2];

  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      v[i][j] = m[i][0] * u[0][j] + m[i][1] * u[1][j];
    }
  }

  printf("V=\n%d %d\n%d %d\n", v[0][0], v[0][1], v[1][0], v[1][1]);
}