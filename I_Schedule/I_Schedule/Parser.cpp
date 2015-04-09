#include "Parser.h"
#include "assert.h"

Parser::Parser()
{
	logfile << "Parser created";
}


Parser::~Parser()
{
}

Smartstring::COMMAND Parser::IdentifyCommand(string input){
	Smartstring expectedCMD;
	istringstream in(input);
	if (in >> expectedCMD){
		return expectedCMD.Command();
	}
	else{
		return Smartstring::COMMAND::INVALID_CMD;
	}
	
	
}

vector<string> Parser::IdentifyTaskFields(string input){
	Smartstring keyword;
	Smartstring::FIELD field = Smartstring::FIELD::DESCRIPTION;
	string info;
	istringstream in(input);
	
	int vectorSize = keyword.numberOfKeywords; //this gets the number of keywords recognized in our system. 

	//start initialize vector
	string blank = "";
	vector<string> output;
	for (int j = 0; j < vectorSize; ++j){
		output.push_back(blank);
	}
	//end initialize vector

	while (in >> keyword){
		if (keyword.IsKeyword()){
			field = keyword.Field(); //identify the field to be entered if it is a keyword and makes it the currently active field
			info = "";
		}
		else{
			if (info == ""){
				info = keyword.ToString(); //if statement ensures that no leading whitespace is added to task description
			}
			else{
				info = info + " " + keyword.ToString();
			}
			output[field] = info;
		}
		output[Smartstring::FIELD::STATUS] = Task::_STATUS_INCOMPLETE; //sets the default status to incomplete when parsing user input
	}
	//NOTE THAT OUTPUT HAS EXCESS BLANKS
	return output;
}


Smartstring::LIST Parser::IdentifyList(string input){
	Smartstring list;
	istringstream in(input);
	if (in >> list){
		return list.ListType();
	}
}

//@author A0094213M
string Parser::RemoveCommand(string input){
	string command; 
	string userInput;
	string remainder = "";
	istringstream in(input);

	if (in >> command){
		if (getline(in, userInput)){
			int endIdx = userInput.length() - 1;
			remainder = userInput.substr(1, endIdx); //remove white space
		}
	}
	
	return remainder;
	
}

//@author A0094213M
string Parser::RemoveKeywords(string input){
	istringstream in(input);

	Smartstring userInput;
	string remainder;
	while (in >> userInput){
		if (!userInput.IsKeyword()){
			remainder = userInput.ToString() + " ";
		}
	}
	int endIdx = remainder.length() - 1;
	remainder = remainder.substr(0, endIdx - 1); // remove white space at the end

	return remainder;
}


//@author A0094213M
vector<string> Parser::Tokenize(string input){
	istringstream in(input);
	vector<string> infos;
	string token;

	while (in >> token){
		infos.push_back(token);
	}

	return infos;
}
