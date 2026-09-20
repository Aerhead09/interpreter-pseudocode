#include <iostream>
#include <string>
#include <fstream>  
#include <sstream>  
#include "Parser.h"
#include "Evaluator.h" 

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Cara penggunaan: .\\tester nama_file.psdc\n";
        return 1; 
    }

    std::string namaFile = argv[1];
    
    std::ifstream fileSource(namaFile);
    if (!fileSource.is_open()) {
        std::cout << "Error Gaib: File '" << namaFile << "' tidak ditemukan atau anda lupa naruh di folder yang benar.\n";
        return 1;
    }

    std::stringstream buffer;
    buffer << fileSource.rdbuf();
    std::string kodeInput = buffer.str();

    std::cout << "=== Mengeksekusi File: " << namaFile << " ===\n\n";

    Lexer lexer(kodeInput);
    Parser parser(lexer);
    ASTNode* akarPohon = parser.parseProgram();

    std::cout << "Wujud Pohon  :\n";
    printTree(akarPohon);
    std::cout << "\n\n--- OUTPUT PROGRAM ---\n";

    std::unordered_map<std::string, int> environment;
    int hasilAkhir = evaluate(akarPohon, environment);
    
    std::cout << "\n-----------------------------------\n";
    std::cout << "Program selesai dengan exit code: " << hasilAkhir << "\n";

    return 0;
}