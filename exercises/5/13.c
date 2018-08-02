# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define MAXLINE 1000

/*
prints the last n lines of the input.

store the n most recently read lines in a circular array l.

while readlines(temp[]) > 0, copy temp[] to l[i % n].

note l should be an array of pointers, rather than a 2d array.
*/

int getlinep(char *s, int maxlen);


// read last n lines into a circular array
// return index of last stored line
int lastlines(char *l[], int n) {

  // each entry p of l points to where a line is stored
  int pos, linelen; // position in l, and length, of currently read line
  char temp[MAXLINE]; // read a line into here
  char *p; // store a line here

  pos = 0;
  while((linelen = getlinep(temp, MAXLINE)) > 0) {
    if((p = malloc(linelen)) == NULL) {
      printf("Sorry, a line was too big!\n");
      return -1; // error, since not enough space
    }
    else {
      strcpy(p, temp);
      l[pos] = p;
      pos = (pos + 1) % n;
    }
  }
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




int main(int argc, char *argv[]) {
  int numlines = atoi(*++argv);
  if(numlines <= 0) {
    printf("you asked me to print fewer than one line, so I'm doing nothing.\n");
    return -1;
  }
  char *l[numlines];
  printf("cretaed arraye\n");
  for(int i = 0; i < numlines; i++)
    l[i] = "";
  int pos;
  pos = lastlines(l, numlines);
  for(int i = 0; i < numlines; i++) {
    printf("%s", l[pos]);
    pos = ((pos + 1) % numlines);
  }
}
