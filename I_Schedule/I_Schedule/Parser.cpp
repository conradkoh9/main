#include "Parser.h"


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
	string info;
	istringstream in(input);
	Smartstring::FIELD field = Smartstring::FIELD::DESCRIPTION;
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

string Parser::RemoveCommand(string input){
	string buffer;
	string remainder;
	istringstream in(input);
	if (in >> buffer){
		if (getline(in, remainder)){
			int endIdx = remainder.length() - 1;
			remainder = remainder.substr(1, endIdx); //remove white space
		}
		else{
			remainder = ""; //manage unwanted values for remainder if getline or in fails
		}
	}
	else{
		remainder = ""; //manage unwanted values for remainder if getline or in fails
	}
	return remainder;
	
}

string Parser::RemoveKeywords(string input){
	istringstream in(input);

	Smartstring current;
	string output;
	while (in >> current){
		if (!current.IsKeyword()){
			output = current.ToString() + " ";
		}
	}
	int endIdx = output.length() - 1;
	output.substr(0, endIdx - 1); // remove white space at the end

	return output;
}



vector<string> Parser::Tokenize(string input){
	istringstream in(input);
	vector<string> tokens;
	string buffer;
	while (in >> buffer){
		tokens.push_back(buffer);
	}

	return tokens;
}
