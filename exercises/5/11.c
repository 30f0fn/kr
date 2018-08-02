# include <stdio.h>
# include <stdlib.h>
# define TAB_WIDTH 8
# define TAB_MAX 10
/* 
entab: when a tab stop follows a string of two or more consecutive spaces, replace that string of spaces with a tab character
this is to say: when line s[] ends with exactly n<9 spaces; while s has length divisble by TAB_WIDTH, replace s with s+\t
*/


// next tab is either next given, or default from TAB_WIDTH
void advance(int linelength, int **nexttab) {
  while(linelength >= **nexttab) {
    if(*(*nexttab+1)) {
      ++*nexttab;
    }
    else {
      *++*nexttab = *(*nexttab) + TAB_WIDTH;
      *(*nexttab + 1) = 0;
    }
  }
}


int entab(int *tabs) {

  printf("entabbing\n");

  int linelength = 0;
  int numspaces = 0;
  char c;
  int *tabp = tabs;
  int **nexttab = &tabp; // could use macro here
  while ((c = getchar()) != EOF) {
    switch(c) {
    case ' ': {
      numspaces++;
      if(linelength + numspaces == **nexttab) {
        putchar('\t');
        linelength += numspaces;
        advance(linelength, nexttab);
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
      // c is neither space nor newline,
      //so print all accumulated spaces followed by c
      while (numspaces > 0) {
        putchar(' '); linelength++; numspaces--;
      }
      putchar(c); linelength++;
      /* printf("\nin entab, nexttab = %d\n", **nexttab); */
      advance(linelength, nexttab);
    }
    }
  }
}



/* detab.  replaces tabs in the input with the proper number of spaces to the next tab stop.
say that a tab stop is every TAB_WIDTH spaces.
suppose line s[] has length len, and contains no tabs.  
we replace s+'\t' with TAB_WIDTH - (len % TAB_WIDTH) spaces.
*/

int detab(int *tabs) {
  printf("detabbing\n");

  int linelength = 0; // line length
  char c; // current char

  int *tabsp = tabs;
  int **nexttab = &tabsp;

  while ((c = getchar()) != EOF) {
    switch(c) {
    case '\t': {
      while(linelength < **nexttab) {
        putchar(' ');
        linelength++;
      }
      advance(linelength, nexttab);
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
      advance(++linelength, nexttab);
    }
    }
  }
}


int main(int argc, char *argv[]) {

  //entab/detab switch 
  char m = **++argv;
  printf("m = %c\n", m);

  // package tab args into 0-terminating array
  /* printf("argc = %d\n", argc); */
  int numtabs = argc - 2;
  int tabs[numtabs];
  tabs[0] = atoi(*++argv);
  int *tabsp = tabs;
  printf("about to generate tab list\n");
  while(--numtabs > 0) {
    *++tabsp = atoi(*++argv);
    printf("tab stop at %d\n", *tabsp);
  }
  *++tabsp = 0;
  printf("generated tab list\n");
  /* for(int i = 0; tabs[i++]; ){ */
    /* printf("tab at %d\n", tabs[i]); */
  /* } */
  switch(m) {
  case '1': {
    /* printf("\nin main, nexttab = %d\n", nexttab);    entab(tabs); */
    entab(tabs);
    break;
  }
  case '2': {
    detab(tabs);
    break;
  }
  default:
    printf("I didn't understand the mode indicator %c", m);
  }
  return 0;
}

  
