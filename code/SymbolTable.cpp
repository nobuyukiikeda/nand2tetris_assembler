//
//  SymbolTable.cpp
//  nand2tetris_assembler
//
//  Created by 池田伸之 on 2020/04/19.
//  Copyright © 2020 池田伸之. All rights reserved.
//

#include <stdio.h>
#include <map>
#include <string>
#include <iostream>

class SymbolTable
{
    std::map<std::string, int> table;
    int current_address;

public:
    SymbolTable()
    {
        table = {
            {"R0", 0},
            {"R1", 1},
            {"R2", 2},
            {"R3", 3},
            {"R4", 4},
            {"R5", 5},
            {"R6", 6},
            {"R7", 7},
            {"R8", 8},
            {"R9", 9},
            {"R10", 10},
            {"R11", 11},
            {"R12", 12},
            {"R13", 13},
            {"R14", 14},
            {"R15", 15},
            {"SP", 0},
            {"LCL", 1},
            {"ARG", 2},
            {"THIS", 3},
            {"THAT", 4},
            {"SCREEN", 16384},
            {"KBD", 24576},
        };
        current_address = 16;
    }

    void add_entry(std::string key, int address = -1)
    {
        std::pair<std::string, int> pair;
        if (address >= 0)
        {
            pair = std::make_pair(key, address);
        }
        else
        {
            pair = std::make_pair(key, current_address);
            current_address++;
        }

        table.insert(pair);
    }

    bool contains(std::string symbol)
    {
        auto t = table.find(symbol);
        if (t != table.end())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    uint get_address(std::string symbol)
    {
        return table[symbol];
    }

    void print_all()
    {
        for (const auto &[key, value] : table)
        {
            std::cout << key << " => " << value << "\n";
        }
    }
};