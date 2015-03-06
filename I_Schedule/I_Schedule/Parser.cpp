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
	int vectorSize = word.numberOfKeywords;
	string blank = " ";
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
				info = word.ToString();
			}
			else{
				info = info + " " + word.ToString();
			}
			output[field] = info; //????
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

void Parser::InitializeVect(vector<string> &input){
	
	return;
}