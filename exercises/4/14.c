
/* 
defines a macro swap(t, x, y) that interchanges two arguments of type t.


 */

# include <stdio.h>

# define swap(t, x, y) {t temp = x; x = y; y = temp;}

int main() {

  int x = 0;
  int y = 1;
  printf("before swap: x = %d, y = %d\n", x, y);
  swap(int, x, y);
  printf("after swap: x = %d, y = %d\n", x, y);
}
