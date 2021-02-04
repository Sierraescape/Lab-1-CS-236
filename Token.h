//
// Created by kyle y on 2/2/2021.
//

#ifndef LEXER_TOKEN_H
#define LEXER_TOKEN_H
#include <string>
#include <utility>

using namespace std;

enum tokenType   {COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES,
        QUERIES, ID, STRING, COMMENT, BLOCK_COMMENT, UNDEFINED, EOF_TYPE};

class Token {
public:
    string value;
    int lineNumber;
    tokenType type;
    string outputString;

    //Constructor sets value, lineNumber, and type to input
    Token(tokenType inputType, string inputValue, int inputLineNumber)   {
        //cout << "In token constructor" << endl;
        value = move(inputValue);
        lineNumber = inputLineNumber;
        type = inputType;
        //cout << "Leaving token constructor" << endl;
    }

    //toString sets and returns outputString. Currently, format does not use spaces.
    //TODO: verify no spaces necessary
    string toString()   {
        //cout << "Converting token values to string" << endl;
        outputString = "(" + enumToString(type) + ",\"" + value + "\"," + to_string(lineNumber) + ")";
        return outputString;
    }

private:
    static string enumToString(tokenType currentEnum)   {
        //cout << "Converting enum values to strings" << endl;
        switch (currentEnum) {
            case COMMA:
                return "COMMA";
            case PERIOD:
                return "PERIOD";
            case LEFT_PAREN:
                return "LEFT_PAREN";
            case RIGHT_PAREN:
                return "RIGHT_PAREN";
            case Q_MARK:
                return "Q_MARK";
            case COLON:
                return "COLON";
            case COLON_DASH:
                return "COLON_DASH";
            case MULTIPLY:
                return "MULTIPLY";
            case ADD:
                return "ADD";
            case SCHEMES:
                return "SCHEMES";
            case FACTS:
                return "FACTS";
            case RULES:
                return "RULES";
            case QUERIES:
                return "QUERIES";
            case ID:
                return "ID";
            case STRING:
                return "STRING";
            case COMMENT:
                return "COMMENT";
            case BLOCK_COMMENT:
                return "BLOCK_COMMENT";
            case UNDEFINED:
                return "UNDEFINED";
            case EOF_TYPE:
                return "EOF";
        }
        //cout << "Unknown enum_type entered" << endl;
        return "UNDEFINED"; //Should never reach this line
    }
};


#endif //LEXER_TOKEN_H
