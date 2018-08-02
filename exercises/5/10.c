#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

# define VAL_HEIGHT 100

/* 
The program expr evaluates a reverse Polish expression from the command line, where each operator or operand is a separate argument.  For example, 
expr 2 3 4 + *
evaluates to 2 * (3 + 4).

maintain a stack valstack of integer values.
When an integer is read, push it to the stack.
When an operator is read, pop the suitable number of values from the stack, apply to them the operation, and push the result.  

Whenever the stack is empty, print the result.

Recall from p106 these idioms:

*p++ = val; 
// set *p to val, then increment p: this pushes val onto stack.  here, p points to next free position
*--p = val; 
// decrement p, then set val to *p: this pops stack into val.  if p points to next free position, then one less than p points to top of stack, and decrementing p frees the top position
*/


int main(int argc, char *argv[]) {
  // prepare stack
  int q[VAL_HEIGHT];
  int *p = &q[0];
  while(--argc > 0) {
    char *a = *++argv;
    printf("read %s\n", a);
    switch(*a) {
    case '+': {
      int n = *p++ = *--p + *--p;
      printf("%d\n", n);
      break;
    }
    case '-': {
      int m = *--p;
      int n = *p++ = *--p - m;
      printf("%d\n", n);
      break;
    }
    case '*': {
      int n = *p++ = *--p * *--p;
      printf("%d\n", n);      
      break;
    }
    case '/': {
      printf("dividing...\n");
      int m = *--p;
      printf("divisor m = %d\n", m);
      int n = *p++ = *--p / m;
      printf("%d\n", n);      
      /* printf("%d / %d = %d\n", 10, 5, 10/5); */
      break;
    }
    default:
      {
        printf("argument must be integer\n");
        for(char *a1 = a; *a1; a1++) {
          printf("starting a cycle");
          printf("checking that %c is a digit\n", *a1);
          if(!isdigit(*a1)) {
            printf("Error: I didn't understand the argument %s\n", a);
            break;
          }
          else
            printf("verified that %c is a digit\n", *a1);
          printf("finished a cycle\n");
        }
        printf("did find integer! pushing %d\n", atoi(a));
        *p++ = atoi(a);
        printf("pushed\n");
      }
    }
  }
}
