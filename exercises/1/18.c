# include <stdio.h>
# define MAXWHITES 10


/*******
remove trailing blanks and tabs from each line of input, deleting lines which are entirely blank 
- set lineBlank to true
- accumulate consecutive blanks/tabs
- upon reaching nonwhitespace character: print and clear whitespace register, set lineBlank to false, then print the char
- upon reaching newline character: clear the whitespace register, print a newline, and set lineBlank to true
- to build whitespace array, check if the array is full and and print a warning if it is
*******/


int main() {

  int numWhites = 0;
  int whites[MAXWHITES];
  int lineBlank = 1;

  char c;
  for (c = getchar(); c != EOF; c = getchar()) {
    // three cases: c is blank, newline, or nonwhitespace
    if (c == '\n') {
      numWhites = 0;
      if (!lineBlank) {
        /* printf("Line was not blank!"); */
        putchar(c);
      }
      lineBlank = 1;
    }
    if (c == ' ' || c == '\t') {
      if (numWhites < MAXWHITES - 1)
        if (c == ' ')
          whites[numWhites++] = '-';
        else
          whites[numWhites++] = '~';
      else
        printf("\nExceeded whitespace max of %d!\n", MAXWHITES);
    }
    else if (20 < c && c < 127) // range of nonwhitespace
      {
      // c is nonwhitespace
      for (int i=0; i<numWhites; i++)
        putchar(whites[i]);
      putchar(c);
      /* printf("I thought %c was nonwhitespace and printed it", c); */
      numWhites = 0;
      lineBlank = 0;
    }
  }
}
