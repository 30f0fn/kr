#include "kr-resources.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define MAX_OCCURRENCES 100

/* write a program which prints a list of all words in a document, plus for each word, the numbers of the lines on which it occurs. 

use a binary tree.  but modify tnode to contain an array of ints, instead of count.
*/


int _getword(char*, int);


struct tnode {
  char *word;
  int count;
  short lines[MAX_OCCURRENCES]; // not sure why this isn't *lines
  char *chrap;
  struct tnode *left;
  struct tnode *right;
};



struct tnode *addentry(struct tnode *, char *, int);
void printindex(struct tnode *);
int getword(char *, int);


int main() {
  struct tnode *root;
  char word[MAXWORD];
  root = NULL;
  int linenum = 1; 
  int c;
  while((c = getword(word, MAXWORD)) != EOF) {
    if(c == '\n') {
      linenum++;
    }
    else if(isalpha(word[0])) {
      root = addentry(root, word, linenum);
    }
  }
  printindex(root);
  return 0;
}

struct tnode *talloc(void);

struct tnode *addentry(struct tnode *p, char *w, int linenum) {
  int cond;
  if(p == NULL) {
    p = talloc();
    p->word = strdup(w);
    p->count = 1;
    (p->lines)[0] = linenum;
    /* printf("found \"%s\" on line %d\n", p->word, (p->lines)[0]); */
    p->left = p->right = NULL;
  }
  else if((cond = strcmp(w, p->word)) == 0) {
    p->count++;
    (p->lines)[p->count - 1] = linenum;    
    printf("found %s on line %d\n", p->word, (p->lines)[p->count - 1]);
  }
  else if(cond < 0)
    p->left = addentry(p->left, w, linenum);
  else
    p->right = addentry(p->right, w, linenum);
  return p;
}

void printindex(struct tnode *p) {
  if(p) {
    printindex(p->left);
    printf("%s: ", p->word);
    for(int i = 0; i < p->count; i++) {
      char sep = (i + 1 < p->count) ? ',' : '\0';      
      printf(" %d%c", (p->lines)[i], sep);
    }
    printf("\n");
    printindex(p->right);
  }
}

struct tnode *talloc(void) {
  return (struct tnode *) malloc(sizeof(struct tnode));
}


int _getword(char *word, int lim) {
  int c, getch(void);
  void ungetch(int);
  char *w = word;

  char d;
  while(isspace(c = getch()) && c != '\n')
    ;

  if(c != EOF)
    *w++ = c;
  if(!isalpha(c)) { // initial is not alpha, so doesn't begin word
    *w = '\0'; // terminate the string
    return c; // return the nonalpha found char
  }

  for( ; --lim > 0; w++) {
    if(!isalnum(*w = getch())) {
      ungetch(*w);
      break;
    }
  }
  *w = '\0';
  /* printf("got word %s\n", word); */
  return word[0];
}
