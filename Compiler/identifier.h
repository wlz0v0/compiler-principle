#ifndef IDENTIFIER_H
#define IDENTIFIER_H
#include <vector>
#include <string>
#include "Token.h"
#include "input.h"

extern std::vector<std::string> symbolTable;

Token identifier2Token();

#endif // IDENTIFIER_H