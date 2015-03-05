#pragma once
#include <string>
#include <sstream>
#include <vector>
using namespace std;
class Smartstring
{
private: 
	string description;
public:
	enum COMMAND { ADD, DELETE, DISPLAY, SEARCH, CLEAR, INVALID_CMD };
	enum FIELD { DESCRIPTION, STARTDATE, ENDDATE, PRIORITY, INVALID_FLD };
	static const char* commands[];
	static const char* keywords[];
	static const int numberOfCommands;
	static const int numberOfFields;

	Smartstring();
	Smartstring(string input);
	~Smartstring();
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

