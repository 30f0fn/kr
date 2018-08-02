# include <stdio.h>
# define MAXLINE 100

void reverse(char s[], int len);
int getLine(char s[], int len);

int main () {
  
  char s[100];
  int len;

  int returnVal = 0;

  while ((len = getLine(s, MAXLINE)) > 0) {
    reverse(s, len);
    printf("%s", s);
    if (len == MAXLINE && s[len-1] == '\n' || s[len-1] == EOF) {
      printf("warning! line was truncated\n");
      returnVal = -1;
    }
  }
  return returnVal;
}


int getLine(char line[], int max) {
  
  int i;
  char c;
  for (i = 0; (c = getchar()) != EOF && c != '\n' && i < max - 1; i++) {
    line[i] = c;
  }
  if (c == '\n') {
    line[i++] = '\n';
  }

  line[i] = '\0';

  return i;
}

void reverse(char s[], int len) {
  // note that len includes the '\n' which we don't want to move
  char swap;
  for (int i = 0; i < (len-1)/2; i++) {
    swap = s[i];
    s[i] = s[len-2-i];
    s[len-2-i] = swap;
  }
}
