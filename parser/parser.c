#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "../symbol_table/hashtable.h"
#include "../lexer/lex.h"
#include "../list/list.h"

//Grammar in grammar.txt

struct list_t *symbol;
struct hashtable_t *symbol_table;

struct List list = {.first = NULL};

char *_EOI   = "\0";
char *_PLUS  = "+";
char *_EOL   = ";";
char *_EQ	 = "=";
char *_PRINT = "print";

void eval_list(struct List *list);

void prog(void)
{
	cmd();
	
	if (list.first != NULL)
	{
		//print_list(&list);
		eval_list(&list);
		reset_list(&list);
	}
	
	loop();

	reset_list(&list);
}

void loop(void)
{
	if (match(EOI))
	{
		insert_token(&list, EOI, _EOI);
		return;
	}

	prog();
}

void cmd(void)
{
	if (match(VAR))
	{
		char _VAR[yyleng+1];
		memcpy(_VAR, yytext, yyleng);
		_VAR[yyleng] = '\0';
		insert_token(&list, VAR, _VAR);
		
		advance();
		
		if (match(EQ))
		{
			insert_token(&list, EQ, _EQ);
			advance();
			expr();
		}
		else
		{
			puts("Expected '='");
			return;
		}
	}
	else if (match(PRINT))
	{
		insert_token(&list, PRINT, _PRINT);
		advance();
		expr();
	}
	else if (match(EOL)) 
	{
		//insert_token(&list, EOL, _EOL);
		advance();
		return;
	}
	else
	{
		advance();
		puts("Expected <VAR> or 'print'");
	}
}

void expr(void)
{
	if (match(VAR) || match(NUM))
	{
		char _VAR_OR_NUM[yyleng+1];
		memcpy(_VAR_OR_NUM, yytext, yyleng);
		_VAR_OR_NUM[yyleng] = '\0';
			
		if (match(VAR))
			insert_token(&list, VAR, _VAR_OR_NUM);
		else
			insert_token(&list, NUM, _VAR_OR_NUM);

		advance();
		rest();
	}
	else
	{
		advance();
		puts("Expected <VAR> or <NUM>");
	}
}

void rest(void)
{
	if (match(PLUS))
	{
		insert_token(&list, PLUS, _PLUS);
		advance();	
		expr();
	}
	else if (match(EOL))
	{
		insert_token(&list, EOL, _EOL);
		return;
	}
	else
		puts("Expected '+' or ';'");
}

int eval_token(struct Token *token)
{
	int ret;
	struct list_t *var_val;

	if (token->type == NUM)
		ret = atoi(token->lexeme);
	else if (token->type == VAR)
	{
		var_val = lookup_string(symbol_table, token->lexeme);
		
		if ((var_val == NULL) || (var_val->value == NULL))
		{
			printf("Undefined variable '%s', default to 0\n", token->lexeme);
			return 0;
		}

		ret = *(var_val->value);
	}

	return ret;
}

int eval_expression(struct Token *begin)
{
	int count = 0;
	if ( (begin->type == NUM) || (begin->type == VAR) )
		count += eval_token(begin); 
	else
	{
		puts("Fucked expression");
	}

	while (begin->type != EOL)
	{
		if (begin->type == PLUS)
		{
			begin = begin->next;
			count += eval_token(begin);
		}

		begin = begin->next;
	}

	return count;
}

void eval_list(struct List *list)
{

	struct Token *aux = list->first;

	if (aux->type == PRINT)
	{
		aux = aux->next;

		printf("%d\n", eval_expression(aux));
	}
	else if (aux->type == VAR)
	{
		symbol = lookup_string(symbol_table, aux->lexeme);
		if (symbol == NULL)
		{
			add_string(symbol_table, aux->lexeme);
			symbol = lookup_string(symbol_table, aux->lexeme);
		}
		if (symbol->value == NULL)
			symbol->value = malloc(sizeof(int));
		
		aux = aux->next;
		if (aux->type == EQ)
		{
			aux = aux->next;	
			int val = eval_expression(aux);

			*(symbol->value) = val;//eval_expression(aux);		
		}
	}
	else
		puts("Go fuck yourself");	
}