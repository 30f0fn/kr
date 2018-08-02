#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define INCREMENT 20

main()
{ 
  int fahr;

  for (fahr = UPPER; fahr >= LOWER; fahr = fahr-INCREMENT) {
    printf("%4d %5.1f\n", fahr, (5.0/9.0)*(fahr-32));
  }
}
