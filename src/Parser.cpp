#include "Parser.h"
#include <iostream>

Precedence getPrecedence(TokenType type) {
    switch (type) {
        case TokenType::EQUALS:
            return Precedence::EQUALS;
        case TokenType::LESS_THAN:
        case TokenType::GREATER_THAN:
        case TokenType::LESS_THAN_EQUALS:
        case TokenType::GREATER_THAN_EQUALS:
            return Precedence::LESSGREATER;
        case TokenType::PLUS:
        case TokenType::MINUS:
            return Precedence::SUM;
        case TokenType::STAR:
        case TokenType::SLASH:
        case TokenType::MOD:
            return Precedence::PRODUCT;
        case TokenType::OR:
            return Precedence::OR;
        case TokenType::AND:
            return Precedence::AND;
        default:
            return Precedence::LOWEST;
    }
}

Parser::Parser(Lexer l) : lexer(l) {
    nextToken();
    nextToken();
}

void Parser::nextToken() {
    currentToken = peekToken;
    peekToken = lexer.nextToken();
}

ASTNode* Parser::parseProgram() {
    ASTNode* programNode = new ASTNode(TokenType::PROGRAM, "PROGRAM_ROOT");

    while (currentToken.type != TokenType::END_OF_FILE) {
        ASTNode* statement = parseStatement();
        
        if (statement != nullptr) { // Masukkan baris kode yang berhasil dirakit ke dalam perut (body) program utama
            programNode->body.push_back(statement);
        } else {
            nextToken();
        }
    }

    return programNode;
}

ASTNode* Parser::parseStatement() {
    if (currentToken.type == TokenType::IF) {
        return parseIfStatement();
    } else if (currentToken.type == TokenType::WHILE) {
        return parseWhileStatement();
    } else if (currentToken.type == TokenType::FOR) {
        return parseForStatement();
    } else if (currentToken.type == TokenType::INPUT) {
        return parseInputStatement();
    } else if (currentToken.type == TokenType::OUTPUT) {
        return parseOutputStatement();
    } else if (currentToken.type == TokenType::IDENTIFIER && peekToken.type == TokenType::ASSIGN) {
        return parseAssignStatement();
    }

    return parseExpression(Precedence::LOWEST);
}

ASTNode* Parser::parseIfStatement() {
    ASTNode* ifNode = new ASTNode(currentToken.type, currentToken.literal);
    
    nextToken(); 
    ifNode->condition = parseExpression(Precedence::LOWEST);
    
    if (currentToken.type == TokenType::THEN) {
        nextToken(); 
    } else {
        std::cout << "Syntax Error: Habis 'if' harus ada 'then'.\n";
        return nullptr;
    }

    while (currentToken.type != TokenType::ENDIF && currentToken.type != TokenType::ELSE && currentToken.type != TokenType::END_OF_FILE) {
        ASTNode* stmt = parseStatement();
        if (stmt != nullptr) {
            ifNode->body.push_back(stmt); 
        } else {
            nextToken();
        }
    }

    if (currentToken.type == TokenType::ELSE) {
        nextToken(); 
        
        while (currentToken.type != TokenType::ENDIF && currentToken.type != TokenType::END_OF_FILE) {
            ASTNode* stmt = parseStatement();
            if (stmt != nullptr) {
                ifNode->alternative.push_back(stmt); 
            } else {
                nextToken();
            }
        }
    }

    if (currentToken.type == TokenType::ENDIF) {
         nextToken(); 
    } else {
         std::cout << "Syntax Error: Blok if lupa ditutup pakai 'endif'!\n";
    }

    return ifNode;
}

ASTNode* Parser::parseWhileStatement() {
    ASTNode* whileNode = new ASTNode(currentToken.type, currentToken.literal);
    
    nextToken(); 
    whileNode->condition = parseExpression(Precedence::LOWEST); 
    
    if (currentToken.type == TokenType::DO) {
        nextToken(); 
    } else {
        std::cout << "Syntax Error: while harus diikuti 'do'.\n";
        return nullptr;
    }

    while (currentToken.type != TokenType::ENDWHILE && currentToken.type != TokenType::END_OF_FILE) {
        ASTNode* stmt = parseStatement();
        if (stmt != nullptr) {
            whileNode->body.push_back(stmt);
        } else {
            nextToken();
        }
    }

    if (currentToken.type == TokenType::ENDWHILE) {
         nextToken();
    } else {
         std::cout << "Syntax Error: Blok while lupa ditutup pakai 'endwhile'.\n";
    }

    return whileNode;
}

ASTNode* Parser::parseForStatement() {
    ASTNode* forNode = new ASTNode(currentToken.type, currentToken.literal);
    nextToken();
    
    if (currentToken.type == TokenType::IDENTIFIER && peekToken.type == TokenType::ASSIGN) {
        forNode->left = parseAssignStatement();
    } else {
        std::cout << "Syntax Error: For loop harus dimulai dengan assignment, misal 'for i <- 1'\n";
        return nullptr;
    }

    if (currentToken.type == TokenType::TO) {
        nextToken();
        forNode->condition = parseExpression(Precedence::LOWEST); 
    } else {
        std::cout << "Syntax Error: Kurang keyword 'to' di dalam for!\n";
        return nullptr;
    }

    if (currentToken.type == TokenType::DO) {
        nextToken(); 
    } else {
        std::cout << "Syntax Error: Kurang keyword 'do' setelah batas for!\n";
    }

    while (currentToken.type != TokenType::ENDFOR && currentToken.type != TokenType::END_OF_FILE) {
        ASTNode* stmt = parseStatement();
        if (stmt != nullptr) {
            forNode->body.push_back(stmt);
        } else {
            nextToken();
        }
    }

    if (currentToken.type == TokenType::ENDFOR) {
         nextToken(); 
    } else {
         std::cout << "Syntax Error: Blok for lupa ditutup pakai 'endfor'\n";
    }

    return forNode;
}

