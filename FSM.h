#pragma once
#include<string>

using namespace  std;

class FSM {
  public:
    FSM();//constructor
    int findState(char temp, int state);
    int FSMtable[6][7];
    void stateTransition(int currentState, char ch, string temp);
  
}
