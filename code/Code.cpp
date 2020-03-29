//
//  code.hpp
//  nand2tetris_assembler
//
//  Created by 池田伸之 on 2020/02/23.
//  Copyright © 2020 池田伸之. All rights reserved.
//

#include <stdio.h>
#include <map>
#include <string>

class Code {
    std::map<std::string, std::string> dest = {
        {"A", "100"},
        {"D", "010"},
        {"M", "001"},
        {"AD", "110"},
        {"AM", "101"},
        {"MD", "011"},
        {"ADM", "111"}
    };

    std::map<std::string, std::string> comp = {
        {"0",   "0101010"},
        {"1",   "0111111"},
        {"-1",  "0111010"},
        {"D",   "0001100"},
        {"A",   "0110000"},
        {"!D",  "0001101"},
        {"!A",  "0110001"},
        {"D+1", "0011111"},
        {"A+1", "0110111"},
        {"D-1", "0001110"},
        {"A-1", "0110010"},
        {"D+A", "0000010"},
        {"D-A", "0010011"},
        {"A-D", "0000111"},
        {"D&A", "0000000"},
        {"D|A", "0010101"},
        {"M",   "1110000"},
        {"!M",  "1110001"},
        {"M+1", "1110111"},
        {"M-1", "1110010"},
        {"D+M", "1000010"},
        {"D-M", "1010011"},
        {"M-D", "1000111"},
        {"D&M", "1000000"},
        {"D|M", "1010101"}
    };

    std::map<std::string, std::string> jump = {
        {"JGT", "001"},
        {"JEQ", "010"},
        {"JGE", "011"},
        {"JLT", "100"},
        {"JNE", "101"},
        {"JLE", "110"},
        {"JMP", "111"}
    };
public:
    std::string get_dest(std::string d) {
        return dest.at(d);
    }
    std::string get_comp(std::string c) {
        return comp.at(c);
    }
    std::string get_jump(std::string j) {
        return jump.at(j);
    }
};
