 # include <stdio.h>

/* returns x with the n bits that begin at position p set to the rightmost n bits of y, le
aving other bits unchanged 

convert x[p, ..., p-(n-1)] to 1s
convert y[...n] to 0s; then leftshift by p-(n-1)
then multiply x by y;

for steps 1 and 2a, want islandOfones(start, end)
*/

int island_of_ones(int, int);


int setbits(int x, int p, int n, int y) {
  x = x & ~island_of_ones(p, p-(n-1));
  y = y & island_of_ones(n-1, 0);
  y = y << (p - n);
  /* return y; */
  return x | y;
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
  int m = setbits(0, 9, 3, 2047);
  printBinary(m);
}

