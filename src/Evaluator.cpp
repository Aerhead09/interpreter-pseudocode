#include "Evaluator.h"
#include <string>
#include <iostream>

int evaluate(ASTNode* node, std::unordered_map<std::string, int>& env) {
    if (node == nullptr) return 0;

    if (node->type == TokenType::TRUE_LITERAL) return 1;
    if (node->type == TokenType::FALSE_LITERAL) return 0;

    if (node->type == TokenType::INT_LITERAL) {
        return std::stoi(node->literal);
    }

    if (node->type == TokenType::IDENTIFIER) {
        if (env.find(node->literal) != env.end()) {
            return env[node->literal];
        } else {
            std::cout << "Runtime Error: Variabel '" << node->literal << "' belum didefinisikan.\n";
            return 0;
        }
    }

    if (node->type == TokenType::PROGRAM) {
        int lastValue = 0;
        for (ASTNode* stmt : node->body) {
            lastValue = evaluate(stmt, env);
        }
        return lastValue; 
    }

    if (node->type == TokenType::IF) {
        int conditionValue = evaluate(node->condition, env);

        if (conditionValue != 0) { 
            for (ASTNode* stmt : node->body) evaluate(stmt, env);
        } else { 
            for (ASTNode* stmt : node->alternative) evaluate(stmt, env);
        }
        return 0; 
    }

    if (node->type == TokenType::WHILE) {
        while (evaluate(node->condition, env) != 0) {
            for (ASTNode* stmt : node->body) evaluate(stmt, env);
        }
        return 0;
    }

    if (node->type == TokenType::FOR) {
        std::string varName = node->left->left->literal;
        int startPos = evaluate(node->left->right, env);
        int endPos = evaluate(node->condition, env);

        for (int i = startPos; i <= endPos; i++) {
            env[varName] = i;
            for (ASTNode* stmt : node->body) {
                evaluate(stmt, env);
            }
        }
        return 0;
    }

    if (node->type == TokenType::ASSIGN) {
        int value = evaluate(node->right, env);
        env[node->left->literal] = value;
        return value;
    }

    if (node->type == TokenType::INPUT) {
        for (ASTNode* arg : node->arguments) {
            int inputVal;
            std::cerr << "Masukkan nilai " << arg->literal << " = ";
            std::cin >> inputVal;
            env[arg->literal] = inputVal;
        }
        return 0;
    }

    if (node->type == TokenType::OUTPUT) {
        std::cout << evaluate(node->left, env) << "\n";
        return 0;
    }

    int leftValue = evaluate(node->left, env);
    int rightValue = evaluate(node->right, env);

    switch (node->type) {
        case TokenType::PLUS:
            return leftValue + rightValue;
        case TokenType::MINUS:
            return leftValue - rightValue;
        case TokenType::STAR:
            return leftValue * rightValue;
        case TokenType::SLASH:
            if (rightValue == 0) {
                std::cout << "Runtime Error: Pembagian dengan nol terdeteksi. Tidak bisa membagi dengan penyebut 0.\n";
                return 0;
            }
            return leftValue / rightValue;
        case TokenType::MOD:
            if (rightValue == 0) {
                std::cout << "Runtime Error: Modulo dengan nol terdeteksi.\n";
                return 0;
            }
            return leftValue % rightValue;
        case TokenType::EQUALS: return leftValue == rightValue ? 1 : 0;
        case TokenType::LESS_THAN: return leftValue < rightValue ? 1 : 0;
        case TokenType::GREATER_THAN: return leftValue > rightValue ? 1 : 0;
        case TokenType::LESS_THAN_EQUALS: return leftValue <= rightValue ? 1 : 0;
        case TokenType::GREATER_THAN_EQUALS: return leftValue >= rightValue ? 1 : 0;
        case TokenType::AND: return (leftValue != 0 && rightValue != 0) ? 1 : 0;
        case TokenType::OR:  return (leftValue != 0 || rightValue != 0) ? 1 : 0;
        default:
            return 0;
    }
}