/***global.h******from Aho, Sethi, Ullman*************************************/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define BSIZE 128
#define NONE -1
#define EOS '\0'

#define NUM 256
#define DIV 257
#define MOD 258
#define ID  259
#define DONE 260
#define READ 261
#define PRINT 262
#define IF 263
#define ELSE 264
#define THEN 265
#define END 266
#define BEGN 267
#define GOTO 268
#define LABEL 269
#define NUL 270
#define STRING 271
#define COMPARATOR 272


#define  SYMMAX 100   /* size of symtable */

char yystring[1000];
int yylex();

int tokenval;    /* value of token atribute  */
int lineno;

typedef struct entry entry;
struct entry { /* form of symbol table entry */
  char *lexptr;
  int token;
  entry *next;
  int count;
};
entry *symtable[SYMMAX]; /* symbol table */
entry *tokensym; /* use in place of tokenval for identifiers */

void error(char *m);
entry* lookup(char s[], int current_token);
void parse();
void expre();
void match(int t);

void parse();
void expr();
void term();
void factor();
void match(int t);

int lexan();
void emit(int t, int tval);
void init();
void exit(int n);
int main();

//added functions
void lines();
void lineend();
void statement();
