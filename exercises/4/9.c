# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>

/*
KR getch/ungetch don't handle EOF correctly.  Fix it.

I don't understand why it's incorrect.  Supposedly the problem is that EOF is defined to be -1, but buf[] is a char array.  still it seems possible to push back and EOF in buf[] and then pop it without trouble...?
*/



# define BUFSIZE 100 // for getch and ungetch

char buf[BUFSIZE]; // buffer for getch and ungetch
int bufp = 0; // next free position in buf

char getch(void) {
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
  if(bufp >= BUFSIZE) 
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}

void main() {
  printf("EOF: %d\n", EOF);
  ungetch(EOF);
  printf("pushed-back EOF: %d\n", getch());
}
