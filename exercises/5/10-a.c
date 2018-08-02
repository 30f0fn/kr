#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


/* 
mwe for debugging in exercise 5-10
*/


int main(int argc, char *argv[]) {
  // prepare stack
  char *a = *++argv;
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
  printf("did find integer, namely %d\n", atoi(a));
  return 0;
}


