/*
the floating point analog of getint()
*/

# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
 
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
  /* putchar(c); */
  *pn *= sign;
  if(c != EOF)
    ungetch(c);
   return(c);
}





int getfloat(float *pn) {
  int  c, sign;
  while(isspace(c = getch()))
        ;
  if(c != EOF && !isdigit(c) && c != '+' && c != '-') {
    ungetch(c);
    return 0;
  }
  sign = (c == '-') ? -1 : 1;
  if(c == '-' || c == '+')
    c = getch();
  *pn = 0;
  while(isdigit(c)) {
    flappend(pn, c);
    c = getch();
    /* printf("%f\n", *pn); */
  }
  if(c == '.') {
    int pow;
    for(pow = 1; isdigit(c = getch()); pow *= 10)
      flappend(pn, c);
    *pn /= pow;
  }
  if(c != EOF)
    ungetch(c);
  return(c);
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


void flappend(float *f, char c) {
  *f = 10 * *f + (c - '0');
}



int main(int argc, char* argv[]) {

  int t;
  float f;
  while((t = getfloat(&f)) != EOF) {
    if(t>0)
      printf("%f\n", f);
    else
      getchar();
  }

}
