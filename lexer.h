#pragma once
#include <iostream>
#include<iomanip>
#include <string>
#include<fstream>
#include <vector>


using namespace std;
class lexer
{
public:
	void readFile(std::string file);
	void finiteStateMachine(int state, char a);




private:
	vector<vector<int>> fsm;
};