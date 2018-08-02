# include <stdio.h>

# define NUMTABSTOPS 10

void tabs() {

  for (int i = 0; i < NUMTABSTOPS; i++) {
    putchar('|');
    putchar('\t');
  }
  putchar('\n');
}

int main () {
  printf("\tthis line began with a tab\n");
  tabs();
  printf("   this line has a tab\tin the middle\n");
  tabs();
  printf("   this line has two tabs\t\tin the middle\n");
  tabs();
  printf("123456789");
}
