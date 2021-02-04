#include <iostream>
#include "Tokenizer.h"
#include "Lexer.h"

using namespace std;

int main(int argc,  char* argv[]) {
    if(argc != 2)   {
        cout << "Usage: <filename>" << endl;
        return 1;
    } //If no string has been provided, or more than one string, exit
    auto* testLexer = new Lexer(argv[1]);
    testLexer->Tokenize();
    //cout << "Initialized Lexer" << endl;
    for (auto & i : testLexer->tokenList) {
        cout << i->toString() << endl;
    }

    cout << "Total Tokens = " << testLexer->tokenList.size() << endl;

    /*
    fstream myFile;
    myFile.open("output.txt");
    if (myFile.is_open()) {
        for (auto &i : testLexer->tokenList) {
            myFile << i->toString() << endl;
        }
        myFile << "Total Tokens = " << testLexer->tokenList.size() << endl;
        myFile.close();
    }
    else   {
        cout << "Unable to open file" << endl;
    }
     */
    return 0;
}
