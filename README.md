# CPSC323Projects
Compilers Project for Lexer 
Problem: Write lexical analyzer using FSMs for identifier, integer, and real, rest is up to us

FSM in Code:
An FSM is a combo of
Set of all possible states the FSM can be in
This initial state the FSM is in
A set of accepting states
Set of all transitions
You can do this by implementing FSM as a class with states as members
transitionFunction - Transitions of an FSM can be modeled w/ a function that takes a state (currentState) and a character (input) while in state (currrentState)
Will be a switch statement on the parameter currentState
Each case will return the next state according to parameter input, like this:


                Refer to the following link for more info: https://hackernoon.com/lexical-analysis-861b8bfe4cb0 



Modular Implementation: 

Our decided approach is to create functions for each step/state in the FSM
We will identify if what we have is a token with a parsing algorithm implemented in isDelimiter to take each full string. 
The string is
Functions:
Booleans
isKeyWord
isIdentifier
isSeparator
isOperator 
isDelimiter - returns true if stumbles upon space
Strings
readFile - reads in file and returns a string of what it read
Spitball:

Use an array of objects to classify lexemes. Each confirmed lexeme has a member for token and a member for character. This method is used in the hackernoon article and is a class called Token



Main program works as follows:
While !EOF do:
Call the lexer for a token
Print the token and lexeme
End while
Extract each potential lexeme as a string 
We classify a potential lexeme as content that is enclosed between two separators.
Separators are (, ), and spaces
I think one line that is particularly helpful is “All possible lexemes that can appear in code written in a programming language, are described in the specification of that programming language as a set of rules called lexical grammar.” ← This would explain all the if “*” | “+” | …. In the examples shown in class
Another line that helped me was “Rules in the lexical grammar are often transformed into automata called fsm. Lexer simulates the fsm to recognize tokens”
Show what you think the fsm is doing then go to office hours to ask him to ammend your picture
Lexical Analyzer - Sequential Execution:

Program Process
Start
While not EOF
Read a character from the file
If the character is a space or ‘(‘
Store that character as a separator immediately
Else if the character is not a space or a parenthesis but is instead an operator
Store that character as an operator immediately
Else if character returns true on isDigit AND character before returns false on isDigit or is a ‘.’
Store the character into a temporary string variable
Keep getting characters from the file
Once you’ve gotten to the delimiter
If the temporary string has a ‘.’
Store it as a real
else 
Store as integer
Else character must be either a keyword or identifier
Store the character into a temporary string variable
Keep getting characters from the file until you get a delimiter
Once you’ve gotten to the delimiter, check if the string is a keyword
Store it as a keyword immediately
Restore the temporary string to empty
else it must be an identifier
Store it as an identifier immediately
Restore the temporary string to empty
