#include <stdio.h>
#include <string.h>
#include <ctype.h>
/* 
convert lower to upper, or upper, depending on argv[0]

So, expect this program to be invoked by different names.  One way to achieve this would be compile it to two differently named binaries.
*/

int main(int argc, char *argv[]) {
  int (* convert) (int);
  convert = (strcmp(argv[0], "./1l") == 0) ? tolower : toupper;
  if(strcmp(argv[0], "./1l") == 0) {
    printf("I read argv[0] as %s, so will convert uppercase to lower\n", argv[0]);
  }
  else {
    printf("I read argv[0] as %s, so will convert lowercase to upper\n", argv[0]);
  }
  char c;
  while((c = getchar()) != EOF) {
    putchar(convert(c));
  }
}
