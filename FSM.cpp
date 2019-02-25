#include "FSM.h"
#include <string>
#include "lexer.h"

using namespace std;



FSM::FSM()
{
}


enum class FSM::states {
	STR, INT, FLOAT, COM, NEW, INVALID
};

FSM::FSM(int states, int initialState, int acceptingStates, int nextState) {


}

int nextState(char currentState, char input) {
	//I believe that each return will be an enumeration
	switch (currentState) {
	case 1:
		if (input == 'a' || input == 'b') {
		return 1;
		}
		break;

	case 2:
		if (input == 'c') {
			return 3;
		}
		break;

	default:
		break;
}

return NoNextState;//constant to specify that there is no next state
	
}

void FSM::run(char input) {

}

void FSM::run(char input) {
	//runs this FSM on the specified 'input' string
	//returns 'true' if 'input' or a subset of 'input' matches
	//the regular experession corresponding to this FSM

	int currentState = initialState;

	for (int i = 0; i < input.length(); i++) {
		//Code to get a character
		readFile()
	}


}

FSM::~FSM()
{
}
