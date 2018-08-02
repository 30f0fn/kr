# include <stdio.h>

int main() {
  char *pmessage = "now is the time";
  char *u = pmessage;
  /* char v[] = pmessage; */
  printf("%d\n", pmessage);
  printf("%d\n", u);
  printf("%c\n", *pmessage);
  printf("%c \n", *u);
  /* printf("%d\n", v); */
}
