//@author A0119513L
#include "Command.h"

const string Command::_FEEDBACK_ERROR_INVALID_INDEX = "INVALID INDEX";
const string Command::_FEEDBACK_DISPLAY = "Displaying all tasks.";
const string Command::_FEEDBACK_EDIT = "Task edited.";
const string Command::_FEEDBACK_SEARCH = "Displaying search results.";
const string Command::_FEEDBACK_UNDO = "Undo previous command.";
const string Command::_FEEDBACK_INVALID_COMMAND = "Invalid command entered.";
const string Command::_MESSAGE_WELCOME = "Welcome to I_Schedule.";
const string Command::_FEEDBACK_INVALID_INPUT = "Invalid input.";
const string Command::_FEEDBACK_INVALID_INDEX = "Invalid index.";
const string Command::_FEEDBACK_INVALID_FIELD = "Invalid field.";

Command::Command(){

}
Command::Command(Storage* store_, Parser* parser_){
	storage = store_;
	parser = parser_;
}

Command::~Command(){
}

string Command::Execute(string){   //default is invalid command
	return _FEEDBACK_INVALID_COMMAND;
}

//Add Command
AddCommand::AddCommand(){

}
AddCommand::AddCommand(Storage* store_, Parser* parser_){
	storage = store_;
	parser = parser_;
}

AddCommand::~AddCommand(){

}

string AddCommand::Execute(string taskInput){
	try{
		if (taskInput == ""){
			throw invalid_input;
		}
		vector<string> taskinfo = parser->IdentifyTaskFields(taskInput);
		Task* task = new Task(taskinfo);
		string feedback = storage->Add(task);
		return task->ToString();
	}
	catch (InvalidInput){
		return _FEEDBACK_INVALID_INPUT;
	}
}

//Clear Command
ClearCommand::ClearCommand(){

}
ClearCommand::ClearCommand(Storage* store_, Parser* parser_){
	storage = store_;
	parser = parser_;
}

ClearCommand::~ClearCommand(){

}

string ClearCommand::Execute(string all){
	storage->Clear();
	return storage->ToString();
}

//Delete Command

DeleteCommand::DeleteCommand(){
}

DeleteCommand::DeleteCommand(Storage* store_, Parser* parser_){
	storage = store_;
	parser = parser_;
}

DeleteCommand::~DeleteCommand(){

}

string DeleteCommand::Execute(string taskInput){
	try{
		int position = atoi(taskInput.c_str());
		if (position < 0){
			throw invalid_index;
		}
		storage->Delete(position);
		return storage->ToString();
	}
	catch (InvalidIndex){
		return _FEEDBACK_INVALID_INDEX;
	}
}


//Display Command
DisplayCommand::DisplayCommand(){

}
DisplayCommand::DisplayCommand(Storage* store_, Parser* parser_){
	storage = store_;
	parser = parser_;
}

DisplayCommand::~DisplayCommand(){

}

string DisplayCommand::Execute(string all){
		return storage->DayView();
}

//Edit Command
EditCommand::EditCommand(){

}
EditCommand::EditCommand(Storage* store_, Parser* parser_){
	storage = store_;
	parser = parser_;
}

EditCommand::~EditCommand(){

}

string EditCommand::Execute(string taskInput){
	try{
		string remainder;
		int position;

		istringstream in(taskInput);
		in >> position;
		if (position < 0){
			throw invalid_index;
		}
		getline(in, remainder);
		vector<string> newinfo = parser->IdentifyTaskFields(remainder);
		if (newinfo.size() == 0){
			throw invalid_field;
		}
		storage->Edit(position, newinfo);
		return storage->ToString();
	}
	catch (InvalidIndex){
		return _FEEDBACK_INVALID_INDEX;
	}
	catch (InvalidField){
		return _FEEDBACK_INVALID_FIELD;
	}
}

//Save Command
SaveCommand::SaveCommand(){

}
SaveCommand::SaveCommand(Storage* store_, Parser* parser_){
	storage = store_;
	parser = parser_;
}

SaveCommand::~SaveCommand(){

}

string SaveCommand::Execute(string input){
	try{
		if (input == ""){
			throw invalid_input;
		}
		string feedback = storage->SaveAs(input);
		return storage->ToString();
	}
	catch (InvalidInput){
		return _FEEDBACK_INVALID_INPUT;
	}
}

//Search Command
SearchCommand::SearchCommand(){

}
SearchCommand::SearchCommand(Storage* store_, Parser* parser_){
	storage = store_;
	parser = parser_;
}

SearchCommand::~SearchCommand(){

}

string SearchCommand::Execute(string taskInput){
	try{
		if (taskInput == ""){
			throw invalid_input;
		}
		return storage->Search(taskInput);
	}
	catch (InvalidInput){
		return _FEEDBACK_INVALID_INPUT;
	}
}

//Complete Command
CompleteCommand::CompleteCommand(){

}
CompleteCommand::CompleteCommand(Storage* store_, Parser* parser_){
	storage = store_;
	parser = parser_;
}

CompleteCommand::~CompleteCommand(){

}

string CompleteCommand::Execute(string input){
	try{
		if (input == ""){
			throw invalid_input;
		}
		istringstream in(input);
		int position;
		in >> position;

		//Complete function
		string feedback = storage->Complete(position);

		return storage->ToString();
	}
	catch (InvalidInput){
		return _FEEDBACK_INVALID_INPUT;
	}
}

//Free Command
FreeCommand::FreeCommand(){

}
FreeCommand::FreeCommand(Storage* store_, Parser* parser_){
	storage = store_;
	parser = parser_;
}

FreeCommand::~FreeCommand(){

}

string FreeCommand::Execute(string input){
	try{
		if (input == ""){
			throw invalid_input;
		}
		string feedback = storage->SearchEmptySlots(input);
		return feedback;
	}
	catch (InvalidInput){
		return _FEEDBACK_INVALID_INPUT;
	}
}

//Load Command
LoadCommand::LoadCommand(){

}
LoadCommand::LoadCommand(Storage* store_, Parser* parser_){
	storage = store_;
	parser = parser_;
}

LoadCommand::~LoadCommand(){

}

string LoadCommand::Execute(string input){
	try{
		if (input == ""){
			throw invalid_input;
		}
		string feedback = storage->Load(input);
		return storage->ToString();
	}
	catch (InvalidInput){
		return _FEEDBACK_INVALID_INPUT;
	}
}


//Undo Command
UndoCommand::UndoCommand(){

}

UndoCommand::UndoCommand(Storage* store_, Parser* parser_){
	storage = store_;
	parser = parser_;
}

UndoCommand::~UndoCommand(){

}

string UndoCommand::Execute(string undo){
	storage->Undo();
	return storage->ToString();
}

//Archived Command

ArchivedCommand::ArchivedCommand(){

}

ArchivedCommand::ArchivedCommand(Storage* store_, Parser* parser_){
	storage = store_;
	parser = parser_;
}

ArchivedCommand::~ArchivedCommand(){

}

string ArchivedCommand::Execute(string input){
	return storage->ArchiveToString();
}
