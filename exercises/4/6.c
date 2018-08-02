# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include <math.h>



/*
calculator from section 4.3.  commands to handle variables with numerical subscript, together with value assignments using '='.  Automatically store the most recently printed value in the variable 'z'.

variables to abbreviate closed-form expressions.  so when = is read, pop the past two items.  If the second-popped item is a variable of index i, set variables[i] = u; then subsequently whenever i is encountered (except in the LHS of assignment), evaluate it as u.

a variable is denoted by a v followed by base-10 numeral; store its value in the corresponding position of a dedicated array.  

to implement this, getop gets another return signal, VARIABLE, and another return case '='.  Analogously to the NUMBER case, getop records the index of the variable in s[].  

As for main, we need to elaborate the push and pop operations.  

when main gets a variable from getop, there are two cases.  
(i) the variable is LHS of an assignment
(ii) otherwise.
in the second case, it would be enough just to look it up in var[], then push the result onto the stack.  In the first case however, we need to store the index in order later to store its assigned value in var[].

so, we need to store the indices for later handling.  These can't just be pushed onto the val stack, because they'll look like ordinary values.  So instead, maintain a stack of variables valv, alongside the stack val of doubles.  When a variable is read, push NAN onto val[] and push the index onto valv[].  Conversely, when main pops from the val stack and returns NAN, we know we're popping a variable; since now the relevant context is available, we either carry out the assignment with var, or retrieve the value from var accordingly.

*/



# define MAXOP 100
# define NUMBER '0' // for main, getop
# define VARIABLE '1' // for main, getop, per exercise 4.6

# define MAXVAL 100 // maximum depth of val stack, for push and pop
# define MAXIND 100 // maximum depth of vind stack, per exercise 4.6

# define BUFSIZE 100 // for getch and ungetch


int sp = 0; // next free stack position
int vsp = 0; // next free vstack position, per 4.6
double val[MAXVAL]; // val stack
int vind[MAXIND]; // per 4.6
double var[MAXIND];

double last_printed; // stores last printed value, recalled by user with 'z'

void vpush(); // called upon reading a variable
int vpop(); // called upon reading =
void push();
double pop(); // enhanced for 4.6
double subpop();

// vind handling in parallel to val, per 4.6 

// push the index onto vind, and push NAND onto val
void vpush(double f) {
  int ff = (int) f;
  if(vsp < MAXIND) {
    vind[vsp++] = ff;
    push(NAN);
    printf("pushed index %d to vind stack\n", ff);
  }
  else
    printf("error! vind stack full, can't push %g\n", f);
}

// pop the vind stack, and delete top entry of val (which should be NAN)
int vpop(void) {
  if(vsp > 0) {
    double f;
    if(!isnan)
      printf("error! can only assign value to a variable, but %f is not a variable\n", f);
    return vind[--vsp];
  }
  else {
    printf("error! tried to pop empty stack vind\n");
    return 0.0;
  }
}


// val handling

void push(double f) {
  if(sp < MAXVAL) {
    val[sp++] = f;
    printf("pushed %5.2g\n", f);
  }
  else
    printf("error! stack full, can't push %g\n", f);
}

// the original pop(); called by vpop() to keep sync
double subpop(void) {
  if(sp > 0) {
    return val[--sp];
  }
  else {
    printf("error! tried to pop empty stack\n");
    return 0.0;
  }
}


// enhanced for 4.6
double pop(void) {
  if(sp > 0) {
    double f = val[--sp];
    if(isnan(f)) {
      int i = vpop();
      double ret = (i >= 0) ? var[i] : - var[-i];
    }
  }
  else {
    printf("error! tried to pop empty stack\n");
    return 0.0;
  }
}


void print() {
  double temp[sp];
  int len = sp;
  while(sp > 0) {
    temp[sp-1] = pop();
  }
  for(int i = 0; i < len; i++) {
    printf("%4.4g ", temp[i]);
    push(temp[i]);
  }
}

// getop: get next operator-or-numeric-operand; return the operator, or store the operand in s and return a signal that an operand was found.  exercise 4.3 adds provision for negative numbers

// for 4.6, introduce 

int getch(void);
int peekch(void);
void ungetch(int);


int getop(char s[]) {
  int i, c, retval;
  while((c = getch()) == ' ' || c == '\t')
    ; // skips initial whitespace
  if(!isdigit(c) && c != '.' && c != '-' && c != 'v') {
    /* printf("getop is about to return c = '%c'\n", c); */
    // not a numeral, a variable, or a subtraction; 
    return c;
  }
  if(c == '-') {
    char next = peekch();
    if(!isdigit(next) && next != 'v' && next != '-')
      // then we are in subtraction, do as above
      return c;
  }
  ungetch(c);
  /*
    now we are looking at something of the form r's*v?(0-9)*'
    i think the cleanest thing to do is simply to store the whole token in s, 
    then unpack it in main. 
    just make sure it does have this form, store a value in s,
    and return the appropriate signal.
    we do delete duplicate -s, so that...
    the value stored in s has the form r'-?v?(0-9)*'
  */
  for(i = 0, s[0] = '-'; (c = getch()) == '-'; i = 1 - i)
    ; // s[0] is '-'; if the number of -s is even then i is 0; else i is 1
  if(c == 'v') {
    while(isdigit(s[i++] = c = getch()))
      ;
    retval = VARIABLE;
  }
  else {
    while(isdigit(s[i] = c)) {
      /* printf("c = %c; i = %d\n", c, i); */
      i++;
      c = getch();
    }
    if(c == '.') {
      s[i++] = c;
      while(isdigit(s[i++] = c)) {
        c = getch();
      }
    }
    retval = NUMBER;
  }
  /* printf("i = %d\n", i); */
  s[i++] = '\0';
  /* printf("i = %d\n", i); */
  if(c != EOF) // why (c != '-') ?
    ungetch(c);
  /* printf("%s", s); */
  return retval; // signal that a number was found
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

// exercise 4.6 requires new cases.  (i) variable.  (ii) equality

/* 
case i.  vpush the index, and modify behavior of pop.  we can be sure pop() is called only when we expect a value to be defined.  therefore, pop can assume v[i] is defined.  so three operations: push the index (vpush); (enhanced) pop; and pop the index (vpop); vpush and vpop should also push/pop NAN from the val stack.

case ii. on LHS, pop index i, on RHS, pop value v; and set var[i] = v; else print an error
*/

int main() {

  int type;
  double op2;
  char s[MAXOP];

  while((type = getop(s)) != EOF) {
    printf("getop got %c\n", type);
    switch(type) {
    case NUMBER:
      /* printf("s = %s\n", s); */
      push(atof(s));
      break;
    case VARIABLE: // per 4.6
      /* printf("s = %s", s); */
      vpush(atof(s));
      break;
    case 'z': // the last printed value
      push(last_printed);
      break;
    case '=': {
      float v = pop();
      int n = vpop();
      var[n] = v;
      printf("assigned v%d the value %.4f\n", n, v);
      push(v); // considered as expression, assignment evaluates to RHS (like C)
      break;
    }
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
      last_printed = pop();
      printf("\t%.8g\n", last_printed);
      break;
    default:
      printf("error: unknown command %s\n", s);
      break;
    }
  }
  return 0;
}

