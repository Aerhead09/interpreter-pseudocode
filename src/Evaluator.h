#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "Parser.h"
#include <unordered_map>
#include <string>

int evaluate(ASTNode* node, std::unordered_map<std::string, int>& env);

#endif