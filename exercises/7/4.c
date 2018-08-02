#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "3.c"

#define MAX_SPEC 20
#define MAX_WORD 20


/*
a version of scanf analogous to minprintf from exercise 7-3.
*/

void minscanf(char *fmt, ...);


/*
 note minscanf and minprintf are inverse
 specifically, if scanf(fmt, ...) reads input into .., 
 then printf(fmt, ...) prints the same (maybe somewhat reformatted) input

*/

int main(int argc, int *argv) {

  int ival, ival2; // integer returned by input word
  char sval[MAX_WORD];
  double dval; // double returned by input word
  float fval;

  char fmt[] = "%d%s%f";

  printf("Scanning...\n\n");
  minscanf(fmt, &ival, sval, &fval);

  printf("Printing...\n\n");
  /* printf("scanned the integer %d, string %s, and float %f\n", ival, sval, fval); */
  minprintf("scanned the integer %d, string %s, and float %f\n", ival, sval, fval);

  
}



// try to get from stdin an int and a double, then print them
int basic_test() {

  
}


/* run through format string fmt; look for literal chars or specifiers; 
 if a literal char, then read a char from stdin and raise an error iif no match; 
if a specifier, get the appropriate type, read a chunk from stdin, try to convert it to the type, and if successful, assign resulting value to the next argument 
*/
void minscanf(char *fmt, ...)
{
  va_list ap; // points to each unnamed arg in turn
  char *p; // runs through format specifier
  char s[MAX_WORD]; // store input word
  char *sp; // accumulates input
  char litchar; // literal in format specifier

  va_start(ap, fmt); // points ap to first unnamed arg
  //iterate through format string



  for(p = fmt; *p; p++) {
    /* printf("read char *p = %c from format string\n", *p); */
    if(*p != '%' && *p != (litchar = getchar())) {
      printf("error! input char %c did not match the literal %c from format string.\n",
             litchar, *p);
      return;
    }
 // format specifier begun (I am not handling %%).  so, read a chunk from stdin.  then, read the rest of the format specifier, and identify appropriate type.  switch accordingly, try to convert chunk to type and assign result to the next argument given by va_arg. 
    for(sp = s; isspace(*sp = getchar()); )
      ;
    switch(*++p) { // format specifier begun.  so, read a chunk from stdin.  identify type from format specifier, try to convert chunk to type and assign result to next argument.  
    case 'd': // integer
      // try to read an integer from input, should be at last one digit
      /* printf("got type integer from format spec\n"); */
      for( ; !isspace(*sp); *++sp = getchar()  ) {
        /* printf("got digit *sp = %c\n", *sp); */
        if(!isdigit(*sp)) {
          printf("nondigit input %c does not match integral format specifier!\n", *sp);
          return;
        }
      }
      *sp = '\0';
      *va_arg(ap, int *) = atoi(s);
      break;

    case 'f': // float
      /* printf("got type integer from format spec\n"); */
      for( ; !isspace(*sp); *++sp = getchar()  ) {
        /* printf("got digit *sp = %c\n", *sp); */
        if(!isdigit(*sp) && *sp != '.') {
          printf("nondigit input %c does not match integral format specifier!\n", *sp);
          return;
        }
      }
      if(*p == '.') {
        *sp++ = *p;
        for( ; !isspace(*sp); *++sp = getchar()  ) {
          /* printf("got digit *sp = %c\n", *sp); */
          if(!isdigit(*sp) && *sp != '.') {
            printf("nondigit input %c does not match integral format specifier!\n", *sp);
            return;
          }
        }
      }
      *sp = '\0';
      /* printf("read the float %.2f\n", *va_arg(ap, float *) = atof(s)); */
      *va_arg(ap, float *) = atof(s);
      /* printf("assigned value to va_arg\n"); */
      break;
    
    case 's': // string
      /* printf("got type string from format spec\n"); */
      for( ; !isspace(*++sp = getchar()); )
        ;
      /* printf("s is %s\n", s); */
      *sp = '\0';
      strcpy(va_arg(ap, char *), s);
      break;
    default:
      /* putchar(*p); */
      break;
    }
  }
  /* printf("scanf: cleaning up\n"); */
  va_end(ap); // final cleanup
  return;


}



