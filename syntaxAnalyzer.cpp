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
	T	FR											FR
	R				e		e	  *FR	  /FR				e		e
	F	 i											(E)
	*/
}
	

void syntaxAnalyzer::useSyntax() {
	//Helper function to convert tokens to enumerations
	//access the lexeme vector
	vector <pair<symbols, string>> showSymbolLexeme;//make new vector with enum symbols
	showSymbolLexeme.push_back(pair<symbols, string>(DOLLAR_SIGN, "$")); //Put a '$' at the end of the vector that's storing the string 
	for (int i = 0; i < showTokenLexeme.size(); i++) {
		if (showTokenLexeme[i].first == "Identifier") {
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

	while (symbolsStack.size() > 0) {//need a pointer system, or like make each command that doesn't call the lexer do i++ so it doesn't go to the next one
		for (int i = 0; i < showTokenLexeme.size(); i++) {
			/*IDENTIFIER, PLUS, MINUS,
				ASTERISK, BACKSLASH, RIGHT_PARENS,
				LEFT_PARENS, DOLLAR_SIGN, EQUAL_SIGN,
				EPSILON*/
			//if (symbolsStack.top() == showSymbolLexeme[i].first) {//if what's on top of the stack is the same as what's in our current location of the string
			// and it's a non terminal
			if((showSymbolLexeme[i].first == IDENTIFIER || showSymbolLexeme[i].first == PLUS || showSymbolLexeme[i].first == MINUS
				|| showSymbolLexeme[i].first == MINUS || showSymbolLexeme[i].first == ASTERISK || showSymbolLexeme[i].first == BACKSLASH
				|| showSymbolLexeme[i].first == RIGHT_PARENS || showSymbolLexeme[i].first == LEFT_PARENS || showSymbolLexeme[i].first == DOLLAR_SIGN
				|| showSymbolLexeme[i].first == EQUAL_SIGN || showSymbolLexeme[i].first == EPSILON) && symbolsStack.top() == showSymbolLexeme[i].first) {
				cout << "Matched symbols: " << showSymbolLexeme[i].first << endl;
				symbolsStack.pop();//Allow the loop to increment now
			}
			else {
				cout << "Rule " << table[symbolsStack.top()][showSymbolLexeme[i].first] << endl;
				switch (table[symbolsStack.top()][showSymbolLexeme[i].first]) {
				case 1: //S -> i = E
					symbolsStack.pop();
					symbolsStack.push(E);          //E
					symbolsStack.push(EQUAL_SIGN);// =
					symbolsStack.push(IDENTIFIER);// i
					i++;//Don't move onto the next element, only for lexer()
					break;

				case 2://E -> TQ
					symbolsStack.pop(); 
					symbolsStack.push(Q);//Q
					symbolsStack.push(T);//T
					i++;
					break;

				case 3://Q -> +TQ
					symbolsStack.pop();
					symbolsStack.push(Q);//Q
					symbolsStack.push(T);  //T
					symbolsStack.push(PLUS);  //+
					i++;
					break;

				case 4://Q -> -TQ
					symbolsStack.pop();
					symbolsStack.push(Q);	 //Q
					symbolsStack.push(T);	 //T
					symbolsStack.push(MINUS);//-
					i++;
					break;

				case 5://Q -> e
					//With ( or $
					//R -> e
					//with + or -
					symbolsStack.pop();
					symbolsStack.push(EPSILON);//e
					i++;
					break;

				case 6://T -> FR
					symbolsStack.pop();
					symbolsStack.push(R);//R
					symbolsStack.push(F);//F
					i++;
					break;

				case 7:// R -> FR
					table[R][BACKSLASH] = 7;//FR
					symbolsStack.pop();
					symbolsStack.push(R);//R
					symbolsStack.push(F);//F
					i++;
					break;

				case 8:// F -> i
					symbolsStack.pop();
					symbolsStack.push(IDENTIFIER);//i
					i++;
					break;

				case 9://F -> (E)
					symbolsStack.pop();
					symbolsStack.push(RIGHT_PARENS);// )
					symbolsStack.push(E);//            E
					symbolsStack.push(LEFT_PARENS);//  )
					i++;
					break;

				default:
					cout << "parsing table defaulted" << endl;
					//return 0;
					break;

				}
			}
		}
		

	}

}




syntaxAnalyzer::~syntaxAnalyzer()
{
}
