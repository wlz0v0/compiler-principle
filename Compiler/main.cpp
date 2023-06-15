#include <filesystem>
#include <iostream>
#include <fstream>
#include "input.h"
#include "identifier.h"
#include "number.h"
#include "note.h"
#include "string.h"
#include "operator.h"
#include "Token.h"

int main(int argc, char** argv) {
	/*if (argc != 2) {
		std::cerr << "参数错误\n";
		system("pause");
		return 1;
	}*/

	std::filesystem::path absolutePath = std::filesystem::path("test.txt");
	// 如果是相对路径，则改为绝对路径
	if (absolutePath.is_relative()) {
		absolutePath = std::filesystem::current_path() / absolutePath;
	}
	if (!std::filesystem::exists(absolutePath)) {
		std::cerr << "文件不存在\n";
		system("pause");
		return 1;
	}
	ifs.open(absolutePath);
	while (!ifs.eof()) {
		char ch = ifs.get();
		if (ch == -1) {
			break;
		} else if (isalpha(ch) || ch == '_') {
			ifs.unget();
			addToken(identifier2Token());
		} else if (isdigit(ch)) {
			ifs.unget();
			addToken(number2Token());
		} else if (ch == '\"') {
			++columnCnt;
			++charCnt;
			addToken(string2Token());
		} else if (ch == '\'') {
			++columnCnt;
			++charCnt;
			addToken(char2Token());
		} else if (ch == '/') {
			ch = ifs.get();
			if (ch == '/') {
				++columnCnt;
				++charCnt;
				skipLineNote();
			} else if (ch == '*') {
				++columnCnt;
				++charCnt;
				Token token = skipBlockNote();
				if (token.type == ERROR) {
					errors.push_back(token);
				}
			} else {
				ifs.unget();
				ifs.unget();
				addToken(operator2Token());
			}
		} else if (ch == ' ') {
			++columnCnt;
			++charCnt;
			continue;
		} else if (ch == '\t') {
			columnCnt += 4;
			++charCnt;
		} else if (ch == '\n') {
			++rowCnt;
			++charCnt;
			columnCnt = 0;
			continue;
		} else {
			if (!ifs.eof()) {
				ifs.unget();
			}
			addToken(operator2Token());
		}
	}
	//for (auto t : tokens) {
	//	
	//}
	//for (auto t : errors) {
	//	std::cout << t.value << "\n";
	//}
	ifs.close();
	std::cout << rowCnt << "\n";
	return 0;
}