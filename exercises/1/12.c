#include <stdio.h>

/* print the output, one word per line */

int main() {

  int lastWasBlank = 0;
  
  for (int c = getchar(); c != EOF; c = getchar()) {
    if (c != ' ' && c != '\n' && c != '\t') {
      putchar(c);
      lastWasBlank = 0;
    }
    else if (!lastWasBlank) {
      printf("\n");
      lastWasBlank = 1;
    }
  }
}

