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
	enum COMMAND { ADD, CLEAR, DELETE, DISPLAY, EDIT, EXIT, SEARCH, INVALID_CMD };
	enum FIELD { DESCRIPTION, STARTDATE, ENDDATE, PRIORITY, INVALID_FLD };

	static bool classInitialized;
	static int numberOfCommands;
	static int numberOfKeywords;
	
	static vector<string> commands;
	static vector<string> keywords;
	static const string COMMAND_ADD;
	static const string COMMAND_CLEAR;
	static const string COMMAND_DELETE;
	static const string COMMAND_DISPLAY;
	static const string COMMAND_EDIT;
	static const string COMMAND_EXIT;
	static const string COMMAND_SEARCH;
	static const int NUMBER_OF_FIELDS;



	static const string KEYWORD_ENDDATE_1;
	static const string KEYWORD_ENDDATE_2;
	static const string KEYWORD_ENDDATE_3;
	static const string KEYWORD_ENDDATE_4;
	static const string KEYWORD_ENDDATE_5;
	static const string KEYWORD_ENDDATE_6;
	static const string KEYWORD_ENDDATE_7;
	static const string KEYWORD_ENDDATE_8;
	static const string KEYWORD_ENDDATE_9;
	static const string KEYWORD_ENDDATE_10;
	static const string KEYWORD_PRIORITY_1;
	static const string KEYWORD_PRIORITY_2;
	static const string KEYWORD_STARTDATE_1;
	static const string KEYWORD_STARTDATE_2;
	static const string KEYWORD_STARTDATE_3;
	static const string KEYWORD_STARTDATE_4;
	static const string KEYWORD_DESCRIPTION_1;

	static const string FEEDBACK_SEARCH_FAIL;
	static const string FEEDBACK_ADD_SUCCESSULLY;
	static const string FEEDBACK_DELETE_SUCCESSFULLY;
	static const string FEEDBACK_DELETE_FAIL;
	static const string FEEDBACK_EDIT_SUCCESSFULLY;
	static const string FEEDBACK_EDIT_FAIL;

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
	friend string& operator+ (string input, Smartstring &ss);
	friend string& operator+ (Smartstring& ss, string& input);
	friend string& operator+ (const char* s, Smartstring &ss);
	friend string& operator+ (Smartstring &ss, const char* s);
	

};

istream& operator>>(istream& is, Smartstring& ss);
ostream& operator<<(ostream& os, Smartstring& ss);
string& operator+ (string input, Smartstring& ss);
string& operator+ (Smartstring& ss, string& input);
string& operator+ (const char* s, Smartstring &ss);
string& operator+ (Smartstring &ss, const char* s);


