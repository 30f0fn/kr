# include <stdio.h>

/*
converts characters like newline and tab into visible escape sequences like \n and \t as it copies string t to string s.  Write a function in the other direction as well.
*/


void escape(char s[], char t[]) {
  char c;
  int i, j;
  for(i = 0, j = 0; i != '\0'; i++, j++) {
    switch(c = s[i]) {
    /* case '\w': t[j] = '\\'; t[++j] = 'w'; break; */
    case '\n': t[j] = '\\'; t[++j] = 'n'; break;
    case '\t': t[j] = '\\'; t[++j] = 't'; break;
    default: t[j] = t[i]; break;
    }
  }
  t[j] = '\0';
}

void de_escape(char t[], char s[]) {
  int escaping = 0;
  int i, j;
  for (i = 0, j = 0; i != '\0'; i++, j++) {
    switch(t[i]) {
      case '\\':
        switch(t[++i]) {
        case 'w': case 'n': case 't': s[j] = t[i]; break;
        }
    default: t[j] = t[i]; break;
    }
  }
  t[j] = '\0';
}

int main(int argc, int* argv[]) {

  int len = 1000;
  char s[len], t[2*len], s1[len];
  

  int i;
  char c;
  /* for (i = 0; (c = getchar()) != EOF && i < len; i++) */
  for (i = 0; (c = getchar()) != EOF && i < len; i++) {
    /* putchar(c); */
    s[i] = c;
  }
  s[i] = '\0';

  escape(s, t);
  de_escape(t, s1);

  for (int i = 0; s[i] != '\0' && t[i] != '\0'; i++) {
    if (s[i] != s1[i])
      printf("Error! Input char %c differs from output char %c\n", s[i], s1[i]);
    else if (s[i]=='\0')
      printf("Error! Input sequence is shorter.\n");
    else if (s1[i]=='\0')
      printf("Error! Output sequence is shorter.\n");
  }
  printf("Transcription was successful!\n");
  // read some file into s.  escape s to t, descape t to s1, then check if s and 1 agree.

}
