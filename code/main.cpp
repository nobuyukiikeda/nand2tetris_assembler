#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "utils.h"
Utils utils;

#include "Parser.cpp"
#include "Code.cpp"


int main() {
    std::ifstream ifs(
                      "/Users/nov/docs/02_勉強/nand2tetris/projects/06/max/Max.asm");
    if(ifs.fail()) {
        std::cerr << "失敗" << std::endl;
    }
    
    Parser parser(std::move(ifs));
    Code code;
    std::map<std::string, int> symbol;
    
    typedef std::bitset<16> ABit;
    std::string str;
    
    while (parser.has_more_command()) {
        
        parser.advance();
        
        if (parser.is_a_command()) {
            std::string symbol_num_string = parser.get_symbol();
            int symbol_num = std::atoi(symbol_num_string.c_str());
            ABit a_bit(symbol_num);
            str = a_bit.to_string();
        } else if (parser.is_c_command()) {
            std::string dest = code.get_dest(parser.get_dest());
            std::string comp = code.get_comp(parser.get_comp());
            std::string jump = code.get_jump(parser.get_jump());
            str = "111" + comp + dest + jump;
        }
    }

    std::cout << str << std::endl;
    return 0;
}
