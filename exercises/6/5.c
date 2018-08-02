# include "hash.h"
# include "kr-resources.h"

# define MAX_WORD 100
# define MAX_DEF 100

/* undef() removes name and a definition from the table maintained by lookup and install. */

void uninstall(char *name);

// test driver
int main(int argc, char *argv[]) {
  for(; ; ) {
    char c = getchar();
    printf("starting loop...\n");
    printf("read command '%c'\n", c);
    if(c == 'i') {
      char name[MAX_WORD];
      char defn[MAX_DEF];
      getword(name, MAX_WORD);
      printf("read name '%s'\n", name);
      while(isspace(c = getchar()))
        ;
      char *d;
      for(d = defn, *d = c; (*++d = getchar()) != '\n'; )
        ;
      *d = '\0';
      printf("read defn %s\n", defn);
      struct nlist *np;
      np = install(name, defn);
      printf("installed name %s with value %s\n", name, np->defn);
    }
    else if(c == 'u') {
      char name[MAX_WORD];
      getword(name, MAX_WORD);
      printf("read name '%s'\n", name);
      uninstall(name);
      printf("uninstalled name %s\n", name);
    }
    else if(c == 'l') {
      char name[MAX_WORD];
      getword(name, MAX_WORD);
      printf("read name '%s'\n", name);
      struct nlist *np = malloc(sizeof(struct nlist));
      printf("allocated to np; looking up %s\n", name);
      np = lookup(name);
      if(np) {
        printf("found entry '%s' with value '%s'\n", name, np->defn);
      }
      else {
          printf("No entry with name %s was found!\n", name);
      }
    }

    else {
      while(isspace(c = getchar()) && c != '\n')
        ;
      printf("I didn't recognize the command %c\n", c);
    }
  }
}


// get the np, plus parent if there is one;
// if parent is found, point it to np->next
// else insert np->next into hashtab
void uninstall(char *name) {
  struct nlist *parent, *np;
  parent = NULL;
  for(np = hashtab[hash(name)];
      np && strcmp(np->name, name) != 0;
      parent = np, np = np->next)
    ;
  if(!np) {
    printf("uninstall: no entry with name '%d' was found!\n", name);
  }
  if(parent) { //child is not none, so point parent to its child
    /* printf("found parent\n"); */
    parent->next = np->next;
  }
  else {
    /* printf("no parent\n"); */
    hashtab[hash(name)] = np->next;
  }
  free((void *) np);
}




