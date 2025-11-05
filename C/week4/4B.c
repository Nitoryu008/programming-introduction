#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N 256

struct node_sub
{
  char *word;
  int count;
  struct node_sub *left;
  struct node_sub *right;
};

struct node_main
{
  char *word;
  struct node_sub *root;
  struct node_main *left;
  struct node_main *right;
};

struct node_sub *alloc_node_sub(char *word)
{
  struct node_sub *p;
  p = (struct node_sub *)malloc(sizeof(struct node_sub));
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

struct node_main *alloc_node_main(char *word)
{
  struct node_main *p;
  p = (struct node_main *)malloc(sizeof(struct node_main));
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
  p->root = NULL;
  p->left = NULL;
  p->right = NULL;
  return p;
}

void print_tree_sub(struct node_sub *p)
{
  if (p == NULL)
    return;
  if (p->left != NULL)
  {
    print_tree_sub(p->left);
  }
  printf(" %s %d", p->word, p->count);
  if (p->right != NULL)
  {
    print_tree_sub(p->right);
  }
}

void print_tree_main(struct node_main *p)
{
  if (p == NULL)
    return;
  if (p->left != NULL)
  {
    print_tree_main(p->left);
  }
  printf("%s:", p->word);
  print_tree_sub(p->root);
  printf("\n");
  if (p->right != NULL)
  {
    print_tree_main(p->right);
  }
}

void free_tree_sub(struct node_sub *p)
{
  if (p == NULL)
    return;
  free_tree_sub(p->left);
  free_tree_sub(p->right);
  free(p->word);
  free(p);
}

void free_tree_main(struct node_main *p)
{
  if (p == NULL)
    return;
  free_tree_main(p->left);
  free_tree_main(p->right);
  free_tree_sub(p->root);
  free(p->word);
  free(p);
}

int get_word_pair(FILE *fp, char buf[2][N])
{
  int i, ch, k;

  for (i = 0; i < 2; i++)
  {
    while (isspace(ch = getc(fp)) && ch != '\n' && ch != EOF)
      ;

    if (ch == EOF)
      return 0;
    if (ch == '\n')
      return 0;

    k = 0;
    buf[i][k++] = tolower(ch);

    while (!isspace(ch = getc(fp)) && ch != EOF)
    {
      if (k < N - 1)
      {
        buf[i][k++] = tolower(ch);
      }
    }
    buf[i][k] = '\0';

    if (ch == EOF)
    {
      return (i == 1);
    }

    if (ch == '\n')
    {
      ungetc(ch, fp);
      if (i == 0)
        return 0;
    }
  }

  while ((ch = getc(fp)) != '\n' && ch != EOF)
    ;

  return 1;
}

void add_to_sub_tree(struct node_sub **root_sub, char *word)
{
  struct node_sub *p;
  int v;

  if (*root_sub == NULL)
  {
    *root_sub = alloc_node_sub(word);
    return;
  }

  p = *root_sub;
  for (;;)
  {
    v = strcmp(word, p->word);
    if (v == 0)
    {
      p->count++;
      break;
    }
    else if (v < 0)
    {
      if (p->left == NULL)
      {
        p->left = alloc_node_sub(word);
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
        p->right = alloc_node_sub(word);
        break;
      }
      else
      {
        p = p->right;
      }
    }
  }
}

int main(int argc, char *argv[])
{
  int i, v;
  struct node_main *root = NULL;
  struct node_main *p_main;
  char buf[2][N];
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

    while (get_word_pair(fp, buf) != 0)
    {
      if (root == NULL)
      {
        root = alloc_node_main(buf[0]);
        p_main = root;
      }
      else
      {
        p_main = root;
        for (;;)
        {
          v = strcmp(buf[0], p_main->word);
          if (v == 0)
          {
            break;
          }
          else if (v < 0)
          {
            if (p_main->left == NULL)
            {
              p_main->left = alloc_node_main(buf[0]);
              p_main = p_main->left;
              break;
            }
            else
            {
              p_main = p_main->left;
            }
          }
          else
          {
            if (p_main->right == NULL)
            {
              p_main->right = alloc_node_main(buf[0]);
              p_main = p_main->right;
              break;
            }
            else
            {
              p_main = p_main->right;
            }
          }
        }
      }

      add_to_sub_tree(&(p_main->root), buf[1]);
    }

    fclose(fp);
  }

  print_tree_main(root);
  free_tree_main(root);

  return 0;
}