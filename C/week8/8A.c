#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_STACK 100

int stack[MAX_STACK];
int stack_top = 0;
char buf[100];

void error(char *f, char *s)
{
  fprintf(stderr, f, s);
  putc('\n', stderr);
  exit(1);
}

int push(int val)
{
  if (stack_top >= MAX_STACK)
    return 0;
  stack[stack_top++] = val;
  return 1;
}

int pop(int *val)
{
  if (stack_top <= 0)
    return 0;
  *val = stack[--stack_top];
  return 1;
}

int read_word(char buf[])
{
  int ch, k = 0;
  while (isspace(ch = getchar()) && ch != EOF)
    ;
  if (ch == EOF)
    return 0;
  buf[k++] = ch;
  while (!isspace(ch = getchar()) && ch != EOF)
    buf[k++] = ch;
  buf[k] = '\0';
  return 1;
}

int main()
{
  int d0, d1;
  while (read_word(buf))
  {
    if (isdigit(buf[0]))
    {
      if (push(atoi(buf)) == 0)
        error("stack full", NULL);
    }
    else if (buf[0] == 'p')
    {
      printf("%d\n", stack[stack_top - 1]);
    }
    else
    {
      if (pop(&d1) == 0)
        error("stack empty", NULL);
      if (pop(&d0) == 0)
        error("stack empty", NULL);
      switch (buf[0])
      {
      case '+':
        if (push(d0 + d1) == 0)
          error("stack full", NULL);
        break;
      case '-':
        if (push(d0 - d1) == 0)
          error("stack full", NULL);
        break;
      case '*':
        if (push(d0 * d1) == 0)
          error("stack full", NULL);
        break;
      default:
        error("illegal input %s", buf);
      }
    }
  }
  return 0;
}