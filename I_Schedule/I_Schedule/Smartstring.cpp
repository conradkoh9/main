#include "Smartstring.h"

const char* Smartstring::commands[] = { "add", "delete", "display", "search" ,"clear"};
const char* Smartstring::keywords[] = {"date:", "by", "priority:", "end:"};
const int Smartstring::numberOfCommands = 5;
const int Smartstring::numberOfFields = 4;

Smartstring::Smartstring()
{
	description = "";
}

Smartstring::Smartstring(string input){
	description = input;
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
	for (int i = 0; i < numberOfFields; ++i){
		if (description == keywords[i]){
			return true;
		}
	}

	return false;
}

Smartstring::COMMAND Smartstring::Command(){
	if (description == "add"){
		return Smartstring::COMMAND::ADD;
	}
	if (description == "delete"){
		return Smartstring::COMMAND::DELETE;
	}
	if (description == "display"){
		return Smartstring::COMMAND::DISPLAY;
	}
	if (description == "search"){
		return Smartstring::COMMAND::SEARCH;
	}
	if (description == "clear"){
		return Smartstring::COMMAND::CLEAR;
	}
	
	return Smartstring::COMMAND::INVALID_CMD;
}

Smartstring::FIELD Smartstring::Field(){
	if (description == "date:"){
		return Smartstring::FIELD::STARTDATE;
	}
	if (description == "by"){
		return Smartstring::FIELD::ENDDATE;
	}
	if (description == "priority:"){
		return Smartstring::FIELD::PRIORITY;
	}

	if (description == "end:"){
		return Smartstring::FIELD::ENDDATE;
	}
	
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