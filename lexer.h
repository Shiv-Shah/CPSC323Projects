#pragma once
#include<string>
#include<vector>

using namespace  std;


extern char operators[21];
extern string keywords[20];
extern vector <pair<string, string>> showTokenLexeme;

class lexer {
public:

	lexer();
	void testLexeme(string temp);
	void sepOrOp(char ch);
	
	//Might need to delete the declarations below
	

};