# include <stdio.h>
# define TABWIDTH 8

/* detab.  replaces tabs in the input with the proper number of spaces to the next tab stop.
say that a tab stop is every TABWIDTH spaces.
suppose line s[] has length len, and contains no tabs.  
we replace s+'\t' with 5 - (len % 5) spaces.
*/

int main() {

  int len = 0;
  char c;

  while ((c = getchar()) != EOF) {
    if (c == '\t') {
      for (int i = 0; i < 5 - (len % 5); i++)
        putchar(' ');// put 5 - (len % 5) spaces
    }
    if (c == '\n') {
      putchar(c);
      len = 0;// put c, reset len;
    }
    else putchar(c);
  }
  
}
