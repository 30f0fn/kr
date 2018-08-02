# include <stdio.h>

/* remove each character in s1 which matches any character in s2 */


void squeeze(char s[], char d) {
  int i, j;
  for (i = j = 0; s[i] != '\0'; i++)
    if (s[i] != d)
      s[j++] = s[i];
  s[j] = '\0';
  /* return s[0]; */
}


int contained(char, char[]);

void multiSqueeze(char s[], char s2[]) {
  int i, j;
  for (i = j = 0; s[i] != '\0'; i++)
    if (!contained(s[i], s2))
      s[j++] = s[i];
  s[j] = '\0';
}


/* int main(int argc, char* argv[]) { */
/*   /\* printf("argv0: %s, argv1: %s, argv2: %s\n", argv[0], argv[1], argv[2]); *\/ */
/*   printf("removing the char  %c from %s...\n", argv[2][0], argv[1]); */
/*   squeeze(argv[1], argv[2][0]); */
/*   printf("the result is %s\n", argv[1]); */
/* } */

int contained(char c, char s2[]) {
  int retval = 0;
  for (int i = 0; s2[i] != 0; i++) {
    if (c == s2[i])
      retval = 1;
  }
  return retval;
}

int main(int argc, char* argv[]) {
  printf("removing all of the chars in %s from %s...\n", argv[2], argv[1]);
  multiSqueeze(argv[1], argv[2]);
  printf("the result is %s\n", argv[1]);
}
