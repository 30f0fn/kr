# include <stdio.h>

/*
 converts upper case letters to lower case, 
with a conditional expression instead of if-else.
 */

char lower(char c) {
  return ('A' <= c && c <= 'Z') ? (c +('a' - 'A')) : c;
}

int main(int argc, char* argv[]) {
  char c;
  for (int i = 0; (c = argv[1][i]) != '\0'; i++)
    {
    putchar(lower(c));
    }
  putchar('\n');
}
