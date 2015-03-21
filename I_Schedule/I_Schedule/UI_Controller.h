#pragma once
#include "Smartstring.h";
#include "Logic.h";
#include "sstream";
#include "DateTime.h";
class UI_Controller
{
public:
	string DISPLAY_TASK_DEADLINE;
	string DISPLAY_TASK_FLOAT;
	string DISPLAY_TASK_TIMED;
	Logic* logic;

	UI_Controller();
	~UI_Controller();
	string Run(string input);

private:
	string Standardize(string input);
};

