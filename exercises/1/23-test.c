#include <stdio.h>

int main () {
  printf("this line contains no comments\n");
  printf("/*this line is a comment\n*/");
  printf("the previous line was a comment\n");
  printf("this line /*here is a comment*/has a comment before the word \"has\"\n");
  printf("this line has some /* /* screwed up */ comments\n");
  printf("in previous, should not have seen \"screwed up\"\n");
}
