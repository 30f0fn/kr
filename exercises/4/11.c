

# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>


/*

modify getop to make getch/ungetch unnecessary.  Hint: use a static internal variable.

a static internal variable retains its value across function executions, but it is only accessible within the function.  here, buf is static internal.

the problem solved by getch/ungetch:  if getop encounters a string of digits (or more generally (r'(0|(1-9)(0-9)?)(\.(0-9)+)?)), it needs to process this as a unit, so to keep consuming digits until it gets a nondigit.  If that nondigit is EOF, no problem.  But if it is e.g. '\n', then this needs to be 'pushed back' to the input stream, so that the stream presents to the next invocation of getop as though the character immediately following the string of digits had not been read. 

the idea of this exercise is to record any overconsumed digit in a buffer.  (the buffer is to be implemented by a static variable, buf, internal to getop.)  each invocation of getop must, in each invocation of getchar(), first check whether buf contains an interesting value.  if it does, it consumes this value as though it were returned by getch(), and then reassigns buf to EOF.  conversely, whenever a character gets overconsumed, it gets recorded in buf.  

Thus, getch is replaced by

- check if buf contains something interesting; if it does retain this and set buf to EOF, else do getchar

while ungetch(c) is replaced by 

- store c in buf.

syntactically, in a wellformed input, the only characters which can follow a number representation are space, newline, EOF.  it seems that either of space and EOF can be treated as the 'uninteresting' value.  Here, I will try using EOF.
 
invocations of getch:
- consuming initial whitespace and first nonwhitespace character
- reading number

invocation of ungetch:
- after reading number



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





int getop(char s[]) {

  static char buf = EOF;

  int i, c;
  if(buf == EOF || buf == ' ' || buf == '\t') {
    while(s[0] = (c = getchar()) == ' ' || c == '\t')
      ;
  }//nothing other than whitespace was pushed back
  else { // buf is neither EOF nor whitespace
    c = buf;
    buf = EOF;
  }

  printf("buf is %c\n", buf);
  printf("c is %c\n", c);

  
  // c is first nonwhitespace char; buf is either EOF or whitespace
  s[1] = '\0';
  if(!isdigit(c) && c!='.') {
    return c;
  }
  /* if we've gotten to this point, we should be reading a number*/
  i = 0; // why not i = 1, then i++ below?  maybe no difference
  if(isdigit(c)) {
    s[i] = c;
    while(isdigit(s[++i] = c = getchar()))
      ; // stores all subsequent digits, and the next nondigit char, at s[1:]
  }
  if(c == '.') {
    while(isdigit(s[++i] = c = getchar()))
      ; // store fractional part in s; '.' was recorded in previous case
  }
  s[i] = '\0';
  if (c != EOF)
    buf = c;
  /* printf("%s", s); */
  return NUMBER; // signal that a number was found
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
      printf("s = %s\n", s);
      push(atof(s));
      break;
    case '+':
      push(pop() + pop());
      break;
    case '*':
      push(pop() * pop());
      break;
    case '/':
      op2 = pop();
      push(pop() / op2);
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





