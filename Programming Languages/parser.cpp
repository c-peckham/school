//Title: parser.cpp                                                                                     
//Name: Burak Inalman                                                                    
//Class: Programming Languages                                                                         
//Description: This program demonstrates how a parser works.                                           

#include "parser.h"

int main()
{
	readflag=1;
	program();     //Calls the parser, that will continually check the scanner for the lexems
  
	return 0;
}

// ************************************************************************
void program(void)
{
    match(begin);		//This is same as match(0);		//check enum tokenType in parser.h
    statementlist();		
    match(end);		    //This is same as match(1);		//check enum tokenType in parser.h
}
// ************************************************************************
void match(int token)
{
	int input=readtoken();
	if(input!=token){
		syntaxerror(token);cout<<"match.."<<input<<"-"<<token<<endl;}
    else{
		cout<<buffer<<" ";
        if(input==begin||input==end||input==semicolon)
            cout<<endl;	
	}
}
// ************************************************************************
void statementlist(void)
{
	int nexttoken;
	nexttoken=peektoken();
	switch(nexttoken)
	{
		case identifier:
			statement();
			statementtail();
			break;
            
		default:
			syntaxerror(identifier);cout<<"statementlist.."<<endl;
	}
}
// ************************************************************************
int readtoken(void)
{
	int input;
	input=getnexttoken();
	readflag=1;
	
	return input;
}
// ************************************************************************
int getnexttoken(void)
{
	static int nexttoken;
	if(readflag==1){
		clear();
		nexttoken=dispatcher();		// cout<<"nexttoken= "<<nexttoken<<endl;
		readflag=0;
	}
    
	return nexttoken;
}
// ************************************************************************
int peektoken(void)
{
	int input;
	input=getnexttoken();
	
	return input;
}
// ************************************************************************
void syntaxerror(int token)
{
	cout<<"\n"<<buffer<<" is an incorrect input\n"<<endl;
}
// ************************************************************************
void statement(void)
{
	int nexttoken;
	nexttoken=peektoken();
	
	switch(nexttoken)
	{
		case identifier:
			 match(identifier);
			 match(assignment);
			 expression();
			 match(semicolon);
			 break;
		default:
			syntaxerror(identifier);cout<<"statement.."<<nexttoken<<endl;
	}
}
// ************************************************************************
void statementtail(void)
{
	int nexttoken;
	nexttoken=peektoken();
	switch(nexttoken)
	{
		case identifier:
             statement();
             statementtail();
             break;
		case end:
			return;
		default:
			syntaxerror(identifier);cout<<"statementtail.."<<nexttoken<<endl;
	}
}
// ************************************************************************
void expression(void)
{
	int nexttoken;
	nexttoken=getnexttoken();
    
	switch(nexttoken)
	{
		case identifier:
		case integer:
		case realConst:
			 factor();
			 expressiontail();
			 break;
		default:
			syntaxerror(identifier);cout<<"expression.."<<nexttoken<<endl;
	}
}
// ************************************************************************
void expressiontail(void)
{
	int nexttoken;
	nexttoken=peektoken();
	switch(nexttoken)
	{
		case plusSign:
		case minusSign:
			 addop();
			 factor();
			 expressiontail();
			 break;
		case semicolon:
		case rightPar:
             return;
		default:
			syntaxerror(plusSign);cout<<"expressiontail.."<<nexttoken<<endl;
	}
}
// ************************************************************************
void factor(void)
{
	primary();
	factortail();
}
// ************************************************************************
void factortail(void)
{
	int nexttoken;
	nexttoken=peektoken();
	switch(nexttoken)
	{
		case multiplication:
			 multop();
			 primary();
			 factortail();
			 break;
		case rightPar:
		case semicolon:
		case plusSign:
		case minusSign:
		case comma:
			 return;
		default:
			syntaxerror(multiplication);cout<<"factortail.."<<nexttoken<<endl;
	}
}
// ************************************************************************
void primary(void)
{
	int nexttoken;
	nexttoken=peektoken();
	switch(nexttoken)
	{
		case leftPar:
			match(leftPar);
			expression();
			match(rightPar);
			break;
		case identifier:
			match(identifier);
			break;
		case realConst:
			match(realConst);
			break;
		default:
			syntaxerror(leftPar);cout<<"primary.."<<nexttoken<<endl;
	}
}
// ************************************************************************
void addop(void)
{
	int nexttoken;
	nexttoken=peektoken();
	switch(nexttoken)
	{
		case plusSign:
			match(plusSign);
			break;
		case minusSign:
			match(minusSign);
			break;
		default:
			syntaxerror(plusSign);cout<<"addop.."<<nexttoken<<endl;
	}
}
// ************************************************************************
void multop(void)
{
	int nexttoken;
	nexttoken=peektoken();
	switch(nexttoken)
	{
	     case multiplication:
              match(multiplication);
              break;
            
	     default:
              syntaxerror(multiplication);cout<<"multop.."<<nexttoken<<endl;
	}
}
// ************************************************************************
// ************************************************************************
// ************************************************************************
int dispatcher(void)
{
	int input;
	int ch, ch2;
    
	ch = cin.get();
	while (isspace(ch)) // Skip spaces
		ch = cin.get();
    
	if (ch == EOF) // Have we reached the end of the file?
		return EOF;
    
	// Take a peek at the next character
	ch2 = cin.peek();
    
	// Put the first character back in the buffer
	cin.putback(ch);
    
	// Figure out which language recongnition function to call
	if (isalpha(ch)) // Letter = Identifier
		input = getReservedOrId();
	else if (isdigit(ch)) // Digit = Real Constant
		input = getRealLit();
	else
	{ 
		switch (ch)
		{
               
            case '(': input = getLeftPar(); break; 
	        case ',': input = getComma(); break;
	        case ';': input = getSemicolon(); break;
	        case ')': input = getRightPar(); break;
			case '"': input = getStrings(); break;
			case '+': input = getPlus(); break;
			case '-': input = getMinus(); break;
			case '*': input = getMult(); break;
			                           
			case '/':
				if (ch2 == '*') input = getComments();
				else input = getDiv();
				break;

            case ':':				
				if (ch2 == '=') 
                    input = getAssignment();
				else input = Invalid();
				break;
				
            default: cout<<"\n"<<ch<<" default\n"<<endl; input = Invalid(); break;      
		}
	}
    
	return input;
}
// ************************************************************************
void clear(void)
{
	for(int i=0;i<80;i++){
		buffer[i]=NULL;
	}
}
// ************************************************************************
void display(int input){
	char *message[]={
		"begin","end",
        "Reserved","Reserved","Reserved","Reserved","Reserved","Reserved","Reserved","Reserved",
        "Indentifier","Comment","Real Constant","String Constant",
        "Plus","Minus","Multiplication","Assignment",
        "Left Parenthesis","Comma","Semicolon","Right Parenthesis","Invalid Character","Integer","Division"
	};
    
	cout.setf(ios::left);
	cout<<setw(25)<<message[input]<<buffer<<endl;
}
// ************************************************************************
tokenType getReservedOrId()
{
	int c,i=0;
	c=cin.get();
	

	if(isalpha(c)){
		buffer[i++]=c;
		c=cin.get();
	
		while(isalnum(c)){  //Letter or digit
			buffer[i++]=c;
			c=cin.get();
	 	}

	}


	cin.putback(c);     //Put the invalid character back into the buffer
	
	//Check to see if invalid character is reserved
	for(int i=0;i<10;i++){
		if(strcmp(buffer,reserved[i])==0)
			return (tokenType)i;
	}

	return identifier;
}
// ************************************************************************
tokenType getComments()
{
	int c,i=0;
	c=cin.get();

	while(!(buffer[i-1]=='*' && c=='/')){
		buffer[i++]=c;
		c=cin.get();
	}

	//If the last character is a '/', place in the buffer
	buffer[i++]=c;

	return comment;
}
// ************************************************************************
tokenType getRealLit()
{
	int c,i=0;
	c=cin.get();

	while(isdigit(c)){
		buffer[i++]=c;
		c=cin.get();
	}
	
	if(c=='.'){       //Continue
		buffer[i++]=c;
		c=cin.get();
		while(isdigit(c)){	
			buffer[i++]=c;
			c=cin.get();
		}
	}

	else{ //Integer
		cin.putback(c);   //put invalid character back into the buffer
		return integer;
	}

	cin.putback(c);          //put invalid character back into the buffer
	return realConst;
}
// ************************************************************************
tokenType getStrings()
{
	int c,i=0;
	c=cin.get();

	if(c=='"'){
		buffer[i++]=c;
		c=cin.get();
		while(c !='"'){
			buffer[i++]=c;
			c=cin.get();
		}

		buffer[i++]=c;
	}

       return stringConst;
}
// ************************************************************************
tokenType getPlus()
{
	buffer[0]=cin.get();
	return plusSign;
}
// ************************************************************************
tokenType getMinus()
{
	buffer[0]=cin.get();
	return minusSign;
}
// ************************************************************************
tokenType getMult()
{
	buffer[0]=cin.get();
	return multiplication;
}
// ************************************************************************
tokenType getDiv()
{
	buffer[0]=cin.get();
	return division;
}
// ************************************************************************
tokenType getAssignment()
{
	int c,i=0;
	c=cin.get();
	buffer[i++]=c;

	if(c==':'){

		c=cin.get();
		buffer[i++]=c;
	}
	else
		cin.putback(c);

	return assignment;
}
// ************************************************************************
tokenType getLeftPar()
{
	buffer[0]=cin.get();
	return leftPar;
}
// ************************************************************************
tokenType getComma()
{
	buffer[0]=cin.get();
	return comma;
}
// ************************************************************************
tokenType getSemicolon()
{
	buffer[0]=cin.get();
	return semicolon;
}
// ************************************************************************
tokenType getRightPar()
{
	buffer[0]=cin.get();
	return rightPar;
}
// ************************************************************************
tokenType Invalid()
{
	int i=0;

	while(!isspace(cin.peek())) //Skip spaces
		buffer[i++]=cin.get();

	return invalid;
}
// ************************************************************************

