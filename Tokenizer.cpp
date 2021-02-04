//
// Created by kyle y on 2/2/2021.
//

#include <iostream>
#include <cctype>
#include <utility>
#include "Tokenizer.h"

Token* Tokenizer::getNextToken() {
    //cout << "Getting next token" << endl;
    if (currentPos < length) {
        char c = myFile.at(currentPos);
        //cout << "Not to end of file yet. Current char is " << c << endl;
        tempString = "";
        //If it's alphanumerical, begin the ID adding space.
        if (isalnum(c)) {
            //cout << "It's alphanumerical." << endl;
            startingLine = currentLine;
            IDFinder();
        } else if (c == ':') {
            //cout << "Found a colon" << endl;
            colonFinder();
        }

        else if (isspace(c)) {
            //cout << "Found whitespace" << endl;
            if (c == '\n') {
                currentLine++;
            }
            currentPos++;
            return getNextToken();
        } else if (c == ',' || c == '.' || c == '?' || c == '(' || c == ')' || c == '*' ||
                   c == '+') {
            //cout << "Found punctuation" << endl;
            punctuationFinder();
        }

        else if (c == '\'') {
            //cout << "Found a string" << endl;
            currentPos++;
            tempString = '\'';
            startingLine = currentLine;
            stringFinder();
        } else if (c == '#') {
            //cout << "Found a comment of some sort" << endl;
            currentPos++;
            tempString = '#';
            if (currentPos < length && myFile.at(currentPos) == '|') {
                startingLine = currentLine;
                tempString += '|';
                currentPos++;
                blockComment();
            } else {
                standardComment();
            }
        } else {
            //cout << "What was found cannot be defined" << endl;
            currentPos++;
            string newString;
            newString.push_back(c);
            tokenBuilder(UNDEFINED, newString, currentLine);
        }
    } else if (currentPos == length)   {tokenBuilder(EOF_TYPE, "", currentLine);}
    //cout << "Returning token (should always happen after token is gotten)" << endl;
    return currentToken;
}

void Tokenizer::IDFinder()   {
    //cout << "Finding an ID" << endl;
    while (isalnum(myFile.at(currentPos))) {
        tempString += myFile.at(currentPos);
        currentPos++;
        //Once the ID has ended, check to see if it's a scheme, fact, rule, or query, and then create a token
        if (currentPos == length || !isalnum(myFile.at(currentPos))) {
            if (tempString == "Schemes") {
                tokenBuilder(SCHEMES, tempString, currentLine);
            } else if (tempString == "Queries") {
                tokenBuilder(QUERIES, tempString, currentLine);
            } else if (tempString == "Rules") {
                tokenBuilder(RULES, tempString, currentLine);
            } else if (tempString == "Facts") {
                tokenBuilder(FACTS, tempString, currentLine);
            } else {
                tokenBuilder(ID, tempString, currentLine);
            }
        }
    }
    //cout << "ID found." << endl;
    tempString = "";
}

void Tokenizer::colonFinder()   {
    //If there's another character after the current one in the string
    //cout << "Finding colon [86]" << endl;
    currentPos++;
    if (currentPos < length && myFile.at(currentPos) == '-')   {
            currentPos++;
            tokenBuilder(COLON_DASH, ":-", currentLine);
    }
    else   {
        tokenBuilder(COLON, ":", currentLine);
    }
}

void Tokenizer::punctuationFinder() {
    //cout << "Finding punctuation" << endl;
    char c = myFile.at(currentPos);
    tempString = "";
    tempString += c;
    if (c == ',') {
        tokenBuilder(COMMA, tempString, currentLine);
    } else if (c == '.') {
        tokenBuilder(PERIOD, tempString, currentLine);
    } else if (c == '?') {
        tokenBuilder(Q_MARK, tempString, currentLine);
    } else if (c == '(') {
        tokenBuilder(LEFT_PAREN, tempString, currentLine);
    } else if (c == ')') {
        tokenBuilder(RIGHT_PAREN, tempString, currentLine);
    } else if (c == '*') {
        tokenBuilder(MULTIPLY, tempString, currentLine);
    } else if (c == '+') {
        tokenBuilder(ADD, tempString, currentLine);
    }
    currentPos++;
}

void Tokenizer::stringFinder()   {
    //cout << "Finding string, current string is " << tempString << endl;
    if (currentPos >= length) {
        tokenBuilder(UNDEFINED, tempString, startingLine);
        return;
    }
    char c = myFile.at(currentPos);
    tempString.push_back(c);
    currentPos++;
    if (c == '\'')   {
        if (currentPos < length && myFile.at(currentPos) == '\'')   {
                tempString.push_back(myFile.at(currentPos));
                currentPos++;
                stringFinder();
                return;
        } else {
            tokenBuilder(STRING, tempString, startingLine);
            tempString = "";
        }
    } else   {
            if(c == '\n')   {
                currentLine++;
            }
            stringFinder();
    }
}

void Tokenizer::blockComment()   {
    //cout << "Finding block comment, current comment is " << tempString << endl;
    if (currentPos == length) {
        tokenBuilder(UNDEFINED, tempString, startingLine);
    }
    else if (myFile.at(currentPos) == '|')  {
        currentPos++;
        tempString += '|';
        if (currentPos < length && myFile.at(currentPos) == '#')   {
            currentPos++;
            tempString += '#';
            tokenBuilder(BLOCK_COMMENT, tempString, startingLine);
        } else   {blockComment();}
    }
    else if (myFile.at(currentPos) == '\n')  {
        currentLine++;
        currentPos++;
        tempString += '\n';
        blockComment();
    }   else  {
        tempString += myFile.at(currentPos);
        currentPos++;
        blockComment();
    }
}

void Tokenizer::standardComment()   {
    //cout << "Finding standard comment, current comment is " << tempString << endl;
    if (currentPos == length) {
        tokenBuilder(COMMENT, tempString, currentLine);
    }
    else if (myFile.at(currentPos) == '\n')  {
        tokenBuilder(COMMENT, tempString, currentLine);
        currentLine++;
        currentPos++;
    }   else   {
        tempString += myFile.at(currentPos);
        currentPos++;
        standardComment();
    }
}

void Tokenizer::tokenBuilder(tokenType type, string value, int lineLocation)   {
    //cout << "Building a token with value " << value << endl;
    currentToken = new Token(type, move(value), lineLocation);
}