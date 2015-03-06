#include "Smartstring.h"

Smartstring::Smartstring(){
	description = "";
	Initialize();
}


Smartstring::Smartstring(string input){
	description = input;
	Initialize();
}

void Smartstring::Initialize(){
	commands.push_back(COMMAND_ADD);
	commands.push_back(COMMAND_CLEAR);
	commands.push_back(COMMAND_DELETE);
	commands.push_back(COMMAND_DISPLAY);
	commands.push_back(COMMAND_SEARCH);
	keywords.push_back(KEYWORD_DATE_1);
	keywords.push_back(KEYWORD_ENDDATE_1);
	keywords.push_back(KEYWORD_ENDDATE_2);
	keywords.push_back(KEYWORD_ENDDATE_3);
	keywords.push_back(KEYWORD_ENDDATE_4);
	keywords.push_back(KEYWORD_PRIORITY_1);
	keywords.push_back(KEYWORD_PRIORITY_2);
	keywords.push_back(KEYWORD_STARTDATE_1);
	keywords.push_back(KEYWORD_STARTDATE_2);
	keywords.push_back(KEYWORD_DESCRIPTION_1);
	numberOfCommands = commands.size();
	numberOfKeywords = keywords.size();

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
	if (description == KEYWORD_ENDDATE_1 || description == KEYWORD_ENDDATE_2 || description == KEYWORD_ENDDATE_3 || description == KEYWORD_ENDDATE_4){
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

string& operator+ (string output, Smartstring& ss){
	return ss.description;
}