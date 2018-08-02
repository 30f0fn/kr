# include <stdio.h>
# include <stdlib.h>
# define TAB_WIDTH 12
# define TAB_MAX 100
/* 
entab: when a tab stop follows a string of two or more consecutive spaces, replace that string of spaces with a tab character
this is to say: when line s[] ends with exactly n<9 spaces; while s has length divisble by TAB_WIDTH, replace s with s+\t
*/


// next tab is either next given, or default from TAB_WIDTH
void advance(int linelength, int **nexttab, int spacing) {
  /* printf("nexttab = %d\n", **nexttab); */
  while(linelength >= **nexttab) {
    if(*(*nexttab+1)) {
      ++*nexttab;
    }
    else {
      *++*nexttab = *(*nexttab) + spacing;
      printf("next tab is %d\n", **nexttab);
      *(*nexttab + 1) = 0;
    }
  }
}


int entab(int *tabs, int spacing) {

  printf("entabbing\n");

  int linelength = 0;
  int numspaces = 0;
  char c;
  int *tabp = tabs;
  int **nexttab = &tabp; // could use macro here
  printf("nexttab = %d\n", **nexttab);
  /* printf("here?"); */
  while ((c = getchar()) != EOF) {
    /* printf("read %c\n", c); */
    switch(c) {
    case ' ': {
      numspaces++;
      if(linelength + numspaces == **nexttab) {
        putchar('\t');
        linelength += numspaces;
        advance(linelength, nexttab, spacing);
        numspaces = 0;
      }
      break;
    }
    case '\n': {
      putchar(c);
      numspaces = 0;
      linelength = 0;
      tabp = tabs; nexttab = &tabp;
      break;
    }
    default: {
      /* c is neither space nor newline, */
      /* so print all accumulated spaces followed by c */
      while (numspaces > 0) {
        putchar(' '); linelength++; numspaces--;
      }
      putchar(c); linelength++;
      /* printf("\nin entab, nexttab = %d\n", **nexttab); */
      advance(linelength, nexttab, spacing);
    }
    }
  }
}



/* detab.  replaces tabs in the input with the proper number of spaces to the next tab stop.
say that a tab stop is every TAB_WIDTH spaces.
suppose line s[] has length len, and contains no tabs.  
we replace s+'\t' with TAB_WIDTH - (len % TAB_WIDTH) spaces.
*/

int detab(int *tabs, int spacing) {
  printf("detabbing\n");

  int linelength = 0; // line length
  char c; // current char

  int *tabsp = tabs;
  int **nexttab = &tabsp;

  while ((c = getchar()) != EOF) {
    switch(c) {
    case '\t': {
      while(linelength < **nexttab) {
        putchar('.');
        linelength++;
      }
      advance(linelength, nexttab, spacing);
      break;
    }
    case '\n': {
      putchar(c);
      linelength = 0;// put c, reset len;
      tabsp = tabs; nexttab = &tabsp;
      break;
    }
    default: {
      putchar(c);
      advance(++linelength, nexttab, spacing);
    }
    }
  }
}


int main(int argc, char *argv[]) {

  //entab/detab switch 
  char mode = **++argv;
  argc--;
  int delay, spacing;
  for(char **arg = ++argv; --argc; ++arg) {
    if(**arg == '-') {
      spacing = -atoi(*arg);
      printf("spacing = %d;\n", spacing);
    }
    else if(**arg == '+') {
      delay = atoi(*arg);
      printf("delay = %d;\n", delay);      
    }
  }


  int tabs[TAB_MAX];
  /* *tabs = TAB_WIDTH; */
  int *tabsp = tabs; 
  /* printf("*tabsp = %d", *tabsp); */
  

  // package default tabs into 0-terminating array
  printf("about to generate tab list\n");
  if(TAB_WIDTH < delay) {
    //ugly but I can't see another way
    *tabsp = TAB_WIDTH;
    while((*tabsp + TAB_WIDTH) < delay) {
      *++tabsp = *tabsp + TAB_WIDTH;      
      printf("tab stop at %d\n", *tabsp);
    }
  }
  else
    *tabsp = spacing;
  *++tabsp = 0;
  printf("generated tab list beginning with %d\n", *tabs);
  switch(mode) {
  case '1': {
    /* printf("\nin main, nexttab = %d\n", nexttab);    entab(tabs); */
    entab(tabs, spacing);
    break;
  }
  case '2': {
    detab(tabs, spacing);
    break;
  }
  default:
    printf("I didn't understand the mode indicator %c", mode);
  }
  return 0;
}

  
