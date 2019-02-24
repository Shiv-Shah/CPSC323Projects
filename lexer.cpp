#include <fstream>
#include <iostream>
#include "lexer.h"


using namespace std; 

void lexer:: readFile(string file)
{
	fstream inFile;
	char temp;
	inFile.open(file.c_str(), ios::in | ios::out);
	int state = 0; 

	while (inFile >> temp >> noskipws)
	{
		finiteStateMachine(state, temp);

	}
	//cin.get();
}



void lexer::finiteStateMachine(int state, char a)
{

}



