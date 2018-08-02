#include "hash.h"
#include "kr-resources.h"

#define MAX_WORD 100
#define MAX_DEFN 100
#define MAX_LINE 1000 
#define DEFN_FLAG "define"

/* 
a simple version of the #define preprocessor, suitable for use in C programs. this does not handle quotes. it doesn't handle macros with parameters.

scan through the document using getline().  

each time a line is read...

1. check if it is a definition
2. run it through the preprocessor; if it's a definition, just process the def section, else process the whole thing; 
3. if it's a definition, absorb the definition into the hashtable
4. if not a definition, print the line

aux functions:

getwordl(word, line, maxword, maxline)
expand(line)
absorb(line)  
is_def(line)
 */


int is_def(char *);
void absorb(char *);
void expand(char *);
int getwordl(char *, char **, int);

int main() {
  char line[MAX_LINE];
  char expandedline[MAX_LINE];
  char c;
  char name[MAX_WORD];
  char defn[MAX_DEFN];

  /* char test_isdef[] = "#define hi hello there"; */
  /* for(; ;) { */
    /* _getline(line, MAX_LINE); */
    /* printf("got line %s\n", line); */
  /* printf("DEFN_FLAG = %s\n", DEFN_FLAG); */
    /* printf("isdef returns %d\n", is_def(line)); */
  /* } */

  /* printf("entering main loop\n"); */
  while(_getline(line, MAX_LINE) > 0) {
    /* printf("got the line %s\n", line); */
    if(is_def(line)) {
      /* printf("identified definition: expanding\n"); */
      absorb(line);
    }
    else {
      /* printf("not a definition: expanding\n"); */
      expand(line);
    }
  }
}




// assume line ends with '\n' or EOF
// always return first char;
// if first char is alpha, consume until non-alphanum is read
// store all word is stored iff return value is alpha
// if called at alphanum string beginning with alpha, store string in word, else store first char in word
// if not in word, if char is alpha, enter word, else return char
// if in word, collect until char is not alphanum, then exit word and return word[0]
// in any case, the successive contents of word equal the contents of the file
int getwordl(char *word, char **line, int lim) {
  int c;
  char *wp = word;
  *wp = *(*line)++;
  if(!isalpha(*wp++)) { // initial is not alpha, so don't enter word
    *wp = '\0'; // terminate the string with the initial
    return *word; // return the nonalpha found char
  }
  // in a word
  for( ; --lim > 0; wp++) {
    if(!isalnum(*wp = *(*line)++)) {
      (*line)--;
      break;
    }
  }
  *wp = '\0';
  /* printf("got word %s\n", word); */
  return *word;
}






int is_def(char *line) {
  char flag[MAX_WORD];
  char *f = flag;
  if(*line++ == '#' && isalpha(*f++ = *line++)) {
    while(isalnum(*f++ = *line++))
      ;
    *--f = '\0';
    /* printf("hash sign found, checking '%s'=='%s'\n", flag, DEFN_FLAG); */
    return(strcmp(flag, DEFN_FLAG) == 0);      
  }
return 0;
}



// print result of 
void expand(char *line) {
  char c;
  char *word;
  while((c = getwordl(word, &line, MAX_WORD)) != '\n' && c != EOF) {
    if(!isalpha(c)) {
      putchar(c);
    }
    else { // we got a word
      struct nlist *np = lookup(word);
      if(np) {
        printf(np->defn);
      }
      else {
        printf(word); 
      }
    }
  }
  putchar(c);
  /* printf("end expansion\n"); */
}

// assume line begins with hash sign, followed by DEFN_FLAG, followed by whitespace
// skip past DEFN_FLAG
// set name = first word result of getword
// set defn = rest of line, minus '\n'
// install(name, defn)
void absorb(char *line) {
  char word[MAX_WORD];
  char defn[MAX_DEFN], name[MAX_WORD];
  defn[0] = '\0';
  char defnf[] = DEFN_FLAG;
  char c;
  /* printf("just after initializing, defn, parenthesized, is (%s)\n", defn); */
  struct nlist *np;
  while(!isspace(c = *line++));
  while(!isalpha(c = getwordl(word, &line, MAX_WORD))) {
    if(c == '\n' || c == EOF) {
      /* printf("bad definition"); */
      return;
    }
  }
  strcpy(name, word);
  while(isspace(c = *line++))
    ;
  line--;
  /* strcpy(defn, --line); */
  char ch[2];
  while((c = getwordl(word, &line, MAX_WORD)) != '\n' && c != EOF) {
    /* printf("got the word %s\n", word); */
    if(!isalpha(c)) {
      ch[0] = c; ch[1] = '\0';
      /* printf("adding (%s) to defn\n", ch); */
      strcat(defn, ch);
      /* printf("now defn, parenthesized, is (%s)\n", defn); */
    }
    else { // we got a word
      struct nlist *np  = lookup(word);
      if(np) {
        /* printf("adding %s to defn\n", np->defn); */
        strcat(defn, np->defn);
        /* printf("now defn, parenthesized, is (%s)\n", defn); */
      }
      else {
        /* printf("adding %s to defn\n", word); */
        strcat(defn, word); 
        /* printf("now defn, parenthesized, is (%s)\n", defn); */
      }
    }
  }
  /* for(d = defn, l = line; *l != '\n' && *l != EOF; *d++ = *l++) */
    /* ; */
  /* *d = '\0'; */
  /* printf("installing definition of %s as %s...\n", name, defn); */
  install(name, defn);
}


