/*** main.c  * from Aho, Sethi, Ullman**/

#include "global.h"
#include <stdio.h> /* added JWJ */
#include <time.h> /* added JWJ for time */

int main()
{
    lineno = 1; 
    init();
    
    printf("Rupal Shah\n");
    
    time_t t;
    time(&t);
    printf("%s\n",ctime(&t));
    
    parse();
    
    print_symbol_table();
    exit(0);  /* successful termination */
}

/********************************************************************/
