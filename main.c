#include <stdio.h>
#include "parser/parser.h"
#include "lexer/lex.h"
#include "symbol_table/hashtable.h"

int main(void)
{
	symbol = NULL;
	symbol_table = create_hashtable(15);
	
	prog();

	free_table(symbol_table);
	fcloseall();
	return 0;
}
