#include <stdio.h>
#include <stdlib.h>

void combine(int start, int depth, int max_depth, int *buff, int n)
{
  int i, j;
  if (depth == max_depth)
  {
    for (j = 0; j < max_depth; j++)
    {
      printf("%d", buff[j]);
    }
    printf("\n");
    return;
  }

  for (i = start; i <= n; i++)
  {
    buff[depth] = i;
    combine(i + 1, depth + 1, max_depth, buff, n);
  }
}

int main(int argc, char *argv[])
{
  int n, len;
  int *buff;

  n = atoi(argv[1]);
  buff = (int *)malloc(sizeof(int) * n);

  for (len = 1; len <= n; len++)
  {
    combine(1, 0, len, buff, n);
  }

  free(buff);
  return 0;
}