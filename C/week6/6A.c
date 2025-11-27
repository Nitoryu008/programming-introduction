#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1024
#define L 256

struct word_pair {
  char *w[2];
} a[N];

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

int cmp(const void *p, const void *q) {
  int v;
  struct word_pair *a = (struct word_pair *)p;
  struct word_pair *b = (struct word_pair *)q;

  if ((v = strcmp(a->w[0], b->w[0])) == 0) {
    return strcmp(b->w[1], a->w[1]);
  } else
    return v;
}

int main(int argc, char *argv[]) {
  int i, k = 0;
  FILE *fp;
  char buf[L];

  for (i = 1; i < argc; i++) {
    if ((fp = fopen(argv[i], "r")) == NULL) {
      fprintf(stderr, "can't open %s\n", argv[i]);
      continue;
    }

    while (1) {
      if (!get_word(fp, buf))
        break;
      a[k].w[0] = (char *)malloc(strlen(buf) + 1);
      if (a[k].w[0] == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
      }
      strcpy(a[k].w[0], buf);

      if (!get_word(fp, buf)) {
        break;
      }
      a[k].w[1] = (char *)malloc(strlen(buf) + 1);
      if (a[k].w[1] == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
      }
      strcpy(a[k].w[1], buf);

      k++;
      if (k >= N) {
        fprintf(stderr, "Array limit reached\n");
        break;
      }
    }
    fclose(fp);
  }

  qsort(a, k, sizeof(struct word_pair), cmp);

  for (i = 0; i < k; i++) {
    printf("%s %s\n", a[i].w[0], a[i].w[1]);

    free(a[i].w[0]);
    free(a[i].w[1]);
  }

  return 0;
}
