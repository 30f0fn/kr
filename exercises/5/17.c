#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIELD_SEPARATOR '&'
#define MAXLINES 100
#define FIELDSIZE_MAX 100
#define MAXLINE 100
#define MAXCOLS 100

/* 
this one was tough...

sort lines according to their values in specified fields, with sorting method specified for each field.

Each line is parsed into an array of pointers, each pointer representing a field value for that line.

the first line of the input file is taken to supply field titles, as in for example

TITLE & AUTHOR &  DATE

the sort method is given with arguments like this:

+TITLE -d -r +DATE -n

the default sort simply takes the fields in order, sorting them by strsort

here are some implementation details.

I. parse the input file.  Begin by reading the first line.  Use this to initialize and populate **fieldnames, and also to initialize ***fieldvalues.  Then iterate through the lines of the file and populate the fieldvalues.  To parse each line we use the function lineintofields.

II. parse the command line arguments, into an array *comparisons[] of pointers to comparison functions, and a permutation, priority[], of the field indices. the nth entry of the priority array is the index of the nth mentioned fieldname in the command line arguments, and the nth entry c[n] of the comparison function array is the correspondingly specified comparison method for that field.

III. define a comparison function fieldcmp, which compares two parsed lines of the input files, as sequences of strings.  besides those two arguments, it takes the array c of pointers to pointer comparison functions, and a permutation priority of the indices 0..len(a)-1.  It iterates through the priority array, seeking the first i such that the comparison c[priority[i]] distinguishes a and b, and returning the value of this comparison.

IV.  The job ends with routine application of quicksort.
*/



int _getline(char *s, int lim);
/* void lineintofields(char *line, char *(*fields[]), int numfields); */
/* int readlineintofields(char *fields[], int numfields); */
void printrow(char *caption, char *fieldnames[], int numfields);

int parseargs(int argc, char *argv[],
              char *fields[],
              int numfields,
              int priority[],
              int (*cmp[])(const char *, const char *));


void qsortf(void *v[], 
            int left, int right,
            int priority[], 
            int (*comparisons[])(const char *, const char *));


/* 
the program
*/



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

  printf("running parseargs...\n");
// initialize priority and comparison arrays, then populate from argc, argv
  int priority[numfields];
  int (*comparisons[numfields + 1])(const char *, const char *); //+ 1 for sentinel
  // parse commandline arguments to build priority and comparison arrays
  int numflags = parseargs(argc, argv, fieldnames, numfields, priority, comparisons);

  if(numflags > 0) {
  printf("sorting...\n");
  qsortf((void **) fieldvalues, 0, numlines-1, priority, comparisons); 
  }

  printf("printing sorted lines...\n");

  for(int line = 0; line < numlines; line++) {
    for(int field = 0; field < numfields; field++) {
      printf("%s", fieldvalues[line][field]);
      if(field < numfields)
        printf(" % ");
    }
    printf("\n");
  }




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
parsing the command line arguments
*/
int getfieldindex(char *fieldname, char *fields[], int numfields);

int parseargs(int argc, char *argv[],
              char *fieldnames[], int numfields, int priority[],
              int (*comparisons[])(const char *, const char *)) {

  int flat, numeric, reverse, dirorder;
  int field = 0;

  ++argv; --argc;
  while(argc > 0 && field < numfields ) {
    if(**argv != '+') {
      printf("I expected the argument %s to begin with '+'.\n", **argv);
      return -1;
    }
    else {
      /* printf("handling flag %s\n", *argv); */
      // we have found a field indicator
      // add field to the priority array
      priority[field] = getfieldindex(*argv+1, fieldnames, numfields);
      // get comparison and add to the comparisons array
      flat = numeric = reverse = dirorder = 0;
      while(--argc > 0 && **++argv == '-') {
        /* printf("argc = %d\n", argc); */
        /* printf("handling the subflag %s\n", *argv); */
        if(strcmp(*argv, "-f") == 0) 
          flat = 1;
        if(strcmp(*argv, "-n") == 0)
          numeric = 1;
        if(strcmp(*argv, "-r") == 0)
          reverse = 1;
        if(strcmp(*argv, "-d") == 0)
          dirorder = 1;
      } // now we have scanned through all - flags succeeding some + flag
      int (* cmp) (const char *, const char *);
      cmp = (numeric ? (reverse ? rnumcmp : numcmp) :
             (reverse ? (flat? (dirorder?dfrstrcmp:frstrcmp) :
                         (dirorder?drstrcmp:rstrcmp)) :
              (flat? (dirorder?dfstrcmp:fstrcmp) : (dirorder?dstrcmp:strcmp))));
      comparisons[field] = cmp;
      /* printf("just set comparisons[%d] to %d!!!!!!!!!\n", field, cmp); */


      field++;
      /* printf("field flags = %d\n", field); */
    }
    comparisons[field] = NULL; // sentinel
  }
  return field;
}


