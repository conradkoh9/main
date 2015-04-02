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
	static const string rtf_timed;
	static const string rtf_deadline;
	static const string rtf_float;
	static const string rtf_main;
	string DISPLAY_STATUS;

	Logic* logic;

	UI_Controller();
	~UI_Controller();
	void Run(string input);
	void QuickSearch(string input);

private:
	static const string _rtfheader;
	static const string _rtffooter;
	static const string _rtfnewline;
	static const string _rtfboldtagstart;
	static const string _rtfboldtagend;

	//rich text formatting to file methods
	void ToRTF(string filename, string input);

	string UpdateDisplays();
	string ClearStreams();
};

