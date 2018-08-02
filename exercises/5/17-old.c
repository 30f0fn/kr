#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIELD_SEPARATOR '&'
#define MAXLINES 100
#define FIELDSIZE_MAX 100
#define MAXLINE 100

/* 
sort lines according to their values in specified fields, with sorting method specified for each field.

Each line is split into an array of pointers, each pointer representing a field value for that line.

the first line of the input file is taken to supply field titles, as in for example

TITLE & AUTHOR &  DATE

the sort method is given with arguments like this:

+TITLE -d -r +DATE -n

the default sort simply takes the field in order sorting them by strsort

to implement, here are the tasks:

I. parse the input file.  This involves two main tasks.  First, use the first line of the input file to initialize an array *fieldvalues[numlines][numfields] of arrays of pointers, along with an array of field titles (so that they can be indexed).  Second,  elaborate readline into readlineintofields. readlineintofields takes as argument an array fieldvalues of arrays of pointers, with each pointer a string constituting a field entry.  It advances to the next array of pointers whenever it encounters a newline. It advances to the next pointer whenever it encounters the field separator character.

II. parse the command line arguments, into an array c of pointers to comparison functions, and a permutation priority of the field indices. the nth entry of the priority array is the index of the nth mentioned fieldname in the command line arguments, and the nth entry c[n] of the comparison function array is the correspondingly specified comparison method for that field.

III. define a comparison function fieldcmp, which compares pointer arrays.  besides a couple of arrays char *a[], char *b[], it takes an array c of pointers to pointer comparison functions, and a permutation priority of the indices 0..len(a)-1.  It iterates through priority[0], ..., priority[len(a) - 1], seeking the first i such that the comparison c[i] distinguishes a and b.  fieldcmp then returns the value of this comparison c[i] between a,b at field priority[i].
*/



void printrow(char *t, char *s[], int numcols);
int _getline(char *s, int lim);
void lineintofields(char *line, char *fields[], int numfields);
/* int readlineintofields(char *fields[], int numfields); */
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

int main(int argc, char *argv[]) {

  char line[MAXLINE];
  _getline(line, MAXLINE);


  // get number of fields
  int numfields = 1;
  for(char *linep = line; *linep != '\0'; linep++) {
    if(*linep == FIELD_SEPARATOR)
      numfields++;
  }

  // initialize fieldnames, populate
  char *fieldnames[numfields];
  /* readlineintofields(fieldnames, numfields); */
  lineintofields(line, fieldnames, numfields);

  printf("getting field values...\n");
  
  // initialize fieldvalues, populate
  char *fieldvalues[numfields][MAXLINES];
  int numlines;

  
  for(numlines = 0;
      numlines < MAXLINES && _getline(line, MAXLINE) > 0;
      numlines++)
    {
      lineintofields(line, fieldvalues[numlines], numfields);
    }

  printf("read data into fields:\n");

  for(int row = 0; row < numlines; row++) {
    printrow("row", fieldvalues[row], numfields);
  }
 
  printrow("after reading data, fieldnames are", fieldnames, numfields);

  
  printf("initializing priority and comparison arrays...\n");

// initialize priority and comparison arrays, then populate from argc,argv
  int priority[numfields];
  int (*comparisons[numfields + 1])(const char *, const char *); //+ 1 for sentinel
  // parse commandline arguments to build priority and comparison arrays

  printf("running parseargs...\n");

  parseargs(argc, argv, fieldnames, numfields, priority, comparisons);

  printf("priority array: ");
  for(int i = 0; i < numfields; i++) {
    printf("%d ", priority[i]);
  }

  printf("sorting...\n");

  qsortf((void **) fieldvalues, 0, numlines, priority, comparisons); 

  printf("printing sorted lines\n");

  for(int line = 0; line < numlines; line++)
    for(int field = 0; field < numfields; field++) {
      printf("%s", fieldvalues[line][field]);
      if(field < numfields)
        printf(" % ");
    }
  
  return 0;
  /* } */
  /* else { */
    /* printf("input has too many lines to sort\n"); */
    /* return -1; */
  /* } */
}











void lineintofields(char *line, char *fields[], int numfields) {
  int charindex, fieldindex, valsize; // currently read char; current target field; size of current val
  char currentval[FIELDSIZE_MAX];
  char c;
  char *valp;
  fieldindex = 0;
  valsize = 0;
  /* printf("%c\n", line[1]); */
  for(charindex = 0; (c = line[charindex]) != '\0'; charindex++) {
    /* putchar(c); */
    if(valsize == 0 && line[charindex] == ' ') {
      ;
      /* printf("skipping whitespace\n"); */
    }
    else if(c != FIELD_SEPARATOR && c != '\n') {
      currentval[valsize++] = c;
    }
    else { // c==FIELD_SEPARATOR 
      currentval[valsize] = '\0';
      while(currentval[valsize-1] == ' ') {
        currentval[--valsize] = '\0';
      }
      valp = malloc(valsize);
      strcpy(valp, currentval); 
      fields[fieldindex++] = valp;
      valsize = 0;
    }
    
  }
  /* printrow("intofields", fields, numfields); */
}


