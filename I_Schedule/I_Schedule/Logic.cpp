#include "Logic.h"

//adding functionality
//1. Add case to Execute
//2. Add function itself in header and cpp

const string Logic::_FEEDBACK_ERROR_INVALID_INDEX = "INVALID INDEX";
const string Logic::_FEEDBACK_DISPLAY = "Displaying all tasks.";
const string Logic::_FEEDBACK_EDIT = "Task edited.";
const string Logic::_FEEDBACK_SEARCH = "Displaying search results.";
const string Logic::_FEEDBACK_UNDO = "Undo previous command.";
const string Logic::_FEEDBACK_INVALID_COMMAND = "Invalid command entered.";
const string Logic::_MESSAGE_WELCOME = "Welcome to I_Schedule.";
ostringstream Logic::fout; //floating task display stream
ostringstream Logic::tout; //timed task display stream
ostringstream Logic::dout; //deadline task display stream
ostringstream Logic::mout; //main display stream
ostringstream Logic::status; //status bar display stream
Logic::Logic()
{
	parser = new Parser();
	storage = new Storage();
	status << _MESSAGE_WELCOME + " " + storage->status.str();
	string test = storage->GetFloatingList();
	fout << storage->GetFloatingList();
	dout << storage->GetDeadlineList();
	tout << storage->GetTimedList();
	mout << storage->ToString();
	logfile << "Logic created";
}

Logic::Logic(string input){
	parser = new Parser();
	storage = new Storage(input);
	status << _MESSAGE_WELCOME;
	fout << storage->GetFloatingList();
	dout << storage->GetDeadlineList();
	tout << storage->GetTimedList();
	mout << storage->ToString();
	logfile << "Logic created";
}

Logic::~Logic()
{
}

string Logic::Run(string input){
	string feedback = Execute(input);
	status << feedback;
	fout << storage->GetFloatingList(); 
	dout << storage->GetDeadlineList(); 
	tout << storage->GetTimedList(); 
	return feedback;
}

string Logic::Execute(string input){
	Smartstring::COMMAND cmd = parser->IdentifyCommand(input);
	string remainder = parser->RemoveCommand(input);
	string feedback;
	switch (cmd){
		case (Smartstring::COMMAND::ADD) : {
			feedback = Add(remainder);
			break;
		}
		case (Smartstring::COMMAND::DELETE) : {
			feedback = Delete(remainder);
			break;
		}
		case (Smartstring::COMMAND::DISPLAY) : {
			feedback = Display();
			break;
		}
		case(Smartstring::COMMAND::EDIT) : {
			feedback = Edit(remainder);
			break;
		}
		case (Smartstring::COMMAND::SEARCH) : {
			feedback = Search(remainder);
			break;
		}
		case (Smartstring::COMMAND::CLEAR) : {
			feedback = Clear();
			break;
		}
		case (Smartstring::COMMAND::COMPLETE) : {
			feedback = Complete(remainder);
			break;
		}
		case (Smartstring::COMMAND::SAVE) : {
			feedback = Save(remainder);
			break;
		}
		case (Smartstring::COMMAND::EMPTYSLOTS) : {
			feedback = EmptySlots(remainder);
			break;
		}
		case (Smartstring::COMMAND::UNDO) : {
			 feedback = Undo();
			 break;
		}
		case (Smartstring::COMMAND::LOAD) : {
			feedback = Load(remainder);
			break;
		}
		case(Smartstring::COMMAND::INVALID_CMD) : {
			feedback = Invalid();
			break;
		}
	}
	return feedback;
}

string Logic::Add(string taskInput){
	vector<string> taskinfo = parser->IdentifyTaskFields(taskInput);
	Task* task = new Task(taskinfo);
	string feedback = storage->Add(task);
	mout << task->ToString();
	return feedback;
}

string Logic::Delete(string taskInput){
	int position = atoi(taskInput.c_str());
	string feedback = storage->Delete(position);
	return feedback;
}

string Logic::Display(){
	mout << storage->ToString();
	return _FEEDBACK_DISPLAY;
}

string Logic::Edit(string taskInput){
	activeTaskList.clear();
	Task* taskptr;
	string indexstr;
	//select 
	istringstream in(taskInput);
	in >> indexstr;
	int index = atoi(indexstr.c_str());
	if (index <= storage->taskList.size() && index > 0){
		index = index - 1; //converting from user index to vector index
		taskptr = storage->taskList[index];
	}
	else{
		return _FEEDBACK_ERROR_INVALID_INDEX;
	}
	//end select

	//analyze string as vect and replace
	//assumption: the IdentifyTaskFields has same ordering as *taskptr
	string remainder;
	getline(in, remainder);
	vector<string> modified = parser->IdentifyTaskFields(remainder);
	for (int i = 0; i < modified.size(); ++i){
		if (modified[i] != ""){
			switch (i){
			case Smartstring::FIELD::DESCRIPTION:{
				taskptr->SetDescription(modified[i]);
				break;
			}
			case Smartstring::FIELD::STARTDATE:{
				taskptr->SetStartDate(modified[i]);
				break;
			}
			case Smartstring::FIELD::ENDDATE:{
				taskptr->SetEndDate(modified[i]);
				break;
			}
			case Smartstring::FIELD::PRIORITY:{
				taskptr->SetPriority(modified[i]);
				break;
			}
			}
		}
	}
	//end analyze string as vect and replace
	mout << taskptr->ToString();
	return _FEEDBACK_EDIT;
}
string Logic::Search(string taskInput){
	mout << storage->Search(taskInput);
	return _FEEDBACK_SEARCH;
}

string Logic::CloseSearch(string input){
	mout << storage->ToString(storage->NearSearch(input));
	return _FEEDBACK_SEARCH;
}

string Logic::Save(string input){
	string feedback = storage->SaveAs(input);
	return feedback;
}

string Logic::EmptySlots(string input){
	string feedback = storage->SearchEmptySlots(input);
	return feedback;
}

string Logic::Complete(string input){
	int position = atoi(input.c_str());
	string feedback = storage->Complete(position);
	return feedback;
}

string Logic::Invalid(){
	mout << storage->ToString();
	return _FEEDBACK_INVALID_COMMAND;
}

string Logic::Clear(){
	string feedback = storage->Clear();
	return feedback;
}

string Logic::Undo(){
	string feedback = storage->Undo();
	return feedback;
}

string Logic::Load(string input){
	string feedback = storage->Load(input);
	return feedback;
}