#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define L 256

struct cell {
  char *word;
  struct cell *next;
};

int get_word(FILE *fp, char buf[]) {
  int ch, k = 0;
  while (!isalpha(ch = getc(fp)) && ch != EOF)
    ;
  if (ch == EOF)
    return 0;
  buf[k++] = ch;
  while ((ch = getc(fp)) != EOF && isalpha(ch)) {
    buf[k++] = ch;
  }
  buf[k] = '\0';
  return 1;
}

struct cell *sort(struct cell *list, struct cell **tail) {
  struct cell *lt = NULL, *lt_tail = NULL;
  struct cell *eq = NULL, *eq_tail = NULL;
  struct cell *gt = NULL, *gt_tail = NULL;
  struct cell *p, *next_p;
  struct cell *key;

  if (list == NULL) {
    *tail = NULL;
    return NULL;
  }

  key = list;
  eq = key;
  eq_tail = key;

  p = list->next;
  key->next = NULL;

  while (p != NULL) {
    next_p = p->next;
    int cmp = strcmp(p->word, key->word);

    if (cmp < 0) {
      p->next = lt;
      lt = p;
    } else if (cmp == 0) {
      p->next = eq;
      eq = p;
    } else {
      p->next = gt;
      gt = p;
    }
    p = next_p;
  }

  struct cell *sorted_lt = NULL, *sorted_gt = NULL;
  struct cell *tail_lt = NULL, *tail_gt = NULL;

  if (lt != NULL) {
    sorted_lt = sort(lt, &tail_lt);
  }
  if (gt != NULL) {
    sorted_gt = sort(gt, &tail_gt);
  }

  struct cell *result_head = NULL;
  struct cell *current_tail = NULL;

  if (sorted_lt != NULL) {
    result_head = sorted_lt;
    tail_lt->next = eq;
  } else {
    result_head = eq;
  }

  struct cell *temp = eq;
  while (temp->next != NULL) {
    temp = temp->next;
  }
  eq_tail = temp;

  if (sorted_gt != NULL) {
    eq_tail->next = sorted_gt;
    current_tail = tail_gt;
  } else {
    eq_tail->next = NULL;
    current_tail = eq_tail;
  }

  *tail = current_tail;

  return result_head;
}

int main(int argc, char *argv[]) {
  int i;
  FILE *fp;
  char buf[L];
  struct cell *root = NULL;
  struct cell *p;

  for (i = 1; i < argc; i++) {
    if ((fp = fopen(argv[i], "r")) == NULL) {
      fprintf(stderr, "can't open %s\n", argv[i]);
      continue;
    }

    while (get_word(fp, buf)) {
      struct cell *new_cell = (struct cell *)malloc(sizeof(struct cell));
      if (new_cell == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
      }

      new_cell->word = (char *)malloc(strlen(buf) + 1);
      if (new_cell->word == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
      }
      strcpy(new_cell->word, buf);

      new_cell->next = root;
      root = new_cell;
    }
    fclose(fp);
  }

  struct cell *final_tail;
  root = sort(root, &final_tail);

  p = root;
  while (p != NULL) {
    printf("%s\n", p->word);
    p = p->next;
  }

  while (root != NULL) {
    p = root;
    root = root->next;
    free(p->word);
    free(p);
  }

  return 0;
}
