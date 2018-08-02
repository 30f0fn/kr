#include <stdio.h>
#define TAB_WIDTH 8
#define MAX_TABS 100


// next tab is either next given, or default from TAB_WIDTH
void advance(int linelength, int **nexttab) {
  printf("-----\n");
  printf("\nlinelength = %d; **nexttab = %d\n", linelength, **nexttab);
  while(linelength >= **nexttab) {
/*     /\* printf("\nlinelength = %d; nexttab = %d\n", linelength, *nexttab); *\/ */
    if(*(*nexttab+1)) {
      printf("*(*nexttab + 1) = %d", *(*nexttab + 1));
      ++*nexttab;
      printf("\nadvancing to next manually input tab stop at %d\n", **nexttab);
    }
/*     // the below does not work, because it modifies the array of manually given tabstops! */
    else {
      *++*nexttab = *(*nexttab) + TAB_WIDTH;
      *(*nexttab + 1) = 0;
      printf("\nadvancing to next DEFAULT tab stop at %d\n", **nexttab);
    }
  }
}

void advance1(int linelength, int **nexttab) {
  *++*nexttab;
}

void reset(int **nexttab, int *tabs) {
  int *tabp = tabs;
  nexttab = &tabp;
}



int main() {

  int linelength;
  int tabs[MAX_TABS];
  int tabs_given[] = {5, 10, 15, 20, 0};
  for(int i = 0; tabs[i] = tabs_given[i]; i++)
    ;
  int *tabp = tabs;
  int **nexttab = &tabp;
  linelength = 34;
  advance(linelength, nexttab);
  printf("nexttab = %d\n", **nexttab);
  for(int i = 0; tabs[i]; printf("tab[i] = %d\n", tabs[i++]));
  linelength = 0;
  reset(nexttab, tabs);
  advance(linelength, nexttab);
}
