# include <stdio.h>

/* 
the assignment is to check syntax of a C program.  that's a bit ambitious... I'll just check for parens.

detect unbalanced parentheses () and [] 
scan through file
push open parens onto stack
if close is encountered, pop from stack and check if they match
implement stack as base three integer
*/


/* int buildStack(); */
int typeAsInt(int n);
void push(int n[], char c);
int pop(int n[]);
int isEmpty(int n[]);

int main() {
  
  int stack[1]; stack[0] = 0;
  char c;

  while ((c = getchar()) != EOF) {
    if (c == '(' || c == '[')
      push(stack, c);
    if (c == ')' || c == ']') {
      int d = pop(stack);
      if (typeAsInt(c) != d) {
        printf("UNMATCHED PARENS!");
        return -1;
      }
    }
  }

  if (!isEmpty(stack)) {
    printf("NOT EVERY PARENS GOT CLOSED!");
    return -1;
  }
  printf("STRING OK!");
  return 0;
}





/*
represent a stack of parens types (number of types is two) by an integer in base 3 (= one more than number of types)
store the integer as entry of a 1-element array
for greater generality, could use second element of array to record number of types
*/

int typeAsInt(int c) {
  if (c == '(' || c == ')')
    return 1;
  else if (c == '[' || c == ']')
    return 2;
  else
    return -1; // error
  
}

/* int buildStack() { */
/*   int n[1]; */
/*   n[0] = 0; */
/*   return n; */
/* } */

int peek(int n[]) {
  return n[0] % 3;
}

int pop(int n[]) {
  int v = n[0] % 3;
  n[0] = n[0] / 3;
  return v;
}

void push(int n[], char c) {
  int t = typeAsInt(c);
  n[0] *= 3;
  n[0] += t;
}

int isEmpty(int n[]) {
  return n[0] == 0;
}
