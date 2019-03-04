#pragma once
#include<string>
#include<vector>

using namespace  std;

class lexer {
  public:

    lexer();
    void testLexeme(string temp);
    void sepOrOp(char ch);
    vector <pair<string, string>>; showTokenLexeme;
    //Might need to delete the declarations below
    char operators[20];
    string keywords[11];


}
