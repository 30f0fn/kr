#include <stdio.h>

/* replace five consecutive spaces with a tab */

int main() {
  int spaceCounter = 0;
  for (char c = getchar(); c != EOF; c = getchar()) {
    if (c != ' ') {
      while (spaceCounter != 0) {
        printf("%c", ' ');
        spaceCounter--;
      }
      printf("%c", (char) c); 
    }
    else {
      if (spaceCounter < 4)
        spaceCounter++;
      else {
        printf("%c", '\t');
        spaceCounter = 0;
      }
    }
  }
}
