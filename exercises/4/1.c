# include <stdio.h>
# include <time.h>

clock_t time_taken;



/*
  strrindex(char s[], char t[]) returns the position of the rightmost occurrence of t in s, or -1 if there is none


  first set retval=-1.  
  Now at each index i of s, 
  scan through t until s[i+k]!=t[k]; 
  update retval to i if t[k]=='\0'
*/

int strrindex(char s[], char t[]) {
  int retval = -1;
  int i;
  for(i = 0; s[i] != '\0'; i++) {
    int k;
    for(k = 0; t[k] != '\0' && t[k] == s[i+k]; k++);
    if(t[k] == '\0')
      retval = i;
  }
  return retval;
}


int strrindex1(char s[], char t[]) {
  int retval = -1;
  int i, j, k;
  for(i = 0; s[i] != '\0'; i++) {
    for(j = i, k = 0; s[j] == t[k]; j++, k++);
    if(t[k] == '\0')
      retval = i-1;
  }
  return retval;
}



int main(int argc, char* argv[]) {
  int val;
  
  time_taken = clock();
  val = strrindex(argv[1], argv[2]);
  time_taken = clock() - time_taken;
  printf("%d\n", val);
  printf("strrindex took %d cycles\n", time_taken);
 
  time_taken = clock();
  val = strrindex1(argv[1], argv[2]);
  time_taken = clock() - time_taken;
  printf("strrindex1 took %d cycles\n", time_taken);

}

