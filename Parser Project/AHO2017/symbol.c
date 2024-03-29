/****    symbol.c   ****from Aho, Sethi, Ullman****/

#include "global.h" /*contains def of symboltable*/
#include "string.h"


/* Hashing comes from Algorithms and Data Structures handout */
enum { MULTIPLIER = 31 };
/* hash: compute hash value of string */
unsigned int hash(char *str)
{
  unsigned int h;
  unsigned char *p;

  h = 0;
  for (p = (unsigned char *) str; *p != 0; p++)
      h = MULTIPLIER * h + *p;
  return h % SYMMAX;
}

entry* lookup(char *s, int current_token)
{
        int h;
        entry *sym;
	char* temp;
	
        h = hash(s);
        for (sym = symtable[h]; sym != NULL; sym = sym->next)
            if (strcmp(s, sym->lexptr) == 0)
                return sym;

        /* Create if not found */
        sym = (entry *) malloc(sizeof(entry));
        temp = (char *) malloc(sizeof(char));
	temp = s;
	sym->lexptr = temp; /* assumed allocated elsewhere */
	sym->token = current_token;
        sym->next = symtable[h];
        symtable[h] = sym;

        return sym;
}

// Goes through the symbol table and prints out all of the symbols in the map
void print_symbol_table(){
        printf("\nSYMBOL TABLE:\n"); 
	for(int i = 0; i < SYMMAX; i++){
		entry *sym = symtable[i];
		if(sym != NULL){
			printf("   %s: %i\n", sym->lexptr, sym->count);
//			printf("%i\n",sym->count);
//			free(sym->lexptr);
			free(sym);
		}
	}
}
