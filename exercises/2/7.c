 # include <stdio.h>

/* 
within the binary representation of x, 
invert the n bits which begin at position p
*/

int island_of_ones(int, int);


int invert(int x, int p, int n) {
  return island_of_ones(p, p-(n-1)) ^ x;
}

int island_of_ones(int p, int n) {
  // the left boundary of the 1s
  int m1 = ~(~0 << p + 1);
  // the right boundary of the 1s
  int m2 = ~0 << n;
  return m1 & m2;
}


void printBinary(unsigned int n) {
  if (n == 0) {
    printf("%d", 0);
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

  int k = (2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2) - 1;
  int m = invert(0, 9, 3);
  printBinary(m);
}

