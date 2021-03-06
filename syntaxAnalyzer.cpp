#include "syntaxAnalyzer.h"
#include "lexer.h"
#include "FSM.h"
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <stack>
#include <map>

//call the syntax analyzer after the token/lexeme pair vector
//show lexeme has gathered everything
enum symbols {
	//Non-Terminals
	S, E, Q, T, R, F,

	IDENTIFIER, PLUS, MINUS,
	ASTERISK, BACKSLASH, RIGHT_PARENS,
	LEFT_PARENS, DOLLAR_SIGN, EQUAL_SIGN,
	EPSILON
};


syntaxAnalyzer::syntaxAnalyzer()
{
	//Production rules:

	/*
		  i			+		-		*		/		(		)		$
	S	i = E
	E	 TQ											TQ
	Q			  +TQ	  -TQ								e		e
	T	 FR											FR
	R				e		e	  *FR	  /FR				e		e
	F	 i											(E)
	*/

	/*
	S = Statement
	E = Expresseion
	Q = Expression Prime
	T = Term
	R = Term Prime
	F = Factor
	i = Identifier
	*/
}
	

void syntaxAnalyzer::useSyntax() {
	//Helper function to convert tokens to enumerations
	//access the lexeme vector
	vector <pair<symbols, string>> showSymbolLexeme;//make new vector with enum symbols
	showSymbolLexeme.push_back(pair<symbols, string>(DOLLAR_SIGN, "$")); //Put a '$' at the end of the vector that's storing the string 
	for (int i = 0; i < showTokenLexeme.size(); i++) {
		if (showTokenLexeme[i].first == "Identifier: \t") {
			showSymbolLexeme.push_back(pair<symbols, string>(IDENTIFIER, showTokenLexeme[i].second));
		}
		else if (showTokenLexeme[i].second == "+") {
			showSymbolLexeme.push_back(pair<symbols, string>(PLUS, showTokenLexeme[i].second));
		}
		else if (showTokenLexeme[i].second == "-") {
			showSymbolLexeme.push_back(pair<symbols, string>(MINUS, showTokenLexeme[i].second));
		}
		else if (showTokenLexeme[i].second == "*") {
			showSymbolLexeme.push_back(pair<symbols, string>(ASTERISK, showTokenLexeme[i].second));
		}
		else if (showTokenLexeme[i].second == "/") {
			showSymbolLexeme.push_back(pair<symbols, string>(BACKSLASH, showTokenLexeme[i].second));
		}
		else if (showTokenLexeme[i].second == "(") {
			showSymbolLexeme.push_back(pair<symbols, string>(RIGHT_PARENS, showTokenLexeme[i].second));
		}
		else if (showTokenLexeme[i].second == ")") {
			showSymbolLexeme.push_back(pair<symbols, string>(LEFT_PARENS, showTokenLexeme[i].second));
		}
		else if (showTokenLexeme[i].second == "$") {
			showSymbolLexeme.push_back(pair<symbols, string>(DOLLAR_SIGN, showTokenLexeme[i].second));
		}
		else if (showTokenLexeme[i].second == "=") {
			showSymbolLexeme.push_back(pair<symbols, string>(EQUAL_SIGN, showTokenLexeme[i].second));
		}
		else {
			cout << "Error: Character does not exist in this grammar" << endl;
		}
	}

	map<symbols, map<symbols, int> >  table;

	//Add production rules
	table[S][IDENTIFIER] = 1;//i = E
	table[E][IDENTIFIER] = 2;//TQ
	table[Q][PLUS] = 3;//+TQ
	table[Q][MINUS] = 4;//-TQ
	table[Q][RIGHT_PARENS] = 5;// epsilon
	table[Q][DOLLAR_SIGN] = 5;//epsilon
	table[T][IDENTIFIER] = 6;//FR
	table[T][RIGHT_PARENS] = 6;//FR
	table[R][PLUS] = 5;//epsilon
	table[R][MINUS] = 5;//epsilon
	table[R][BACKSLASH] = 7;//FR
	table[R][RIGHT_PARENS] = 5;//epsilon
	table[R][DOLLAR_SIGN] = 5;//epsilon
	table[F][IDENTIFIER] = 8;//i
	table[F][LEFT_PARENS] = 9;//(E)

	//initialize the  symbols stack
	stack<symbols> symbolsStack;
	symbolsStack.push(DOLLAR_SIGN);
	symbolsStack.push(S);

	string tokenString = "";
	while (symbolsStack.size() > 0) {
		for (int i = 0; i < showSymbolLexeme.size(); i++) {
			for (int j = 0; j < sizeof(symbols); j++) {
				if (showSymbolLexeme[i].first == IDENTIFIER) {
					tokenString = "identifier";
				}
				else if (showSymbolLexeme[i].first == PLUS || showSymbolLexeme[i].first == MINUS ||
					showSymbolLexeme[i].first == ASTERISK || showSymbolLexeme[i].first == BACKSLASH
					|| showSymbolLexeme[i].first == DOLLAR_SIGN || showSymbolLexeme[i].first == EQUAL_SIGN) {
					tokenString = "Operator";
				}
				else if (showSymbolLexeme[i].first == RIGHT_PARENS || showSymbolLexeme[i].first == LEFT_PARENS) {
					tokenString = "SEPERATOR";
				}
				else if (showSymbolLexeme[i].first == EPSILON) {
					tokenString = "e";
				}
				else {
					tokenString = "invalid Syntax";
				}

			}
			if (symbolsStack.top() == showSymbolLexeme[i].first) {
				cout << "Token: " << tokenString << "\t ";
				cout << "Lexeme: " << showSymbolLexeme[i].second << endl;
				symbolsStack.pop();//Allow the loop to increment now
			}
			else if (symbolsStack.top() == EQUAL_SIGN) {
				cout << "Token: " << tokenString << "\t ";
				cout << "Lexeme: " << showSymbolLexeme[i].second << endl;
				symbolsStack.pop();
			}
			else {
				cout << "Rule " << table[symbolsStack.top()][showSymbolLexeme[i].first] << endl;

				switch (table[symbolsStack.top()][showSymbolLexeme[i].first]) {
				case 1: //S -> i = E
					symbolsStack.pop();
					symbolsStack.push(E);          //E
					symbolsStack.push(EQUAL_SIGN);// =
					symbolsStack.push(IDENTIFIER);// i
					cout << "<Statement> -> <identifier> = <Expression>" << endl;//Don't move onto the next element, only for lexer()
					i--;
					break;

				case 2://E -> TQ
					symbolsStack.pop();
					symbolsStack.push(Q);//Q
					symbolsStack.push(T);//T
					cout << "<Expression> -> <Term><Expression Prime>" << endl;
					i--;
					break;

				case 3://Q -> +TQ
					symbolsStack.pop();
					symbolsStack.push(Q);//Q
					symbolsStack.push(T);  //T
					symbolsStack.push(PLUS);  //+
					cout << "<Expression Prime> -> +<Term><Expression Prime>" << endl;
					i--;
					break;

				case 4://Q -> -TQ
					symbolsStack.pop();
					symbolsStack.push(Q);	 //Q
					symbolsStack.push(T);	 //T
					symbolsStack.push(MINUS);//-
					cout << "<Expression Prime> -> -<Term><Expression Prime>" << endl;
					i--;
					break;

				case 5://Q -> e
					   //With ( or $
					   //R -> e
					   //with + or -
					symbolsStack.pop();
					//symbolsStack.push(EPSILON);//e
					cout << "<Expression Prime> or <Term Prime> -> <ε>" << endl;
					i--;
					break;

				case 6://T -> FR
					symbolsStack.pop();
					symbolsStack.push(R);//R
					symbolsStack.push(F);//F
					cout << "<Term> -> <Factor><Term Prime>" << endl;
					i--;
					break;

				case 7:// R -> FR
					table[R][BACKSLASH] = 7;//FR
					symbolsStack.pop();
					symbolsStack.push(R);//R
					symbolsStack.push(F);//F
					cout << "<Term Prime> -> <Factor><Term Prime>" << endl;
					i--;
					break;

				case 8:// F -> i
					symbolsStack.pop();
					symbolsStack.push(IDENTIFIER);//i
					cout << "<Factor> -> <identifier>" << endl;
					i--;
					break;

				case 9://F -> (E)
					symbolsStack.pop();
					symbolsStack.push(RIGHT_PARENS);// )
					symbolsStack.push(E);//            E
					symbolsStack.push(LEFT_PARENS);//  )
					cout << "<Factor> -> (Expression)" << endl;
					i--;
					break;

				default:
					cout << "parsing table defaulted" << endl;
					//return 0;
					break;
				}
			}
			cout << endl;
		}
	}
}

syntaxAnalyzer::~syntaxAnalyzer()
{
}
