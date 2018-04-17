#include "lex.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

char *yytext = "";		//Lexeme (not '\0' terminated)
int yyleng = 0;			//Lexeme length
int yylineno = 0;		//Input line number

static int Lookahead = -1; //Lookahead token

int lex(void)
{
  static char input_buffer[128];
  char *current;

  current = yytext + yyleng;		//Skip current lexeme

  while (1)
  {
	while (!*current)
    {
      /* Get new lines, skipping any leading white space on the line,
		until a nonblank line is found.
      */

      current = input_buffer;
      if (!fgets(input_buffer, 128, stdin))
      {
		    *current = '\0';
        return EOI;
      }

      ++yylineno;

      while (isspace(*current))
        ++current;
	}
    for (; *current; ++current)
    {
      //Get the next token

      yytext = current;
      yyleng = 1;

      switch (*current)
      {
        case EOF: return EOI;
        case '+':	return PLUS;
        case ';': return EOL;
        case '=': return EQ;
        case '\n':
        case '\t':
        case ' ':	break;

        default:
          if (isdigit(*current))
          {
            while (isdigit(*current))
            {
              current++;
            }
            yyleng = current - yytext;

            return NUM;
          }
          else if (isalpha(*current))
          {
            while (isalpha(*current))
            {
              current++;
            }
            yyleng = current - yytext;

            if (!strncmp("print", yytext, yyleng))
              return PRINT;
            
            return VAR;
          }
          else
          {
            fprintf(stderr, "Ignoring illegal input <%c>\n", *current);
            break;
          }
      }
    }
  }
}

int match(int token)
{
  //Return true if token match with lookahead symbol

  if (Lookahead == -1)
    Lookahead = lex();

  return token == Lookahead;
}

void advance(void)
{
  //Advance the lookahead to the next input symbol

  Lookahead = lex();
}