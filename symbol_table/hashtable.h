
struct list_t
{
	char *string;
	int *value;
	struct list_t *next;
};

struct hashtable_t
{
	int size;
	struct list_t **table;
};

struct hashtable_t *create_hashtable(int size);
unsigned int hash(struct hashtable_t *hashtable, char *string);
struct list_t *lookup_string(struct hashtable_t *hashtable, char *string);
int add_string(struct hashtable_t *hashtable, char *string);
void free_table(struct hashtable_t *hashtable); 