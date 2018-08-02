# include <stdio.h>

/* converts string, interpreted as hexidecimal, to corresponding number */

int is_digit(char);
int digit_to_integer(char);

int main(char s[]) {
  int n = 0, i = 0;
  char c;
  if (s[0] == '0' && (s[1] == 'x' || s[1]== 'X'))
    i = 2 ;
  while (is_digit(c = s[i]))
    n = 16 * n + digit_to_integer(c);    
  return n;
}

int is_digit(char c) {
  return ('A' <= c && c <= 'F') ||
    ('a' <= c && c <= 'f') ||
    ('0' <= c && c <= '9');
}

int digit_to_integer(char c) {
  if ('A' <= c && c <= 'F') return c-'A';
  if ('a' <= c && c <= 'f') return c-'a';
  if ('0' <= c && c <= '9') return c-'0';
  return -1;
}
