# include <stdio.h>

/* write a loop equivalent to 

for (i = 0; i < lim - 1 && (c = getchar()) != '\n' && c != EOF; ++i) 
    s[i] = c;

which does not use &&.  

*/

/* instead of using a break statement, set the loop counter to the maximum */

int loop1() {
  char c;
  int i;
  for (int j = 0; j < lim - 1; j++) {
    i = j;
    c = getchar();
    if (c == '\n') j = lim - 1;
    if (c == EOF) j = lim - 1;
    if (j != i) s[i] = c; 
  }
} 

/* 
show j != i iff c is '\n' or EOF.
suppose j != i.   Then j got reassigned after i = j, so RHS holds.
conversely, suppose c is '\n' or EOF.  Then j is lim - 1.  However, at the outset of this pass of the for-loop, we had j < lim - 1, and this was the value of j when i got its last assignment, which was for i = j.  Hence, i < lim - 1.  So, j ! = i.
*/
