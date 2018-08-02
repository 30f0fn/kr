# include <stdio.h>

/* Removes all comments from a C program.  Handles quoted strings and character constants.

   Boolean "in-comment" is switched on by \/\*, switched off by next \*\/.  So, if some comment-delimiter precedes point, then in-comment is on if the latest comment-delimiter is open-comment, and it's off otherwise.

   Read through the input, and print each character scanned while inComment is false.

*/ 

int main() {
  
  int inComment = 0;
  char c;

  while ((c = getchar()) != EOF) {
    if (!inComment) {
      if (c == '/') {
        if ((c = getchar()) == '*') // comment just opened
          {
            inComment = 1;
            printf("<IN>");
          }
        else if (c == EOF) return 0;
        else {
          putchar('/');
          putchar(c);
        }
      }
      else putchar(c);
    }
    else { // in a comment
      if (c == '*') {
        if ((c = getchar()) == '/') // comment was closed
          {
            inComment = 0;
            printf("<OUT>");
          }
        else if (c == EOF) return 0;
      }
    }
  }

  return 0;

}
