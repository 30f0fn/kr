# include <stdio.h>
# include <ctype.h>

/*
fix the text treatment of '+' and '-'
*/

# define BUFSIZE 100 // for getch and ungetch



char getch(void);
void ungetch(int);
void flappend(float *, char);



int getint(int *pn) {
  int c, sign;
  while(isspace(c = getch()))
    ;
  if(!isdigit(c) && c != '-' && c != '+' && c != EOF) {
    ungetch(c);
    return 0;
  }
  sign = (c == '-') ? -1 : 1;
  if(c == '-' || c == '+') {
    char c0 = c;
    if(!isdigit(c = getch())) {
      ungetch(c);
      ungetch(c0);
      return 0;
    }
  }
  for(*pn = 0; isdigit(c); c = getch()) {  
    *pn = 10 * *pn + (c - '0');
  }
  /* printf("pn = %d\n", *pn); */
  /* putchar(c); */
  *pn *= sign;
  if(c != EOF)
    ungetch(c);
  return(c); // c is either -1 (i.e., EOF) or in ('0'...'9')
}




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




int main(int argc, char* argv[]) {

  int t;
  int n;
  char c;
  while((t = getint(&n)) != EOF) {
    if(t>0)
      printf("%d\n", n);
    else {
      c = getch();
      printf("skipping over %c\n", c); 
    }
  }
}

