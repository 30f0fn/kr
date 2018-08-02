# include <stdio.h>


/*
expands shorthand notations like a-z in the string s1 into the equivalent list abc...xyz in s2.  Allows for letters of either case as well as digits, and be prepared to handle cases like a-b-c and a-z0-9 and -a-z.  Arrange that a leading or trailing - is taken literally.  Assumes s1 has size > 0.
*/

/* general idea: */
/* iterate through s, at each step getting c=s[i] */
/* two cases: c=='-', or not. */
/* If not, simply copy the letter to t. */
/* Else c=='-', and two cases are possible: */
/* (i) the earlier and later characters belong to the same range, and the earlier precedes the later */
/* (ii) otherwise. */
/* In case (ii), just treat the hyphen as a literal. */
/* In case (i), add all the letters in the range to t (excluding endpoints: so, a-b simply deletes the hyphen). */

void expand(char s[], char t[]) {
  int spans_range(char, char);
  t[0] = s[0];
  int i, j;
  for(i = 1, j = 1; s[i] != '\0' && s[i+1] != '\0'; i++) {
    if(s[i] == '-' && spans_range(s[i-1], s[i+1])) {
      for(char k = s[i - 1] + 1; k < s[i + 1]; k++) {
        printf("%d: %c\n", j, k);
        t[j++] = k;
      }
    }
    else {
      printf("%d: %c\n", j, s[i]);
      t[j++] = s[i];
    }
  }
  t[j++] = s[i];
  t[j] = '\0';
}

int spans_range(char a, char b) {
  return ('0' <= a && a <= b & b <= '9') ||
    ('a' <= a && a <= b && b <= 'z') ||
    ('A' <= a && a <= b && b <= 'Z');
}



int main(int argc, char* argv[]) {
  /* take string argument from command line, print its expansion */
  int len = sizeof(argv[1])/sizeof(argv[1][0]);
  char t[26*len];
  expand(argv[1], t);
  printf("%s\n", t);
  int len2 = sizeof(t)/sizeof(t[0]);
  int i;
  for (i = 0; t[i] !=0; i++);
  printf("length of array is %d\n", i);
}

