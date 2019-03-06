#pragma once
#include<string>

using namespace  std;
extern int FSMtable[6][7];
class FSM {
public:
	FSM();//constructor
	int findState(char temp, int state);

	void stateTransition(int &currentState,  char &temp, string &tempString, string fileString, int i);

};