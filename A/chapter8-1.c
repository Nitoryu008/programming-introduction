#include <stdio.h>

int main()
{
  char str[100];
  scanf("%s", str);

  for (int i = 0; i < 99; i++)
  {
    if (str[i] == '\0')
    {
      break;
    }
    if (str[i - 1] == str[i])
    {
      str[i - 1] = '*';
      str[i] = '*';
    }
  }

  printf("%s\n", str);
}