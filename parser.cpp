// Parser
//

#include "pch.h"
#include <iostream>
#include "ctype.h"

using namespace std;
enum tokenType
{
	AND, BEGIN, END, FOR, IF, NOT, OR, READ, WHILE, WRITE, COMMENT, ID, REAL, STRING,
	PLUS, MULTIPLICATION, ASSIGNMENT, EQUAL, GREATERTHAN, LESSTHAN, LEFTP, COMMA, RIGHTP,
	SEMICOLON, INVALID, DIVISION, INTEGER
};
int main()
{
	tokenType getId()
	{
		static char reservedWord[][10] = { “AND”, “BEGIN”, “END”, “FOR”, “IF”, “NOT”,
															 “OR”, “READ”, “WHILE”, “WRITE” };
		tokenType code;
		int   ch, i = 0;
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

			/*---- find out if it is a reserved word using the binary search--*/
			int first = 0,
				mid;
			last = 9;
			bool  notFound = true;
			while (first <= last && notFound)
			{
				mid = (first + last) / 2;
				int  answer = strcmp(tokenBuffer, reservedWord[mid]);
				if (answer == 0)
					notfound = false;
				else if (answer > 0)
					first = mid + 1;
				else
					last = mid – 1;
			}
			if (notFound)
				code = ID;
			else
				code = (tokenType)mid;
		}
		else  	// it is not a letter
		{
			cin.putback(ch);
			code = INVALID;
		}
		return(code);
	};


	//FA for C language comments : / ’ * ’ Not(‘*’ / )* ‘*’ /

	tokenType  getComment()
	{
		tokenType code;
		int   ch, i = 0;
		ch = cin.get();
		if (ch == ‘ / ’ && cin.peek() == ‘ * ’)
		{
			tokenBuffer[i++] = ch;		// store the first symbol into the buffer

			// read the second symbol and store it into the buffer
			ch = cin.get();
			tokenBuffer[i++] = ch;

			ch = cin.get();
			while (!(ch == ‘ * ’  &&  cin.peek() == ‘ / ’) && cin.peek() != EOF)
			{
				tokenBuffer[i++] = ch;		// store the first symbol into the buffer

				// read the second symbol and store it into the buffer
				ch = cin.get();
			}
			if (cin.peek() == EOF)
				code = INVALID;
			else
			{
				tokenBuffer[i++] = ch;		// store the first symbol into the buffer

				// read the second symbol and store it into the buffer
				ch = cin.get();
				tokenBuffer[i++] = ch;
				code = COMMENT;
			}
		}
		else			// it is not “/*”
		{
			cin.putback(ch);
			code = INVALID;
		}
		return(code);
	};


	//FA for Real Constant : D + .D +
	tokenType  getReal()
	{
		tokenType code;
		int   ch, i = 0;
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
			if (ch = = ‘.’)
			{
				tokenBuffer[i++] = ch;
				ch = cin.get();
				if (isdigit(ch)
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
			else  	// it is not a period
			{
				cin.putback(ch);
				code = INVALID;
			}
		else  	// it is not a digit
		{
			cin.putback(ch);
			code = INVALID;
		}
		return(code);
			}
		

			FA for String Constants : “ Not(“)*”

				tokenType  getStrings()
			{
				tokenType code;
				int   ch, i = 0;
				ch = cin.get();
				if (ch == ‘\”’)
				{
					tokenBuffer[i++] = ch;		// store the first symbol into the buffer

					ch = cin.get();
					while (!(ch == ‘\”’) && ch != EOF)
					{
						tokenBuffer[i++] = ch;		// store the symbol into the buffer

						// read the second symbol and store it into the buffer
						ch = cin.get();
					}
					if (ch == EOF)
						code = INVALID;
					else
					{
						tokenBuffer[i++] = ch;		// store the first symbol into the buffer
						code = STRING;
					}
				}
				else			// it is not “
				{
					cin.putback(ch);
					code = INVALID;
				}
				return(code);
			}


			FA for the assignment : =

				tokenType getAssign()
			{
				tokenType code;
				int   ch, i = 0;
				ch = cin.get();
				if (ch == ‘:’ && cin.peek() == ‘ = ’)
				{
					tokenBuffer[i++] = ch;		// store the first symbol into the buffer

					// read the second symbol and store it into the buffer
					ch = cin.get();
					tokenBuffer[i] = ch;
					code = ASSIGNMENT;
					{
				else			// it is not an assignment
				{
					cin.putback(ch);
					code = INVALID;
				}
				return(code);
					}


					FA for the operator +

						tokenType getPlus()
					{
						tokenType code;
						int   ch, i = 0;
						ch = cin.get();
						if (ch == ‘ + ’)
						{
							tokenBuffer[i++] = ch;		// store it into the buffer
							code = PLUS;
						}
						else			// it is not the operator +
						{
							cin.putback(ch);
							code = INVALID;
						}
						return(code);
					}




}



