//
// Created by kyley on 2/2/2021.
//

#include "Lexer.h"

void Lexer::Tokenize() {
    //cout << "Tokenizing" << endl;
    if (Stringify()) {
        Tokenizer myTokenizer(fileContents);
        do {
            //cout << "Creating new token" << endl;
            tempToken = myTokenizer.getNextToken();
            tokenList.push_back(tempToken);
        } while (tempToken->type != EOF_TYPE);
    }
}

bool Lexer::Stringify()   {
    //cout << "Converting file into a string" << endl;
    myFile.open(fileName);
    //Open file fileName in fstream myFile
    if (myFile.is_open())   {
        while(!myFile.eof())   {
            getline(myFile, tempString);
            fileContents += tempString + "\n";
        }
        fileContents.pop_back();
        myFile.close();
        return true;
    }
    else {
        cout << "Failed to open file." << endl;
        return false;
    }
}