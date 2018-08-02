# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>

/*
calculator from section 4.3.  added modulus operator to main(), and provision for negative numbers in getop();
*/



# define MAXOP 100
# define NUMBER '0' // for main, getop

# define MAXVAL 100 // maximum depth of val stack, for push and pop

# define BUFSIZE 100 // for getch and ungetch



int sp = 0; // next free stack position
double val[MAXVAL]; // val stack

void push(double f) {
  if(sp < MAXVAL) {
    val[sp++] = f;
    printf("pushed %.2g\n", f);
  }
  else
    printf("error! stack full, can't push %g\n", f);
}

double pop(void) {
  if(sp > 0) {
    return val[--sp];
  }
  else {
    printf("error! tried to pop empty stack\n");
    return 0.0;
  }
}


// getop: get next operator-or-numeric-operand; return the operator, or store the operand in s and return a signal that an operand was found.  exercise 4.3 adds provision for negative numbers

int getch(void);
int peekch(void);
void ungetch(int);


int getop(char s[]) {
  int i, c;
  while((s[0] = c = getch()) == ' ' || c == '\t')
    ; // skips initial whitespace, stores first nonwhitesp char at s[0]
  s[1] = '\0';
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
  i = 0; // why not i = 1, then i++ below?  maybe no difference
  if(isdigit(c) || c == '-')
    while(isdigit(s[++i] = c = getch()))
      ; // stores all subsequent digits, and the next nondigit char, at s[1:]
  if(c == '.')
    while(isdigit(s[++i] = c = getch()))
      ; // store fractional part in s; '.' was recorded in previous case
  s[i] = '\0';
  if (c != EOF)
    ungetch(c);
  /* printf("%s", s); */
  return NUMBER; // signal that a number was found
}



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

// the calculator

int main() {

  int type;
  double op2;
  char s[MAXOP];

  while((type = getop(s)) != EOF) {
    printf("getop got %c\n", type);
    switch(type) {
    case NUMBER:
      push(atof(s));
      break;
    case '+':
      push(pop() + pop());
      break;
    case '*':
      push(pop() * pop());
      break;
    case '-': 
      op2 = pop();
      push(pop() - op2);
      break;
    case '/':
      op2 = pop();
      push(pop() / op2);
      break;
    case '%':
      op2 = pop();
      float op1 = pop();
      /* if(op2 < 0) { */
        /* printf("sorry, negative modulus is undefined.\n"); */
        /* return 0; */
      /* } */
      if(op1 > 0) 
        for (int i = 0; op1 >= op2 ; i++, op1 -= op2)
          ;
      else
        for(int i = 0; op1 < op2; i++, op1 += op2);
      push(op1);
      break;
    case '\n':
      printf("\t%.8g\n", pop());
      break;
    default:
      printf("error: unknown command %s\n", s);
      break;
    }
  }
  return 0;
}


