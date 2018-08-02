# include <stdio.h>

/* generate histogram of length of words in the input */

# define IN 1
# define OUT 0
# define MAX_LENGTH 10

int isWhiteSpace(char c) {
  return c == ' ' || c == '\t' || c == '\n';
}

void main() {

  int counts[MAX_LENGTH];
  for (int i = 0; i < MAX_LENGTH; i++) {
    counts[i] = 0;
  }

  /* scan input and count lengths in counts */

  int state = OUT;
  int len = 0;
  for (int c = getchar(); c != EOF; c = getchar()) {
    if (!isWhiteSpace(c)) {
      len++;
      state = IN;
    }
    /* upon in->out, increment count[len] and set len=0; */
    else if (state = IN) {
      counts[len]++;
      len = 0;
    }
  }

  for (int i = 0; i < MAX_LENGTH; i++) {
    printf("number of words of length %d: %d\n", i, counts[i]);
  }


  /* /\* print counts *\/ */
  int max_count = 0;
  for (int i = 0; i < MAX_LENGTH; i++) {
    if (counts[i] > max_count) max_count = counts[i];
  }
  
  /* printf("max count is %d", max_count); */
  
  int height = max_count;
  while (height > 0) {
    /* printf("%d", height); */
    for (int i = 1; i < MAX_LENGTH; i++) {
      if (counts[i] >= height) printf(" 0");
      else printf("  ");
    }
    putchar('\n');
    height--;
  }
  for (int i = 1; i < MAX_LENGTH; i++) {
    printf(" %d", i);
  }
  printf("\n");

}
