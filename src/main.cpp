#include "parser/SyntaxTree.hpp"
#include <fstream>
#include <iostream>
#include <stdlib.h>

ast::SyntaxTree syntax_tree;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "用法: " << argv[0] << " <输入文件>\n";
        return 1;
    }
    
    std::ifstream input_file(argv[1]);
    if (!input_file) {
        std::cerr << "错误: 无法打开文件 " << argv[1] << "\n";
        return 1;
    }
    
    ast::parse_file(input_file);
    syntax_tree.print();
    
    return 0;
}