#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N 1024

struct node
{
  char *word;
  int count;
  struct node *left;
  struct node *right;
};

struct node *alloc_node(char *word)
{
  struct node *p;

  p = (struct node *)malloc(sizeof(struct node));
  if (p == NULL)
  {
    fprintf(stderr, "malloc failed\n");
    exit(1);
  }

  p->word = (char *)malloc(strlen(word) + 1);
  if (p->word == NULL)
  {
    fprintf(stderr, "malloc failed\n");
    exit(1);
  }

  strcpy(p->word, word);
  p->count = 1;
  p->left = NULL;
  p->right = NULL;

  return p;
}

void print_tree(struct node *p)
{
  if (p == NULL)
    return;

  if (p->left != NULL)
  {
    print_tree(p->left);
  }

  printf("%s %d\n", p->word, p->count);

  if (p->right != NULL)
  {
    print_tree(p->right);
  }
}

int get_word(FILE *fp, char buf[])
{
  int ch, k = 0;

  while (!isalpha(ch = getc(fp)) && ch != EOF)
    ;

  if (ch == EOF)
    return 0;

  buf[k++] = tolower(ch);

  while ((ch = getc(fp)) != EOF && isalpha(ch))
  {
    if (k < N - 1)
    {
      buf[k++] = tolower(ch);
    }
  }

  buf[k] = '\0';
  return 1;
}

void free_tree(struct node *p)
{
  if (p == NULL)
    return;
  free_tree(p->left);
  free_tree(p->right);
  free(p->word);
  free(p);
}

int main(int argc, char *argv[])
{
  int i, v;
  struct node *root = NULL;
  struct node *p;
  char buf[N];
  FILE *fp;

  if (argc < 2)
  {
    fprintf(stderr, "Usage: %s file1 file2 ... fileN\n", argv[0]);
    return 1;
  }

  for (i = 1; i < argc; i++)
  {
    if ((fp = fopen(argv[i], "r")) == NULL)
    {
      fprintf(stderr, "Error: Cannot open file %s\n", argv[i]);
      continue;
    }

    while (get_word(fp, buf) != 0)
    {

      if (root == NULL)
      {
        root = alloc_node(buf);
      }
      else
      {
        p = root;

        for (;;)
        {
          v = strcmp(buf, p->word);

          if (v == 0)
          {
            p->count++;
            break;
          }
          else if (v < 0)
          {
            if (p->left == NULL)
            {
              p->left = alloc_node(buf);
              break;
            }
            else
            {
              p = p->left;
            }
          }
          else
          {
            if (p->right == NULL)
            {
              p->right = alloc_node(buf);
              break;
            }
            else
            {
              p = p->right;
            }
          }
        }
      }
    }

    fclose(fp);
  }

  print_tree(root);
  free_tree(root);

  return 0;
}