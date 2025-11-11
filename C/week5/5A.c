#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cell
{
  char *word;
  struct cell *next;
} *list = NULL;

int main(int argc, char *argv[])
{
  int i;
  FILE *fp;
  char buf[1024];
  struct cell *p, *q;

  for (i = 1; i < argc; i++)
  {
    fp = fopen(argv[i], "r");
    if (fp == NULL)
    {
      perror(argv[i]);
      continue;
    }

    while (fscanf(fp, "%1023s", buf) != EOF)
    {
      p = (struct cell *)malloc(sizeof(struct cell));
      if (p == NULL)
      {
        fprintf(stderr, "malloc error\n");
        exit(1);
      }
      p->word = (char *)malloc(strlen(buf) + 1);
      if (p->word == NULL)
      {
        fprintf(stderr, "malloc error\n");
        exit(1);
      }
      strcpy(p->word, buf);
      p->next = list;
      list = p;
    }
    fclose(fp);
  }

  for (p = list; p != NULL; p = p->next)
  {
    for (q = p->next; q != NULL; q = q->next)
    {
      if (strcmp(p->word, q->word) > 0)
      {
        char *temp = p->word;
        p->word = q->word;
        q->word = temp;
      }
    }
  }

  for (p = list; p != NULL; p = p->next)
  {
    printf("%s\n", p->word);
  }

  return 0;
}