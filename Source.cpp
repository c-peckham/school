#include <iostream>
#include <iomanip>
#include <string.h>
#include <ctype.h>

using namespace std;

enum tokenType {
	AND, BEGIN, END, FOR, IF, NOT, OR, READ, WHILE, WRITE, COMMENT,
	ID, REAL, STRING, PLUS, MULTIPLICATION, ASSIGNMENT, EQUAL, GREATERTHAN, LESSTHAN,
	LEFTP, COMMA, RIGHTP, SEMICOLON, INVALID, DIVISION, INTEGER
};

char tokenBuffer[80];
int getIDBinarySearch(void); // Performs a binary search on the reserved words table.
void skipSpaces(); // Skips over space characters in the input stream.
void clearBuffer(void); // Sets all the elements of the buffer tokenBuffer[] to the null character.
void displayToken(tokenType code); /* Receives as argument a token code, displays the appropriate message, and prints the contents of the buffer. */
tokenType lexical_error(void);
tokenType getId(void); // Recognizes an identifier.
tokenType getComment(void); // EXTRA CREDIT: Recognizes a comment, or division character depending on the subsequent character.
tokenType getReal(void); // EXTRA CREDIT: Recognizes a real constant, or integer.
tokenType getStrings(void); // Recognizes a string constant.

tokenType getPlus(void); // Recognizes +
tokenType getMul(void); // Recognizes *
tokenType getAssign(void); // Recognizes : 
tokenType getEqual(void); // Recognizes =
tokenType getGreater(void);
tokenType getLess(void);
tokenType getLP(void);
tokenType getRP(void);
tokenType getComma(void);
tokenType getSemiColon(void);

tokenType scanner(void)
{
	skipSpaces();
	tokenType code;
	int ch = cin.get();

	if (ch == EOF)
		code = (tokenType)EOF;
	else
	{
		cin.putback(ch);
		int ch2 = cin.peek();
		switch (ch2)
		{
		case '/':
			code = getComment();
			break;
		case '\"':
			code = getStrings();
			break;
		case ':':
			code = getAssign();
			break;
		case '+':
			code = getPlus();
			break;
		case '*':
			code = getMul();
			break;
		case '=':
			code = getEqual();
			break;
		case '>':
			code = getGreater();
			break;
		case '<':
			code = getLess();
			break;
		case '(':
			code = getLP();
			break;
		case ')':
			code = getRP();
			break;
		case ',':
			code = getComma();
			break;
		case ';':
			code = getSemiColon();
			break;
		default:
			if (isalpha(ch2))
				code = getId();
			else if (isdigit(ch2))
				code = getReal();
			else
				code = lexical_error();
			break;
		}
	}
	return code;
}

void skipSpaces()
{
	int ch;
	ch = cin.get();
	while (isspace(ch))
		ch = cin.get();
	cin.putback(ch);
}

void clear_buf(void)
{
	for (int i = 0; i < 80; i++)
		tokenBuffer[i] = '\0';
}

void display_token(tokenType code)
{
	static const char *message[] = { "and", "begin", "end", "for", "if", "not", "or",
							 "read", "while", "write", "comment", "identifier",
							 "real constant", "string", "plus", "multiplication",
							 "assignment", "equal", "greater than", "less than",
							 "left parenthesis", "comma", "right parenthesis",
							 "semicolon", "invalid", "division", "integer" };
	cout << " \n" << setw(16) << message[(int)code] << "\t" << tokenBuffer;
}

tokenType getId(void)
{
	static const char *reservedWord[] = { "AND", "BEGIN", "END", "FOR", "IF", "NOT", "OR",
								   "READ", "WHILE", "WRITE" };
	tokenType code;
	int ch, i = 0;
	ch = cin.get();
	if (isalpha(ch))
	{
		tokenBuffer[i++] = ch;
		ch = cin.get();
		while (isalnum(ch))
		{
			tokenBuffer[i++] = ch;
			ch = cin.get();
		}
		cin.putback(ch);
		int first = 0, mid, last = 9;
		bool notFound = true;
		while (first <= last && notFound)
		{
			mid = (first + last) / 2;
			int answer = strcmp(tokenBuffer, reservedWord[mid]);
			if (answer == 0)
				notFound = false;
			else if (answer > 0)
				first = mid + 1;
			else
				last = mid - 1;
		}
		if (notFound)
			code = ID;
		else
			code = (tokenType)mid;
	}
	else
	{
		cin.putback(ch);
		code = INVALID;
	}
	return code;
}

tokenType getComment(void)
{
	tokenType code;
	int ch, i = 0;
	ch = cin.get();
	if (ch == '/' && cin.peek() == '*')
	{
		tokenBuffer[i++] = ch;
		ch = cin.get();
		tokenBuffer[i++] = ch;
		ch = cin.get();
		while (!(ch == '*' && cin.peek() == '/') && cin.peek() != EOF)
		{
			tokenBuffer[i++] = ch;
			ch = cin.get();
		}
		if (cin.peek() == EOF)
			code = INVALID;
		else
		{
			tokenBuffer[i++] = ch;
			ch = cin.get();
			tokenBuffer[i++] = ch;
			code = COMMENT;
		}
	}
	else
	{
		cin.putback(ch);
		code = INVALID;
	}
	return code;
}

