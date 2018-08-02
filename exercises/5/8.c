#include <stdio.h>
#include <stdlib.h>
/* 
add error checking to day_of_year and month_day 
*/


static char daytab[2][13] = {
  {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};



int check_day_of_year(int year, int month, int day) {
  int leap = year %4 == 0 && year % 100 != 0 || year % 400 == 0;
  printf("year %d is leap? %d\n", year, leap);
  return (1 <= month && month <= 12 &&
          1 <= day && day <= daytab[leap][month]);
}

int check_month_day(int year, int day) {
  int leap = year %4 == 0 && year % 100 != 0 || year % 400 == 0;
  if(day < 1) return 0;
  for(int month = 1; day > 0 && month < 13; day -= daytab[leap][month--])
    ;
  return(day <= 0); 
}


int main(int argc, char* argv[]) {
  int mode = **++argv;
  switch(mode) {
  case '1': {
    int y = atoi(*++argv);
    int m = atoi(*++argv);
    int d = atoi(*++argv);
    printf("y, m, d = %d, %d, %d\n", y, m, d);
    int v = check_day_of_year(y, m, d);
    printf("%d\n", v);
    break;
  }
  case '2': {
    int y = atoi(*++argv);
    int d = atoi(*++argv);
    printf("y, d = %d, %d\n", y, d);
    int v = check_month_day(y, d);
    printf("%d\n", v);
    break;
  }
  default:
     printf("command %c not recognized\n!", mode);
  }
}
