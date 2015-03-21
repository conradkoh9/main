#include "UI_Controller.h"


UI_Controller::UI_Controller()
{
	logic = new Logic();
}


UI_Controller::~UI_Controller()
{
}

string UI_Controller::Run(string input){
	DISPLAY_TASK_TIMED = Standardize(logic->Execute(input));
	DateTime* now = new DateTime();
	DISPLAY_TASK_DEADLINE = Standardize(now->Now());
	return DISPLAY_TASK_TIMED;
}

//the intended purpose of the standardize function is for the translation of characters from console to windows in 
//the expression that we desire.
string UI_Controller::Standardize(string input){
	//start replace new line characters
	static int startIdx = 0;
	int endIdx = input.length() - 1;
	int found = input.find_first_of('\n');
	while (found!=string::npos){
		static char carriageReset = '\r';
		string before = input.substr(0, found);
		string after = input.substr(found, endIdx);
		string result = before + carriageReset + after;
		input = result;

		startIdx = found + 2;
		found = input.find_first_of('\n', startIdx);

	}
	//end replace new line characters
	return input;
}