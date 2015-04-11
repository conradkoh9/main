//@author A0119513L
#pragma once
#include <string>
#include "Parser.h"
#include "Storage.h"
#include "Smartstring.h"  //do we need smartstring?
#include "Logger.h"  //no logging inside Command yet

using namespace std;
using namespace logging;

class Command
{
public:
	Command();
	Command(string input);
	~Command();
	Storage* storage;
	Parser* parser;

	/*string GetStatus();
	string sGetTimedList();
	string sGetDeadlineList();
	string sGetFloatingList();
	string sGetMainList();*/
	virtual string Execute(string);

	////display streams
	//static ostringstream fout; //floating task display stream
	//static ostringstream tout; //timed task display stream
	//static ostringstream dout; //deadline task display stream
	//static ostringstream mout; //main display stream
	//static ostringstream status; //status bar display stream

	static const string _FEEDBACK_ERROR_INVALID_INDEX;
	static const string _FEEDBACK_DISPLAY;
	static const string _FEEDBACK_EDIT;
	static const string _FEEDBACK_SEARCH;
	static const string _FEEDBACK_UNDO;
	static const string _FEEDBACK_INVALID_COMMAND;
	static const string _MESSAGE_WELCOME;


};

class AddCommand : public Command{
public:
	AddCommand();
	~AddCommand();

	string Execute(string) override;
};

class ClearCommand : public Command{
public:
	ClearCommand();
	~ClearCommand();

	string Execute(string) override;
};

class DeleteCommand : public Command{
public:
	DeleteCommand();
	~DeleteCommand();

	string Execute(string) override;
};

class DisplayCommand : public Command{
public:
	DisplayCommand();
	~DisplayCommand();

	string Execute(string) override;
};

class EditCommand : public Command{
public:
	EditCommand();
	~EditCommand();

	string Execute(string) override;
};

class SaveCommand : public Command{
public:
	SaveCommand();
	~SaveCommand();

	string Execute(string) override;
};

class SearchCommand : public Command{
public:
	SearchCommand();
	~SearchCommand();

	string Execute(string) override;
};

class CompleteCommand : public Command{
public:
	CompleteCommand();
	~CompleteCommand();

	string Execute(string) override;
};

class FreeCommand : public Command{
public:
	FreeCommand();
	~FreeCommand();

	string Execute(string) override;
};

class LoadCommand : public Command{
public:
	LoadCommand();
	~LoadCommand();

	string Execute(string) override;
};

class UndoCommand : public Command{
public:
	UndoCommand();
	~UndoCommand();

	string Execute(string) override;
};

class ArchivedCommand : public Command{
public:
	ArchivedCommand();
	~ArchivedCommand();

	string Execute(string) override;
};

class Invalid_cmdCommand : public Command{
public:
	Invalid_cmdCommand();
	~Invalid_cmdCommand();

	string Execute(string) override;
};