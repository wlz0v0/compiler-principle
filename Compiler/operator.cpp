#include "operator.h"
#include <map>
#include <string>
#include "input.h"

bool isOperator(char c);

std::map<std::string, TokenType> opTypeMap = {
	{"<", LT},
	{"<=", LTE},
	{">", GT},
	{">=", GTE},
	{"==", EQUAL},
	{"!=", NE},
	{"&&", AND},
	{"||", OR},
	{"!", NOT},
	{"+", PLUS},
	{"-", MINUS},
	{"*", TIMES},
	{"/", OVER},
	{"++", INC},
	{"--", DEC},
	{"%", MOD},
	{"<<", SHL},
	{">>", SHR},
	{"&", BIT_AND},
	{"|", BIT_OR},
	{"^", BIT_NOR},
	{"~", BIT_NOT},
	{"+=", ADD},
	{"-=", SUB},
	{"*=", MUL},
	{"/=", DIV},
	{"<<=", SHL_ASSIGN},
	{">>=", SHR_ASSIGN},
	{"&=", AND_ASSGIN},
	{"|=", OR_ASSGIN},
	{"^=", NOR_ASSGIN},
	{"%=", MOD_ASSGIN},
	{"=", ASSIGN},
	{"->", ARROW}
};

std::map<std::string, TokenType> singleOpTypeMap = {
	{"(", LEFT_PARENTHESIS},
	{")", RIGHT_PARENTHESIS},
	{"[", LEFT_BRACKET},
	{"]", RIGHT_BRACKET},
	{"{", LEFT_BRACE},
	{"}", RIGHT_BRACE},
	{",", COMMA},
	{".", DOT},
	{";", SIMICOLON},
	{":", COLON},
	{"?", QUESTION}
};

Token operator2Token() {
	Token token;
	token.rowNum = rowCnt;
	token.columnNum = columnCnt;
	char ch = ifs.get();
	++columnCnt;
	++charCnt;
	std::string op;
	auto it = singleOpTypeMap.find(std::string(1, ch));
	if (it != singleOpTypeMap.end()) {
		token.type = it->second;
		return token;
	}
	while (isOperator(ch)) {
		op += ch;
		ch = ifs.get();
		++columnCnt;
		++charCnt;
	}
	if (!ifs.eof()) {
		ifs.unget();
		--columnCnt;
		--charCnt;
	}
	it = opTypeMap.find(op);
	while (it == opTypeMap.end() && op.size() != 1) {
		op.erase(op.size() - 1);
		ifs.unget();
		--columnCnt;
		--charCnt;
		it = opTypeMap.find(op);
	}
	if (it == opTypeMap.end()) {
		token.type = ERROR;
		token.value = "无法识别标记";
	} else {
		token.type = it->second;
		token.value = op;
	}
	return token;
}

bool isOperator(char c) {
	return (c >= 33 && c <= 47) ||
		(c >= 58 && c <= 64) ||
		(c >= 91 && c <= 96) ||
		(c >= 123 && c <= 126);
}
