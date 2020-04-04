//
//  utils.h
//  nand2tetris_assembler
//
//  Created by 池田伸之 on 2020/02/23.
//  Copyright © 2020 池田伸之. All rights reserved.
//

#pragma once
#ifndef utils_h
#define utils_h

#include <fstream>
#include <iostream>
#include <string>

class Utils {
public:
    static void ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                        [](int ch) { return !std::isspace(ch); }));
    }
    
    static void rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(),
                             [](int ch) { return !std::isspace(ch); })
                .base(),
                s.begin());
    }
    
    static void trim(std::string &s) {
        ltrim(s);
        rtrim(s);
    }
    
    std::string parse_instruction(std::string &str) {
        std::string instruction_a = "0";
        std::string instruction_c = "000000";
        std::string instruction_d = "000";
        std::string instruction_j = "000";
        
        std::size_t equel_pos = str.find_first_of("=");
        // compニーモニック
        std::string comp_target = str.substr(equel_pos + 1);
        if(comp_target == "0") {
            instruction_c = "101010";
        } else if(comp_target == "1") {
            instruction_c = "111111";
        } else if(comp_target == "-1") {
            instruction_c = "111010";
        } else if(comp_target == "D") {
            instruction_c = "001100";
        } else if(comp_target == "A") {
            instruction_c = "110000";
        } else if(comp_target == "!D") {
            instruction_c = "001101";
        } else if(comp_target == "!A") {
            instruction_c = "110001";
        } else if(comp_target == "D+1") {
            instruction_c = "011111";
        } else if(comp_target == "A+1") {
            instruction_c = "110111";
        } else if(comp_target == "D-1") {
            instruction_c = "001110";
        } else if(comp_target == "A-1") {
            instruction_c = "110010";
        } else if(comp_target == "D+A") {
            instruction_c = "000010";
        } else if(comp_target == "D-A") {
            instruction_c = "010011";
        } else if(comp_target == "A-D") {
            instruction_c = "000111";
        } else if(comp_target == "D&A") {
            instruction_c = "000000";
        } else if(comp_target == "D|A") {
            instruction_c = "010101";
        } else if(comp_target == "M") {
            instruction_a = "1";
            instruction_c = "110000";
        } else if(comp_target == "!M") {
            instruction_a = "1";
            instruction_c = "110001";
        } else if(comp_target == "M+1") {
            instruction_a = "1";
            instruction_c = "110111";
        } else if(comp_target == "M-1") {
            instruction_a = "1";
            instruction_c = "110010";
        } else if(comp_target == "D+M") {
            instruction_a = "1";
            instruction_c = "000010";
        } else if(comp_target == "D-M") {
            instruction_a = "1";
            instruction_c = "010011";
        } else if(comp_target == "M-D") {
            instruction_a = "1";
            instruction_c = "000111";
        } else if(comp_target == "D&M") {
            instruction_a = "1";
            instruction_c = "000000";
        } else if(comp_target == "D|M") {
            instruction_a = "1";
            instruction_c = "010101";
        }
        
        // distニーモニック
        std::string dist_target = str.substr(0, equel_pos);
        if(dist_target.find("A") != std::string::npos) {
            instruction_d[0] = '1';
        }
        if(dist_target.find("D") != std::string::npos) {
            instruction_d[1] = '1';
        }
        if(dist_target.find("M") != std::string::npos) {
            instruction_d[2] = '1';
        }
        
        // jumpニーモニック
        if(str.find("JGT") != std::string::npos) {
            instruction_j = "001";
        } else if(str.find("JEQ") != std::string::npos) {
            instruction_j = "010";
        } else if(str.find("JGE") != std::string::npos) {
            instruction_j = "011";
        } else if(str.find("JLT") != std::string::npos) {
            instruction_j = "100";
        } else if(str.find("JNE") != std::string::npos) {
            instruction_j = "101";
        } else if(str.find("JLE") != std::string::npos) {
            instruction_j = "110";
        } else if(str.find("JMP") != std::string::npos) {
            instruction_j = "111";
        }
        std::string instruction_string =
        "111" + instruction_a + instruction_c + instruction_d + instruction_j;
        
        return instruction_string;
    }
};



#endif /* utils_h */
