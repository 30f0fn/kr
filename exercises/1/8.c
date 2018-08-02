#include <stdio.h>

/* count blanks, tabs and newlines */

main() {
  int blanks = 0;
  int tabs = 0;
  int newlines = 0;

  for (int c = getchar(); c != EOF; c = getchar()) {
    if (c == ' ') blanks++;
    if (c == '\t') tabs++;
    if (c == '\n') newlines++;
  }
  printf("I read the file.  It contains\n...%d blanks,\n...%d tabs, and\n...%d newlines.", blanks, tabs, newlines);
}
