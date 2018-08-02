#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
extend 14.c by adding flag -f to ignore case distinctions in the (alphabetic) sort.

mw will ignore -f when combined with -n.
*/

#define MAXLINES 100
#define MAXLEN 100
char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsortp(void *lineptr[], int left, int right,
            int (*comp)(const char *, const char *));
int numcmp(char const *, char const *); // adding const fixes compiler warning
int rnumcmp(const char *, const char *); // adding const fixes compiler warning
int rstrcmp(char const *, char const *); // adding const fixes compiler warning
int frstrcmp(char const *, char const *); // adding const fixes compiler warning
int fstrcmp(char const *, char const *); // adding const fixes compiler warning

/* 
the program
*/

int main(int argc, char *argv[]) {
  int nlines; 
  int flat = 0;
  int numeric = 0;
  int reverse = 0;

  /* printf("checking flags\n"); */

  while(--argc > 0) {
    argv++;
    if(strcmp(*argv, "-f") == 0) 
      flat = 1;
    if(strcmp(*argv, "-n") == 0)
      numeric = 1;
    if(strcmp(*argv, "-r") == 0)
      reverse = 1;
  }

  /* printf("flatten = %d\n", flat); */

  int (* cmp) (const char *, const char *);
  cmp = (numeric ? (reverse ? rnumcmp : numcmp) :
         (reverse ? (flat? frstrcmp : rstrcmp) :
          (flat? fstrcmp : strcmp)));

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
  return -numcmp(s, t);
}

int rstrcmp(const char *s, const char *t) {
   return -strcmp(s, t);
 }

void flatten(char *s) {
  for( ; *s; s++) 
    if('A' <= *s && *s <= 'Z') 
      *s -= ('A' - 'a');
}


int fstrcmp(const char *s, const char *t) {
  /* printf("FSTRCMP!\n"); */
  char *s1, *t1;
  s1 = malloc(MAXLEN);
  t1 = malloc(MAXLEN);
  /* while(*s1++ = *s++); */
  /* while(*t1++ = *t++); */
  strcpy(s1, s);
  strcpy(t1, t);
  flatten(s1);
  flatten(t1);
  return strcmp((const char *) s1, (const char *) t1);
}


int frstrcmp(char const *s, char const *t) {
  return -fstrcmp(s, t);
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

