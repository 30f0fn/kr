#include <stdio.h>

#define STR_MAX 100

/*
the pointer-based function,
strcatp(s, t) 
copies string t to the end of s.
*/



void strcatp(char *s, char *t) {
  for( ; *s != '\0'; s++)
    ;
  while(*s++ = *t++)
    ;
}


int main(int argc, char* argv[]) {
  char *a, *b;
  a = *++argv;
  b = *++argv;
  char s[STR_MAX];
  strcatp(s, a);
  strcatp(s, b);
  printf("%s + %s\n = \n%s\n", a, b, s);
}
