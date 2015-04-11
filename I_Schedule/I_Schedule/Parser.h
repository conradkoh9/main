#pragma once
#include <string>
#include <vector>
#include <sstream>
#include "Smartstring.h"
#include "Task.h"
#include "Logger.h";

using namespace std;
using namespace logging;
class Parser
{
public:
	Parser();
	~Parser();

	Smartstring::COMMAND IdentifyCommand(string input);
	Smartstring::LIST IdentifyList(string input);
	vector<string> IdentifyTaskFields(string input);

	string RemoveCommand(string input);
	string RemoveKeywords(string input);
	vector<string> Tokenize(string input);


private:

};

