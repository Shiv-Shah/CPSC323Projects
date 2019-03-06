#pragma once
#include<string>
#include<vector>

using namespace  std;


extern char operators[21];
extern string keywords[20];

class lexer {
public:

	lexer();
	void testLexeme(string temp);
	void sepOrOp(char ch);
	vector <pair<string, string>> showTokenLexeme;
	//Might need to delete the declarations below
	

};