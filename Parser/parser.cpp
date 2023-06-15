#include <iostream>
#include <stack>
#include <vector>
#include <map>
#include <string>
using namespace std;
string filename = "";
string input = "";

constexpr int ERROR = 0;
constexpr int ACC = 1;
constexpr int SHIFT = 2;
constexpr int REDUCE = 3;
constexpr int GOTO = 4;

class Action {
public:
	int type; // 0 error, 1 acc, 2 shift, 3 reduce, 4 goto
	int state;
	Action() : type(0), state(0) {}
	Action(int type, int state) : type(type), state(state) {}
};

class Production {
public:
	char left;
	string right;
	Production(char left, string right) : left(left), right(right) {}
	friend ostream& operator<<(ostream& os, Production& p) {
		string right = p.right.empty() ? "e" : p.right;
		os << p.left << "->" << right;
		return os;
	}
};

class TreeNode {
public:
	char val;
	vector<TreeNode*> children;
	TreeNode(char val) : val(val) {}
};

vector<vector<Action>> parseTable(22, vector<Action>(13));
map<char, int> symbolColumnMap;
vector<Production> productions = {
	{'E', "TA"}, {'A', "+TA"}, {'A', "-TA"}, {'A', ""}, {'T', "FB"},
	{'B', "*FB"}, {'B', "/FB"}, {'B', ""}, {'F', "(E)"}, {'F', "n"}
};

string statement;
stack<TreeNode*> symbolStack;
stack<int> stateStack;
stack<Production> res;

void dfsPrint(TreeNode* n);
void initParseTable();
void digitReplace();
void generateParseTree();
void act(Action action);
void shift(int state);
void reduce(int num);
void _goto();

string getInput() {
	if (input == "") {
		char c;
		string s;
		while (cin.get(c)) {
			s += c;
		}
		return s;
	}
	return input;
}

string getFilename() {
	if (filename == "") {
		char s[20];
		cin.getline(s, 20);
		string fs = "/data/workspace/myshixun/src/step1/";
		return fs + string(s).substr(2, 20);
	}
	return filename;
}

int main() {
	filename = getFilename();
	input = getInput();
	statement = input;
	//从这里开始你的编程
	initParseTable();
	generateParseTree();
	dfsPrint(symbolStack.top());
	return 0;
}

void dfsPrint(TreeNode* n) {
	if (!n->children.empty()) {
		cout << n->val << "->";
		for (auto c : n->children) {
			cout << c->val;
		}
		cout << "\n";
	}
	for (auto c : n->children) {
		dfsPrint(c);
	}
}

