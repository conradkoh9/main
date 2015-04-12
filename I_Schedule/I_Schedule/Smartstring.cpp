//@author A0094213M
#include "Smartstring.h"
#include <iostream>
//note: static fields always need to be redeclared in cpp file

//adding commands or keywords here
//IMPORTANT: PLEASE ADD COMMANDS IN ALPHABETICAL ORDER AND FOLLOW THE ORDERING IN ALL FILES
//1. add a static string in header
//2. define command or keyword in the list of const strings
//3. push the string into commands and keywords vectors respectively in Initialize() function
//4. change Command and Field functions for commands and keywords respectively
//5. check the enum within smartstring to check if it matches the cases
//6. add to the current test cases in Libtest

const string Smartstring::COMMAND_ADD = "add";
const string Smartstring::COMMAND_CLEAR = "clear";
const string Smartstring::COMMAND_DELETE = "delete";
const string Smartstring::COMMAND_DISPLAY = "display";
const string Smartstring::COMMAND_EDIT = "edit";
const string Smartstring::COMMAND_SAVE = "save";
const string Smartstring::COMMAND_SEARCH = "search";
const string Smartstring::COMMAND_COMPLETE = "complete";
const string Smartstring::COMMAND_EMPTYSLOTS = "free";
const string Smartstring::COMMAND_UNDO = "undo";
const string Smartstring::COMMAND_LOAD = "load";
const string Smartstring::COMMAND_ARCHIVED = "archived";


const string Smartstring::KEYWORD_ENDDATE_1 = "date:";
const string Smartstring::KEYWORD_ENDDATE_2 = "by:";
const string Smartstring::KEYWORD_ENDDATE_3 = "e:";
const string Smartstring::KEYWORD_ENDDATE_4 = "end:";
const string Smartstring::KEYWORD_ENDDATE_5 = "t:";
const string Smartstring::KEYWORD_ENDDATE_6 = "to:";
const string Smartstring::KEYWORD_ENDDATE_7 = "till:";
const string Smartstring::KEYWORD_ENDDATE_8 = "deadline:";
const string Smartstring::KEYWORD_ENDDATE_9 = "d:";
const string Smartstring::KEYWORD_ENDDATE_10 = "before:";
const string Smartstring::KEYWORD_ENDDATE_11 = "deadline:";
const string Smartstring::KEYWORD_ENDDATE_12 = "due:";
const string Smartstring::KEYWORD_PRIORITY_1 = "priority:";
const string Smartstring::KEYWORD_PRIORITY_2 = "p:";
const string Smartstring::KEYWORD_STARTDATE_1 = "f:";
const string Smartstring::KEYWORD_STARTDATE_2 = "from:";
const string Smartstring::KEYWORD_STARTDATE_3 = "s:";
const string Smartstring::KEYWORD_STARTDATE_4 = "start:";
const string Smartstring::KEYWORD_STARTDATE_5 = "on:";
const string Smartstring::KEYWORD_STARTDATE_6 = "at:";
const string Smartstring::KEYWORD_STARTDATE_7 = "d:";
const string Smartstring::KEYWORD_DESCRIPTION_1 = "description:";
const string Smartstring::KEYWORD_TIMED_1 = "timed:";
const string Smartstring::KEYWORD_DEADLINE_1 = "deadline:";
const string Smartstring::KEYWORD_FLOAT_1 = "float:";


const string Smartstring::FEEDBACK_ADD_SUCCESSULLY = "add the entry successfully";
const string Smartstring::FEEDBACK_DELETE_SUCCESSFULLY = "delete the entry successfully";
const string Smartstring::FEEDBACK_DELETE_FAIL= "fail to delete the entry";
const string Smartstring::FEEDBACK_EDIT_SUCCESSFULLY="edit the entry successfully";
const string Smartstring::FEEDBACK_EDIT_FAIL="fail to edit the entry";
const string Smartstring::FEEDBACK_SEARCH_FAIL="cannot find";


bool Smartstring::classInitialized = false;
int Smartstring::numberOfCommands;
int Smartstring::numberOfKeywords;
const int Smartstring::NUMBER_OF_FIELDS = 5;
vector<string> Smartstring::commands;
vector<string> Smartstring::keywords;

