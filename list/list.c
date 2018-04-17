#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void insert_token(struct List *list, int type, char *lexeme)
{
	if (list->first == NULL)
	{
		list->first = malloc(sizeof(struct Token));
		list->first->type = type;
		list->first->lexeme = strdup(lexeme);
		list->first->next = NULL;
	}
	else
	{
		struct Token *aux = list->first;
		while (aux->next != NULL)
			aux = aux->next;

		aux->next = malloc(sizeof(struct Token));
		aux->next->type = type;
		aux->next->lexeme = strdup(lexeme);
		aux->next->next = NULL;
	}
}

void print_list(struct List *list)
{
	struct Token *aux;
	if (list->first == NULL)
	{
		puts("Go fuck yourself");
		return;
	}	
	else
	{
		aux = list->first;
		while (aux != NULL)
		{
			printf("TOK(%d) = %s\n", aux->type, aux->lexeme);
			aux = aux->next;
		}
	}
}

void reset_list(struct List *list)
{
	struct Token *aux = list->first;
	while (aux != NULL)
	{
		list->first = list->first->next;	
		free(aux->lexeme);
		free(aux);
		aux = list->first;
	}
	free(list->first);
	list->first = NULL;
}