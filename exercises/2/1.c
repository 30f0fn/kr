# include <stdio.h>
# include <limits.h>
/* # include <floats.h> */

/* 
determines the range of char, short, int, and long, both signed and unsigned, by (i) printing values from the appropriate headers, and (ii) direct computation.  (Do the same for the floating-point types float, double and long double (signed and unsigned). )

a numeric datatype obeys laws of arithmetic mod 2^k where k is the number of bits in the type.

so to determine range of type by direct computation, evaluate the modulus of its arithmetic.

mod(arith(T)) = k iff k = min(j: 2^j=0)
*/

int main() {
  /* direct computation */

  printf("According to header flie limits.h...\n");

  printf("     the maximum of type CHAR (unsigned) is %d\n", UCHAR_MAX);
  printf("     the maximum of type SHORT  is %d\n", SHRT_MAX);
  printf("     the maximum of type INT (unsigned) is %d\n", UINT_MAX);
  printf("     the maximum of type LONG (unsigned) is %d\n", ULONG_MAX);
  printf("     the maximum of type CHAR (signed) is %d\n", SCHAR_MAX);
  /* printf("     the maximum of type CHAR (unsigned) is %d\n", S_MAX); */
  printf("     the maximum of type LONG (signed) is %d\n", LONG_MAX);
  /* printf("     the maximum of type CHAR (unsigned) is %d\n", UCHAR_MAX); */

  printf("According to direct computation...\n");

  int p = 0;

  char c;
  p = 0;
  for (c = 1; c != 0; c += c)  {
    p++;
  }
  printf("     the range of type CHAR (unsigned) is 2^%d\n", p);

  short s;
  for (s = 1; s != 0; s += s)  {
    p++;
  }
  printf("     the range of type SHORT (unsigned) is 2^%d\n", p);


  int r;
  for (r = 1; r != 0; r += r)  {
    p++;
  }
  printf("     the range of type INT (unsigned) is 2^%d\n", p);

  long l;
  for (l = 1; l != 0; l += l)  {
    p++;
  }
  printf("     the range of type LONG (unsigned) is 2^%d\n", p);



  signed char pc;
  p = 0;
  for (pc = +1; pc != 0; pc += pc)  {
    p++;
  }
  printf("     the range of type CHAR (signed) is 2^%d\n", p);

  signed short ps;
  for (ps = +1; ps != 0; ps += ps)  {
    p++;
  }
  printf("     the range of type SHORT (signed) is 2^%d\n", p);


  signed int pr;
  for (pr = +1; pr != 0; pr += pr)  {
    p++;
  }
  printf("     the range of type INT (signed) is 2^%d\n", p);

  signed long pl;
  for (pl = +1; pl != 0; pl += pl)  {
    p++;
  }
  printf("     the range of type LONG (signed) is 2^%d\n", p);


  return 0;
}
