#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Parser.h"
#include "Evaluator.h"

int main(int argc, char* argv[]) {
    bool showTree = false;
    std::string namaFile;

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--tree" || arg == "-t") {
            showTree = true;
        } else if (namaFile.empty()) {
            namaFile = arg;
        }
    }

    if (namaFile.empty()) {
        std::cerr << "Cara penggunaan: interpreter [--tree] nama_file.psdc\n";
        return 1;
    }

    std::ifstream fileSource(namaFile);
    if (!fileSource.is_open()) {
        std::cerr << "Error: File '" << namaFile << "' tidak ditemukan.\n";
        return 1;
    }

    std::stringstream buffer;
    buffer << fileSource.rdbuf();
    std::string kodeInput = buffer.str();

    Lexer lexer(kodeInput);
    Parser parser(lexer);
    ASTNode* akarPohon = parser.parseProgram();

    if (showTree) {
        std::cerr << "--- AST ---\n";
        printTree(akarPohon);
        std::cerr << "-----------\n\n";
    }

    std::unordered_map<std::string, int> environment;
    evaluate(akarPohon, environment);

    return 0;
}