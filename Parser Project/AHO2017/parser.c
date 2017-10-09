/*** parser.c  *****from Aho, Sethi, Ullman**************/

#include "global.h"

int lookahead;
int lookaheadcopy;
void parse()   /*parses and translates expression list  */
{
	lookahead = yylex(); /* was lookahead = laxan() */
	lookaheadcopy = lookahead;
	parse_lines();
	printf("Parsing Successful!\n");
//	while(lookahead != DONE) {
//		expr(); match(';');
//	})
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
		lookahead = yylex();
	}
	else error("syntax error - unexpected token");
}



/*---------- ADDED CODE BY RUPAL SHAH----------*/

void parse_lines(){ 

	while(lookahead != DONE){
		switch(lookahead){
			case NUM:  //looks for line number
				match(lookahead);
				parse_line_end();
				continue;
			default:  
				error("Syntax Error.\n");
				printf("Parsing Failed.\n");
				break;
		}
	}

}


void parse_line_end(){ 

	switch(lookahead){
		case BEGN:
			match(lookahead);
			break;
		case END:
			match(lookahead);
			break;
		case DONE:
			match(lookahead);
			break;
		default:
			parse_statement();	
	}

}


void parse_statement(){

	switch(lookahead){
		case NUL:
			match(lookahead);
			match(';');
			parse_goto();
			break;
		case ID:
			parse_assignment();
			match(';');
			parse_goto();
			break;
		case IF:
			parse_if_statement();
			break;
		case PRINT:
			parse_print();
			match(';');
			parse_goto();
			break;
		default:
			error("Invalid Statement");
			printf("Parsing Failed.\n");
	}

}


void parse_assignment(){

	switch(lookahead){
		case ID:
			match(lookahead);
			match('=');
			expr();
			break;
		default:
			error("Invalid Assignment");
			printf("Parsing Failed\n");
	}

}

void parse_goto(){
	
	switch(lookahead){
		case GOTO:
			match(lookahead);
			match(NUM);  //look for number after goto
			
			if(lookahead == ';'){  //semicolon not required - do not output error if no semicolon
				match(lookahead);
			}
		default:  
			return;  //goto is not required - do not output error

	}
}


void parse_print(){

	switch(lookahead){
		case PRINT:
			match(lookahead);

			switch(lookahead){  //cases that can follow PRINT statement
				case ID:
					match(lookahead);
					break;	
				case STRING:
					match(lookahead);
					break;
				case NUM:
					match(lookahead);
					break;
				default:
					error("Invalid PRINT Statement.");
					printf("Parsing Failed.\n");

			}

			break;
		default:
			error("Invalid PRINT Statement.");
			printf("Parsing Failed.\n");
	}
}


void parse_if_statement(){
	
	switch(lookahead){
		case IF:
			
			match(lookahead);
			match('(');
			
			expr();
			
			switch(lookahead){
				case COMPARATOR:
					match(COMPARATOR);
					expr();
					break;
				default:
					error("Invalid IF Statement.");
					printf("Parsing Failed.\n");
			}
			
			match(')');
			
			if(lookahead == THEN){
				match(lookahead);
			}

			parse_goto();
			
			if(lookahead == ELSE){
				match(lookahead);
				parse_goto();
			}
				
			break;
		default:
			error("Invalid IF Statement.");
			printf("Parsing Failed.\n");
	}


}