ASTNode* Parser::parseExpression(Precedence precedence) {
    ASTNode* leftNode = nullptr;

        if (currentToken.type == TokenType::INT_LITERAL || 
        currentToken.type == TokenType::IDENTIFIER ||
        currentToken.type == TokenType::TRUE_LITERAL ||
        currentToken.type == TokenType::FALSE_LITERAL)  {
        leftNode = new ASTNode(currentToken.type, currentToken.literal);
        nextToken();
    } else if (currentToken.type == TokenType::LPAREN) {
        nextToken();
        leftNode = parseExpression(Precedence::LOWEST);
        if (currentToken.type == TokenType::RPAREN) {
            nextToken();
        } else {
            std::cout << "syntax Error: Ndak ada tutup kurung nya, tolong isi tutup kurung\n";
            return nullptr;
        }
    } else {
        return nullptr;
    }

    while (currentToken.type != TokenType::END_OF_FILE && precedence < getPrecedence(currentToken.type)) {
        Token operatorToken = currentToken;
        Precedence currentPrecedence = getPrecedence(currentToken.type);
        ASTNode* infixNode = new ASTNode(operatorToken.type, operatorToken.literal);
        infixNode->left = leftNode;
        nextToken();
        infixNode->right = parseExpression(currentPrecedence);
        leftNode = infixNode;
    }

    return leftNode;
}

ASTNode* Parser::parseAssignStatement() {
    ASTNode* assignNode = new ASTNode(TokenType::ASSIGN, "=");
    assignNode->left = new ASTNode(currentToken.type, currentToken.literal);
    
    nextToken(); //
    nextToken(); //
    assignNode->right = parseExpression(Precedence::LOWEST);

    return assignNode;
}

ASTNode* Parser::parseInputStatement() {
    ASTNode* inputNode = new ASTNode(currentToken.type, currentToken.literal);
    nextToken(); 

    bool pakaiKurung = false;
    if (currentToken.type == TokenType::LPAREN) {
        pakaiKurung = true;
        nextToken(); 
    }

    if (currentToken.type == TokenType::IDENTIFIER) {
        inputNode->arguments.push_back(new ASTNode(currentToken.type, currentToken.literal));
        nextToken();
    } else {
        std::cout << "Syntax Error: Perintah 'input' harus diikuti nama variabel.\n";
        return nullptr;
    }

    while (currentToken.type == TokenType::COMMA) {
        nextToken(); // Maju ninggalin koma
        if (currentToken.type == TokenType::IDENTIFIER) {
            inputNode->arguments.push_back(new ASTNode(currentToken.type, currentToken.literal));
            nextToken();
        } else {
            std::cout << "Syntax Error: Setelah koma harus ada nama variabel.\n";
            return nullptr;
        }
    }

    if (pakaiKurung) {
        if (currentToken.type == TokenType::RPAREN) {
            nextToken(); 
        } else {
            std::cout << "Syntax Error: Kurung tutup ')' pada input kurang.\n";
            return nullptr;
        }
    }

    return inputNode;
}

ASTNode* Parser::parseOutputStatement() {
    ASTNode* outputNode = new ASTNode(currentToken.type, currentToken.literal);
    nextToken(); 

    outputNode->left = parseExpression(Precedence::LOWEST);
    
    return outputNode;
}

void printTreeHelper(ASTNode* node, int depth, std::ostream& out) {
    if (node == nullptr) return;

    std::string indent(depth * 2, ' ');

    bool isLeaf = (node->left == nullptr && node->right == nullptr &&
                   node->condition == nullptr && node->body.empty() &&
                   node->alternative.empty() && node->arguments.empty());

    out << indent << node->literal;
    if (isLeaf) {
        out << "\n";
        return;
    }
    out << "\n";

    if (node->condition != nullptr) {
        out << indent << "  [cond]\n";
        printTreeHelper(node->condition, depth + 2, out);
    }

    if (node->left != nullptr) {
        out << indent << "  [left]\n";
        printTreeHelper(node->left, depth + 2, out);
    }

    if (node->right != nullptr) {
        out << indent << "  [right]\n";
        printTreeHelper(node->right, depth + 2, out);
    }

    if (!node->body.empty()) {
        out << indent << "  [body]\n";
        for (ASTNode* stmt : node->body) {
            printTreeHelper(stmt, depth + 2, out);
        }
    }

    if (!node->alternative.empty()) {
        out << indent << "  [else]\n";
        for (ASTNode* stmt : node->alternative) {
            printTreeHelper(stmt, depth + 2, out);
        }
    }

    if (!node->arguments.empty()) {
        out << indent << "  [args]\n";
        for (ASTNode* arg : node->arguments) {
            printTreeHelper(arg, depth + 2, out);
        }
    }
}

void printTree(ASTNode* node) {
    printTreeHelper(node, 0, std::cout);
}