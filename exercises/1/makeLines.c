# include <stdio.h>
# define MINLENGTH 60
# define MAXLENGTH 100

int main (int argc, char *argv[]) {
  for (int i = MINLENGTH; i < MAXLENGTH; i++) {
    printf("%d", i);
    for (int j = 0; j < i; j++) putchar('o');
    putchar('\n');
  }
   
}
