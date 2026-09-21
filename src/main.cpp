#include <iostream>
#include <string>
#include <fstream>  
#include <sstream>  
#include "Parser.h"
#include "Evaluator.h" 

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Cara penggunaan: interpreter nama_file.psdc\n";
        return 1;
    }

    std::string namaFile = argv[1];

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

    std::unordered_map<std::string, int> environment;
    evaluate(akarPohon, environment);

    return 0;
}