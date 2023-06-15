#include "string.h"
#include <string>
#include "input.h"

Token string2Token() {
	Token token;
	token.rowNum = rowCnt;
	token.columnNum = columnCnt;
	std::string val;
	char ch = ifs.get();
	++columnCnt;
	++charCnt;
	while (ch != '\"' && ch != '\n' && !ifs.eof()) {
		val += ch;
		ch = ifs.get();
		++columnCnt;
		++charCnt;
	}
	if (ch == '\n' || ifs.eof()) {
		Token::setNoRightQuotation(token);
	} else {
		token.type = STRING;
		token.value = val;
	}
	return token;
}

Token char2Token() {
	Token token;
	token.rowNum = rowCnt;
	token.columnNum = columnCnt;
	std::string val;
	char ch = ifs.get();
	++columnCnt;
	++charCnt;
	while (ch != '\'' && ch != '\n' && !ifs.eof()) {
		val += ch;
		ch = ifs.get();
		++columnCnt;
		++charCnt;
	}
	if (ch == '\n' || ifs.eof()) {
		Token::setNoRightQuotation(token);
	} else if (val.size() == 0) {
		token.type = ERROR;
		token.value = "应至少包含一个字符";
	} else if (val.size() > 1) {
		token.type = ERROR;
		token.value = "字符数量过多";
	} else {
		token.type = CHAR;
		token.value = val;
	}
	return token;
}
