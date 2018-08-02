#include <stdio.h>
#include <string.h>

#define MAXLINES 500

/* 
revises readlines to store lines in an array supplied by main, rather than calling alloc to maintain storage.

in the original, alloc is called by readlines, to set aside storage for the pointer p to the current line.
 */

#define MAXLEN 1000 // max len of any input line

char *lineptr[MAXLINES];

char lines[MAXLINES][MAXLEN];

int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

int main() {
  int nlines; // number of lines read
  if((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    qsort(lineptr, 0, nlines - 1);
    writelines(lineptr, nlines - 1);
    return 0;
  } else {
    printf("error: input too big to sort\n");
    return 1;
  }
}

#define MAXLEN 1000 // max len of any input line

int getlinep(char *s, int maxlen);

int readlines(char *lineptr[], int maxlines) {
  int len, nlines; // len current line, and num lines so far read

  /* char *p, line[MAXLEN]; // pointer to current line, and current line */
  char line[MAXLEN];

  nlines = 0;
  while(nlines < maxlines && (len = getlinep(lines[nlines], MAXLEN)) > 0) {
    if(nlines >= maxlines)
      return -1;
    else {
      lines[nlines][len - 1] = '\0';
      /* lines[nlines][len - 1] = '\0'; */
      lineptr[nlines++] = lines[nlines]; 
    }
  }
  return nlines;
}

void writelines(char *lineptr[], int nlines) {
  while (nlines-- > 0)
    printf("%s\n", *lineptr++);
}

void qsort(char *v[], int left, int right) {
  int i, last;
  void swap(char *v[], int i, int j);
  
  if(left >= right)
    return;
  swap(v, left, (left + right) / 2);
  last = left;
  for(i = left+1; i <= right; i++) {
    if(strcmp(v[i], v[left]) < 0) {
      swap(v, ++last, i);
    }
  }
  swap(v, left, last);
  qsort(v, left, last - 1);
  qsort(v, last + 1, right);
}

void swap(char *v[], int i, int j) {
  char *temp;
  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
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
