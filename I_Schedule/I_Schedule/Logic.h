//@author A0119513L
#pragma once
#include <string>
#include "Parser.h"
#include "Storage.h"
#include "Smartstring.h"
#include "Logger.h";
#include "Command.h"

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
	Command* command;

	//methods
	void Run(string input);
	string Execute(string input);
	Command* GetCommand(Smartstring::COMMAND command);
	string QuickSearch(string input);
	/*void UpdateDisplays();*/


	//display streams
	static ostringstream fout; //floating task display stream
	static ostringstream tout; //timed task display stream
	static ostringstream dout; //deadline task display stream
	static ostringstream mout; //main display stream
	static ostringstream status; //status bar display stream

private:
	static const string _FEEDBACK_ERROR_INVALID_INDEX;
	static const string _FEEDBACK_DISPLAY;
	static const string _FEEDBACK_EDIT;
	static const string _FEEDBACK_SEARCH;
	static const string _FEEDBACK_UNDO;
	static const string _FEEDBACK_INVALID_COMMAND;
	static const string _MESSAGE_WELCOME;

};

