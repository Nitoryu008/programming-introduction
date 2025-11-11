#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
  char *word;
  int count;
  struct node *left;
  struct node *right;
};

void insert(struct node **p, char *word)
{
  if (*p == NULL)
  {
    *p = (struct node *)malloc(sizeof(struct node));
    if (*p == NULL)
    {
      fprintf(stderr, "malloc error\n");
      exit(1);
    }
    (*p)->word = (char *)malloc(strlen(word) + 1);
    if ((*p)->word == NULL)
    {
      fprintf(stderr, "malloc error\n");
      exit(1);
    }
    strcpy((*p)->word, word);
    (*p)->count = 1;
    (*p)->left = NULL;
    (*p)->right = NULL;
    return;
  }

  int cmp = strcmp(word, (*p)->word);
  if (cmp < 0)
  {
    insert(&((*p)->left), word);
  }
  else if (cmp > 0)
  {
    insert(&((*p)->right), word);
  }
  else
  {
    (*p)->count++;
  }
}

void swap_values(struct node *a, struct node *b)
{
  char *temp_word = a->word;
  int temp_count = a->count;
  a->word = b->word;
  a->count = b->count;
  b->word = temp_word;
  b->count = temp_count;
}

void sift(struct node *p)
{
  if (p == NULL)
    return;

  struct node *larger_child = NULL;

  if (p->left != NULL && p->right == NULL)
  {
    if (p->left->count <= p->count)
      return;
    larger_child = p->left;
  }
  else if (p->left == NULL && p->right != NULL)
  {
    if (p->right->count <= p->count)
      return;
    larger_child = p->right;
  }
  else if (p->left != NULL && p->right != NULL)
  {
    if (p->left->count > p->right->count)
    {
      larger_child = p->left;
    }
    else
    {
      larger_child = p->right;
    }
    if (larger_child->count <= p->count)
      return;
  }
  else
  {
    return;
  }

  if (larger_child != NULL)
  {
    swap_values(p, larger_child);
    sift(larger_child);
  }
}

void make_heap(struct node *p)
{
  if (p == NULL)
    return;
  if (p->left != NULL)
  {
    make_heap(p->left);
  }
  if (p->right != NULL)
  {
    make_heap(p->right);
  }
  sift(p);
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
  int i;
  FILE *fp;
  char buf[1024];
  struct node *root = NULL;

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
      insert(&root, buf);
    }
    fclose(fp);
  }

  if (root == NULL)
  {
    return 0;
  }

  make_heap(root);

  while (root->count > 0)
  {
    printf("%s %d\n", root->word, root->count);
    root->count = 0;
    sift(root);
  }

  free_tree(root);

  return 0;
}