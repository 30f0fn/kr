# include <stdio.h>
# define MAXLINE 100

/*
print all input lines which are longer than 80 characters
 */

/* store the line contents, up to 80 chars, in an array
if more contents remain, print array contents, then print remaining contents
*/

char printLongLine(char lineBuffer[], int lineNumber);

int main() {

  int lineNumber = 0;
  char lineBuffer[80];
  
  char c;
  while ((c = printLongLine(lineBuffer, lineNumber)) != EOF) {
    lineNumber++;
  }

}

char printLongLine(char lineBuffer[], int lineNumber) {
  char c;
  for (int i = 0; i<80 && (c=getchar())!='\n' && c!=EOF; i++) {
    lineBuffer[i] = c;
  }
  // c is '\n' or EOF, iff line was <80 characters
  if (c!='\n' && c!=EOF) {
    printf("Line %d:  ", lineNumber);
    /* printf("%s", lineBuffer); */
    for (int i=0; i<80; i++) putchar(lineBuffer[i]);
    while (c!='\n') putchar(c=getchar());
    if (c=='\n') putchar(c);
  }
  // if file has ended, c is EOF
  return c;
}
