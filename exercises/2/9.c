# include <stdio.h>


int bitcount(unsigned x) {
  int b = 0;
  while (x != 0 ) {
    x &= (x-1);
    b++;
  }
  return b;
}

void printBinary(unsigned n) {
  if (n == 0) {
    printf("%d\n", 0);
    return;
  }
  int digit = 1;
  while (digit*2 <= n)
    digit = digit*2;
  while (digit > 0) {
    if (n >= digit) {
      printf("%d", 1);
      n -= digit;
      /* printf("%d\n", digit); */
    }
    else printf("%d", 0);
    digit = digit/2;
  }
  putchar('\n');
}


int main(int argc, char* argv[]) {

  /* int k = (2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2) - 1; */

  int m = bitcount(2047);
  /* int m = 100; */
  printBinary(m);
}

