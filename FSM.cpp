#include <iostream>
#include <string>
#include <cctype>
#include "FSM.h"
#include "lexer.h"

FSM::FSM() {
  //contructor
  FSMtable[6][7] = {
      1, 2, 4, 0, 0, 0, 0,
      1, 1, 4, 0, 0, 0, 0, 
      5, 2, 4, 0, 3, 0, 0, 
      4, 4, 0, 4, 4, 4, 4, 
      0, 0, 0, 0, 0, 0, 0
    };
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

int FSM::findState(char temp, int state) {
  lexer lexerObject;
  int currentState = state;
  if(isalpha(temp)) {//if temp is alphabetic
    currentState = FSMtable[currentState][0];
    return currentState;
  } else if(isdigit(temp) || temp == '$') {
    //if it's a number or dollar sign
    currentState = FSMtable[currentState][1];
    return currentState;
  } else if(temp == lexerObject.operators[19]) {
    //[20] == '!'
    currentState = FSMtable[currentState][2];
    return currentState;
  } else if(temp == lexerObject.operators[15]) {
    //[16] == '.'
    currentState = FSMtable[currentState][4];
    return currentState; 
  } else if(isspace(temp)) {
    currentState = FSMtable[currentState][6];
  } else {

    for(int i = 0; i < 8; i++) {
      if(temp == lexerObject.operators[i] || isspace(temp)) {
        currentState = FSMtable[currentState][5];
        return currentState;
      }
    }

    for(int i = 8; i < 22; i++) {
      if(temp == lexerObject.operators[i] || isspace(temp)) {
        currentState = FSMtable[currentState][3];
        return currentState;
      }
    }
  }
}

void FSM::stateTransition(int currentState, char ch, string temp) {
  lexer lexerObject;
  if(currentState != 4) {
    currentState = findState(currentState, ch);
    switch(currentState) {
      case 0:
        lexerObject.testLexeme(temp);
        lexerObject.sepOrOp(ch);
        break;
      case 1 || 2 || 3:
        temp += ch;
        break;
      case 4:
        lexerObject.testLexeme(temp);
        temp = "";
        break;
      case 5:
        lexerObject.testLexeme(temp);
        lexerObject.sepOrOp(ch);
        temp = "";
        }
      }
    else if(ch == '!' && currentState == 4) {
      currentState = FSMtable[currentState][2];
    }

    lexerObject.testLexeme(temp);
    temp = "";
  }


//displayTemp(temp);
  //showTokenLexeme(string, string);
//displayChar(ch);
  //sepOrOp(ch);
