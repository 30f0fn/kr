# include <stdio.h>
# define STR_MAX 100

/* 
versions of the library functions strncpy, strncat, and strncmp, which operate on the first n characters of their argument strings.

strncopy(s, t, n) copies the first n characters of t to s

strncat(s, t, n) appends the first n characters of t to s

strncmp(s, t, n) compares first n characters of s to t; returning <0 if s < t; 0 if s == t; >0 if s > t
*/

//copy the first n characters of t to s, assuming s has enough space
//i.e. overwrite the first n chars of s with the first n chars of t
void strncpy1(char *s, char *t, int n) {
  /* int i = 0; */
  /* while((*s++ = *t++) && i++ != n) */
  /*   ; */
  for(int i = 0; (*s++ = *t++) && i++ != n; )
    ;
}


//  append the first n characters of t to s, assuming s has enough space
void strncat1(char *s, char *t, int n) {
  for( ; *s != 0; s++)
    ;
  for(int i = 0; (*s++ = *t++) && i++ != n; )
    ;
}

// void compare first n characters of s to t; returning <0 if s < t; 0 if s == t; >0 if s > t
int strncmp1(char *s, char *t, int n) {
  for(int i = 0; *s == *t && i++ != n; s++, t++)
    ;
  return *s - *t;
}




int main(int argc, char* argv[]) {
  char *s, *t;
  int n;
  int m;
  m = **++argv;
  s = *++argv;
  t = *++argv;
  n = **++argv - '0'; // only works for n < 10
  switch(m) {
  case '1': 
    strncpy1(s, t, n);
    printf("strncpy1 up to %d gives %s\n", n, s);
    break;
  case '2':
    strncat1(s, t, n);    
    printf("strncat1 up to %d gives %s\n", n, s);
    break;
  case '3':
    /* strncmp1(s, t, n); */
    printf("strncmp up to %d gives %d\n", n, strncmp1(s, t, n));
    break;
  default:
    printf("the command was not recognized:(\n");
  }
}
