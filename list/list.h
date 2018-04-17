struct Token
{
	int type;
	char *lexeme;
	struct Token *next;
};

struct List
{
	struct Token *first;
};

void insert_token(struct List *list, int type, char *lexeme);
void reset_list(struct List *list);
void print_list(struct List *list);