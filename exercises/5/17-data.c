#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIELD_SEPARATOR '&'
#define MAXLINES 100
#define FIELDSIZE_MAX 100
#define MAXLINE 100
#define MAXCOLS 100

int _getline(char *s, int lim);
/* void lineintofields(char *line, char *(*fields[]), int numfields); */
/* int readlineintofields(char *fields[], int numfields); */
void printrow(char *caption, char *fieldnames[], int numfields);

/* 
the program
*/

// I think the problem is the memory allocated by the call to malloc inside of lineintofields gets overwritten in function main

char **lineintofields(char *line, int numfields);




int main(int argc, char *argv[]) {
  
  // read and save first line of input 
  char firstline[MAXLINE];
  char line[MAXLINE];
  _getline(firstline, MAXLINE);

  // get number of fields
  int numfields = 1;
  for(char *linep = firstline; *linep != '\0'; linep++) {
    if(*linep == FIELD_SEPARATOR)
      numfields++;
  }

  char ** fieldnames;
  fieldnames = lineintofields(firstline, numfields);
  /* printrow("fieldnames are", fieldnames, numfields); */

  int numlines;
  char *** fieldvalues;
  fieldvalues = malloc(MAXLINES * FIELDSIZE_MAX * numfields);
  for(numlines = 0;
      numlines < MAXLINES && _getline(line, MAXLINE) > 0;
      numlines++)
    {
      * (fieldvalues + numlines) = lineintofields(line, numfields);
    }
  /* for(int row = 0; row < numlines; row++) { */
    /* printrow("row", fieldvalues[row], numfields); */
  /* } */

  return 0;
}


// split line into a row of fields and return it
// could return array of pointers instead?

char **lineintofields(char *line, int numfields) {
  char **row;
  row = malloc(FIELDSIZE_MAX * numfields);
  int charindex, fieldindex, valsize; // currently read char; current target field; size of current val
  char c;
  fieldindex = 0;
  valsize = 0;
  char current_val[FIELDSIZE_MAX];
  char *valp;
  for(charindex = 0;
      (c = line[charindex]) != '\0'  && fieldindex < numfields && valsize < FIELDSIZE_MAX;
      charindex++) {
    if(valsize == 0 && line[charindex] == ' ') {
      ;
    }
    else if(c != FIELD_SEPARATOR && c != '\n') {
      if(valsize < FIELDSIZE_MAX) {
        current_val[valsize++] = c;        
      }
      else {
        printf("Warning! Truncating an overlarge field\n");
      }
    }
    else { // (c==FIELD_SEPARATOR || c=='\n')
      current_val[valsize] = '\0'; // terminator
      while(current_val[valsize-1] == ' ') { // clear trailing whitespace
        current_val[--valsize] = '\0';
      } 
      valp = malloc(FIELDSIZE_MAX); // allocate and save
      strcpy(valp, current_val); // allocate and save
      row[fieldindex++] = valp;
      valsize = 0; // update indices
    }
  }
  return row;
}









int _getline(char s[], int lim) {
  char c;
  int i = 0;
  while((s[i++] = (c = getchar())) != EOF && c != '\n' && lim--)
    ;
  if(c == '\n')
    s[i++] = c;
  s[i] = '\0';
  /* printf("\n\ngl has %d\n", c); */
  return c;
}



void printrow(char *t, char *s[], int numcols) {
  printf("%s: \n\t", t);
  for(int i = 0; i < numcols; i++) {
    printf("%d:%s%s", i, s[i], i < numcols? "  ": "");
  }
  putchar('\n');
}



