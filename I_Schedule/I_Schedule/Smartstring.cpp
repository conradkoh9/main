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
const string Smartstring:: COMMAND_ADD = "add";
const string Smartstring::COMMAND_CLEAR = "clear";
const string Smartstring:: COMMAND_DELETE = "delete";
const string Smartstring:: COMMAND_DISPLAY = "display";
const string Smartstring::COMMAND_EDIT = "edit";
const string Smartstring::COMMAND_EXIT = "exit";
const string Smartstring:: COMMAND_SEARCH = "search";

const string Smartstring:: KEYWORD_DATE_1 = "date:";
const string Smartstring:: KEYWORD_ENDDATE_1 = "by";
const string Smartstring:: KEYWORD_ENDDATE_2 = "by:";
const string Smartstring:: KEYWORD_ENDDATE_3 = "date:";
const string Smartstring:: KEYWORD_ENDDATE_4 = "end:";
const string Smartstring:: KEYWORD_ENDDATE_5 = "on:";
const string Smartstring::KEYWORD_ENDDATE_6 = "to:";
const string Smartstring::KEYWORD_ENDDATE_7 = "till:";
const string Smartstring::KEYWORD_ENDDATE_8 = "till";
const string Smartstring:: KEYWORD_PRIORITY_1 = "priority:";
const string Smartstring:: KEYWORD_PRIORITY_2 = "priority";
const string Smartstring:: KEYWORD_STARTDATE_1 = "from";
const string Smartstring:: KEYWORD_STARTDATE_2 = "from:";
const string Smartstring:: KEYWORD_DESCRIPTION_1 = "description:";
bool Smartstring::classInitialized = false;
int Smartstring::numberOfCommands;
int Smartstring::numberOfKeywords;
vector<string> Smartstring::commands;
vector<string> Smartstring::keywords;

Smartstring::Smartstring(){
	description = "";
	Initialize();
	
}


Smartstring::Smartstring(string input){
	description = input;
	Initialize();
}

void Smartstring::Initialize(){
	if (!classInitialized){
		commands.push_back(COMMAND_ADD);
		commands.push_back(COMMAND_CLEAR);
		commands.push_back(COMMAND_DELETE);
		commands.push_back(COMMAND_DISPLAY);
		commands.push_back(COMMAND_EDIT);
		commands.push_back(COMMAND_EXIT);
		commands.push_back(COMMAND_SEARCH);

		keywords.push_back(KEYWORD_DATE_1);
		keywords.push_back(KEYWORD_ENDDATE_1);
		keywords.push_back(KEYWORD_ENDDATE_2);
		keywords.push_back(KEYWORD_ENDDATE_3);
		keywords.push_back(KEYWORD_ENDDATE_4);
		keywords.push_back(KEYWORD_ENDDATE_5);
		keywords.push_back(KEYWORD_ENDDATE_6);
		keywords.push_back(KEYWORD_ENDDATE_7);
		keywords.push_back(KEYWORD_ENDDATE_8);
		keywords.push_back(KEYWORD_PRIORITY_1);
		keywords.push_back(KEYWORD_PRIORITY_2);
		keywords.push_back(KEYWORD_STARTDATE_1);
		keywords.push_back(KEYWORD_STARTDATE_2);
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
		if (description == commands[i]){
			return true;
		}
	}
	
	return false;
}

bool Smartstring::IsKeyword(){
	for (int i = 0; i < numberOfKeywords; ++i){
		if (description == keywords[i]){
			return true;
		}
	}

	return false;
}

Smartstring::COMMAND Smartstring::Command(){
	if (description == COMMAND_ADD){
		return Smartstring::COMMAND::ADD;
	}
	if (description == COMMAND_DELETE){
		return Smartstring::COMMAND::DELETE;
	}
	if (description == COMMAND_DISPLAY){
		return Smartstring::COMMAND::DISPLAY;
	}
	if (description == COMMAND_EDIT){
		return Smartstring::COMMAND::EDIT;
	}
	if (description == COMMAND_SEARCH){
		return Smartstring::COMMAND::SEARCH;
	}
	if (description == COMMAND_CLEAR){
		return Smartstring::COMMAND::CLEAR;
	}
	assert(!IsCommand()); //takes care of the case when we add cases to field but did not update static list commands[];
	return Smartstring::COMMAND::INVALID_CMD;
}

Smartstring::FIELD Smartstring::Field(){
	if (description == KEYWORD_STARTDATE_1 || description == KEYWORD_STARTDATE_2){
		return Smartstring::FIELD::STARTDATE;
	}
	if (description == KEYWORD_PRIORITY_1 || description == KEYWORD_PRIORITY_2){
		return Smartstring::FIELD::PRIORITY;
	}
	if (description == KEYWORD_ENDDATE_1 || description == KEYWORD_ENDDATE_2 || description == KEYWORD_ENDDATE_3 || description == KEYWORD_ENDDATE_4 || description == KEYWORD_ENDDATE_5 || description == KEYWORD_ENDDATE_6 || description == KEYWORD_ENDDATE_7){
		return Smartstring::FIELD::ENDDATE;
	}
	if (description == KEYWORD_DESCRIPTION_1){
		return Smartstring::FIELD::DESCRIPTION;
	}
	
	assert(!IsKeyword()); //takes care of the case when we add cases to field but did not update static list keywords[];
	return Smartstring::FIELD::INVALID_FLD;
}

string Smartstring::ToString(){
	return description;
}

//operator overloading
ostream& operator<<(ostream& os, Smartstring& ss){
	os << ss.description;
	return os;
}

istream& operator>>(istream& is, Smartstring& ss){
	is >> ss.description;
	return is;
}

string& operator+ (string input, Smartstring& ss){
	return (input + ss.description);
}

string& operator+ (Smartstring& ss, string& input){
	return (ss.description + input);
}

string& operator+ (const char* s, Smartstring &ss){
	string out;
	string first = s;
	out = first + ss.description.c_str();
	return out;
}
string& operator+ (Smartstring &ss, const char* s){
	string out;
	string first = s;
	out = first + ss.description.c_str();
	return out;
}