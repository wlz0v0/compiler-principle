#include "input.h"
#include <iostream>

std::ifstream ifs;
size_t charCnt = 0;
size_t rowCnt = 1;
size_t columnCnt = 0;
std::vector<Token> tokens;
std::vector<Token> errors;

void addToken(Token token) {
	if (token.type == ERROR) {
		errors.push_back(token);
	} else {
		tokens.push_back(token);
	}
	std::cout << token.type << " " << token.value << "\n";
}
