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
	Smartstring::COMMAND IdentifyCommand(string input);
	vector<string> IdentifyTaskFields(string input);
	string RemoveCommand(string input);
	string RemoveKeywords(string input);
	vector<string> Tokenize(string input);


private:

};

