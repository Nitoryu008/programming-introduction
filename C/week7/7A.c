#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int cost[20][20];
int s[20], best[20];
int min_cost = INT_MAX;
int n;

void perm(int k, int n, int a[])
{
  int i, t, c;
  if (k == n)
  {
    c = 0;
    for (i = 1; i < n; i++)
    {
      c += cost[a[i - 1]][a[i]];
    }
    c += cost[a[n - 1]][a[0]];

    if (c < min_cost)
    {
      min_cost = c;
      for (i = 0; i < n; i++)
      {
        best[i] = a[i];
      }
    }
  }
  else
  {
    for (i = k; i < n; i++)
    {
      t = a[k];
      a[k] = a[i];
      a[i] = t;
      perm(k + 1, n, a);
      t = a[k];
      a[k] = a[i];
      a[i] = t;
    }
  }
}

int main(int argc, char *argv[])
{
  FILE *fp;
  int i, j;

  if ((fp = fopen(argv[1], "r")) == NULL)
  {
    fprintf(stderr, "can't open %s\n", argv[1]);
    exit(1);
  }

  fscanf(fp, "%d", &n);
  for (i = 0; i < n; i++)
  {
    for (j = 0; j < n; j++)
    {
      fscanf(fp, "%d", &cost[i][j]);
    }
  }
  fclose(fp);

  for (i = 0; i < n; i++)
    s[i] = i;

  perm(0, n, s);

  printf("%d: ", min_cost);
  for (i = 0; i < n; i++)
  {
    printf("%d ", best[i]);
  }
  printf("%d\n", best[0]);

  return 0;
}