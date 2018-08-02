#include <stdio.h>

#define STR_MAX 100

/*
the pointer-based function,
strendp(s, t) 
returns 1 if t occurs at the end of s, 
and returns 0 otherwise.
*/



int strendp(char *s, char *t) {
  char *t1 = t; // remember initial value of t
  // scan to end of the strings begun at s and t
  for( ; *s != '\0'; s++)
    ;
  for( ; *t != '\0'; t++)
    ;
  // scan back through s and t until match fails
  for( ; *s == *t && t >= t1; s--, t--)
    ;
  // say whether we reached initial value of t
  return (++t == t1);
}


int main(int argc, char* argv[]) {
  char *a, *b;
  a = *++argv;
  b = *++argv;
  printf("strendp(%s, %s) = %d \n", a, b, strendp(a, b));
}
