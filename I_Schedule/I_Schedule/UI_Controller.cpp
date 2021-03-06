#include "UI_Controller.h"

const string UI_Controller::rtf_timed = "tout.display";
const string UI_Controller::rtf_deadline = "dout.display";
const string UI_Controller::rtf_float = "fout.display";
const string UI_Controller::rtf_main = "mout.display";
const string UI_Controller::_rtfheaderStartBlock = "{\\rtf1\\ansi\\ansicpg1252\\deff0\\nouicompat{ \\fonttbl{ \\f0\\fnil\\fcharset0 Calibri; } }\n";
const string UI_Controller::_rtfheaderColorBlock = "{\\colortbl; \\red0\\green77\\blue187; \\red255\\green0\\blue0; }\n";
const string UI_Controller::_rtfheaderGeneratorBlock = "{\\*\\generator Riched20 6.3.9600}\\viewkind4\\uc1\n";
const string UI_Controller::_rtfheaderFontBlock = "\\pard\\sa200\\sl276\\slmult1\\b\\f0\\fs20\\lang9 ";
string UI_Controller::_rtfheadercolor = _rtfheaderStartBlock + _rtfheaderColorBlock + _rtfheaderGeneratorBlock + _rtfheaderFontBlock;

const string UI_Controller::_rtfheaderbw = "{\\rtf1\\ansi\\ansicpg1252\\deff0\\nouicompat{\\fonttbl{\\f0\\fnil\\fcharset0 Calibri;}}\n{\\*\\generator Riched20 6.3.9600}\\viewkind4\\uc1\n\\pard\\sa200\\sl276\\slmult1\\f0\\fs18\\lang9 ";
//note: fs18 = 2 * font size 9;
const string UI_Controller::_rtffooter = "}";
const string UI_Controller::_rtfnewline = "\\line  ";
const string UI_Controller::_rtfboldtagstart = "\\b ";
const string UI_Controller::_rtfboldtagend = "\\b0 ";

//@author A0099303A
UI_Controller::UI_Controller()
{
	logic = new Logic();
	UpdateDisplays();
	ClearStreams();
	logfile << "UI Created";
}


UI_Controller::~UI_Controller()
{
}

void UI_Controller::Run(string input){
	logic->Run(input);
	UpdateDisplays();
	ClearStreams();
	return;
}

//@author A0119491B
void UI_Controller::QuickSearch(string input){
	if (!input.empty()){
		logic->QuickSearch(input);
		UpdateDisplays();
		ClearStreams();
	}
	return;
}

void UI_Controller::ToRTF(string filename, string input){
	string dbg = input;
	ofstream of;
	of.open(filename.c_str(), ios::trunc);
	of << _rtfheadercolor;

	//start replace new line characters
	static int startIdx = 0;
	int endIdx = input.length() - 1;
	int found = input.find_first_of('\n');
	while (found != string::npos){
		string before = input.substr(0, found);
		string after = input.substr(found + 1, endIdx);
		string result = before + _rtfnewline + after;
		input = result;

		startIdx = found + _rtfnewline.length();
		found = input.find_first_of('\n', startIdx);

	}
	//end replace new line characters

	of << input;
	of << _rtffooter;
	of.close();

	return;
}

string UI_Controller::UpdateDisplays(){
	string feedback = "";
	string dbg = logic->mout.str();
	DISPLAY_STATUS = logic->status.str();
	ToRTF(rtf_main, logic->mout.str());
	ToRTF(rtf_deadline, logic->dout.str());
	ToRTF(rtf_float, logic->fout.str());
	ToRTF(rtf_timed, logic->tout.str());
	return feedback;
}

string UI_Controller::ClearStreams(){
	string feedback;
	logic->dout.clear();
	logic->dout.str("");
	logic->fout.clear();
	logic->fout.str("");
	logic->tout.clear();
	logic->tout.str("");
	logic->mout.clear();
	logic->mout.str("");
	logic->status.clear();
	logic->status.str("");
	return feedback;
}