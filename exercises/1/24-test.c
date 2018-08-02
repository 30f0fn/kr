# include <stdio.h>

/* this isn't finished, because not too helpful
easier to work in shell directly
input string of numerals between 0 and 3
print corresponding string of parentheses
*/

int main(argv, *argc) {
  char chars[] = {'(', ')', '[', ']'};
  for (int i = 0; i < TEST_LENGTH; i++) {
    putchar(chars[toInt(argv[i]));
  }
}

int toInt(int c) { // convert numeral to corresponding int
  return c - 48;
}
