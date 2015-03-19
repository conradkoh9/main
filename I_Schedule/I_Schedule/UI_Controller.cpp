#include "UI_Controller.h"


UI_Controller::UI_Controller()
{
	logic = new Logic();
}


UI_Controller::~UI_Controller()
{
}

string UI_Controller::Run(string input){
	DISPLAY_TASK_TIMED = logic->Execute(input);
	return DISPLAY_TASK_TIMED;
}