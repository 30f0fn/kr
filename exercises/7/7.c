#include <stdio.h>
#include <string.h>
#include "kr-resources.h"

#define MAXLINE 1000

/* 
Modifies the pattern finding program of Chapter 5 to take its input from a set of named files or, if no files are named as arguments, from the standard input. The file name will be printed when a matching line is found. 

if given with no arguments, put sources = {stdin}; else put sources = argv+1.  Now run find(sought, sources).

*/

int find(char *sought, FILE *fp, char *filename, int *numfound);

// find: print lines that match pattern from 1st arg 
// expect argc to be > 2, since argc[0] is 7, argc[1] is sought phrase.
// optional subsequent values argc[2], ..., are filenames.
int main(int argc, char *argv[])
{
  char line[MAXLINE];
  int numfound = 0;
  char *sought = argv[1];

  printf("searching for the string %s\n", sought);
  
  if(argc < 2)
    printf("usage: \n\tsearch-phrase file1 file2 ...\n\tsearch-phrase\n");
  if(argc == 2) 
    find(sought, stdin, "stdin", &numfound);
  else {
    FILE *fp;
    for(int i = 2; i < argc; i++) {
      fp = fopen(argv[i], "r");
      find(sought, fp, argv[i], &numfound);
      fclose(fp);
    }
  }
  printf("found %d occurrences\n", numfound);
  return numfound; 
}


int find(char *sought, FILE *fp, char *filename, int *numfound)
{
  /* printf("searching the file %s\n", filename); */
  char line[MAXLINE];
  for(int linenumber = 0; fgets(line, MAXLINE, fp); linenumber++) {
    if(strstr(line, sought) != NULL) {
      printf("[in %s, at line %d] %s", filename, linenumber, line);
      ++*numfound;
    }
  }
}
