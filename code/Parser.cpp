//
//  Parser.cpp
//  nand2tetris_assembler
//
//  Created by 池田伸之 on 2020/02/23.
//  Copyright © 2020 池田伸之. All rights reserved.
//

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "utils.h"

enum CommandType
{
    A_COMMAND,
    C_COMMAND,
    L_COMMAND,
    null
};

class Parser
{
    std::ifstream ifstream;
    std::string command;
    CommandType commandType;

public:
    Parser(std::ifstream ifs) : ifstream(std::move(ifs)) {}

    bool has_more_command()
    {
        if (ifstream.peek() != EOF)
        {
            return true;
        }
        return false;
    }

    void advance()
    {
        std::getline(ifstream, command);

        // コメント、前後空白を削除
        std::size_t comment_pos = command.find("//");
        if (comment_pos != std::string::npos)
        {
            command = command.substr(0, comment_pos);
        }
        Utils::trim(command);
        if (command.length() > 0)
        {
            set_command_type();
        }
    }

    void reset()
    {
        ifstream.seekg(0);
        command = "";
        commandType = null;
    }

    std::string get_command()
    {
        return command;
    }

    bool is_a_command()
    {
        if (commandType == A_COMMAND)
        {
            return true;
        }
        return false;
    }
    bool is_c_command()
    {
        if (commandType == C_COMMAND)
        {
            return true;
        }
        return false;
    }
    bool is_l_command()
    {
        if (commandType == L_COMMAND)
        {
            return true;
        }
        return false;
    }
    std::string get_symbol()
    {
        if (is_a_command())
        {
            int number = std::atoi(command.substr(1).c_str());
            if (number == 0 && command != "@0")
            {
                return command.substr(1);
            }
            return "";
        }
        else if (is_l_command())
        {
            return command.substr(1, command.size() - 2);
        }
        return "";
    }
    std::string get_dest()
    {
        if (is_c_command())
        {
            std::string d = command;
            if (d.find(";") != std::string::npos)
            {
                d = d.substr(0, d.find(";"));
            }
            if (d.find("=") != std::string::npos)
            {
                d = d.substr(0, d.find("="));
            }
            else
            {
                d = "";
            }
            return d;
        }
        return "";
    }
    std::string get_comp()
    {
        if (is_c_command())
        {
            std::string c = command;
            if (c.find(";") != std::string::npos)
            {
                c = c.substr(0, c.find(";"));
            }
            if (c.find("=") != std::string::npos)
            {
                c = c.substr(c.find("=") + 1);
            }
            return c;
        }
        return "";
    }
    std::string get_jump()
    {
        if (is_c_command())
        {
            std::string j = command;
            if (j.find(";") != std::string::npos)
            {
                j = j.substr(j.find(";") + 1);
            }
            else
            {
                j = "";
            }
            return j;
        }
        return "";
    }

    void replace_symbol(int number)
    {
        command = "@" + std::to_string(number);
    }

private:
    void set_command_type()
    {
        if (command.find("@") == 0)
        {
            commandType = A_COMMAND;
        }
        else if (command.find("(") == 0 && command.find(")") + 1 == command.size())
        {
            commandType = L_COMMAND;
        }
        else
        {
            commandType = C_COMMAND;
        }
    }
};
