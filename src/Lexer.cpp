#include "Lexer.h"

Lexer::Lexer(std::string input) {
    this->input = input;
    this->position = 0;
    this->readPosition = 0;
    this->ch = 0;

    readChar();
}

void Lexer::readChar() {
    if (readPosition >= input.length()) {
        ch = 0;
    } else {
        ch = input[readPosition];
    }

    position = readPosition;
    readPosition += 1;
}

char Lexer::peekChar() {
    if (readPosition >= input.length()) {
        return 0;
    } else {
        return input[readPosition];
    }
}

void Lexer::skipWhiteSpace() {
    while (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
        readChar();
    }
}

bool Lexer::isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Lexer::isDigit(char c) {
    return (c >= '0' && c <= '9');
}

std::string Lexer::readIdentifier() {
    int startPos = position;
    while (isLetter(ch)) {
        readChar();
    }
    return input.substr(startPos, position - startPos);
}

std::string Lexer::readNumber() {
    int startPos = position;
    while (isDigit(ch)) {
        readChar();
    }
    return input.substr(startPos, position - startPos);
}

TokenType Lexer::lookupIdent(const std::string& ident) {
    if (ident == "Program") return TokenType::PROGRAM;
    if (ident == "endprogram") return TokenType::ENDPROGRAM;
    if (ident == "int") return TokenType::TYPE_INT;
    if (ident == "input") return TokenType::INPUT;
    if (ident == "output") return TokenType::OUTPUT;
    if (ident == "for") return TokenType::FOR;
    if (ident == "to") return TokenType::TO;
    if (ident == "do") return TokenType::DO;
    if (ident == "endfor") return TokenType::ENDFOR;
    if (ident == "while") return TokenType::WHILE;
    if (ident == "endwhile") return TokenType::ENDWHILE;
    if (ident == "if") return TokenType::IF;
    if (ident == "then") return TokenType::THEN;
    if (ident == "else") return TokenType::ELSE;
    if (ident == "endif") return TokenType::ENDIF;
    if (ident == "AND") return TokenType::AND;
    if (ident == "OR") return TokenType::OR;
    if (ident == "true" || ident == "TRUE") return TokenType::TRUE_LITERAL;
    if (ident == "false" || ident == "FALSE") return TokenType::FALSE_LITERAL;

    return TokenType::IDENTIFIER;
}

Token Lexer::nextToken() {
    Token tok;
    
    skipWhiteSpace();

    switch (ch) {
        case '=':
            tok = {TokenType::EQUALS, std::string(1,ch)};
            break;
        case '+':
            tok = {TokenType::PLUS, std::string(1, ch)};
            break;
        case '-':
            tok = {TokenType::MINUS, std::string(1, ch)};
            break;
        case '*':
            tok = {TokenType::STAR, std::string(1, ch)};
            break;
        case '/':
            tok = {TokenType::SLASH, std::string(1, ch)};
            break;
        case ':':
            tok = {TokenType::COLON, std::string(1, ch)};
            break;
        case ',':
            tok = {TokenType::COMMA, std::string(1, ch)};
            break;
        case '(':
            tok = {TokenType::LPAREN, std::string(1, ch)};
            break;
        case ')':
            tok = {TokenType::RPAREN, std::string(1, ch)};
            break;
        case '<':
            if (peekChar() == '-') {
                char currentCh = ch;
                readChar();
                std::string literal = std::string(1, currentCh) + std::string(1, ch);
                tok = {TokenType::ASSIGN, literal};
            } else if (peekChar() == '=') {
                char currentCh = ch;
                readChar();
                std::string literal = std::string(1,currentCh) + std::string(1,ch);
                tok = {TokenType::LESS_THAN_EQUALS, literal};
            } else {
                tok = {TokenType::LESS_THAN, std::string(1, ch)};
            }
            break;
        case '>':
            if (peekChar() == '=') {
                char currentCh = ch;
                readChar();
                std::string literal = std::string(1,currentCh) + std::string(1,ch);
                tok = {TokenType::GREATER_THAN_EQUALS, literal};
            } else {
                tok = {TokenType::GREATER_THAN, std::string(1, ch)};
            }
            break;
        case 0:
            tok = {TokenType::END_OF_FILE, ""};
            break;
        default:
            if (isLetter(ch)) {
                tok.literal = readIdentifier();
                tok.type = lookupIdent(tok.literal);
                return tok;
            } else if (isDigit(ch)) {
                tok.type = TokenType::INT_LITERAL;
                tok.literal = readNumber();
                return tok;
            } else {
                tok = {TokenType::IDENTIFIER, std::string(1, ch)};
            }
            break;
    }
    readChar();

    return tok;
}