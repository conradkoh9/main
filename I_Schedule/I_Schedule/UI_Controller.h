#pragma once
#include "Smartstring.h";
#include "Logic.h";
#include "sstream";
#include "DateTime.h";
#include "Logger.h";

using namespace logging;
class UI_Controller
{
public:
	string DISPLAY_TASK_DEADLINE;
	string DISPLAY_TASK_FLOAT;
	string DISPLAY_TASK_TIMED;
	string DISPLAY_MAIN;
	string DISPLAY_STATUS;
	Logic* logic;

	UI_Controller();
	~UI_Controller();
	string Run(string input);

private:
	string Standardize(string input);
	string UpdateDisplays();
	string ClearStreams();
};

