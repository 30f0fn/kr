#include <stdio.h>
#include <stdlib.h>
/* 
add error checking to day_of_year and month_day 
*/


static char daytab[2][13] = {
  {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};





int day_of_year(int year, int month, int day) {
  int leap = year %4 == 0 && year % 100 != 0 || year % 400 == 0;
  if(!(1 <= month && month <= 12 &&
          1 <= day && day <= daytab[leap][month]))
    return -1;
  while(--month)
    day += daytab[leap][month]; // add day length of month - 1, month - 2, ...
  return day;
}

int month_day(int year, int day, int *pmonth, int *pday) {
  int leap = year %4 == 0 && year % 100 != 0 || year % 400 == 0;
  *pday = day;
  for(*pmonth = 1; *pday  > daytab[leap][*pmonth]; ++*pmonth) {
    *pday -= daytab[leap][*pmonth];
  }
  return(1 - (1 <= *pday <= daytab[leap][*pmonth])); // 0 if within bounds, -1 else
}




int main(int argc, char* argv[]) {
  int mode = **++argv;
  switch(mode) {
  case '1': {
    int y = atoi(*++argv);
    int m = atoi(*++argv);
    int d = atoi(*++argv);
    printf("y, m, d = %d, %d, %d\n", y, m, d);
    int v = day_of_year(y, m, d);
    printf("%d\n", v);
    break;
  }
  case '2': {
    int y = atoi(*++argv);
    int d = atoi(*++argv);
    int pmonth, pday;
    printf("y, d = %d, %d\n", y, d);
    int v = month_day(y, d, &pmonth, &pday);
    printf("month = %d; day = %d\n", pmonth, pday);
    break;
  }
  default:
     printf("command %c not recognized\n!", mode);
  }
}
