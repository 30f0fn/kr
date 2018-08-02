# include <stdio.h>

/* any(s1, s2) returns the first location in s1 where any character in s2 occurs, or -1 if s1 contains no character from s2 */

int contained(char, char[]);

int any(char s1[], char s2[]) {
  for (int i = 0; s1[i] != '\0'; i++)
    if (contained(s1[i], s2))
      return i;
  return -1;
}

int contained(char c, char s2[]) {
  int retval = 0;
  for (int i = 0; s2[i] != 0; i++) {
    if (c == s2[i])
      retval = 1;
  }
  return retval;
}


int main(int argc, char* argv[]) {
  printf("the index of the first occurrence in %s of a character in %s is %d\n",
         argv[1], argv[2], any(argv[1], argv[2])
         );
}

