#pragma once
#include <string>
#include <vector>
#include <sstream>
#include "Smartstring.h"
#include "Task.h"
using namespace std;
class Parser
{
public:
	Parser();
	~Parser();
	//methods
	string integerLiteral(string);
	string identifierLiteral(string);
	string stringLiteral(string);
	
	//suggestions for methods by Conrad
	vector<string> Identify(string input);
	vector<string> Tokenize(string input);


private:

};

