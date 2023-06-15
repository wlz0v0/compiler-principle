#include "Token.h"

Token::Token() :rowNum(-1), columnNum(-1), type(IDENTIFIER), value("") {
}
void Token::setErrorIdName(Token& token) {
	token.type = ERROR;
	token.value = "����ı�ʶ����";
}

void Token::setNoRightQuotation(Token& token) {
	token.type = ERROR;
	token.value = "ȱ��������";
}

std::ostream& operator<<(std::ostream& os, Token& token) {
	std::string val = token.value;
	std::string type;
	switch (token.type) {
	case IDENTIFIER: {
		int index = std::stoi(token.value);
		// val = symbolTable[index];
		if (index <= 32) {
			type = "�ؼ���";
		} else {
			type = "��ʶ��";
		}
		break;
	}
	case ADD:
	case SUB:
	case MUL:
	case DIV:
	case ASSIGN:
		type = "��ֵ";
		break;
	case NUMBER:
		type = "����";
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
		type = "�����";
		break;
	case LEFT_PARENTHESIS:
	case RIGHT_PARENTHESIS:
	case LEFT_BRACKET:
	case RIGHT_BRACKET:
	case LEFT_BRACE:
	case RIGHT_BRACE:
	case SIMICOLON:
		type = "�ָ���";
		break;
	default:
		break;
	}
	os << val << type;
	return os;
}