int getfieldindex(char *fieldname, char *fieldnames[], int numfields) {
  /* printf("got fieldname %s\n", fieldname); */
  for(int i = 0; i < numfields; i++) {
    /* printf("comparing with %s\n", fieldnames[i]); */
    if(strcmp(fieldnames[i], fieldname) == 0) {
      /* printf("gfi applied to %s returning %d\n", fieldname, i); */
      return i;
    }
  }
  return -1;
}








int numcmp(char const *s1, char const *s2) {
  /* printf("HELLO?! numstrcmp %s, %s\n", s1, s2); */
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
  /* printf("HELLO?! rnumstrcmp %s, %s\n", s, t); */
  return -numcmp(s, t);
}

int rstrcmp(const char *s, const char *t) {
  /* printf("HELLO?! rstrcmp %s, %s\n", s, t); */
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
  /* printf("DIRORDERED %s into %s\n", ss, ss1); */

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
  /* printf("DIRORDERED %s into %s\n", ss, ss1); */
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
  /* printf("HELLO?! dstrcmp %s, %s\n", s, t); */
  char *s1, *t1;
  s1 = malloc(FIELDSIZE_MAX);
  t1 = malloc(FIELDSIZE_MAX);
  dirto(s1, s);
  dirto(t1, t);
  /* printf("FLATTENING %s -> %s\n", s, s1); */
  return strcmp((const char *) s1, (const char *) t1);
}


int fstrcmp(const char *s, const char *t) {
  /* printf("HELLO?! fstrcmp %s, %s\n", s, t); */
  char *s1, *t1;
  s1 = malloc(FIELDSIZE_MAX);
  t1 = malloc(FIELDSIZE_MAX);
  flattento(s1, s);
  flattento(t1, t);
  return strcmp((const char *) s1, (const char *) t1);
}

int dfstrcmp(const char *s, const char *t) {
  /* printf("HELLO?! dfstrcmp %s, %s\n", s, t); */
  char *s1, *t1;
  s1 = malloc(FIELDSIZE_MAX);
  t1 = malloc(FIELDSIZE_MAX);
  dirflattento(s1, s);
  dirflattento(t1, t);
  return strcmp((const char *) s1, (const char *) t1);
}


int frstrcmp(char const *s, char const *t) {
  /* printf("HELLO?! frstrcmp %s, %s\n", s, t); */
  return -fstrcmp(s, t);
}

int dfrstrcmp(char const *s, char const *t) {
  /* printf("HELLO?! dfrstrcmp %s, %s\n", s, t); */
  return -dfstrcmp(s, t);
}

int drstrcmp(char const *s, char const *t) {
  /* printf("HELLO?! drstrcmp %s, %s\n", s, t); */
  return -dstrcmp(s, t);
}





int fieldcmp(char *line1[], char *line2[], 
              int priority[],
              int (*cmp[])(const char *, const char *)) {
  int i = 0;
  while(cmp[i]) {
    char c;
    if((c = (*cmp[i])(line1[priority[i]], line2[priority[i]])) != 0) {
      return c;
    }
    i++;
  }
  return 0;
}




void swap(void *v[], int i, int j) {
  int *temp;
  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}








void qsortf(void *v[], 
            int left, int right,
            int priority[], 
            int (*comparisons[])(const char *, const char *)) {

  int i, last;
  void swap(void *v[], int, int);

  if(left >= right)
    return;

  swap(v, left, (left + right) / 2);
  // left is pivot
  last = left;
  // last is last position arranged to be no greater than pivot


  for(i = left+1; i <= right; i++) {
    if(fieldcmp(v[i], v[left], priority, comparisons) < 0) {
      swap(v, ++last, i);
    }
  }


  swap(v, left, last);



  qsortf(v, left, last-1, priority, comparisons);
  qsortf(v, last+1, right, priority, comparisons);
}