Smartstring::Smartstring(){
	information = "";
	Initialize();
	
}


Smartstring::Smartstring(string input){
	information = input;
	Initialize();
}

void Smartstring::Initialize(){
	if (!classInitialized){
		commands.push_back(COMMAND_ADD);
		commands.push_back(COMMAND_CLEAR);
		commands.push_back(COMMAND_DELETE);
		commands.push_back(COMMAND_DISPLAY);
		commands.push_back(COMMAND_EDIT);
		commands.push_back(COMMAND_SAVE);
		commands.push_back(COMMAND_SEARCH);
		commands.push_back(COMMAND_COMPLETE);
		commands.push_back(COMMAND_UNDO);
		commands.push_back(COMMAND_LOAD);
		commands.push_back(COMMAND_ARCHIVED);

		keywords.push_back(KEYWORD_ENDDATE_1);
		keywords.push_back(KEYWORD_ENDDATE_2);
		keywords.push_back(KEYWORD_ENDDATE_3);
		keywords.push_back(KEYWORD_ENDDATE_4);
		keywords.push_back(KEYWORD_ENDDATE_5);
		keywords.push_back(KEYWORD_ENDDATE_6);
		keywords.push_back(KEYWORD_ENDDATE_7);
		keywords.push_back(KEYWORD_ENDDATE_8);
		keywords.push_back(KEYWORD_ENDDATE_9);
		keywords.push_back(KEYWORD_ENDDATE_10);
		keywords.push_back(KEYWORD_ENDDATE_11);
		keywords.push_back(KEYWORD_ENDDATE_12);
		keywords.push_back(KEYWORD_PRIORITY_1);
		keywords.push_back(KEYWORD_PRIORITY_2);
		keywords.push_back(KEYWORD_STARTDATE_1);
		keywords.push_back(KEYWORD_STARTDATE_2);
		keywords.push_back(KEYWORD_STARTDATE_3);
		keywords.push_back(KEYWORD_STARTDATE_4);
		keywords.push_back(KEYWORD_STARTDATE_5);
		keywords.push_back(KEYWORD_STARTDATE_6);
		keywords.push_back(KEYWORD_STARTDATE_7);
		keywords.push_back(KEYWORD_DESCRIPTION_1);
		numberOfCommands = commands.size();
		numberOfKeywords = keywords.size();
		classInitialized = true;
	}
		
	return;
}


Smartstring::~Smartstring()
{
}

bool Smartstring::IsCommand(){
	for (int i = 0; i < numberOfCommands; ++i){
		if (information == commands[i]){
			return true;
		}
	}
	
	return false;
}

bool Smartstring::IsKeyword(){
	for (int i = 0; i < numberOfKeywords; ++i){
		if (information == keywords[i]){
			return true;
		}
	}

	return false;
}

Smartstring::COMMAND Smartstring::Command(){
	if (information == COMMAND_ADD){
		return Smartstring::COMMAND::ADD;
	}
	if (information == COMMAND_DELETE){
		return Smartstring::COMMAND::DELETE;
	}
	if (information == COMMAND_DISPLAY){
		return Smartstring::COMMAND::DISPLAY;
	}
	if (information == COMMAND_EDIT){
		return Smartstring::COMMAND::EDIT;
	}
	if (information == COMMAND_SEARCH){
		return Smartstring::COMMAND::SEARCH;
	}
	if (information == COMMAND_CLEAR){
		return Smartstring::COMMAND::CLEAR;
	}
	if (information == COMMAND_SAVE){
		return Smartstring::COMMAND::SAVE;
	}
	if (information == COMMAND_COMPLETE){
		return Smartstring::COMMAND::COMPLETE;
	}
	if (information == COMMAND_EMPTYSLOTS){
		return Smartstring::COMMAND::FREE;
	}
	if (information == COMMAND_UNDO){
		return Smartstring::COMMAND::UNDO;
	}
	if (information == COMMAND_LOAD){
		return Smartstring::COMMAND::LOAD;
	}
	if (information == COMMAND_ARCHIVED){
		return Smartstring::COMMAND::ARCHIVED;
	}

	assert(!IsCommand()); //takes care of the case when we add cases to field but did not update static list commands[];
	return Smartstring::COMMAND::INVALID_CMD;
}

