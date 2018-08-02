# include <stdio.h>
# include <ctype.h>
# define STR_MAX 100

/* 
pointer-based versions of some previously introduced functions.
*/


// read line from stdin into s, return its length.
int getlinep(char *s, int lim) {
  char c;
  int i = 0;
  while((*(s+i) = (c = getchar())) != '\n' && c != EOF && i++ < lim)
    ;
  if(c == '\n') 
    *(s+i++) = c;
  *(s+i) = '\0';
  return i;
}

// convert s to integer and return it
int atoip(char *s) {
  int n = 0;
  int sign = (*s == '-') ? -1 : 1;
  if(*s == '+' || *s == '-')
    s++;
  while(isdigit(*s))
    n = 10 * n + (*s++ - '0');
  n *= sign;
  return n;
}
 

void reversep(char *s) {
  char *last;
  for(last = s; *last; last++)
    ; // *last == 0
  char temp;
  while(s < --last) {
    temp = *s;
    *s++ = *last;
    *last = temp;
  }
}


// convert int n to string and store it in s
// do it backwards, then reverse s
void itoap(int n, char *s) {
  char *s1 = s;
  for(*s++ = n % 10 + '0'; n /= 10; *s++ = n % 10 + '0')
    ;
  *s = '\0';
  reversep(s1);
}


// return index of t in s, or -1
// scan through s1 = s and t
// upon nonmatch, increment s and rescan
// else, return s
int strindexp(char *s, char *t) {
  char *s1, *t1;
  while(++*s) {
    for(s1 = s++, t1 = t; *t1 && *s1++ == *t1++; )
      ;
    if(!*t1) // K&R put t1 > t here?
      return s1 - s;
  }
  return -1;
}






// getop: get next operator-or-numeric-operand; return the operator, or store the operand in s and return a signal that an operand was found.  exercise 4.3 adds provision for negative numbers

#define NUMBER 1

int getch(void);
int peekch(void);
void ungetch(int);


int getopp(char s[]) {
  int i, c;
  while((*s = c = getch()) == ' ' || c == '\t')
    ; // skips initial whitespace, stores first nonwhitesp char at s[0]
  *(s+1) = '\0';
  if(!isdigit(c) && c != '.' && c != '-')
    return c; // not a number; hopefully an operator
  if(c == '-') {
    char next = peekch();
    if(!isdigit(next)) 
      return c;
    /* else */
      /* c = getchar(); // s[0] is unary - */
  }
  /* printf("s: %s\n", s); */
  /* if we've gotten to this point, we should be reading a number*/
  /* i = 0; // why not i = 1, then i++ below?  maybe no difference */
  if(isdigit(*s) || *s == '-')
    while(isdigit(*++s = c = getch()))
      ; // stores all subsequent digits, and the next nondigit char, at s[1:]
  if(c == '.')
    while(isdigit(*++s = c = getch()))
      ; // store fractional part in s; '.' was recorded in previous case
  *++s = '\0';
  if (c != EOF)
    ungetch(c);
  /* printf("%s", s); */
  return NUMBER; // signal that a number was found
}



# define BUFSIZE 10

char buf[BUFSIZE]; // buffer for getch and ungetch
int bufp = 0; // next free position in buf

int getch(void) {
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
  if(bufp >= BUFSIZE) 
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}

int peekch(void) {
  char c = getch();
  ungetch(c);
  return c;
}




int main(int argc, char* argv[]) {
  int m = **++argv;
  switch(m) {
  case '1': {
    char s[STR_MAX];
    int l = getlinep(s, STR_MAX);
    printf("getlinep got string %s and found length %d\n", s, l);
    break; }
  case '2': {
    char *s = *++argv;
    int l = atoip(s);
    printf("atoip got string %s and returned int %d\n", s, l);
    break; }
  case '3': {
    char *s = *++argv;
    reversep(s);
    printf("reversep gives %s\n", s);
    break; }
  case '4': {
    char *s = *++argv;    
    int n = atoip(s);
    itoap(n, s);
    printf("itoap got int %d and returned string %s\n", n, s);
    break; }
  case '5': {
    char *s = *++argv;    
    char *t = *++argv;    
    int n = strindexp(s, t);
    printf("strindexp found string %s to occur in string %s at index %d\n", s, t, n);
    break; }
  case '6': {
    char s[STR_MAX];
    getopp(s);
  }
  default:
    printf("command not recognized :(");
  }
}
