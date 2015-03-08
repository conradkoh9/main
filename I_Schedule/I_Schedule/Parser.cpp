#include "Parser.h"


Parser::Parser()
{
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

vector<string> Parser::IdentifyTaskFields(string input){
	Smartstring word;
	string info;
	istringstream in(input);
	Smartstring::FIELD field = Smartstring::FIELD::DESCRIPTION;
	int vectorSize = word.numberOfKeywords;
	string blank = "";
	vector<string> output;
	for (int j = 0; j < vectorSize; ++j){
		output.push_back(blank);
	}
	
	while (in >> word){
		if (word.IsKeyword()){
			field = word.Field();
			info = "";
		}
		else{
			if (info == ""){
				info = word.ToString(); //if statement ensures that no leading whitespace is added to task description
			}
			else{
				info = info + " " + word.ToString();
			}
			output[field] = info;
		}
	}
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
