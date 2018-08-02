#include "tree.h"
#include "fancygetword.h"

/* reads a C program and print in alphabetical order each group of variable names that are identical in the first six characters.  doesn't count words within strings and comments. 

after initializing, two stages: (i) build the tree.  (ii) print.

in stage (i), simply read through the file with getword, and whenever getword returns a variable name, insert it into the tree.  a variable name is a result of getword which begins with an a letter, but which is not a keyword.  assume isvarname(word) returns 1 iff word is a variable name.

in stage (ii), recurse through the tree.  

to handle words with fewer than six characters, treat the blank as a character.  then no two words with fewer than six characters have their first six letters in common, and each word with fewer than six characters forms a singleton group. to simplify the recursion, might simply pad these shorter words with blanks.  then delete the blanks upon printing.

now for the actual printing: recurse through the tree in alphabetical order.  print, as a singleton group, each word with no descendants but with depth less than six.  also, each time the depth falls below five, begin printing a group.  note that beginning and end of a group of words corresponds with the depth of the recursion falling below and then climbing back above level five.

*/

int isvarname(char *);
void printword(char *);
char *padword(char *, int);
void treeprintg(struct tnode *p, char seg[]);
void truncinto(char seg[], char *p);


# define SIM_DEPTH 6

int main() {

  // initialize the root of the tree
  struct tnode *root = NULL;
  char word[MAXWORD];



  // 
  while(_getword(word, MAXWORD) != EOF) {
    /* *word = padword(word); */
    if(isvarname(word)) {
      root = addtree(root, word);
      /* printf("added word %s\n", word); */
    }
  }
  printf("printing the groups...\n");
  char seg[5];
  if(root)
    truncinto(seg, root->word);
  treeprintg(root, seg);
  /* treeprint(root); */
}



int isvarname(char *word) {
  /* return 0; */
  return(isalpha(word[0]) && binsearch(word, keytab, NKEYS) < 0);
}

void printword(char *word) {
  char c;
  for( ; c = *word || c == ' '; word++)
    ;
  *word = '\0';
  printf("%s", word);
}

char *padword(char *word, int len) {
  char *w = word;
  int i;
  for(i = 0; *w; w++, i++)
    ;
  while(i < len)
    *w++ = ' ';
  *w = '\0';
  return word;
}

// returns 1 iff seg is an initial seg of word
// assume word has length >= length of seg
int matches(char seg[], char *word) {
  for( ; *seg ; word++, seg++)
    if(*word != *seg)
      return 0;
  return 1;
}



// print nodes of tree
// break with newline if *seg does not match *p->word
void treeprintg(struct tnode *p, char seg[]) {
  if(p != NULL) {
    treeprintg(p->left, seg);
    char s = matches(seg, p->word) ? '\0' : '\n';
    putchar(s);
    printf("%s ", p->word);
    truncinto(seg, p->word);
    treeprintg(p->right, seg);
  }
}



// put initial chars of word into seg
void truncinto(char seg[], char *word) {
  /* printf("truncating %s\n", word); */
  for(int i = 0; i < SIM_DEPTH; i++) {
    if(*word)
      seg[i] = *word++;
    else
      seg[i] = ' ';
  }
  /* printf("seg is %s\n", seg); */
}

