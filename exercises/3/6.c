# include <stdio.h>


/*
itoa(n, s, w) converts integer n to base 10 representation in the string s; s should be left padded with 0s to ensure its width is w 

assumes w is big enough
*/

void itoa(int n, char s[], int w) {
  void reverse(char*);
  char to_digit(int, int);
  int i = 0;
  do {
    s[i++] = to_digit((n % 10), 10);
    n /= 10;
  }
  while(n > 0);
  while(i < w) {
    s[i++] = '0';
  }
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
  int n, i;
  for(i = 0; s[i] != '\0'; i++) {
    n *= 10;
    n += (s[i] - '0');
  }
  return n;
}




int main(int argc, char* argv[]) {
  
  
  char w = int_from_string(argv[1]);
  printf("got width %d\n", w);

  int n = 0;
  int i;
  for(i = 0; argv[2][i] != '\0'; i++) {
    n *= 10;
    n += (argv[2][i] - '0');
  }
  
  if(w < i) {
    printf("w is not big enough!\n");
    return -1;
  }

  char s[w];

  itoa(n, s, w);
  printf("%s\n", s);
}

