# include <stdio.h>
# define TABWIDTH 8

/* 
entab: when a tab stop follows a string of two or more consecutive spaces, replace that string of spaces with a tab character
this is to say: when line s[] ends with exactly n<9 spaces; while s has length divisble by TABWIDTH, replace s with s+\t
*/


int entab() {
  int linelength = 0;
  int numspaces = 0;
  char c;
  while ((c = getchar()) != EOF) {
    if (c == ' ') {
      numspaces++;
      if ((linelength + numspaces) % TABWIDTH == 0) {
        putchar('\t');
        numspaces = 0;
      }
    }
    else if (c == '\n') {
      while (numspaces > 0) {
        putchar(' '); numspaces--;
      }
      putchar(c);
      linelength = 0;
    }
    else {
      while (numspaces > 0) {
        putchar(' '); numspaces--; linelength++;
      }
      putchar(c); linelength++;
    }
  }
}






int main(int argc, char *argv) {
  char m = **++argv;
  switch(m) {
  case '1': {
    entab(argv);
  }
  case '2': {
    detab(argv);
  }
  }
}
  
