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
	Logic(string input);
	~Logic();
	Parser* parser;
	Storage* storage;
	vector<Task*> taskList;
	vector<Task*> activeTaskList;
	//methods
	string Run(string input);
	string Execute(string input);
	string Add(string taskInput);
	string Delete(string taskInput);
	string Display(string taskInput);
	string Edit(string taskInput);
	string Search(string taskInput);
	string Clear();

	

private:
	static const string _FEEDBACK_ERROR_INVALID_INDEX;
};

