#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_word(FILE *fp, char buf[])
{
  int ch, k = 0;
  while (!isalpha(ch = getc(fp)) && ch != EOF)
    ;
  if (ch == EOF)
    return 0;

  buf[k++] = ch;
  while ((ch = getc(fp)) != EOF && isalpha(ch))
    buf[k++] = ch;
  buf[k] = '\0';
  return 1;
}

int main(int argc, char *argv[])
{
  struct cell
  {
    char *word;
    int count;
    struct cell *next;
  } *list = NULL, *p;

  int i;
  FILE *fp;
  char buf[1024];

  for (i = 1; i < argc; i++)
  {
    if ((fp = fopen(argv[i], "r")) == NULL)
    {
      fprintf(stderr, "cannot open %s\n", argv[i]);
      exit(1);
    }
    while (get_word(fp, buf) != 0)
    {
      for (p = list; p != NULL; p = p->next)
      {
        if (strcmp(buf, p->word) == 0)
        {
          p->count++;
          goto next;
        }
      }

      p = (struct cell *)malloc(sizeof(struct cell));
      p->word = (char *)malloc(strlen(buf) + 1);
      strcpy(p->word, buf);
      p->count = 1;
      p->next = list;
      list = p;

    next:;
    }

    fclose(fp);
  }

  struct cell *sorted_list = (struct cell *)malloc(sizeof(struct cell));
  sorted_list->next = NULL;

  while (list != NULL)
  {
    p = list;
    list = list->next;
    struct cell *q = sorted_list;

    while (q->next != NULL)
    {
      if (q->next->count < p->count)
      {
        p->next = q->next;
        q->next = p;
        goto sorted;
      }

      q = q->next;
    }

    q->next = p;
    p->next = NULL;

  sorted:;
  }

  for (p = sorted_list->next; p != NULL; p = p->next)
    printf("%s %d\n", p->word, p->count);
}
