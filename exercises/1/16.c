# include <stdio.h>
# define MAXLINE 100

/*
 revise program in text to print length of longest line, and as much as possible of its text
 */

int getLine(char line[], int maxline); // read line up to maxline into line[], return length of whole (if not entirely copied) thing


/* print length of longest input line, and its contents up to length MAXLINE */
int main() {

  int len; // length of current line
  char line[MAXLINE]; // current line up to length MAXLINE

  int i = 0;
  while ((len = getLine(line, MAXLINE)) > 0) {
    printf("LINE %d (%d chars):  ", i, len);
    for (i = 0; i < len; i++) printf("%c", line[i]);
    putchar('\n');
    /* printf("%s", line); */
    i++;
  }
  
  return 0;
}

/* // read a line, copy its first lim characters into s[], and return its length */
int getLine(char s[], int lim) {
  int i, c;
  i = 0; c = getchar();
  while (c != '\n' && c != EOF) {
    if (i < lim - 1) s[i] = c;
    ++i; c = getchar();
  }
  if (c == '\n') {
    if (i < lim) s[i] = c;
    ++i;
  }
  return i;
}


