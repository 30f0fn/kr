# include "tree.h"

#define MAX_WORD 100

/*
prints the distinct words in its input, in decreasing order of frequency of occurrence.  Each word is preceded by its count.

strategies: store word counts in a binary tree as usual, together with a count of distinct words.  copy the nodes into a pointer array, apply qsort with custom cmp, and finally print.
*/


// declarations for main
struct tnode *addword(struct tnode *, char *, int *);
void flatteninto(struct tnode entries[], int *pos, struct tnode *);
void qsortf(struct tnode v[], int left, int right,
            int (*comp)(struct tnode, struct tnode));
int compfreq(struct tnode, struct tnode);
void arrprint(struct tnode[], int numwords);


int main() {

  char word[MAX_WORD];
  int numwords = 0;
  struct tnode *root;
  root = NULL;

  printf("READING FILE...\n");

  while(getword(word, MAX_WORD) != EOF) {
    /* printf("read the word %s\n", word); */
    if(isalpha(word[0])) {
      /* printf("inserting the word %s\n", word); */
      root = addword(root, word, &numwords);
    }
  }

  printf("INITIALIZING TNODE ARRAY; size = %d...\n", numwords);
  struct tnode words[numwords];
  printf("COPYING INTO TNODE ARRAY...\n");
  
  int *pos;
  *pos = 0;
  flatteninto(words, pos, root);

  /* printf("PRINTING UNSORTED ARRAY...\n"); */
  /* for(int i = 0; i < numwords; i++) { */
    /* printf("%d %s\n", words[i].count, words[i].word); */
  /* } */

  printf("SORTING...\n");
  qsortf(words, 0, numwords - 1,
         compfreq);
  printf("PRINTING...\n");  
  arrprint(words, numwords);
}

struct tnode *addword(struct tnode *p, char *w, int *numwords) {
  int cond;
  if(p == NULL) {
    p = talloc();
    p->word = strdup(w);
    /* printf("inserting tnode with word %s\n", w); */
    p->count = 1;
    p->left = p->right = NULL;
    ++*numwords;
    /* printf("incrementing numwords to %d\n", *numwords); */
  }
  else if((cond = strcmp(w, p->word)) == 0) {
    p->count++;
    /* printf("incrementing count of tnode with word %s, to %d\n", w, p->count); */
  }

  else if(cond < 0)
    p->left = addword(p->left, w, numwords);
  else
    p->right = addword(p->right, w, numwords);
  return p;
}

// copy nodes of tree to an array
void flatteninto(struct tnode entries[], int *pos, struct tnode *entry) {
  if(entry) {
    flatteninto(entries, pos, entry->left);
    /* printf("copying %s to position %d\n", entry->word, *pos); */
    entries[(*pos)++] = *entry;
    flatteninto(entries, pos, entry->right);
  }
}


void arrprint(struct tnode words[], int numwords) {
  struct tnode tn;
  for(int i = 0; i < numwords; i++) {
    tn = words[i];
    printf("%4d\t%s\n", tn.count, tn.word);
  }
}


// compare tnodes by frequency, for the sort
int compfreq(struct tnode u, struct tnode v) {
  /* printf("comparing %s and %s\n", u->word, v->word); */
  /* printf("comparing %d and %d\n", u.count, v.count); */
  return v.count - u.count;
}


// the sort
void qsortf(struct tnode v[], int left, int right,
           int (*comp)(struct tnode, struct tnode)) {


  /* printf("INITIALIZING\n"); */

  int i, last;
  void swap(struct tnode v[], int, int);

  /* printf("CHECKING FOR TERMINATION\n"); */

  if(left >= right)
    return;

  /* printf("POSITIONING PIVOT\n"); */

  swap(v, left, (left + right) / 2);
  // left is pivot
  last = left;
  // last is last position arranged to be no greater than pivot

  /* printf("ENTERING MAIN LOOP\n"); */

  for(i = left+1; i <= right; i++) {
    /* printf("handling i=%d in interval [%d, %d]\n", i, left+1, right); */
    /* printf("about to compare v[i]->count = %d and v[left]->count = %d\n", */
           /* v[i].count, v[left].count);     */
    if((*comp)(v[i], v[left]) < 0) {
      /* printf("swapping...\n"); */
      swap(v, ++last, i);
    }
  }

  /* printf("REPOSITIONING PIVOT\n"); */


  swap(v, left, last);
  qsortf(v, left, last-1, comp);
  qsortf(v, last+1, right, comp);
}


void swap(struct tnode v[], int i, int j) {
  struct tnode temp;
  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}
