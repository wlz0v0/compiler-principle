#include "number.h"
#include <string>
#include "input.h"

bool isalpha_(char ch);
std::string getNextNum(char& ch);
Token setErrorIdName(Token token);

Token number2Token() {
    Token token;
    token.rowNum = rowCnt;
    token.columnNum = columnCnt;
    std::string num;
    char ch = ifs.get();
    while (ch == '0') {
        ch = ifs.get();
        ++columnCnt;
        ++charCnt;
    }
    if (isdigit(ch)) {
        num += ch;
        num += getNextNum(ch);
        if (ch != 'e' && ch != 'E' && isalpha_(ch)) {
            return setErrorIdName(token);
        }
    }
    switch (ch) {
    case '.':
        if (num.size() == 0) {
            num += '0';
        }
        num += ch;
        num += getNextNum(ch);
        if (ch != 'e' && ch != 'E') {
            if (isalpha_(ch)) {
                return setErrorIdName(token);
            } else {
                token.type = NUMBER;
                token.value = num;
                if (!ifs.eof()) {
                    ifs.unget();
                    --columnCnt;
                    --charCnt;
                }
            }
            return token;
        }
    case 'e':
    case 'E':
        if (num.size() == 0) {
            num += '0';
        }
        num += ch;
        ch = ifs.get();
        if (ch == '+' || ch == '-') {
            ++columnCnt;
            ++charCnt;
            num += ch;
        } else {
            ifs.unget();
        }
        num += getNextNum(ch);
        if (isalpha_(ch)) {
            return setErrorIdName(token);
        }
    default:
        if (num.size() == 0) {
            num += '0';
        }
        token.type = NUMBER;
        token.value = num;
        if (!ifs.eof()) {
            ifs.unget();
            --columnCnt;
            --charCnt;
        }
    }
    return token;
}

bool isalpha_(char ch) {
    return isalpha(ch) || ch == '_';
}

Token setErrorIdName(Token token) {
    char ch = ifs.get();
    ++columnCnt;
    ++charCnt;
    while (isalnum(ch) || ch == '_') {
        ch = ifs.get();
        ++columnCnt;
        ++charCnt;
    }
    Token::setErrorIdName(token);
    return token;
}

std::string getNextNum(char& ch) {
    std::string num;
    ch = ifs.get();
    ++columnCnt;
    ++charCnt;
    while (isdigit(ch)) {
        num += ch;
        ch = ifs.get();
        ++columnCnt;
        ++charCnt;
    }
    return num;
}