tokenType getReal(void)
{
	tokenType code;
	int ch, i = 0;
	ch = cin.get();
	if (isdigit(ch))
	{
		tokenBuffer[i++] = ch;
		ch = cin.get();
		while (isdigit(ch))
		{
			tokenBuffer[i++] = ch;
			ch = cin.get();
		}
		if (ch == '.')
		{
			tokenBuffer[i++] = ch;
			ch = cin.get();
			if (isdigit(ch))
			{
				tokenBuffer[i++] = ch;
				ch = cin.get();
				while (isdigit(ch))
				{
					tokenBuffer[i++] = ch;
					ch = cin.get();
				}
				cin.putback(ch);
				code = REAL;
			}
			else
			{
				cin.putback(ch);
				code = INVALID;
			}
		}
		else
		{
			cin.putback(ch);
			code = INVALID;
		}
	}
	else
	{
		cin.putback(ch);
		code = INVALID;
	}
	return code;
}

tokenType getStrings(void)
{
	tokenType code;
	int ch, i = 0;
	ch = cin.get();
	if (ch == '\"')
	{
		tokenBuffer[i++] = ch;
		ch = cin.get();
		while (!(ch == '\"') && ch != EOF)
		{
			tokenBuffer[i++] = ch;
			ch = cin.get();
		}
		if (ch == EOF)
			code = INVALID;
		else
		{
			tokenBuffer[i++] = ch;
			code = STRING;
		}
	}
	else
	{
		cin.putback(ch);
		code = INVALID;
	}
	return code;
}

tokenType getPlus(void)
{
	tokenType code;
	int ch = cin.get();
	if (ch == '+')
	{
		tokenBuffer[0] = ch;
		code = PLUS;
	}
	else
	{
		cin.putback(ch);
		code = INVALID;
	}
	return code;
}

tokenType getMul(void)
{
	tokenType code;
	int ch = cin.get();
	if (ch == '*')
	{
		tokenBuffer[0] = ch;
		code = MULTIPLICATION;
	}
	else
	{
		cin.putback(ch);
		code = INVALID;
	}
	return code;
}

tokenType getAssign(void)
{
	tokenType code;
	int ch1 = cin.get();
	int ch2 = cin.peek();
	if (ch1 == ':' && ch2 == '=')
	{
		tokenBuffer[0] = ch1;
		ch1 = cin.get();
		tokenBuffer[1] = ch1;
		code = ASSIGNMENT;
	}
	else
	{
		cin.putback(ch1);
		code = INVALID;
	}
	return code;
}

tokenType getEqual(void)
{
	tokenType code;
	int ch = cin.get();
	if (ch == '=')
	{
		tokenBuffer[0] = ch;
		code = EQUAL;
	}
	else
	{
		cin.putback(ch);
		code = INVALID;
	}
	return code;
}

tokenType getGreater(void)
{
	tokenType code;
	int ch = cin.get();
	if (ch == '>')
	{
		tokenBuffer[0] = ch;
		code = GREATERTHAN;
	}
	else
	{
		cin.putback(ch);
		code = INVALID;
	}
	return code;
}

tokenType getLess(void)
{
	tokenType code;
	int ch = cin.get();
	if (ch == '<')
	{
		tokenBuffer[0] = ch;
		code = LESSTHAN;
	}
	else
	{
		cin.putback(ch);
		code = INVALID;
	}
	return code;
}

tokenType getLP(void)
{
	tokenType code;
	int ch = cin.get();
	if (ch == '(')
	{
		tokenBuffer[0] = ch;
		code = LEFTP;
	}
	else
	{
		cin.putback(ch);
		code = INVALID;
	}
	return code;
}

tokenType getRP(void)
{
	tokenType code;
	int ch = cin.get();
	if (ch == ')')
	{
		tokenBuffer[0] = ch;
		code = RIGHTP;
	}
	else
	{
		cin.putback(ch);
		code = INVALID;
	}
	return code;
}

tokenType getComma(void)
{
	tokenType code;
	int ch = cin.get();
	if (ch == ',')
	{
		tokenBuffer[0] = ch;
		code = COMMA;
	}
	else
	{
		cin.putback(ch);
		code = INVALID;
	}
	return code;
}

tokenType getSemiColon(void)
{
	tokenType code;
	int ch = cin.get();
	if (ch == ';')
	{
		tokenBuffer[0] = ch;
		code = SEMICOLON;
	}
	else
	{
		cin.putback(ch);
		code = INVALID;
	}
	return code;
}

tokenType lexical_error(void)

{
	tokenType code;
	int ch = cin.get();
	tokenBuffer[0] = ch;
	code = INVALID;
	return code;
}

int main()
{
	tokenType code = scanner();
	cout << setw(16) << "TOKENS/TYPES" << "\t" << "WORDS/LEXEMS"
		<< "\n    -------------\t-------------" << endl;

	while (code != EOF)
	{
		clear_buf();
		code = scanner();
		display_token(code);
	}
	return 0;
}



