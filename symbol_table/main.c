/* Some tests with hashtable implementation */
#include "hashtable.h"
#include <stdio.h>

int main(void)
{
	struct list_t *list;
	struct hashtable_t *hashtable = create_hashtable(3);
	
	add_string(hashtable, "Teste1");
	add_string(hashtable, "SegundoSimbolo");
	add_string(hashtable, "FUCING_TEST");
	add_string(hashtable, "another one");
	add_string(hashtable, "last one");
	add_string(hashtable, "Jingle");
	add_string(hashtable, "Bells");
	add_string(hashtable, "Bye");

	list = lookup_string(hashtable, "another one");
	if (list != NULL)
		printf("%p = %s\n", list, list->string);

	list = lookup_string(hashtable, "Bells");
	if (list != NULL)
		printf("%p = %s\n", list, list->string);

	list = lookup_string(hashtable, "Test1");
	if (list != NULL)
		printf("%p = %s\n", list, list->string);

	list = lookup_string(hashtable, "last one");
	if (list != NULL)
		printf("%p = %s\n", list, list->string);

	list = lookup_string(hashtable, "SegundoSimbolo");
	if (list != NULL)
		printf("%p = %s\n", list, list->string);


	free_table(hashtable);

	return 0;
}