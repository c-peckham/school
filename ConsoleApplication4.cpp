#include <iostream>
#include <iomanip>
#include <cstring>
#include "ctype.h"
#include "pch.h"

using namespace std;

enum tokenType {
	AND, BEGIN, END, FOR, IF, NOT, OR, READ, WHILE, WRITE, COMMENT,
	ID, REAL, STRING, PLUS, MULTIPLICATION, ASSIGNMENT, EQUAL, GREATERTHAN, LESSTHAN,
	LEFTP, COMMA, RIGHTP, SEMICOLON, INVALID, DIVISION, INTEGER
};

char tokenBuffer[80];
void skipSpaces();
void clearBuffer(void);
void displayToken(tokenType code);
void match(tokenType token);
void syntaxError(tokenType token);
void program(void);
void statementList(void);
void statement(void);

bool needToken = true;
tokenType lexical_error(void);

tokenType getId(void);
tokenType getComment(void);
tokenType getReal(void);
tokenType getStrings(void);
tokenType getPlus(void);
tokenType getMul(void);
tokenType getAssign(void);
tokenType getEqual(void);
tokenType getGreater(void);
tokenType getLess(void);
tokenType getLP(void);
tokenType getRP(void);
tokenType getComma(void);
tokenType getSemiColon(void);
tokenType getNextToken(void);
tokenType peekToken(void);
tokenType readToken(void);


