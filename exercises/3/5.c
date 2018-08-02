 # include <stdio.h>

/*
itob(n, s, b) converts given integer n into its base b character representation in the string s.  For example, itob(n, s, 16) formats n as hexadecimal integer in s.

allow bases up to 36.

first build in s the reverse of the desired representation, then apply reverse().

while n is not zero, take its value d modulo b; now store s[i++] = to_digit(d, b); finally divide n by b
*/

char itob(int n, char s[], int b) {
  char to_digit(int, int);
  void reverse(char*);
  // first handle sign
  int negative;
  if(negative = (n < 0)) {
    n = -n;
  }
  int i = 0;
  do {
    s[i++] = to_digit(n % b, b);
  } while((n /= b) > 0);
  if(negative)
    s[i++] = '-';
  s[i] = '\0';
  reverse(s);
}

char to_digit(int d, int b) {
  if(b < 1 || b > 36 || d < 0 || d > b) {
    return -1;
  }
  if(d <= 9)
    return d + '0';
  else // (d-10)th digit of the sequence a-z... I'm not sure about 36 here
    return d - 10 + 'a';
}

void reverse(char s[]) {
  int len;
  for(len = 0; s[len] != '\0'; len++);
  char temp;
  int i, j;
  for(i = 0, j = len - 1; i < j; i++, j--) {
    temp = s[i];
    s[i] = s[j];
    s[j] = temp;
  }
}

int int_from_string(char s[]) {
  int n;
  for(int i = 0; s[i] != '\0'; i++) {
    n *= 10;
    n += (s[i] - '0');
  }
  return n;
}




int main(int argc, char* argv[]) {
  // specify n and b, in that order, as command-line arguments
  char b = int_from_string(argv[1]);
  printf("got base %d\n", b);
  
  // from argv[2], get n and i = log_10 n
  int n = 0;
  int i;
  for(i = 0; argv[2][i] != '\0'; i++) {
    n *= 10;
    n += (argv[2][i] - '0');
  }

  printf("converted string input to integer %d\n", n);
  printf("found n to have %d digits\n", i);
  int result_len = 0;
  int m = n;
  while(m > 0) {
    m /= b;
    result_len++;
  }
  printf("result should have %d digits\n", result_len);
  char s[result_len];
  itob(n, s, b);
  printf("%s\n", s);
}

