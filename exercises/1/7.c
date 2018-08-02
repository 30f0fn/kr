#include <stdio.h>

/* determine values of getchar() != EOF, and of EOF */

main() {
  int c;
  c = getchar();
  while (c != EOF) {
    int d = (c == EOF);
    int e = (c == 'a');
    int f = ((c != EOF) == 0);
    printf("getchar() returned %d\n", c);
    printf("...the value of getchar()==EOF is %d\n", d);    
    printf("...the value of getchar()==a is %d\n", e);
    printf("...the value of (getchar()!=EOF)==0 is %d\n", f);
    c = getchar();
  }
  printf("the condition (c!=EOF) failed, and the value of (c==EOF) is %d\n",  (c==EOF));
}