void printrow(char *t, char *s[], int numcols) {
  printf("%s: ", t);
  for(int i = 0; i < numcols; i++) {
    printf("%d:%s%s", i, s[i], i + 1 < numcols? " ": "");
  }
  putchar('\n');
}



int _getline(char s[], int lim) {
  char c;
  int i = 0;
  while((s[i++] = (c = getchar())) != EOF && c != '\n' && lim--)
    ;
  if(c == '\n')
    s[i++] = c;
  s[i] = '\0';
  return c;
}




/*
print output
*/










int rstrcmp(char const *, char const *); // adding const fixes compiler warning

int numcmp(char const *, char const *); 
int rnumcmp(const char *, const char *); 

int fstrcmp(char const *, char const *); 
int frstrcmp(char const *, char const *); 

int dstrcmp(char const *, char const *); 
int drstrcmp(char const *, char const *); 
int dfstrcmp(char const *, char const *); 
int dfrstrcmp(char const *, char const *); 


int getfieldindex(char *fieldname, char *fields[], int numfields);


/*
parsing the command line arguments
*/

int parseargs(int argc, char *argv[],
              char *fieldnames[], int numfields, int priority[],
              int (*comparisons[])(const char *, const char *)) {



  int flat, numeric, reverse, dirorder;
  int field = 0;



  while(--argc > 0 && field < numfields ) {
    if(**++argv != '+') {
      printf("sorry I did not understand those arguments.\n");
      return -1;
    }
    else {
      printf("handling flag %s\n", *argv);
      // we have found a field indicator
      // add field to the priority array
      /* for(int i = 0; i < numfields; i++) */
        /* printf(fields[i]); */

      priority[field] = getfieldindex(*argv+1, fieldnames, numfields);

      // get comparison and add to the comparisons array
      flat = numeric = reverse = dirorder = 0;
      while(--argc > 0 && **++argv == '-') {
        printf("handling the subflag %s\n", *argv);
        if(strcmp(*argv, "-f") == 0) 
          flat = 1;
        if(strcmp(*argv, "-n") == 0)
          numeric = 1;
        if(strcmp(*argv, "-r") == 0)
          reverse = 1;
        if(strcmp(*argv, "-d") == 0)
          dirorder = 1;
        int (* cmp) (const char *, const char *);
        cmp = (numeric ? (reverse ? rnumcmp : numcmp) :
               (reverse ? (flat? (dirorder?dfrstrcmp:frstrcmp) :
                           (dirorder?drstrcmp:rstrcmp)) :
                (flat? (dirorder?dfstrcmp:fstrcmp) : (dirorder?dstrcmp:strcmp))));
        comparisons[field] = cmp;

      } // now we have scanned through all - flags succeeding some + flag
      field++;
      /* printf("field flags = %d\n", field); */
    }
    comparisons[field] = NULL; // sentinel
  }

  
  int (* cmp) (const char *, const char *);
  // yuck below but don't know how to improve
  cmp = (numeric ? (reverse ? rnumcmp : numcmp) :
         (reverse ? (flat? (dirorder?dfrstrcmp:frstrcmp) : (dirorder?drstrcmp:rstrcmp)) :
          (flat? (dirorder?dfstrcmp:fstrcmp) : (dirorder?dstrcmp:strcmp))));

}




int getfieldindex(char *fieldname, char *fieldnames[], int numfields) {
  printf("got fieldname %s\n", fieldname);
  for(int i = 0; i < numfields; i++) {
    printf("comparing with %s\n", fieldnames[i]);
    if(strcmp(fieldnames[i], fieldname) == 0)
      return i;
  }
  return -1;
}

























int fieldcmp(char *line1[], char *line2[], 
              int priority[],
              int (*cmp[])(const char *, const char *)) {
   
  for(int i = 0; cmp[i]; i++) {
    char c;
    if((c = (*cmp[i])(line1[i], line2[i])) != 0) {
      return c;
    }
  }
  return 0;
}


/* 
the sort
*/


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


  for(i = left+1; i <= right; i++)
    if(fieldcmp(v[i], v[left], priority, comparisons) < 0) {
      swap(v, ++last, i);
    }


  swap(v, left, last);
  qsortf(v, left, last-1, priority, comparisons);
  qsortf(v, last+1, right, priority, comparisons);
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
  s1 = malloc(FIELDSIZE_MAX);
  t1 = malloc(FIELDSIZE_MAX);
  dirto(s1, s);
  dirto(t1, t);
  /* printf("FLATTENING %s -> %s\n", s, s1); */
  return strcmp((const char *) s1, (const char *) t1);
}


int fstrcmp(const char *s, const char *t) {
  printf("HELLO?! fstrcmp %s, %s\n", s, t);
  char *s1, *t1;
  s1 = malloc(FIELDSIZE_MAX);
  t1 = malloc(FIELDSIZE_MAX);
  flattento(s1, s);
  flattento(t1, t);
  return strcmp((const char *) s1, (const char *) t1);
}

int dfstrcmp(const char *s, const char *t) {
  printf("HELLO?! dfstrcmp %s, %s\n", s, t);
  char *s1, *t1;
  s1 = malloc(FIELDSIZE_MAX);
  t1 = malloc(FIELDSIZE_MAX);
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


