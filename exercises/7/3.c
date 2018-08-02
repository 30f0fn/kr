#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_SPEC 20
/*
revise minprintf to handle more of the facilities of printf

a conversion specifier has the form
%<minus?><field_width>.<precision><conversion character>

a minus specifies left-alignment, rather than right-, within the field

besides d, f, s given in text, other conversion characters are:
o - octal
x - unsigned hex with abcdef for 10...15
c - single character

laziest approach is just to grab the whole format specifier from p, and pass it, enquoted, to printf

*/

// void minprintf(char *fmt, ...);


// test driver
// submit command line arguments to minprintf
// how?  minprintf with %f expects additional arg as float, not as string
// indicate cast with prefix char f, i, s

/* union targ { */
/*   int ival; */
/*   float fval; */
/*   char *sval; */
/* }; */



/* int main(int argc, char *argv[]) { */
/*   printf("for test driver, please see exercise 7-4.\n"); */
/*   /\* u =  *\/ */
/*   /\* if(argc == 2) *\/ */
/*   /\*   minprintf(argv[1]); *\/ */
/*   /\* if(argc == 3) *\/ */
/*   /\*   minprintf(argv[1], *castarg(argv[2])); *\/ */
/*   /\* if(argc == 4) *\/ */
/*   /\*   minprintf(argv[1], *castarg(argv[2]), *castarg(argv[3])); *\/ */
/*   /\* putchar('\n'); *\/ */
/* } */


// take format string *fmt, plus optional args, and print the args per the format string

void minprintf(char *fmt, ...)
{
  va_list ap; // points to each unnamed arg in turn
  char *p;
  char specifier[MAX_SPEC];
  char *spec;
  spec = specifier;
  char *sval;  
  int ival;
  double dval;

  va_start(ap, fmt); // points ap to first unnamed arg
  for(p = fmt; *p; p++) {
    if(*p != '%') {
      putchar(*p);
      continue;
    }
    for(spec = specifier; isspace(*spec = *p++); )
      ;
    // I am not handling %%
    spec++;
    /* printf("found format spec indicator\n"); */
    if(*p == '-')
      *spec++ = *p++;
    while('0' <= *p && *p <= '9')
      *spec++ = *p++;
    if(*p == '.')
      *spec++ = *p++;
    while('0' <= *p && *p <= '9')
      *spec++ = *p++;
    if(isalpha(*p)) {
      *spec++ = *p;
    }
    *spec = '\0';
    /* printf("specifier is (%s)\n", specifier); */
    /* printf("*p is %c\n", *p); */
    switch(*p) { // 
    case 'd': // integer
      ival = va_arg(ap, int);
      printf(specifier, ival);
      break;
    case 'f': // float
      dval = va_arg(ap, double);
      /* printf("printing float %f\n", dval); */
      printf(specifier, dval);
      break;
    case 'o': // float
      ival = va_arg(ap, int);
      printf(specifier, dval);
      break;
    case 'x': // float
      ival = va_arg(ap, int);
      printf(specifier, ival);
      break;
    case 'c': // float
      ival = va_arg(ap, int);
      printf(specifier, ival);
      break;
    case 's': // string
      sval = va_arg(ap, char *);
      printf(specifier, sval);
      break;
    default:
      printf("couldnt parse specifier, printing literally\n");
      putchar(*p);
      break;
    }
  va_end(ap); // final cleanup
  }
}





/* void minprintf(char *fmt, ...) */
/* { */
/*   va_list ap; // points to each unnamed arg in turn */
/*   char *p, *sval;   */
/*   char cval; */
/*   int ival; */
/*   double dval; */

/*   va_start(ap, fmt); // points ap to first unnamed arg */
/*   for(p = fmt; *p; p++) { */
/*     if(*p != '%') { */
/*       putchar(*p); */
/*       continue; */
/*     } */
/*     switch(*p++) { // format specifier begun, so there must be another argument */
/*     case 'd': // integer */
/*       ival = va_arg(ap, int); */
/*       printf("%d", ival); */
/*       break; */
/*     case 'f': // float */
/*       dval = va_arg(ap, double); */
/*       printf("%f", dval); */
/*       break; */
/*     case 'o': // float */
/*       dval = va_arg(ap, double); */
/*       printf("%o", ival); */
/*       break; */
/*     case 'x': // float */
/*       dval = va_arg(ap, int); */
/*       printf("%x", ival); */
/*       break; */
/*     case 'c': // float */
/*       cval = va_arg(ap, int); */
/*       printf("%c", cval); */
/*       break; */
/*     case 's': // string */
/*       for(sval = va_arg(ap, char *); *sval; putchar(*sval++)) */
/*         ; */
/*       break; */
/*     default: */
/*       putchar(*p); */
/*       break; */
/*     } */
/*   } */
/*   va_end(ap); // final cleanup */
/* } */

