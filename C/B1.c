#include <stdio.h>
#include <string.h>

char count[128] = {0};

int main(int argc, char *argv[])
{
  int maxi, maxlen;
  for (int i = 1; i < argc; i++)
  {
    int len = strlen(argv[i]);
    if (len > maxlen)
    {
      maxi = i;
      maxlen = len;
    }
  }

  char count[128] = {0};
  char *maxlenstr = argv[maxi];
  for (int j = 0; j < maxlen; j++)
  {
    count[maxlenstr[j]]++;
  }

  char maxk = 0;
  for (int k = 1; k < 128; k++)
  {
    if (count[k] > count[maxk])
    {
      maxk = k;
    }
  }

  printf("%c %d\n", maxk, count[maxk]);
}