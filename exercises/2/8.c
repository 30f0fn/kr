# include <stdio.h>

/* 
returns the value of x rotated to the right by n bit positions
within the binary representation of x, 
invert the n bits which begin at position p

iterate on n.  at each step, get the rightmost bit of x as x & 1; multiply arithmetically by ~(~0U >> 1) to get the same bit value in the leftmost column; then take the logical sum of this with x.
*/

int rightrot(unsigned x, int n) {
  while (n > 0) {
    unsigned leftmost = (x & 1) * ~(~0U >> 1);
    x = x >> 1; // an assignment operator appears in the next section
    x = x | leftmost; // ditto
    n--;
  }
  return x;
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
  /* int m = invert(0, 9, 3); */
  /* printBinary(); */

  int x = 1;
  short m = rightrot(x, 2);
  printBinary(m);
  /* printf("%d", rightrot(x, 1)); */
}

