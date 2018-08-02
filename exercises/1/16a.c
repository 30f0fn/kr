# include <stdio.h>
# define MAXLINE 10

/*
 revise program in text to print length of longest line, and as much as possible of its text
 */

/* int getLine(char line[], int maxline); // read line up to maxline into line[], return length of whole (if not entirely copied) thing */
/* void copy(char to[], char from[]);  */

/* print length of longest input line, and its contents up to length MAXLINE */
int main() {

  int len; // length of line in line[]
  int max; // length of line in longest[]
  char line[MAXLINE]; // current line
  char longest[MAXLINE]; // currently longest seen

  printf("hi");

/*   // compute max and longest[] */
/*   max = 0; */
/*   while ((len = getLine(line, MAXLINE)) != 0) { */
/*     if (len > max) { */
/*       max = len; */
/*       copy(longest, line); */
/*     } */
/*   } */
  
/*   // printing */
/*   if (max > 0) printf("THE LONGEST LINE IS \n    %s\n", longest); */
/*   printf("ITS LENGTH IS %d\n", max); */
/*   // return status */
/*   return 0; */
/* } */

// read a line, copy its first lim characters into s[], and return its length
/* int getLine(char s[], int lim) { */
/*   int i, c; */
/*   for (i = 0; (c = getchar()) != '\n' && c != EOF; ++i) { */
/*     if (i < lim) s[i] = c; */
/*   } */
/*   if (c == '\n') { */
/*     if (i < lim) s[i] = c; */
/*     ++i; */
/*   } */
/*   s[i] = '\0'; */
/*   printf("%d ", i); */
/*   return i; */
/* } */

/* void copy(char to[], char from[]) { */
/*   int i; */
/*   i = 0; */
/*   while ((to[i]=from[i]) != '\0') ++i; */

  /* alternatively 
     for (int i=0; (to[i] == from[i]) != '\0') { } 
     ?
  */
}
