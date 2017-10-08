/*** parser.c  *****from Aho, Sethi, Ullman**************/

#include "global.h"

int lookahead;
void parse()   /*parses and translates expression list  */
{
	lookahead = yylex(); /* was lookahead = laxan() */
	lines();
//	while(lookahead != DONE) {
//		expr(); match(';');
//	}
//	lines();
}

/*
E -> TE'
 parse_E(){
   parse_term();
   Parse_E'();
}


E'-> +TE' | epsilon
 parse_E'() {
   if (lookahead == '+') {
       match('+');
       parse_T();
       parse_E'();
      }
   else
    if (lookahead == '+') {
       match('+');
       parse_T();
       parse_E'();
     }
   else error("unexpected token");
 }

The resulting code is a result of:
  -  removing the tail recursion from parse_E'()
  -  inlining the modified parse_E'() in parse_E().

*/

// <lines> -> LABEL <linetail><lines>

void expr()
{
	int t;
	term();
	while(1)
		switch (lookahead) {
		case '+': case '-':
			t=lookahead;
			match(lookahead); term(); emit(t, NONE);
			continue;
		default:
			return;
	}
}

/*
 T  -> FT'
 T' -> *FT' | epsilon 
 Similar steps: remove recursion, inline
*/
void term()
{
	int t;
	factor();
	while(1)
		switch(lookahead) {
		case '*': case '/' : case DIV: case MOD:
			t=lookahead;
			match(lookahead); factor(); emit (t, NONE);
			continue;
		default:
			return;
		}
}

/*
 F -> ( E ) | ID | NUM
*/
void factor()
{
		switch(lookahead) {
			case '(':
				match('('); expr(); match(')'); break;
			case NUM:
				emit(NUM, tokenval); match(NUM); break;
			case ID:
				emit(ID, tokenval); match(ID); break;
			default:
				error("syntax error");
	}
}

void match(t)
	int t;
{
	if (lookahead == t){
		printf("MATCH");
		lookahead = yylex();
	}
	else error("syntax error - unexpected token");
}



/*---------- ADDED CODE ----------*/

void lines(){   //rename linenum

	printf("%d",lookahead);
	printf("\n");	

	while(lookahead != DONE){
		switch(lookahead){
			case NUM:
				printf("num\n");
				match(lookahead);
				lineend();
				continue;
			default:
				error("parsing failed\n");
				break;
		}
	}

}

void lineend(){  //rename lines
	
	printf("%d",lookahead);
	printf("\n");

	switch(lookahead){
		case BEGN:
			printf("begin\n");
			match(lookahead);
			break;
		case END:
			printf("end\n");
			match(lookahead);
			break;
		case DONE:
			printf("end of file\n");
			match(lookahead);
			break;
		default:
			printf("statement\n");
			statement();	
	}

}


void statement(){

	printf("%d",lookahead);
	printf("\n");

	switch(lookahead){
		case NUL:
			printf("null\n");
			match(lookahead);
			match(';');
//			gotostmt();
			break;
		case ID:
			printf("variable\n");
			assignment();
			match(lookahead);
			match(';');
//			gotostmt();
			break;
		case IF:
			printf("if\n");
//			ifstmt();
			break;
		case PRINT:
			printf("print\n");
			match(lookahead);
			match(';');
//			gotostmt();
			break;
		default:
			error("parsing failed");
		
			
	}

}

void assignment(){

	printf("%d",lookahead);
	printf("\n");

	switch(lookahead){
		case ID:
			printf("assignment\n");
			match(lookahead);
			match('=');
//			printf("%d\n",lookahead);
//			printf("yeet2");
//			printf("%d",lookahead);
			expr();
//			printf("yeet");
			break;
		default:
			error("parsing failed\n");
	}

}

