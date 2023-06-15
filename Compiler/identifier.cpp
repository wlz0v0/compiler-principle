#include "identifier.h"
#include <iostream>

std::vector<std::string> symbolTable = {
    "void",
    "short",
    "int",
    "long",
    "double",
    "float",
    "char",
    "signed",
    "unsigned",
    "struct",
    "union",
    "enum",
    "typedef",
    "sizeof",
    "inline",
    "auto",
    "static",
    "register",
    "extern",
    "const",
    "volatile",
    "return",
    "continue",
    "break",
    "goto",
    "if",
    "else",
    "switch",
    "case",
    "default",
    "for",
    "while",
    "do"
};

Token identifier2Token() {
    Token token;
    std::string symbol;
    token.rowNum = rowCnt;
    token.columnNum = columnCnt;
    char ch = ifs.get();
    ++charCnt;
    ++columnCnt;
    while (isalnum(ch) || ch == '_') {
        symbol += ch;
        ch = ifs.get();
        ++charCnt;
        ++columnCnt;
    }
    if (!ifs.eof()) {
        ifs.unget();
        --charCnt;
        --columnCnt;
    }
    int i = 0;
    while (i != symbolTable.size()) {
        if (symbolTable[i] == symbol) {
            break;
        }
        ++i;
    }
    token.type = IDENTIFIER;
    token.value = std::to_string(i);
    if (i == symbolTable.size()) {
        symbolTable.push_back(symbol);
    }
    return token;
}
