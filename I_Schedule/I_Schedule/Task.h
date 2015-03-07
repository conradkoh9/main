#pragma once
#include <string>
#include <vector>
#include "Smartstring.h"
using namespace std;

class Task
{
private:
	string description;
	string startdate;
	string enddate;
	string priority;

public:
	Task();
	Task(vector<string> input);
	~Task();
	
	static const string FIELD_DESCRIPTION;
	static const string FIELD_STARTDATE;
	static const string FIELD_ENDDATE;
	static const string FIELD_PRIORITY;

	static const string _FEEDBACK_DESCRIPTION_SET;
	static const string _FEEDBACK_STARTDATE_SET;
	static const string _FEEDBACK_ENDDATE_SET;
	static const string _FEEDBACK_PRIORITY_SET;

	string SetDescription(string input);
	string SetStartDate(string input);
	string SetEndDate(string input);
	string SetPriority(string input);

	string GetDescription();
	string GetStartDate();
	string GetEndDate();
	string GetPriority();

	string ToString();

	friend ostream& operator<<(ostream& out, Task& task);
	friend istream& operator>>(istream& in, Task& task);
};

ostream& operator<<(ostream& out, Task& task);