tokenType scanner(void)
{
	skipSpaces();
	tokenType code;
	int input = cin.get();

	if (input == EOF)
		code = (tokenType)EOF;
	else
	{
		cin.putback(input);
		int input2 = cin.peek();
		switch (input2)
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
			if (isalpha(input2))
				code = getId();
			else if (isdigit(input2))
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
	int input;
	input = cin.get();
	while (isspace(input))
		input = cin.get();
	cin.putback(input);
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
	int input, i = 0;
	input = cin.get();
	if (isalpha(input))
	{
		tokenBuffer[i++] = input;
		input = cin.get();
		while (isalnum(input))
		{
			tokenBuffer[i++] = input;
			input = cin.get();
		}
		cin.putback(input);
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
		cin.putback(input);
		code = INVALID;
	}
	return code;
}

tokenType getComment(void)
{
	tokenType code;
	int input, i = 0;
	input = cin.get();
	if (input == '/' && cin.peek() == '*')
	{
		tokenBuffer[i++] = input;
		input = cin.get();
		tokenBuffer[i++] = input;
		input = cin.get();
		while (!(input == '*' && cin.peek() == '/') && cin.peek() != EOF)
		{
			tokenBuffer[i++] = input;
			input = cin.get();
		}
		if (cin.peek() == EOF)
			code = INVALID;
		else
		{
			tokenBuffer[i++] = input;
			input = cin.get();
			tokenBuffer[i++] = input;
			code = COMMENT;
		}
	}
	else
	{
		cin.putback(input);
		code = INVALID;
	}
	return code;
}

tokenType getReal(void)
{
	tokenType code;
	int input, i = 0;
	input = cin.get();
	if (isdigit(input))
	{
		tokenBuffer[i++] = input;
		input = cin.get();
		while (isdigit(input))
		{
			tokenBuffer[i++] = input;
			input = cin.get();
		}
		if (input == '.')
		{
			tokenBuffer[i++] = input;
			input = cin.get();
			if (isdigit(input))
			{
				tokenBuffer[i++] = input;
				input = cin.get();
				while (isdigit(input))
				{
					tokenBuffer[i++] = input;
					input = cin.get();
				}
				cin.putback(input);
				code = REAL;
			}
			else
			{
				cin.putback(input);
				code = INVALID;
			}
		}
		else
		{
			cin.putback(input);
			code = INVALID;
		}
	}
	else
	{
		cin.putback(input);
		code = INVALID;
	}
	return code;
}

tokenType getStrings(void)
{
	tokenType code;
	int input, i = 0;
	input = cin.get();
	if (input == '\"')
	{
		tokenBuffer[i++] = input;
		input = cin.get();
		while (!(input == '\"') && input != EOF)
		{
			tokenBuffer[i++] = input;
			input = cin.get();
		}
		if (input == EOF)
			code = INVALID;
		else
		{
			tokenBuffer[i++] = input;
			code = STRING;
		}
	}
	else
	{
		cin.putback(input);
		code = INVALID;
	}
	return code;
}

tokenType getPlus(void)
{
	tokenType code;
	int input = cin.get();
	if (input == '+')
	{
		tokenBuffer[0] = input;
		code = PLUS;
	}
	else
	{
		cin.putback(input);
		code = INVALID;
	}
	return code;
}

tokenType getMul(void)
{
	tokenType code;
	int input = cin.get();
	if (input == '*')
	{
		tokenBuffer[0] = input;
		code = MULTIPLICATION;
	}
	else
	{
		cin.putback(input);
		code = INVALID;
	}
	return code;
}

tokenType getAssign(void)
{
	tokenType code;
	int input1 = cin.get();
	int input2 = cin.peek();
	if (input1 == ':' && input2 == '=')
	{
		tokenBuffer[0] = input1;
		input1 = cin.get();
		tokenBuffer[1] = input1;
		code = ASSIGNMENT;
	}
	else
	{
		cin.putback(input1);
		code = INVALID;
	}
	return code;
}

tokenType getEqual(void)
{
	tokenType code;
	int input = cin.get();
	if (input == '=')
	{
		tokenBuffer[0] = input;
		code = EQUAL;
	}
	else
	{
		cin.putback(input);
		code = INVALID;
	}
	return code;
}

tokenType getGreater(void)
{
	tokenType code;
	int input = cin.get();
	if (input == '>')
	{
		tokenBuffer[0] = input;
		code = GREATERTHAN;
	}
	else
	{
		cin.putback(input);
		code = INVALID;
	}
	return code;
}

tokenType getLess(void)
{
	tokenType code;
	int input = cin.get();
	if (input == '<')
	{
		tokenBuffer[0] = input;
		code = LESSTHAN;
	}
	else
	{
		cin.putback(input);
		code = INVALID;
	}
	return code;
}

tokenType getLP(void)
{
	tokenType code;
	int input = cin.get();
	if (input == '(')
	{
		tokenBuffer[0] = input;
		code = LEFTP;
	}
	else
	{
		cin.putback(input);
		code = INVALID;
	}
	return code;
}

tokenType getRP(void)
{
	tokenType code;
	int input = cin.get();
	if (input == ')')
	{
		tokenBuffer[0] = input;
		code = RIGHTP;
	}
	else
	{
		cin.putback(input);
		code = INVALID;
	}
	return code;
}

tokenType getComma(void)
{
	tokenType code;
	int input = cin.get();
	if (input == ',')
	{
		tokenBuffer[0] = input;
		code = COMMA;
	}
	else
	{
		cin.putback(input);
		code = INVALID;
	}
	return code;
}

tokenType getSemiColon(void)
{
	tokenType code;
	int input = cin.get();
	if (input == ';')
	{
		tokenBuffer[0] = input;
		code = SEMICOLON;
	}
	else
	{
		cin.putback(input);
		code = INVALID;
	}
	return code;
}

tokenType lexical_error(void)

{
	tokenType code;
	int input = cin.get();
	tokenBuffer[0] = input;
	code = INVALID;
	return code;
}

tokenType getNextToken(void)
{
	tokenType nextToken;
	if (needToken)
	{
		nextToken = scanner();
		needToken = false;
	}
	return nextToken;
}

tokenType peekToken(void)
{
	return getNextToken();
}

tokenType readToken(void)
{
	tokenType token = getNextToken();
	needToken = true;
	return token;
}

void syntaxError(tokenType token)
{
	static char message[][20] = { AND, BEGIN, END, FOR, IF, NOT, OR, READ, WHILE, WRITE, COMMENT,
	ID, REAL, STRING, PLUS, MULTIPLICATION, ASSIGNMENT, EQUAL, GREATERTHAN, LESSTHAN,
	LEFTP, COMMA, RIGHTP, SEMICOLON, INVALID, DIVISION, INTEGER };
	cout << " token \"" << message[(int)token] << ": Syntax # " << (int)token << endl;
}

void match(tokenType token)
{
	int input = readToken();
	if (token == input)
	{
		if (input != SEMICOLON)
		{
			cout << tokenBuffer << endl;
			clear_buf();
		}
	}
	else
		syntaxError(token);
}

void program(void)
{
	match(BEGIN);
	statementList();
	match(END);
}

void statementList(void)
{
	tokenType nextToken = peekToken();
	if (nextToken)
	{
		statement();
		match(SEMICOLON);
		statementList();
	}
	else
		syntaxError(nextToken);
}

void statement(void)
{
	tokenType nextToken = peekToken();
	if (nextToken)
	{
		match(peekToken());
		match(ASSIGNMENT);
		statementList();
		match(SEMICOLON);
	}
	else
		syntaxError(nextToken);
}

int main()
{
	program();
	return 0;
}
