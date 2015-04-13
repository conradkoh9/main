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
	storage = new Storage();
	status << _MESSAGE_WELCOME + " " + storage->status.str();
	tout << storage->GetTimedList();
	dout << storage->GetDeadlineList();
	fout << storage->GetFloatingList();
	mout << storage->ToString();
	storage->status.clear();
	storage->status.str("");
	logfile << "Logic created";
}

Logic::Logic(string input){
	parser = new Parser();
	storage = new Storage(input);
	status << _MESSAGE_WELCOME;

	tout << storage->GetTimedList();
	dout << storage->GetDeadlineList();
	fout << storage->GetFloatingList();
	logfile << "Logic created";
}

Logic::~Logic()
{
}


void Logic::Run(string input){
	Execute(input);
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
	storage->status.clear();
	storage->status.str("");
	return "";
}

Command* Logic::GetCommand(Smartstring::COMMAND command){
	Command* cmd_o = new Command();
	switch (command){
		case (Smartstring::COMMAND::ADD) : {
			cmd_o = new AddCommand(storage, parser);
			break;
		}
		case (Smartstring::COMMAND::DELETE) : {
			cmd_o = new DeleteCommand(storage, parser);
			break;
		}
		case (Smartstring::COMMAND::DISPLAY) : {
			cmd_o = new DisplayCommand(storage, parser);
			break;
		}
		case(Smartstring::COMMAND::EDIT) : {
			cmd_o = new EditCommand(storage, parser);
			break;
		}
		case (Smartstring::COMMAND::SEARCH) : {
			cmd_o = new SearchCommand(storage, parser);
			break;
		}
		case (Smartstring::COMMAND::CLEAR) : {
			cmd_o = new ClearCommand(storage, parser);
			break;
		}
		case (Smartstring::COMMAND::COMPLETE) : {
			cmd_o = new CompleteCommand(storage, parser);
			break;
		}
		case (Smartstring::COMMAND::SAVE) : {
			cmd_o = new SaveCommand(storage, parser);
			break;
		}
		case (Smartstring::COMMAND::FREE) : {
			cmd_o = new FreeCommand(storage, parser);
			break;
		}
		case (Smartstring::COMMAND::UNDO) : {
			cmd_o = new UndoCommand(storage, parser);
			break;
		}
		case (Smartstring::COMMAND::LOAD) : {
			cmd_o = new LoadCommand(storage, parser);
			break;
		}
		case (Smartstring::COMMAND::ARCHIVED) : {
			cmd_o = new ArchivedCommand(storage, parser);
			break;
		}
		case(Smartstring::COMMAND::INVALID_CMD) : {       
			cmd_o = new Command(storage, parser);
			break;
		}
	}
	return cmd_o;
}

//@auhtor A0119491B
string Logic::QuickSearch(string input){
	Command* cmd = GetCommand(Smartstring::SEARCH);
	mout << cmd->Execute(input);
	return "";
}