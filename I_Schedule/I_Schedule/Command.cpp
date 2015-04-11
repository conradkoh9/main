//@author A0119513L
#include "Command.h"

const string Command::_FEEDBACK_ERROR_INVALID_INDEX = "INVALID INDEX";
const string Command::_FEEDBACK_DISPLAY = "Displaying all tasks.";
const string Command::_FEEDBACK_EDIT = "Task edited.";
const string Command::_FEEDBACK_SEARCH = "Displaying search results.";
const string Command::_FEEDBACK_UNDO = "Undo previous command.";
const string Command::_FEEDBACK_INVALID_COMMAND = "Invalid command entered.";
const string Command::_MESSAGE_WELCOME = "Welcome to I_Schedule.";

Command::Command(){
}

Command::Command(string input){
}

Command::~Command(){
}

//string Command::GetStatus(){
//	string sstatus = storage->status.str();
//	return sstatus;
//}
//
//string Command::sGetTimedList(){
//	string feedback1= storage->GetTimedList();
//	return feedback1;
//}
//
//string Command::sGetDeadlineList(){
//	string feedback2 = storage->GetDeadlineList();
//	return feedback2;
//}
//
//string Command::sGetFloatingList(){
//	string feedback3 = storage->GetFloatingList();
//	return feedback3;
//}
//
//string Command::sGetMainList(){
//	string feedback4 = storage->ToString();
//	return feedback4;
//}

string Command::Execute(string){   //invalid command
	return _FEEDBACK_INVALID_COMMAND;
}

//string Command::GetFloating(){
//	return fout.str();
//}
//string Command::GetTimed(){
//	return tout.str();
//}
//string Command::GetDisplay(){
//	return dout.str();
//}
//string Command::GetStatus(){
//	return status.str();
//}

//Add Command

AddCommand::AddCommand(){

}

AddCommand::~AddCommand(){

}

string AddCommand::Execute(string taskInput){
	vector<string> taskinfo = parser->IdentifyTaskFields(taskInput);
	Task* task = new Task(taskinfo);
	string feedback = storage->Add(task);
	mout << task->ToString();
	return feedback;
}

//Clear Command

ClearCommand::ClearCommand(){

}

ClearCommand::~ClearCommand(){

}

string ClearCommand::Execute(string all){
	string feedback = storage->Clear();
	return feedback;
}

//Delete Command

DeleteCommand::DeleteCommand(){

}

DeleteCommand::~DeleteCommand(){

}

string DeleteCommand::Execute(string taskInput){
	Smartstring listname;
	istringstream in(taskInput);
	int position;
	in >> listname;
	in >> position;
	//delete from list function
	string feedback = storage->DeleteFromList(position, listname.ListType());
	return feedback;
}


//Display Command

DisplayCommand::DisplayCommand(){

}

DisplayCommand::~DisplayCommand(){

}

string DisplayCommand::Execute(string all){
	return _FEEDBACK_DISPLAY;
}

//Edit Command

EditCommand::EditCommand(){

}

EditCommand::~EditCommand(){

}

string EditCommand::Execute(string taskInput){
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
	storage->Edit(position, listname.ListType(), newinfo);
	return storage->ToString();
}

//Save Command

SaveCommand::SaveCommand(){

}

SaveCommand::~SaveCommand(){

}

string SaveCommand::Execute(string input){
	string feedback = storage->SaveAs(input);
	return storage->ToString();
}

//Search Command

SearchCommand::SearchCommand(){

}

SearchCommand::~SearchCommand(){

}

string SearchCommand::Execute(string taskInput){
	return storage->Search(taskInput);
}

//Complete Command

CompleteCommand::CompleteCommand(){

}

CompleteCommand::~CompleteCommand(){

}

string CompleteCommand::Execute(string input){
	Smartstring listname;
	istringstream in(input);
	int position;
	in >> listname;
	in >> position;

	//Complete function
	string feedback = storage->Complete(position);
	mout << storage->ToString();

	return feedback;
}

//Free Command

FreeCommand::FreeCommand(){

}

FreeCommand::~FreeCommand(){

}

string FreeCommand::Execute(string input){
	string feedback = storage->SearchEmptySlots(input);
	return feedback;
}

//Load Command

LoadCommand::LoadCommand(){

}

LoadCommand::~LoadCommand(){

}

string LoadCommand::Execute(string input){
	string feedback = storage->Load(input);
	return feedback;
}


//Undo Command

UndoCommand::UndoCommand(){

}

UndoCommand::~UndoCommand(){

}

string UndoCommand::Execute(string undo){
	string feedback = storage->Undo();
	mout << storage->ToString();
	return feedback;
}

//Archived Command

ArchivedCommand::ArchivedCommand(){

}

ArchivedCommand::~ArchivedCommand(){

}

string ArchivedCommand::Execute(string input){
	string feedback = "Viewing archived";
	mout << storage->ArchiveToString();
	return feedback;
}
