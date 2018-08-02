#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* 
the text version of getword does not properly handle underscores, string constants, comments, or preprocessor control lines.  write a better version.

underscores: allow a word to contain underscores anywhere.  

string constants: treat as single words.

comments and control lines: ignore like whitespace
*/


int _getword(char *word, int lim) {
  int c, getch(void);
  void ungetch(int);
  char *w = word;

  char d;
  while(isspace(c = getch()))
    ;

  // skip over multiline comment
  if((d = c) == '/') {
    if((c = getch()) != '*') {
      ungetch(c);
      return d;
    }
    else { // we are in a comment, eat until terminator
      for( ; d != '*' || c != '/'; d = c, c = getch()) {
        if(c == EOF) {
          return -1;        
        }
      }
    }
  }

  // skip control line
  if(c == '#')
     while((d = getch()) != '\n')
      ;

  if(c == '\"') {
    /* printf("entering quote\n"); */
    *w++ = c;
    while((c = (*w++ = getch())) != '\"') {
      /* putchar(c); */
      if(c == EOF)
        return -1;
      ;
    }
    *w = '\0';
    /* printf("exiting quote\n"); */
    printf("got quoted word %s\n", word);
    return word[0];
  }

  if(c != EOF)
    *w++ = c;
  if(!isalpha(c) && c != '_') { // initial is not alpha, so doesn't begin word
    *w = '\0'; // terminate the string
    return c; // return the nonalpha found char
  }

  for( ; --lim > 0; w++) {
    if(!isalnum(*w = getch()) && *w != '_') {
      ungetch(*w);
      break;
    }
  }
  *w = '\0';
  printf("got word %s\n", word);
  return word[0];
}





# define MAXWORD 100
# define NKEYS (sizeof keytab / sizeof keytab[0])

struct key {
  char * word;
  int count;
} keytab[] = {
  "auto", 0,
  "break", 0,
  "case", 0,
  "char", 0,
  "const", 0,
  "continue", 0,
  "default", 0,
  "do", 0,
  "double", 0,
  "else", 0,
  "enum", 0,
  "extern", 0,
  "float", 0,
  "for", 0,
  "goto", 0,
  "if", 0,
  "int", 0,
  "long", 0,
  "register", 0,
  "return", 0,
  "short", 0,
  "signed", 0,
  "sizeof", 0,
  "static", 0,
  "struct", 0,
  "switch", 0,
  "typedef", 0,
  "union", 0,
  "unsigned", 0,
  "void", 0,
  "volatile", 0,
  "while", 0,
};



int getword(char *, int);
int binsearch(char *, struct key *, int);

/* count C keywords */

int main(int argc, char argv[]) {
  int n;
  char word[MAXWORD];

  // count occurrences
  while(_getword(word, MAXWORD) != EOF) {
    if(isalpha(word[0])) {
      if((n = binsearch(word, keytab, NKEYS)) >= 0) {
        keytab[n].count++;
      }
    }
  }
  // print the results
  for(n = 0; n < NKEYS; n++) {
    if(keytab[n].count > 0) {
      printf("%4d %s\n",
             keytab[n].count, keytab[n].word);
    }
  }
  return 0;
}

int binsearch(char *word, struct key tab[], int n) {
  // n is number of keywords in tab
  int cond;
  int low, high, mid;

  low = 0;
  high = n-1;
  while(low <= high) {
    mid = (low + high) / 2;
    if((cond = strcmp(word, tab[mid].word)) < 0)
      high = mid - 1;
    else if(cond > 0)
      low = mid + 1;
    else
      return mid; // found it, return the index
  }
  return -1; // didn't find it
}















# define BUFSIZE 10

char buf[BUFSIZE]; // buffer for getch and ungetch
int bufp = 0; // next free position in buf

int getch(void) {
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
  if(bufp >= BUFSIZE) 
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}
