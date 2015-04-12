//@author A0119513L
#pragma once
#include <string>
#include "Parser.h"
#include "Storage.h"
#include "Logger.h"  //no logging inside Command yet

using namespace std;
using namespace logging;

class Command
{
public:
	Command();
	Command(Storage* store_, Parser* parser_);;
	~Command();
	Storage* storage;
	Parser* parser;

	virtual string Execute(string);

	static const string _FEEDBACK_ERROR_INVALID_INDEX;
	static const string _FEEDBACK_DISPLAY;
	static const string _FEEDBACK_EDIT;
	static const string _FEEDBACK_SEARCH;
	static const string _FEEDBACK_UNDO;
	static const string _FEEDBACK_INVALID_COMMAND;
	static const string _MESSAGE_WELCOME;
	static const string _FEEDBACK_INVALID_INPUT;
	static const string _FEEDBACK_INVALID_INDEX;
	
	//exceptions
	class InvalidIndex : public exception{
	} invalid_index;

	class InvalidList : public exception{
	} invalid_list;

	class InvalidInput : public exception{
	} invalid_input;

	class LoadFailure : public exception{
	} load_failure;

	class FirstRun : public LoadFailure{
	} first_run;

	class CorruptedData : public LoadFailure{
	} corrupted_data;

};

class AddCommand : public Command{
public:
	AddCommand();
	AddCommand(Storage* store_, Parser* parser_);
	~AddCommand();

	string Execute(string) override;
};

class ClearCommand : public Command{
public:
	ClearCommand();
	ClearCommand(Storage* store_, Parser* parser_);
	~ClearCommand();

	string Execute(string) override;
};

class DeleteCommand : public Command{
public:
	DeleteCommand();
	DeleteCommand(Storage* store_, Parser* parser_);
	~DeleteCommand();

	string Execute(string) override;
};

class DisplayCommand : public Command{
public:
	DisplayCommand();
	DisplayCommand(Storage* store_, Parser* parser_);
	~DisplayCommand();

	string Execute(string) override;
};

class EditCommand : public Command{
public:
	EditCommand();
	EditCommand(Storage* store_, Parser* parser_);
	~EditCommand();

	string Execute(string) override;
};

class SaveCommand : public Command{
public:
	SaveCommand();
	SaveCommand(Storage* store_, Parser* parser_);
	~SaveCommand();

	string Execute(string) override;
};

class SearchCommand : public Command{
public:
	SearchCommand();
	SearchCommand(Storage* store_, Parser* parser_);
	~SearchCommand();

	string Execute(string) override;
};

class CompleteCommand : public Command{
public:
	CompleteCommand();
	CompleteCommand(Storage* store_, Parser* parser_);
	~CompleteCommand();

	string Execute(string) override;
};

class FreeCommand : public Command{
public:
	FreeCommand();
	FreeCommand(Storage* store_, Parser* parser_);
	~FreeCommand();

	string Execute(string) override;
};

class LoadCommand : public Command{
public:
	LoadCommand();
	LoadCommand(Storage* store_, Parser* parser_);
	~LoadCommand();

	string Execute(string) override;
};

class UndoCommand : public Command{
public:
	UndoCommand();
	UndoCommand(Storage* store_, Parser* parser_);
	~UndoCommand();

	string Execute(string) override;
};

class ArchivedCommand : public Command{
public:
	ArchivedCommand();
	ArchivedCommand(Storage* store_, Parser* parser_);
	~ArchivedCommand();

	string Execute(string) override;
};

class Invalid_cmdCommand : public Command{
public:
	Invalid_cmdCommand();
	Invalid_cmdCommand(Storage* store_, Parser* parser_);
	~Invalid_cmdCommand();

	string Execute(string) override;
};
