#pragma once
#include <string>
#include "Parser.h"
#include "Storage.h"
#include "Smartstring.h"
#include "Logger.h";

using namespace std;
using namespace logging;

class Logic
{
public:
	Logic();
	Logic(string input);
	Logic(string input, ostringstream deadlinestrm, ostringstream floatstrm, ostringstream timedstrm);
	~Logic();
	bool exit = false;
	Parser* parser;
	Storage* storage;
	vector<Task*> activeTaskList;
	//methods
	string Run(string input);
	string Execute(string input);
	string Add(string taskInput);
	string Delete(string taskInput);
	string Display();
	string Edit(string taskInput);
	string Search(string taskInput);
	string Clear();

	//display streams
	static ostringstream fout; //floating task display stream
	static ostringstream tout; //timed task display stream
	static ostringstream dout; //deadline task display stream
	static ostringstream mout; //main display stream


private:
	static const string _FEEDBACK_ERROR_INVALID_INDEX;

};

