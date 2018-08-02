#include <stdio.h>

/*
Prints arbitrary input in a sensible way.  Print non-graphic characters in octal or hexadecimal, and break non-text lines.

Non-graphic characters have codes between 0-31 or 127.

Local custom is...

separate characters with newline.  print graphic characters using putchar.  for nongraphic, print octal representation surrounded by angle brackets.  precede input angle brackets with backslash; precede backslash with backslash.
*/

int main(int argc, char *argv[]) {
  char c;
  int len = 0;
  /* putchar('\n'); */
  while((c = getchar())!=EOF) {
    if(c == '<' || c == '>' || c == '\\') { //escape
      /* printf("read escape\n"); */
      printf("\\%c", c);
    }
    else if(c == 137 || 0 <= c && c <= 32) { //nongraphic
      /* printf(" read nongraphic\n"); */
      printf("<%o>", c);
    }
    else {
      /* printf("read graphic\n"); */
      printf("%c", c);
    }
    if(len++ == 40) {
      printf("\n");
      len = 0;
    }
  }
  putchar('\n');
}
