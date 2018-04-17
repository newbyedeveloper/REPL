#define EOI		0 // End of Input
#define EOL		1 // ';'
#define VAR 	2 // [az-AZ]+
#define NUM		3 // [0-9]+
#define PLUS	4 // '+'
#define EQ 		5 // '='
#define PRINT 	6 // "print"

extern char *yytext;    //-- In lex.c
extern int yyleng;      //||
extern int yylineno;    //--

int lex(void);
int match(int token);
void advance(void);