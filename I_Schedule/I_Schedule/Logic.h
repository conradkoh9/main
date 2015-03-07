#pragma once
#include <string>
#include "Parser.h"
#include "Storage.h"
#include "Smartstring.h"

using namespace std;

class Logic
{
public:
	Logic();
	~Logic();
	Parser* parser;
	vector<Task*> taskList;
	//methods
	string Run(string input);
	string Execute(string input);
	string Add(string input);
	string Delete(string input);
	string Display(string input);
	string Search(string input);
	string Clear();

	

private:
	enum COMMAND{};
};