Smartstring::FIELD Smartstring::Field(){
	if (information == KEYWORD_STARTDATE_1 || information == KEYWORD_STARTDATE_2 || information == KEYWORD_STARTDATE_3 || information == KEYWORD_STARTDATE_4 || information == KEYWORD_STARTDATE_5 || information == KEYWORD_STARTDATE_6 || information == KEYWORD_STARTDATE_7){
		return Smartstring::FIELD::STARTDATE;
	}
	if (information == KEYWORD_PRIORITY_1 || information == KEYWORD_PRIORITY_2){
		return Smartstring::FIELD::PRIORITY;
	}
	if (information == KEYWORD_ENDDATE_1 || information == KEYWORD_ENDDATE_2 || information == KEYWORD_ENDDATE_3 || information == KEYWORD_ENDDATE_4 || information == KEYWORD_ENDDATE_5 || information == KEYWORD_ENDDATE_6 || information == KEYWORD_ENDDATE_7 || information == KEYWORD_ENDDATE_8 || information == KEYWORD_ENDDATE_9 || information == KEYWORD_ENDDATE_10 || information == KEYWORD_ENDDATE_11 || information == KEYWORD_ENDDATE_12){
		return Smartstring::FIELD::ENDDATE;
	}
	if (information == KEYWORD_DESCRIPTION_1){
		return Smartstring::FIELD::DESCRIPTION;
	}
	
	assert(!IsKeyword()); //takes care of the case when we add cases to field but did not update static list keywords[];
	return Smartstring::FIELD::INVALID_FLD;
}

Smartstring::LIST Smartstring::ListType(){
	if (information == KEYWORD_TIMED_1){
		return Smartstring::LIST::TIMED;
	}
	if (information == KEYWORD_DEADLINE_1){
		return Smartstring::LIST::DEADLINE;
	}
	if (information == KEYWORD_FLOAT_1){
		return Smartstring::LIST::FLOAT;
	}
	return Smartstring::LIST::DEFAULT;
}


string Smartstring::ToString(){
	return information;
}

vector<string> Smartstring::Tokenize(string delimiters){
	int found = 0;
	int startIdx = 0;
	vector<string> tokens;
	while (found != string::npos){
		found = information.find_first_of(delimiters.c_str(), startIdx);
		int length = found - startIdx;
		string result = information.substr(startIdx, length);
		if (result.length() != 0){
			tokens.push_back(result);
		}
		startIdx = found + 1;
	}
	return tokens;
}

vector<string> Smartstring::ContainedTokenize(string delimiters){
	int found = 0;
	string input = information;
	int startFrame = 0;
	int endFrame = 0;
	int startIdx = 0;
	int endIdx = 0;
	vector<string> tokens;
	while (startFrame != string::npos && endFrame != string::npos){
		startFrame = input.find_first_of(delimiters.c_str(), startIdx);
		if (startFrame != string::npos){
			endFrame = input.find_first_of(delimiters.c_str(), startFrame + 1);
			if (endFrame != string::npos){
				int length = endFrame - startFrame - 1;
				string result = input.substr(startFrame + 1, length);
				tokens.push_back(result);
			}
		}
		startIdx = endFrame + 1;
	}
	return tokens;
}


//operator overloading
ostream& operator<<(ostream& os, Smartstring& ss){
	os << ss.information;
	return os;
}

istream& operator>>(istream& is, Smartstring& ss){
	is >> ss.information;
	return is;
}

string& operator+ (string input, Smartstring& ss){
	return (input + ss.information);
}

string& operator+ (Smartstring& ss, string& input){
	return (ss.information + input);
}

string& operator+ (const char* s, Smartstring &ss){
	string out;
	string first = s;
	out = first + ss.information.c_str();
	return out;
}
string& operator+ (Smartstring &ss, const char* s){
	string out;
	string first = s;
	out = first + ss.information.c_str();
	return out;
}