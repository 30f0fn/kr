#include <stdio.h>
#include <stdlib.h>

/*
Prints a set of files, starting each new one on a new page, with a title and a running page count for each file.

iterate through files with fileprint(*files++)
*/

#define NUMLINES 20
#define MAXLINE 1000
#define PROG_TITLE "8"

int fileprint(FILE *fp, char *filename, int *pagecount);

int main(int argc, char *argv[])
{
  if(argc < 2) {
    printf("Usage: \n\t %s filename1 filename2 ...\n", PROG_TITLE);
    return 1;
  }
  int pagecount = 0;
  FILE *fp;
  for(int i = 1; i < argc; i++) {
    fp = fopen(argv[i], "r");
    fileprint(fp, argv[i], &pagecount);
  }
}

int fileprint(FILE *fp, char *filename, int *pagecount) 
{
  int linenum = 0;
  char line[MAXLINE];
  printf("************ %s ************\n", filename);
  linenum++;
  while(fgets(line, MAXLINE, fp)) {
    if(linenum % NUMLINES == 0) {
      printf("****** %s - page %d ******\n", filename, (*pagecount)++);
      linenum = 1;
    }
    printf("%s", line);
    linenum++;
  }
}
