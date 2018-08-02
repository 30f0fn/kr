# include <stdio.h>


/*
a recursive implementation of string reversal.
*/

void swap(char s[], int i, int j) {
  char temp = s[i];
  s[i] = s[j];
  s[j] = temp;
}

void reverse(char s[], int ind) {
  static int strlen;
  for(strlen = 0; s[strlen] != '\0'; strlen++);
  if(ind < strlen / 2) {
    swap(s, ind, strlen - 1 - ind);
    reverse(s, ++ind);
  }
}



int main(int argc, char* argv[]) {
  /* take string argument from command line*/
  int arg_len = sizeof(argv[1])/sizeof(argv[1][0]);
  reverse(argv[1], 0);
  printf("reversing the input gave %s\n", argv[1]);
}

