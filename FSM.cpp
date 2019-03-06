#include <iostream>
#include <string>
#include <cctype>
#include "FSM.h"
#include "lexer.h"

int FSMtable[6][7] = {
	{ 1, 2, 4, 0, 0, 0, 0 },
	{ 1, 1, 4, 0, 0, 0, 0 },
	{ 5, 2, 4, 0, 3, 0, 0 },
	{ 5, 3, 4, 0, 5, 0, 0 },
	{ 4, 4, 0, 4, 4, 4, 4 },
	{ 0, 0, 0, 0, 0, 0, 0 }
};

FSM::FSM() {
	//contructor

}

/*------------------Sammi's state trans table----------------------
---------------------Credit Given (Period 1)-----------------------
This Function is designed to navigate through the State Transition table.
Given the specific character being currently read from the file, the state will
change according to the table. Table is initialized in global scope but can be
referenced as such:
char num  '!' sep '.' ops  '\n'
new(0)			1,	2,	4,	0,	0,	0,  0
string(1)		1,	1,	4,	0,	0,	0,  0
int(2)			5,	2,	4,	0,	3,	0,  0
float(3)		5,	3,	4,	0,	5,	0,  0
comment(4)	4,	4,	0,	4,	4,	4,  4
invalid(5)	0,	0,	0,	0,	0,	0   0
*/

int FSM::findState(char temp, int state) {//continue to use a character
	lexer lexerObject;
	int currentState = state;
	if (isalpha(temp)) {//if temp is alphabetic
		currentState = FSMtable[currentState][0];
		return currentState;
	}
	else if (isdigit(temp) || temp == '$') {
		//if it's a number or dollar sign
		currentState = FSMtable[currentState][1];
		return currentState;
	}
	else if (temp == operators[19]) {
		//[20] == '!'
		currentState = FSMtable[currentState][2];
		return currentState;
	}
	else if (temp == operators[15]) {
		//[16] == '.'
		currentState = FSMtable[currentState][4];
		return currentState;
	}
	else if (temp == operators[20]) {
		//[21] == ' '
		currentState = FSMtable[currentState][6];
		return currentState; 
	}
	else {

		for (int i = 0; i < 8; i++) {
			if (temp == operators[i] || isspace(temp)) {
				currentState = FSMtable[currentState][5];
				return currentState;
			}
		}

		for (int i = 8; i < 22; i++) {
			if (temp == operators[i] || isspace(temp)) {
				currentState = FSMtable[currentState][3];
				return currentState;
			}
		}
	}
	
}
// ----------Modifying StateTransition () to better reflect your main -------------- Sami
// Best solution is to pass tempString,currentState and char by reference to be able to modify the vaule in main and display
// 		if neccesary
// Also adding in fileString to be able to test string immediately 
// added int i to get current location of file string.
void FSM::stateTransition(int &currentState,  char &temp, string &tempString, string fileString, int i) {
	lexer lexerObject;

	temp = fileString[i];
	if (currentState != 4) {
		
		currentState = findState(temp , currentState);// Changed ch (char type) to temp (char type) like in 
															
		switch (currentState) {
		case 0: // Displays Lexem if valid input
			lexerObject.testLexeme(tempString); 
		//	LexerObject.testLexeme(temp);
			lexerObject.sepOrOp(temp);			
		// 	lexerObject.sepOrOp(ch);
			tempString = "";
			break;
		case 1: 
			tempString += temp;
			//temp += ch;
			break;
		case 2: // continue to read for ints
			tempString += temp;
			//	temp += ch;
			break;
		case 3: // Continue to read for float
			tempString += temp;
			//	temp += ch;
			break;
		case 4: // Displays Lexeme if '!' is detected
			lexerObject.testLexeme(tempString);
			tempString = ""; 					
		//	temp = "";
			break;
		case 5: 
			lexerObject.testLexeme(tempString); 
		//	LexerObject.testLexeme(temp);
			lexerObject.sepOrOp(temp);			
		// 	lexerObject.sepOrOp(ch);	
			tempString = "";
			//temp = "";
			break;
		}
		
	}
	else if (temp == '!' && currentState == 4) {
		currentState = FSMtable[currentState][2];
	}

	//lexerObject.testLexeme(tempString);
	//tempString = ""; 					
//	temp = "";
}
