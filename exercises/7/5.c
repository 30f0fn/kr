# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include <stdarg.h>

# include "kr-resources.h"

/*
modify the calculator implementation from exercise 4.3by using scanf or sscanf for input and number conversion.

getop() reads standard input.  if it reads an operator, return it; otherwise it should be reading a number, so store it as char array and return NUMBER.
*/



# define MAXOP 100
# define NUMBER '0' // for main, getop
# define MAXVAL 100 // maximum depth of val stack, for push and pop
# define MAX_LINE 100


int sp = 0; // next free stack position
double val[MAXVAL]; // val stack

void push(double f) {
  if(sp < MAXVAL) {
    val[sp++] = f;
    /* printf("pushed %.2g\n", f); */
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



// getop: get next operator-or-numeric-operand; then return the operator, or read and store a number, returning a signal that an operand was found.
// note that according to the calc interface, a scanned string is an operator iff it has length 1 and its entry is neither a digit nor a decimal.
// this solution runs through initial whitespace looking for newline; it returns newline if it finds it, else pushes back first nonwhitespace character.  seems inefficient, but sinec scanf skips whitespace (including newlines) I don't know how else to check for newline. 
 
int getop(float *number) {
  char s[MAXOP];
  char c;
  while(isspace(c = getchar()))
    if(c == '\n')
      return c;
  ungetc(c, stdin);
  scanf("%s", s);
  if(s[1] == '\0' && !isdigit(s[0])) {
    return s[0];
  }
  sscanf(s, "%f", number);
  return NUMBER;
}




// the calculator

int main() {

  char c;
  int type;
  double op2;
  float number;

  while((type = getop(&number)) != EOF) {
    /* printf("getop got %c\n", type); */
    switch(type) {
    case NUMBER:
      push(number);
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
      if(op2 < 0) {
        printf("sorry, negative modulus is undefined.\n");
        return -1;
      }
      double op1 = pop();
      if(op1 >= 0) 
        for( ; op1 > op2; op1 -= op2)
          ;
      else 
        for( ; op1 < 0; op1 += op2)
          ;
      push(op1);
      break;
    case '\n':
      printf("\t%.8g\n", pop());
      break;
    default:
      printf("error: unknown command %d\n", type);
      break;
    }
  }
  return 0;
}


