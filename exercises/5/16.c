#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
extend 15.c by adding "directory order" flag -d, which compares only letters, numbers and blanks.  make sure it works in conjunction with -f.

this could mean: identify all other characters with some one character before or after all proper comperables; or it could mean "skip over" each noncomparable character in either compared string; or it could mean terminate string at first noncomparable.  I will go for the second option since it seems most interesting.

to avoid too many tedious definitions, mw will just add the possibilities -d, -df, -dr, -drf, i.e., ignoring combos of -d with -n.

*/

#define MAXLINES 100
#define MAXLEN 100
char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsortp(void *lineptr[], int left, int right,
            int (*comp)(const char *, const char *));

int rstrcmp(char const *, char const *); // adding const fixes compiler warning

int numcmp(char const *, char const *); 
int rnumcmp(const char *, const char *); 

int fstrcmp(char const *, char const *); 
int frstrcmp(char const *, char const *); 

int dstrcmp(char const *, char const *); 
int drstrcmp(char const *, char const *); 
int dfstrcmp(char const *, char const *); 
int dfrstrcmp(char const *, char const *); 

/* 
the program
*/

int main(int argc, char *argv[]) {
  int nlines; 
  int flat = 0;
  int numeric = 0;
  int reverse = 0;
  int dirorder = 0;

  /* printf("checking flags\n"); */

  while(--argc > 0) {
    argv++;
    if(strcmp(*argv, "-f") == 0) 
      flat = 1;
    if(strcmp(*argv, "-n") == 0)
      numeric = 1;
    if(strcmp(*argv, "-r") == 0)
      reverse = 1;
    if(strcmp(*argv, "-d") == 0)
      dirorder = 1;
  }

  printf("flatten = %d, dirorder = %d\n", flat, dirorder);

  int (* cmp) (const char *, const char *);
  // yuck below but don't know how to improve
  cmp = (numeric ? (reverse ? rnumcmp : numcmp) :
         (reverse ? (flat? (dirorder?dfrstrcmp:frstrcmp) : (dirorder?drstrcmp:rstrcmp)) :
          (flat? (dirorder?dfstrcmp:fstrcmp) : (dirorder?dstrcmp:strcmp))));

  
  /* printf("cmp == dfstrcmp? %d\n", cmp == dfstrcmp); */

  if((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    qsortp((void **) lineptr, 0, nlines - 1,
           cmp);
    writelines(lineptr, nlines);
    return 0;
  }
  else {
    printf("input too big to sort\n");
    return -1;
  }
}



/* 
the sort
*/

void qsortp(void *v[], int left, int right,
           int (*comp)(const char *, const char *)) {


  int i, last;
  void swap(void *v[], int, int);

  if(left >= right)
    return;

  swap(v, left, (left + right) / 2);
  // left is pivot
  last = left;
  // last is last position arranged to be no greater than pivot


  for(i = left+1; i <= right; i++)
    if((*comp)(v[i], v[left]) < 0) {
      swap(v, ++last, i);
    }


  swap(v, left, last);
  qsortp(v, left, last-1, comp);
  qsortp(v, last+1, right, comp);
}


int numcmp(char const *s1, char const *s2) {
  printf("HELLO?! numstrcmp %s, %s\n", s1, s2);
  double v1, v2;

  v1 = atof(s1);
  v2 = atof(s2);
  if(v1 < v2)
    return -1;
  else if(v2 < v1)
    return 1;
  else
    return 0;
}

int rnumcmp(const char *s, const char *t) {
  printf("HELLO?! rnumstrcmp %s, %s\n", s, t);
  return -numcmp(s, t);
}

int rstrcmp(const char *s, const char *t) {
  printf("HELLO?! rstrcmp %s, %s\n", s, t);
   return -strcmp(s, t);
 }

void dirto(char *s1, const char *s) {
  const char *ss = s;
  char *ss1 = s1;
  for( ; *s; s++) {
    if('a' <= *s && *s <= 'z' || 'A' <= *s && *s <= 'Z'
       || *s == ' ' || '0' <= *s && *s <= '9') {
      *s1++ = *s;
    }
    /* else */
      /* *s1++ = '#'; */
  }
  printf("DIRORDERED %s into %s\n", ss, ss1);

}


void dirflattento(char *s1, const char *s) {
  const char *ss = s;
  char *ss1 = s1;
  for( ; *s; s++) {
    if('A' <= *s && *s <= 'Z') 
      *s1++ = *s - ('A' - 'a');
    else if('0' <= *s && *s <= '9' || 'a' <= *s && *s <= 'z' || *s == ' ')
      *s1++ = *s;
  }
  printf("DIRORDERED %s into %s\n", ss, ss1);
}

void flattento(char *s1, const char *s) {
  for( ; *s; s++) {
    if('A' <= *s && *s <= 'Z') 
      *s1++ = *s - ('A' - 'a');
    else
      *s1++ = *s;
  }
}


int dstrcmp(const char *s, const char *t) {
  printf("HELLO?! dstrcmp %s, %s\n", s, t);
  char *s1, *t1;
  s1 = malloc(MAXLEN);
  t1 = malloc(MAXLEN);
  dirto(s1, s);
  dirto(t1, t);
  /* printf("FLATTENING %s -> %s\n", s, s1); */
  return strcmp((const char *) s1, (const char *) t1);
}


int fstrcmp(const char *s, const char *t) {
  printf("HELLO?! fstrcmp %s, %s\n", s, t);
  char *s1, *t1;
  s1 = malloc(MAXLEN);
  t1 = malloc(MAXLEN);
  flattento(s1, s);
  flattento(t1, t);
  return strcmp((const char *) s1, (const char *) t1);
}

int dfstrcmp(const char *s, const char *t) {
  printf("HELLO?! dfstrcmp %s, %s\n", s, t);
  char *s1, *t1;
  s1 = malloc(MAXLEN);
  t1 = malloc(MAXLEN);
  dirflattento(s1, s);
  dirflattento(t1, t);
  return strcmp((const char *) s1, (const char *) t1);
}


int frstrcmp(char const *s, char const *t) {
  printf("HELLO?! frstrcmp %s, %s\n", s, t);
  return -fstrcmp(s, t);
}

int dfrstrcmp(char const *s, char const *t) {
  printf("HELLO?! dfrstrcmp %s, %s\n", s, t);
  return -dfstrcmp(s, t);
}

int drstrcmp(char const *s, char const *t) {
  printf("HELLO?! drstrcmp %s, %s\n", s, t);
  return -dstrcmp(s, t);
}

void swap(void *v[], int i, int j) {
  int *temp;
  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

int getlinep(char *s, int lim);


int readlines(char *lineptr[], int maxlines) {
  int len, nlines; // len current line, and num lines so far read

  char *p, line[MAXLEN]; // pointer to current line, and current line
  /* char line[MAXLINES]; */


  nlines = 0;
  while(nlines < maxlines && (len = getlinep(line, MAXLINES)) > 0) {
    if(nlines >= maxlines || (p = malloc(len)) == NULL)
      return -1;
    else {
      line[len-1] = '\0'; // K&R delete newline for some reason
      strcpy(p, line); 
      lineptr[nlines++] = p;
    }
  }
  return nlines;
}


void writelines(char *lineptr[], int nlines) {
  while (nlines-- > 0)
    printf("%s\n", *lineptr++);
}

int getlinep(char *s, int lim) {
  char c;
  int i = 0;
  while((*(s+i) = (c = getchar())) != '\n' && c != EOF && i++ < lim)
    ;
  if(c == '\n') 
    *(s+i++) = c;
  *(s+i) = '\0';
  return i;
}

