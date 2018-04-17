#include <string.h>
#include <stdlib.h>
#include "hashtable.h"


struct hashtable_t *create_hashtable(int size)
{
	struct hashtable_t *new_hashtable;

	if (size < 1)
		return NULL;

	if ((new_hashtable = malloc(sizeof(struct hashtable_t))) == NULL)
		return NULL;

	if ((new_hashtable->table = malloc(sizeof(struct list_t *) * size)) == NULL)
		return NULL;

	for (int i = 0; i < size; i++)
		new_hashtable->table[i] = NULL;

	new_hashtable->size = size;

	return new_hashtable;
}

unsigned int hash(struct hashtable_t *hashtable, char *string)
{
	unsigned int hashval = 0;

	for (; *string != '\0'; string++)
		hashval = *string + (hashval << 5) - hashval;

	return hashval % hashtable->size;	
}

struct list_t *lookup_string(struct hashtable_t *hashtable, char *string)
{
	struct list_t *list;
	unsigned int hashval = hash(hashtable, string);

	for (list = hashtable->table[hashval]; list != NULL; list = list->next)
		if (strcmp(string, list->string) == 0)
			return list;

	return NULL;
}

int add_string(struct hashtable_t *hashtable, char *string)
{
	struct list_t *newlist, *currentlist;
	unsigned int hashval = hash(hashtable, string);

	if ((newlist = malloc(sizeof(struct list_t))) == NULL)
		return 1;

	currentlist = lookup_string(hashtable, string);

	if (currentlist != NULL)
		return 2;

	newlist->value  = NULL;
	newlist->string = strdup(string);
	newlist->next = hashtable->table[hashval];
	hashtable->table[hashval] = newlist;

	return 0;
}

void free_table(struct hashtable_t *hashtable)
{
	struct list_t *list, *temp;

	if (hashtable == NULL)
		return;

	for (int i = 0; i < hashtable->size; i++)
	{
		list = hashtable->table[i];
		while (list != NULL)
		{
			temp = list;
			list = list->next;
			free(temp->string);
			if (temp->value != NULL)
				free(temp->value);
			free(temp);
		}
	}

	free(hashtable->table);
	free(hashtable);
}