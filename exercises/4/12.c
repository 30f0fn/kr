# include <stdio.h>


# define MAX_DIGITS 10
/*
Adapt the ideas of printd to write a recursive version of itoa, that is, convert an integer into a string by calling a recursive routine.
*/

char s[MAX_DIGITS];

void itoa(int n) {
  static int count = 0;
  if(n < 0) {
    s[count++] = '-';
    n = -n;
  }
  if(n/10) {
    itoa(n/10);
  }
  if(count > 9) 
    printf("Integer too long!");
  else
    s[count++] = n % 10 + '0';
}



int main(int argc, char* argv[]) {
  /* take string argument from command line*/
  int arg_len = sizeof(argv[1])/sizeof(argv[1][0]);
  itoa(1234987);
  printf("s = %s\n", s);
}

