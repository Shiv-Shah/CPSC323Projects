#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include "FSM.h"
#include "lexer.h"


lexer::lexer() {
  char operators[20] = {

      ' ',',',';','.',':',
      '[',']','{','(',')', 
      '}','/','\'','%','>',
      '<','=','-','+','*' 

    };

    string keywords[11] = {
      "if", "else", "then",
      "while", "do", "for", 
      "and", "or", "bool", 
      "float", "int"
    };
}

//We might have to make it so this
//takes the vector of lexemes
void lexer::testLexeme(string temp) {
  //called for separator, keyword, or invalid
  //tests input for : integer, float, identifier, keyworkd, invalid
  if(temp != "") {
    //instantiate your boolean
    bool isKeyword = 0;
    for(int i = 0; i < 11; i++) {//are there more keywords
                                //that we should include?
      if(keywords[i] == temp) {
        //show the output for a keyword
        showTokenLexeme.push_back(pair<string, string>("Keyword: \t", temp));
        return;
      }
    }
    isKeyword = 1;//(TRUE)
    if(isalpha(temp[0]) && isKeyword == 1) {
      //then it's an identifier, show output for that
      showTokenLexeme.push_back(pair<string, string>("Identifier: \t", temp));
      return;
    } 

    int isFloat = 0;
    for(int i = 0; i < temp.length(); i++) {
      if(temp[i] == '.') {
        isFloat = 1;
        break;//it's a float. Stop the whole while loop here
      }
    }
    if(isFloat == 0) {
      showTokenLexeme.push_back(pair<string, string>("Integer: \t", temp));
      return;

    } else if(isFloat == 1) {
      showTokenLexeme.push_back(pair<string, string>("Float: \t", temp));
      return;
    }

    //Lastly, it must be invalid
    showTokenLexeme.push_back(pair<string, string>("Invalid: \t", temp));
    return;
  }
  
}

void lexer::sepOrOp(char ch) {
  //operate w/ strings of 
  //single byte characters
  string temp = string(1, ch);
  for(int i = 0; i < 8; i++) {
    if(ch == operators[i]) {
      showTokenLexeme.push_back(pair<string, string>("Operator: \t", temp));
    }
  }
  for(int i = 8; i < 20; i++) {
    if(ch == operators[i] && ch != '!' && !isspace(ch)) {
      showTokenLexeme.push_back(pair<string, string>("Separator: \t", temp));
    }
  }
}