void initParseTable() {
	string symbols = "+-*/()n$ETFAB";
	for (int i = 0; i < 13; ++i) {
		symbolColumnMap.insert({ symbols[i], i });
	}
	int rows[6] = { 0, 4, 7, 8, 10, 11 };
	for (int i = 0; i < 6; ++i) {
		parseTable[rows[i]][symbolColumnMap['(']] = Action(SHIFT, 4);
		parseTable[rows[i]][symbolColumnMap['n']] = Action(SHIFT, 5);
	}
	int b[6] = { 0, 1, 4, 5, 6, 7 };
	int a[6] = { 2, 3, 4, 5, 6, 7 };
	parseTable[0][symbolColumnMap['E']] = Action(GOTO, 1);
	parseTable[0][symbolColumnMap['T']] = Action(GOTO, 2);
	parseTable[0][symbolColumnMap['F']] = Action(GOTO, 3);
	parseTable[1][symbolColumnMap['$']] = Action(ACC, 0);
	parseTable[2][symbolColumnMap['+']] = Action(SHIFT, 7);
	parseTable[2][symbolColumnMap['-']] = Action(SHIFT, 8);
	for (int i = 0; i < 6; ++i) {
		parseTable[2][a[i]] = Action(REDUCE, 3);
		parseTable[13][a[i]] = Action(REDUCE, 3);
		parseTable[14][a[i]] = Action(REDUCE, 3);
		parseTable[3][b[i]] = Action(REDUCE, 7);
		parseTable[15][b[i]] = Action(REDUCE, 7);
		parseTable[16][b[i]] = Action(REDUCE, 7);
	}
	parseTable[2][symbolColumnMap['A']] = Action(GOTO, 6);
	parseTable[3][symbolColumnMap['*']] = Action(SHIFT, 10);
	parseTable[3][symbolColumnMap['/']] = Action(SHIFT, 11);
	parseTable[3][symbolColumnMap['B']] = Action(GOTO, 9);
	parseTable[4][symbolColumnMap['E']] = Action(GOTO, 12);
	parseTable[4][symbolColumnMap['T']] = Action(GOTO, 2);
	parseTable[4][symbolColumnMap['F']] = Action(GOTO, 3);
	for (int i = 0; i < 8; ++i) {
		parseTable[5][i] = Action(REDUCE, 9);
	}
	for (int i = 0; i < 8; ++i) {
		parseTable[6][i] = Action(REDUCE, 0);
	}
	for (int i = 7; i <= 8; ++i) {
		parseTable[i][symbolColumnMap['T']] = Action(GOTO, i + 6);
		parseTable[i][symbolColumnMap['F']] = Action(GOTO, 3);
	}
	for (int i = 0; i < 8; ++i) {
		parseTable[9][i] = Action(REDUCE, 4);
	}
	for (int i = 10; i <= 11; ++i) {
		parseTable[i][symbolColumnMap['F']] = Action(GOTO, i + 5);
	}
	parseTable[12][symbolColumnMap[')']] = Action(SHIFT, 17);
	for (int i = 13; i <= 14; ++i) {
		parseTable[i][symbolColumnMap['+']] = Action(SHIFT, 7);
		parseTable[i][symbolColumnMap['-']] = Action(SHIFT, 8);
		parseTable[i][symbolColumnMap['A']] = Action(GOTO, i + 5);
	}
	for (int i = 15; i <= 16; ++i) {
		parseTable[i][symbolColumnMap['*']] = Action(SHIFT, 10);
		parseTable[i][symbolColumnMap['/']] = Action(SHIFT, 11);
		parseTable[i][symbolColumnMap['B']] = Action(GOTO, i + 5);
	}
	int num[5] = { 8, 1, 2, 5, 6 };
	for (int i = 17; i < 22; ++i) {
		for (int j = 0; j < 8; ++j) {
			parseTable[i][j] = Action(REDUCE, num[i - 17]);
		}
	}
}

void digitReplace() {
	for (char& c : statement) {
		if (isdigit(c)) {
			c = 'n';
		}
	}
}

void generateParseTree() {
	digitReplace();
	statement += '$';
	stateStack.push(0);
	while (1) {
		Action a = parseTable[stateStack.top()][symbolColumnMap[statement.front()]];
		if (a.type == ACC) {
			break;
		}
		act(a);
	}
}

void act(Action action) {
	switch (action.type) {
	case ERROR:
		break;
	case ACC:
		break;
	case SHIFT:
		shift(action.state);
		break;
	case REDUCE:
		reduce(action.state);
	case GOTO:
		_goto();
		break;
	default:
		break;
	}
}

void shift(int state) {
	TreeNode* n = new TreeNode(statement.front());
	symbolStack.push(n);
	statement.erase(statement.begin());
	stateStack.push(state);
}

void reduce(int num) {
	Production p = productions[num];
	TreeNode* father = new TreeNode(p.left);
	if (p.right.size() == 0) {
		father->children.push_back(new TreeNode('e'));
	}
	for (int i = p.right.size() - 1; i >= 0; --i) {
		father->children.insert(father->children.begin(), symbolStack.top());
		symbolStack.pop();
		stateStack.pop();
	}
	symbolStack.push(father);
	res.push(p);
}

void _goto() {
	Action action = parseTable[stateStack.top()][symbolColumnMap[symbolStack.top()->val]];
	stateStack.push(action.state);
}