#include "Parser.h"


Parser::Parser()
{
}


Parser::~Parser()
{
}

vector<string> Parser::Identify(string input){
	Smartstring word;
	string info;
	istringstream in(input);
	Smartstring::FIELD field = Smartstring::FIELD::DESCRIPTION;
	vector<string> output(word.numberOfKeywords);
	
	while (in >> word){
		if (word.IsKeyword()){
			field = word.Field();
			info = "";
		}
		else{
			info = info + " " + word;
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