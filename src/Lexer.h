#ifndef LEXER_H
#define LEXER_H

#include <string>
#include "Token.h"

class Lexer {
private:
    std::string input;
    int position;
    int readPosition;
    char ch;

    void readChar();
    char peekChar();
    void skipWhiteSpace();

    bool isLetter(char c);
    bool isDigit(char c);
    std::string readIdentifier();
    std::string readNumber();

    TokenType lookupIdent(const std::string& ident);

public:
    Lexer(std::string input);
    Token nextToken();
};

#endif