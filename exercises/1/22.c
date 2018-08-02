# include <stdio.h>
# define MAXCOL 50
/* 
'fold' long input lines into two or more shorter lines after the last non-blank character which occurs before the nth column of input.  do something intelligent with very long lines, and if there are no blanks or tabs before the specified column

initialize line buffer s[MAXCOL]
read into s the first up-to-MAXCOL characters of the line, recording position of last blank character;
print s up to position of last blank character;
copy remainder of s to front of s (don't need swap since no overlap of entries)
*/


int main() {

  char s[MAXCOL+1];
  char c;
  int lastSpace;

  /* read into s the first up-to-MAXCOL characters of the line, recording position of last blank character;   */
  int i;
  while (c != EOF) {
    lastSpace = -1;    
    for (i = 0; i < MAXCOL && (c = getchar()) != '\n' && c != EOF; i++) {
      s[i] = c;
      if (c == ' ') lastSpace = i;
    }
    /* if (c == '\n') s[i++] = c; */
    s[i] = '\0';

    if (i < MAXCOL) {
      printf(s);
      putchar('\n');
      /* printf("s had length < MAXCOL\n"); */
    }

    else {
      /* printf("s had length >= MAXCOL\n"); */
      if (lastSpace < 0) {
        printf(s);
        putchar('\n');
        printf("<<LINE WAS BROKEN WITHOUT SPACE!>>");
        putchar('\n');
      }
      else {
        for (int i = 0; i < lastSpace; i ++)
          putchar(s[i]);
        putchar('\n');
        for (int i = lastSpace + 1; i < MAXCOL; i++)
          putchar(s[i]);
      }
    }
  }


  /* two possibilities: (i) the line has length < MAXCOL; (ii) line length > MAXCOL
     in case (i), simply print the contents of s, including terminal '\n'
     case (ii) splits into subcases: 
     (iia) lastSpace<0: print s and give a warning
     (iib) lastSpace >= 0: print s just through lastSpace; print '\n'; print remainder of s
*/
  


}

int getLine() {}
