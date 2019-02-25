#pragma once
#include <string>
#include "lexer.h"
using namespace std;

class FSM
{
public:
	FSM();//constructor
	FSM(int states, int initialState, int acceptingStates, int nextState);//overloaded constructor
	enum class states;
	void run(char input);
	int nextState(string currentState, string input);
	~FSM();//destructor

private:
	int states;
	int initialState;
	int acceptingStates;
	int nextStates;
};


