#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <cassert>
using namespace std;
class Smartstring
{
private: 
	
public:
	string description;
	enum COMMAND { ADD, DELETE, DISPLAY, SEARCH, CLEAR, INVALID_CMD };
	enum FIELD { DESCRIPTION, STARTDATE, ENDDATE, PRIORITY, INVALID_FLD };
	vector<string> commands;
	vector<string> keywords;
	const string COMMAND_ADD = "add";
	const string COMMAND_DELETE = "delete";
	const string COMMAND_DISPLAY = "display";
	const string COMMAND_SEARCH = "search";
	const string COMMAND_CLEAR = "clear";
	const string KEYWORD_DATE_1 = "date:";
	const string KEYWORD_ENDDATE_1 = "by";
	const string KEYWORD_ENDDATE_2 = "by:";
	const string KEYWORD_ENDDATE_3 = "date:";
	const string KEYWORD_ENDDATE_4 = "end:";
	const string KEYWORD_PRIORITY_1 = "priority:";
	const string KEYWORD_PRIORITY_2 = "priority";
	const string KEYWORD_STARTDATE_1 = "from";
	const string KEYWORD_STARTDATE_2 = "from:";
	const string KEYWORD_DESCRIPTION_1 = "description:";

	int numberOfCommands;
	int numberOfKeywords;

	Smartstring();
	Smartstring(string input);
	~Smartstring();
	void Initialize();
	COMMAND Command();
	FIELD Field();
	bool IsCommand();
	bool IsKeyword();

	string ToString();



	friend istream& operator>>(istream& is, Smartstring& ss);
	friend ostream& operator<< (ostream& os, Smartstring& ss);
	friend string& operator+(string output, Smartstring &ss);

};

istream& operator>>(istream& is, Smartstring& ss);
ostream& operator<<(ostream& os, Smartstring& ss);
string& operator+ (string output, Smartstring& ss);

