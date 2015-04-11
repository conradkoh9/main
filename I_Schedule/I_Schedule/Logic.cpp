//@author A0119513L
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
	command = new Command();
	string sstatus = command->GetStatus();
	//status << _MESSAGE_WELCOME + " " + storage->status.str();
	status << _MESSAGE_WELCOME + " " + sstatus;
	/*
	tout << storage->GetTimedList();
	dout << storage->GetDeadlineList();
	fout << storage->GetFloatingList();

	mout << storage->ToString();
	*/
	string sTimedList = command->sGetTimedList();
	string sDeadlineList = command->sGetDeadlineList();
	string sFloatingList = command->sGetFloatingList();
	string sMainList = command->sGetMainList();
	tout << sTimedList;
	dout << sDeadlineList;
	tout << sFloatingList;
	tout << sMainList;
	logfile << "Logic created";
}

Logic::Logic(string input){
	parser = new Parser();
	storage = new Storage(input);
	status << _MESSAGE_WELCOME;
	//string sTimedList = command->sGetTimedList();
	//string sDeadlineList = command->sGetDeadlineList();
	//string sFloatingList = command->sGetFloatingList();
	//string sMainList = command->sGetMainList();
	//tout << sTimedList;
	//dout << sDeadlineList;
	//tout << sFloatingList;
	//tout << sMainList;
	logfile << "Logic created";
}

Logic::~Logic()
{
}

void Logic::Run(string input){
	Execute(input);
	/*
	tout << storage->GetTimedList();
	dout << storage->GetDeadlineList();
	fout << storage->GetFloatingList(); 
	*/
	//string sTimedList = command->sGetTimedList();
	//string sDeadlineList = command->sGetDeadlineList();
	//string sFloatingList = command->sGetFloatingList();
	//string sMainList = command->sGetMainList();

	return;
}

string Logic::Execute(string input){
	Smartstring::COMMAND cmd = parser->IdentifyCommand(input);
	string remainder = parser->RemoveCommand(input);
	Command* cmd_e = GetCommand(cmd);
	string mainDisplay = cmd_e->Execute(remainder); 

	tout << storage->GetTimedList();
	dout << storage->GetDeadlineList();
	fout << storage->GetFloatingList();
	mout << mainDisplay;
	status << storage->status.str();
	return "";
}

Command* Logic::GetCommand(Smartstring::COMMAND command){
	Command* cmd_o = new Command();
	switch (command){
		case (Smartstring::COMMAND::ADD) : {
			cmd_o = new AddCommand();
			break;
		}
		case (Smartstring::COMMAND::DELETE) : {
			cmd_o = new DeleteCommand();
			break;
		}
		case (Smartstring::COMMAND::DISPLAY) : {
			cmd_o = new DisplayCommand();
			break;
		}
		case(Smartstring::COMMAND::EDIT) : {
			cmd_o = new EditCommand();
			break;
		}
		case (Smartstring::COMMAND::SEARCH) : {
			cmd_o = new SearchCommand();
			break;
		}
		case (Smartstring::COMMAND::CLEAR) : {
			cmd_o = new ClearCommand();
			break;
		}
		case (Smartstring::COMMAND::COMPLETE) : {
			cmd_o = new CompleteCommand();
			break;
		}
		case (Smartstring::COMMAND::SAVE) : {
			cmd_o = new SaveCommand();
			break;
		}
		case (Smartstring::COMMAND::FREE) : {
			cmd_o = new FreeCommand();
			break;
		}
		case (Smartstring::COMMAND::UNDO) : {
			cmd_o = new UndoCommand();
			break;
		}
		case (Smartstring::COMMAND::LOAD) : {
			cmd_o = new LoadCommand();
			break;
		}
		case (Smartstring::COMMAND::ARCHIVED) : {
			cmd_o = new ArchivedCommand();
			break;
		}
		case(Smartstring::COMMAND::INVALID_CMD) : {       //shouldn't it be set just as default
			cmd_o = new Command();
			break;
		}
	}
	return cmd_o;
}

void Logic::UpdateDisplays(){
	return;
}
/*
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
		case (Smartstring::COMMAND::FREE) : {
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
		case (Smartstring::COMMAND::ARCHIVED) : {
			feedback = Archived(remainder);
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

string Logic::Complete(string input){
	istringstream in(input);
	int position;
	in >> position;

	//Complete function
	string feedback = storage->Complete(position);
	mout << storage->ToString();

	return feedback;
}


string Logic::Delete(string taskInput){
	//Smartstring listname;
	//istringstream in(taskInput);
	//int position;
	//in >> listname;
	//in >> position;
	////delete from list function
	//string feedback = storage->DeleteFromList(position, listname.ListType());
	//mout << storage->ToString();

	int position = atoi(taskInput.c_str());
	string feedback = storage->Delete(position);
	return feedback;
}

string Logic::Display(){
	mout << storage->DayView();
	
	return _FEEDBACK_DISPLAY;
}

string Logic::Edit(string taskInput){

	Smartstring listname;
	Smartstring info;
	Smartstring::FIELD field;
	string remainder;
	int position;

	istringstream in(taskInput);
	in >> listname;
	in >> position;
	getline(in, remainder);
	vector<string> newinfo = parser->IdentifyTaskFields(remainder);
	
	string feedback = storage->Edit(position, listname.ListType(), newinfo);
	//Edit function
	mout << storage->ToString();
	return feedback;
}
string Logic::Search(string taskInput){
	mout << storage->Search(taskInput);
	return _FEEDBACK_SEARCH;
}


string Logic::Save(string input){
	string feedback = storage->SaveAs(input);
	return feedback;
}

string Logic::EmptySlots(string input){
	string feedback = "empty slots";
	mout << storage->SearchEmptySlots(input);
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
	mout << storage->ToString();
	return feedback;
}

string Logic::Load(string input){
	string feedback = storage->Load(input);
	return feedback;
}

string Logic::Archived(string input){
	string feedback = "Viewing archived";
	mout << storage->ArchiveToString();
	return feedback;
}

*/