//
// Created by kyley on 2/2/2021.
//
#ifndef LEXER_LEXER_H
#define LEXER_LEXER_H
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Tokenizer.h"

using namespace std;

class Lexer {
public:
    Lexer(string file)   {
        //cout << "Constructing Lexer" << endl;
        fileName = file;
        fileContents = "";
        tempString = "";
        tempToken = NULL;
    }
    vector<Token*> tokenList;
    void Tokenize();

private:
    bool Stringify();
    string fileName;
    string fileContents;
    string tempString;
    fstream myFile;
    Token* tempToken;
};


#endif //LEXER_LEXER_H
