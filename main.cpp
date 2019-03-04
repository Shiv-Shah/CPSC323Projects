#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "FSM.h"
#include "lexer.h"
using namespace std;


int main() {

  string file;
  string values;
  int stringLength = 0;
  char testChar;
  fstream inFile;
  string temp;
  FSM useFSM;
  lexer useLexer;
  //initialize currentState as 0 to start
  int currentState = 0;

  cout << "Enter a file to open: " << endl;

  cin >> file;

  inFile.open(file.c_str(), ios::in|ios::out);
  while(inFile >> temp >> noskipws) {
    //I believe your method already takes
    //a character. So no need to further parse
    //with a for loop?

    //FSM transition function added here
    stateTransition(currentState, testChar, string temp);
  }

  //Output the vector
  for(int i = 0; i < useLexer.showTokenLexeme.size(); i++) {
    cout << useLexer.showTokenLexeme[i].first << "\t" << useLexer.showTokenLexeme[i].second << endl;
    
  }

  inFile.close();
  cout << endl;

  return 0;

}

