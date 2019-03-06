#include <iostream>
#include <iomanip>
#include <cctype>
#include <fstream>
#include <string>
#include <vector>
#include <typeinfo>

//----------------------------------------- 
#include "FSM.h"
#include "lexer.h"
//-----------------------------------------
using namespace std;

string extractPotKeywords(string fileString, int &continueHere);

int main() {

	string file;
	fstream inFile;
	int continueHere = 0;
	//unsigned char temp;
	char temp;
	//---------------------------
	string tempString = ""; 
	//----------------------------
		string fileString = "";
	//initialize currentState as 0 to start
	int currentState = 0;
	cout << "Enter a file to open: " << endl;

	cin >> file;

	//open test file
	//dataFile = open('test.txt', 'r');
	int counter = 0;
	inFile.open(file.c_str(), ios::in | ios::out);
	while (inFile >> temp >> noskipws) {
		fileString += temp;
	}

	int sizeOfFileString = fileString.size();
	cout << "Num of char in file is: " << sizeOfFileString;



	cout << "fileString = " << fileString << endl;
	cout << "Num of char in file is: " << fileString.length();
	inFile.close();



	for (unsigned int i = continueHere; i < fileString.size(); i++)
	{
		FSM fsm = FSM();
		fsm.stateTransition(currentState, temp, tempString, fileString, i); // Reference stateTransition for more info
		//Note: The keywords are already being tested within the textLexeme() which is called in the 
		//			stateTransition ()
	}
	//------------------------------------------------------------------

	//lexer token; 
	for (unsigned int i = 0; i < showTokenLexeme.size(); i++)
	{
		cout << showTokenLexeme[i].first <<  " " << showTokenLexeme[i].second << endl;
	}

	cout << endl;
	system("pause"); 
	return 0;

}

//Still need to check if everything here works
//You should iterate through the op/seps array when you're checking for a delimiter
string extractPotKeywords(string fileString, int &continueHere) {
	for (unsigned int i = continueHere; i < fileString.size(); i++) {
		string testString = "";
		if (isspace(fileString[i]) || fileString[i] == '(' || fileString[i] == '\n' || fileString[i] == '{' || fileString[i] == ':' || fileString[i] == ',') {
			//Save this index to start from again after
			i++;//check what's next to it
			while (fileString[i] != ')' || fileString[i] != '}' || fileString[i] != ':' || fileString[i] != '\n') {
				if (isspace(fileString[i]) != 0) {
					break;
				}
				testString += fileString[i];
				i++;
			}
			i = continueHere;
		}
		return testString;
	}
}