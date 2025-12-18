#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK 100

int stack_k[MAX_STACK];
int stack_i[MAX_STACK];
int top = 0;

void push_state(int k, int i)
{
  stack_k[top] = k;
  stack_i[top] = i;
  top++;
}

int pop_state(int *k, int *i)
{
  if (top == 0)
    return 0;
  top--;
  *k = stack_k[top];
  *i = stack_i[top];
  return 1;
}

int main(int argc, char *argv[])
{
  int n, i, k, t;
  int *a;

  if (argc < 2)
  {
    printf("Usage: %s n\n", argv[0]);
    return 1;
  }
  n = atoi(argv[1]);

  a = (int *)malloc(sizeof(int) * n);
  for (i = 0; i < n; i++)
    a[i] = i + 1;

  k = 0;
  i = 0;

START:
  if (k == n)
  {
    for (i = 0; i < n; i++)
      printf("%d ", a[i]);
    putchar('\n');
    goto RETURN_POINT;
  }

  i = k;

LOOP:
  if (i < n)
  {
    t = a[k];
    a[k] = a[i];
    a[i] = t;

    push_state(k, i);
    k = k + 1;
    goto START;

  RESUME:
    pop_state(&k, &i);

    t = a[k];
    a[k] = a[i];
    a[i] = t;

    i++;
    goto LOOP;
  }

RETURN_POINT:
  if (top > 0)
    goto RESUME;

  free(a);
  return 0;
}