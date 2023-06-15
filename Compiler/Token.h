#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <iostream>

enum TokenType {
	ERROR,
	IDENTIFIER,
	NUMBER,
	STRING,
	CHAR,
	// operators
	LT, // <
	LTE, // <=
	GT, // >
	GTE, // >=
	EQUAL, // ==
	NE, // !=
	AND, // &&
	OR, // ||
	NOT, // !
	INC, // ++
	DEC, // --
	PLUS, // +
	MINUS, // -
	TIMES, // *
	OVER, // /
	MOD, // %
	SHL, // <<
	SHR, // >>
	BIT_AND, // &
	BIT_OR, // |
	BIT_NOR, // ^
	BIT_NOT, // ~
	ADD, // +=
	SUB, // -=
	MUL, // *=
	DIV, // /=
	SHL_ASSIGN, // <<=
	SHR_ASSIGN, // >>=
	AND_ASSGIN, // &=
	OR_ASSGIN, // |=
	NOR_ASSGIN, // ^=
	MOD_ASSGIN, // %=
	ASSIGN, // =
	LEFT_PARENTHESIS, // (
	RIGHT_PARENTHESIS, // )
	LEFT_BRACKET, // [
	RIGHT_BRACKET, // ]
	LEFT_BRACE, // {
	RIGHT_BRACE, // }
	COMMA, // ,
	DOT, // .
	SIMICOLON, // ;
	COLON, // :
	QUESTION, // ?
	ARROW // ->
};

class Token
{
public:
	size_t rowNum;
	size_t columnNum;
	TokenType type;
	std::string value;

	Token();
	static void setErrorIdName(Token& token);
	static void setNoRightQuotation(Token& token);
	friend std::ostream& operator<<(std::ostream& os, Token& token);
};

#endif // TOKEN_H