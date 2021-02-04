//
// Created by kyley on 2/2/2021.
//

#ifndef LEXER_TOKENIZER_H
#define LEXER_TOKENIZER_H
#include "Token.h"

class Tokenizer {
private:
    string tempString;
    string myFile;
    int currentPos;
    int currentLine;
    int startingLine;
    int length;
    Token* currentToken;
    void IDFinder();
    void colonFinder();
    void punctuationFinder();
    void stringFinder();
    void blockComment();
    void standardComment();
    void tokenBuilder(tokenType type, string value, int lineLocation);
public:
    Tokenizer(string input)   {
        myFile = input;
        currentPos = 0;
        currentLine = 1;
        tempString = "";
        startingLine = 1;
        currentToken = NULL;
        length = input.length();
    }
    Token* getNextToken();
};

#endif //LEXER_TOKENIZER_H
