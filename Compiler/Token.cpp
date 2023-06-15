#include "Token.h"

Token::Token() :rowNum(-1), columnNum(-1), type(IDENTIFIER), value("") {
}
void Token::setErrorIdName(Token& token) {
	token.type = ERROR;
	token.value = "错误的标识符名";
}

void Token::setNoRightQuotation(Token& token) {
	token.type = ERROR;
	token.value = "缺少右引号";
}

std::ostream& operator<<(std::ostream& os, Token& token) {
	std::string val = token.value;
	std::string type;
	switch (token.type) {
	case IDENTIFIER: {
		int index = std::stoi(token.value);
		// val = symbolTable[index];
		if (index <= 32) {
			type = "关键字";
		} else {
			type = "标识符";
		}
		break;
	}
	case ADD:
	case SUB:
	case MUL:
	case DIV:
	case ASSIGN:
		type = "赋值";
		break;
	case NUMBER:
		type = "常数";
		break;
	case LT:
	case LTE:
	case GT:
	case GTE:
	case EQUAL:
	case INC:
	case DEC:
	case PLUS:
	case MINUS:
	case TIMES:
	case OVER:
		type = "运算符";
		break;
	case LEFT_PARENTHESIS:
	case RIGHT_PARENTHESIS:
	case LEFT_BRACKET:
	case RIGHT_BRACKET:
	case LEFT_BRACE:
	case RIGHT_BRACE:
	case SIMICOLON:
		type = "分隔符";
		break;
	default:
		break;
	}
	os << val << type;
	return os;
}
