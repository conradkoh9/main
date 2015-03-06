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

	static bool classInitialized;
	static int numberOfCommands;
	static int numberOfKeywords;
	static vector<string> commands;
	static vector<string> keywords;
	static const string COMMAND_ADD;
	static const string COMMAND_DELETE;
	static const string COMMAND_DISPLAY;
	static const string COMMAND_SEARCH;
	static const string COMMAND_CLEAR;
	static const string KEYWORD_DATE_1;
	static const string KEYWORD_ENDDATE_1;
	static const string KEYWORD_ENDDATE_2;
	static const string KEYWORD_ENDDATE_3;
	static const string KEYWORD_ENDDATE_4;
	static const string KEYWORD_ENDDATE_5;
	static const string KEYWORD_PRIORITY_1;
	static const string KEYWORD_PRIORITY_2;
	static const string KEYWORD_STARTDATE_1;
	static const string KEYWORD_STARTDATE_2;
	static const string KEYWORD_DESCRIPTION_1;

	

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


