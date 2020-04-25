#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <bitset>

#include "utils.h"
Utils utils;

#include "SymbolTable.cpp"
#include "Parser.cpp"
#include "Code.cpp"

int main()
{
    // 入力ファイルのセット
    std::cout << "ファイルパスを入力してください。" << std::endl;
    std::string path;
    std::cin >> path;

    // 出力ファイルのセット
    std::string filename = path;
    std::size_t extention_pos = filename.find_last_of(".");
    std::string output_filename = filename.erase(extention_pos) + ".hack";
    std::ofstream writing_file;
    writing_file.open(output_filename, std::ios::out);

    // ファイルの読み込み
    std::ifstream ifs(path);

    if (ifs.fail())
    {
        std::cerr << "失敗" << std::endl;
    }

    SymbolTable symbolTable;
    Code code;

    // std::cout << "1週目" << std::endl;

    // 1週目： (Symbol) をsymbolMapに登録
    Parser parser(std::move(ifs));
    int i = 0;
    while (parser.has_more_command())
    {

        parser.advance();

        // コメント行・空行のケース
        if (parser.get_command().length() == 0)
        {
            continue;
        }

        // Lコマンドのケース
        if (parser.is_l_command())
        {
            std::string symbol = parser.get_symbol();
            symbolTable.add_entry(symbol, i);
        }
        else
        {
            // Aコマンド, Cコマンドのケース
            ++i;
        }
    }

    // std::cout << "2週目" << std::endl;
    // symbolTable.print_all();

    // 2週目： @Symbol をsymbolMapに登録
    parser.reset();
    i = 0;
    while (parser.has_more_command())
    {

        parser.advance();

        // コメント行・空行のケース
        if (parser.get_command().length() == 0)
        {
            continue;
        }

        // Aコマンドのケース
        if (parser.is_a_command())
        {
            std::string symbol = parser.get_symbol();
            // std::cout << symbol << " " << symbolTable.contains(symbol) << std::endl;
            if (symbol != "" && !symbolTable.contains(symbol))
            {
                symbolTable.add_entry(symbol);
            }
        }
    }

    // std::cout << "3週目" << std::endl;

    // 3週目： ファイルに出力
    parser.reset();
    typedef std::bitset<16> ABit;
    std::string str;
    while (parser.has_more_command())
    {

        parser.advance();

        // コメント行・空行のケース
        if (parser.get_command().length() == 0)
        {
            continue;
        }

        // Lコマンドのケース
        if (parser.is_l_command())
        {
            continue;
        }

        // Aコマンドのケース
        if (parser.is_a_command())
        {
            std::string symbol = parser.get_symbol();
            if (symbol != "")
            {
                parser.replace_symbol(symbolTable.get_address(symbol));
            }

            // コマンドの数字部分をint型->2進数に変換
            ABit a_bit(std::atoi(parser.get_command().substr(1).c_str()));
            str = a_bit.to_string();
        }

        // Cコマンドのケース
        if (parser.is_c_command())
        {
            std::string dest = code.get_dest(parser.get_dest());
            std::string comp = code.get_comp(parser.get_comp());
            std::string jump = code.get_jump(parser.get_jump());
            str = "111" + comp + dest + jump;
        }

        std::cout << str << std::endl;
        writing_file << str << std::endl;
    }
    return 0;
}
