#include <stdio.h>

/* replace strings of blanks with a single blank */

int main() {

  int lastWasBlank = 0;
  
  for (int c = getchar(); c != EOF; c = getchar()) {
    if (c != ' ') {
      putchar(c);
      lastWasBlank = 0;
    }
    else if (!lastWasBlank) {
      putchar(c);
      lastWasBlank = 1;
    }
  }
}

