#ifndef INPUT_H
#define INPUT_H
#include <fstream>
#include <vector>
#include "Token.h"

extern std::ifstream ifs;
extern size_t charCnt;
extern size_t rowCnt;
extern size_t columnCnt;
extern std::vector<Token> tokens;
extern std::vector<Token> errors;

void addToken(Token token);

#endif // INPUT_H