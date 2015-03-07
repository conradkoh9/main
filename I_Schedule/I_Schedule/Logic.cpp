#include "Logic.h"


Logic::Logic()
{
	parser = new Parser();
}


Logic::~Logic()
{
}

string Logic::Run(string input){
	string feedback = Execute(input);
	return feedback;
}

string Logic::Execute(string input){
	Smartstring::COMMAND cmd = parser->IdentifyCommand(input);
	string feedback;
	switch (cmd){
		case (Smartstring::COMMAND::ADD) : {
			feedback = Add(input);
			break;
		}
		case (Smartstring::COMMAND::DELETE) : {
			feedback = Delete(input);
			break;
		}
		case (Smartstring::COMMAND::DISPLAY) : {
			feedback = Display(input);
			break;
		}
		case (Smartstring::COMMAND::SEARCH) : {
			feedback = Search(input);
			break;
		}
		case (Smartstring::COMMAND::CLEAR) : {
			feedback = Clear();
			break;
		}
	}
	return feedback;
}

string Logic::Add(string input){
	string taskInput = parser->RemoveCommand(input);
	vector<string> taskinfo = parser->IdentifyTaskFields(taskInput);
	Task* task = new Task(taskinfo);
	taskList.push_back(task);
	return task->ToString();
}
string Logic::Delete(string input){
	return "function not defined";
}
string Logic::Search(string input){
	return "function not defined";
}
string Logic::Display(string input){
	return "function not defined";
}

string Logic::Clear(){
	return "function not defined";
}