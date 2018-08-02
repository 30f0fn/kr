# include <stdlib.h>
# include <stdio.h>
# include <string.h>

# define MAX_LINE 1000

/* 
Compares two files, printing the first line where they differ. 

Open them both.  
*/

void filecompare (char *f1, char *f2);

int main(int argc, char *argv[]) {
  filecompare(argv[1], argv[2]);
}

void filecompare (char *f1, char *f2) {
  FILE *fp1;
  FILE *fp2;
  fp1 = fopen(f1, "r");
  fp2 = fopen(f2, "r");
  char line1[MAX_LINE];
  char line2[MAX_LINE];
  
  for(int i = 0; ; i++) {
    printf("checking line %d...\n", i);
    int f1end = (fgets(line1, MAX_LINE, fp1) == NULL);
    int f2end = (fgets(line2, MAX_LINE, fp2) == NULL);
    if(f1end && f2end) {
      printf("->the files %s and %s agree on every line.\n", f1, f2);
      return;
    }
    else {
      if(strcmp(line1, line2) != 0) {
        printf("->the files differ at line %d.\n %s: %s %s: %s",
               i, f1, line1, f2, line2);
        return;
      }
    }
  }
}
