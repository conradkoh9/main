#pragma once
#include <string>
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

private:

};

