#include "note.h"
#include "input.h"

void skipLineNote() {
    char ch = -1;
    do {
        ch = ifs.get();
        ++columnCnt;
        ++charCnt;
    } while (ch != '\n' && !ifs.eof());
}

Token skipBlockNote() {
    char ch = -1;
    Token token;
    token.rowNum = rowCnt;
    token.columnNum = columnCnt;
    while (!ifs.eof()) {
        ch = ifs.get();
        ++columnCnt;
        ++charCnt;
        if (ch == '*') {
            ch = ifs.get();
            ++columnCnt;
            ++charCnt;
            if (ch == '/') {
                break;
            }
        }
    }
    if (ifs.eof()) {
        token.type = ERROR;
        token.value = "¿é×¢ÊÍÎ´±ÕºÏ";
    }
    return token;
}