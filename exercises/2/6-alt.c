 # include <stdio.h>

/* returns x with the n bits that begin at position p set to the rightmost n bits of y, le
aving other bits unchanged 

this is clearer (maybe) but slower than the 'island of 1s' approach I gave in 6.c

another strategy would be to use 

*/


// set ith bit of x equal to jth bit of y
int setbit(int x, int i, int y, int j) {
  // set ith bit of x to 1
  x = x | (1 << i);
  // set all bits of y to 0, except for jth bit
  y = (y & (1 << j)) << i - j;
  x = x | y;
  return x;
}

int setbits(int x, int p, int n, int y) {
  for (int i = 0; i < n; i++) {
    x = setbit(x, p-i, y, n-1-i);
  }
  return x;
}


void printBinary(unsigned int n) {
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
  /* int m = setbit(0, 8, 2047, 3); */
  /* int setbits(int x, int p, int n, int y)  */
  int m = setbits(0, 9, 3, 2047); 
  printBinary(m);
  /* putchar('\n'); */
  /* printBinary(2047); */
}

