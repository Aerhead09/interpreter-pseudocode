#ifndef PARSER_H
#define PARSER_H

#include "Lexer.h"
#include "Token.h"
#include <vector>

enum class Precedence {
    LOWEST = 0,
    OR,
    AND,
    EQUALS,
    LESSGREATER,
    SUM,
    PRODUCT,
    PREFIX
};

struct ASTNode {
    TokenType type;
    std::string literal;

    ASTNode* left = nullptr;
    ASTNode* right = nullptr;

    ASTNode* condition = nullptr;              
    std::vector<ASTNode*> body;                
    std::vector<ASTNode*> alternative;  
    std::vector<ASTNode*> arguments;       

    ASTNode(TokenType t, std::string l) : type(t), literal(l), left(nullptr), right(nullptr) {}
};

class Parser {
private:
    Lexer lexer;
    Token currentToken;
    Token peekToken;

    void nextToken();
    ASTNode* parseExpression(Precedence precedence);
    ASTNode* parseStatement();
    ASTNode* parseIfStatement();
    ASTNode* parseWhileStatement();
    ASTNode* parseForStatement();
    ASTNode* parseAssignStatement();
    ASTNode* parseInputStatement();
    ASTNode* parseOutputStatement();

public:
    Parser(Lexer lexer);
    ASTNode* parseProgram();
};

void printTree(ASTNode* node);

#endif