# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>

/*
reorganize the calculator to use getline().  now getch() and ungetch() will not be necessary.

main simply interleaves getline() with a new function processline().  processline() contains all the material from main() except it exits upon reading '\n' (and, as with main, popping and printing).

*/


# define MAXLINE 100

# define MAXOP 100
# define NUMBER '0' // for main, getop

# define MAXVAL 100 // maximum depth of val stack, for push and pop





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


// getop: get next operator-or-numeric-operand; return the operator, or store the operand in s and return a signal that an operand was found.  exercise 4.3 adds provision for negative numbers



// pos ranges over position in line
// i ranges over positions in s

char line[MAXLINE];
int pos = 0;

int getop(char s[]) {
  /* printf("getting op at pos %d from %s\n", pos, line); */
  int i, c;
  while((s[0] = c = line[pos++]) == ' ' || c == '\t')
    /* printf("skipping whitespace\n"); */
    ; // skips initial whitespace, stores first nonwhitesp char at s[0]
  s[1] = '\0';
  if(!isdigit(c) && c != '.' && c != '-') {
    /* printf("this case?! c = %d as digit, c = '%c' as c\n", c); */
    return c; // not a number; hopefully an operator    
  }
  if(c == '-') {
    char next = line[pos+1];
    if(!isdigit(next)) 
      return c;
  }
  /* printf("s: %s\n", s); */
  /* if we've gotten to this point, we should be reading a number*/
  i = 0; // why not i = 1, then i++ below?  maybe no difference
  if(isdigit(c) || c == '-')
    while(isdigit(s[++i] = c = line[pos++]))
      ; // stores all subsequent digits, and the next nondigit char, at s[1:]
  if(c == '.')
    while(isdigit(s[++i] = c = line[pos++]))
      ; // store fractional part in s; '.' was recorded in previous case
  s[i] = '\0';
  /* printf("getop returning number %s\n", s); */
  return NUMBER; // signal that a number was found
}



void processline() {

  printf("processing line %s\n", line);
  int type;
  double op2;
  char s[MAXOP];

  pos = 0;


  /* printf("pos is %d", pos); */

  while((type = getop(s)) != EOF && type != '\n' && type != 0) {
    /* printf("getop got type %c\n", type); */
    switch(type) {
    case NUMBER:
      push(atof(s));
      /* printf("s=%f\n", atof(s)); */
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
    default:
      printf("error: unknown command %s\n", s);
      break;
    }
  }
  if(type == '\n' || type == EOF)
    printf("\t%.8g\n", pop());
  return;
}



/* getline:  get line into s, return length */
int getLine(char s[], int lim)
{
  
  /* printf("getting line %s\n", line); */
  int c, i;

  i = 0;
  while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
    s[i++] = c;
  if (c == '\n')
    s[i++] = c;
  s[i] = '\0';

  return i;
}




// the calculator

int main() {
  

  /* getLine(line, MAXLINE); */
  /* printf("getLine put %s into line\n", line); */
  /* processline(line); */

  
while(getLine(line, MAXLINE) > 0) {
    /* printf("%s\n", line); */
    processline(line);
  }

  return 0;
}


