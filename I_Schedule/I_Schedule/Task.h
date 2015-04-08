#pragma once
#include <string>
#include <vector>
#include "DateTime.h"
#include <iomanip>
#include <cstring>
#include <climits>
using namespace std;

class Task
{
private:
	string description;
	string startdate;
	string enddate;
	string priority;
	string standardStart;
	string standardEnd;
	string status;
	DateTime* standardStartdt;
	DateTime* standardEnddt;

public:
	Task();
	Task(vector<string> input);
	~Task();
	int numberOfFields;

	enum TASKTYPE{ FLOATING, DEADLINE, TIMED };

	static const string FIELD_DESCRIPTION;
	static const string FIELD_STARTDATE;
	static const string FIELD_ENDDATE;
	static const string FIELD_PRIORITY;
	static const string FIELD_STATUS;


	static const string _FEEDBACK_DESCRIPTION_SET;
	static const string _FEEDBACK_STARTDATE_SET;
	static const string _FEEDBACK_ENDDATE_SET;
	static const string _FEEDBACK_PRIORITY_SET;
	static const string _FEEDBACK_STATUS_SET;
	static const string _FEEDBACK_STANDARD_START_DATE_SET;
	static const string _FEEDBACK_STANDARD_END_DATE_SET;

	static const string _STATUS_COMPLETE;
	static const string _STATUS_INCOMPLETE;

	string Edit(vector<string> newinfo);

	string SetDescription(string input);
	string SetStartDate(string input);
	string SetEndDate(string input);
	string SetPriority(string input);
	string SetStatus(string input);
	string SetStandardStartDate();
	string SetStandardEndDate();

	string GetDescription();
	string GetStartDate();
	string GetEndDate();
	string GetPriority();
	string GetStatus();
	string GetStandardStartDateTime();
	string GetStandardEndDateTime();

	string MarkComplete();

	string ToString();
	string ToFloatingString();
	string ToDeadlineString();
	string ToTimedString();
	string ToShortString(); //used for display
	string ToTXTString(); //used to write to txt files
	string ToCSVString(); //used to write to csv files

	TASKTYPE GetType();
	bool isContains(string input);
	bool isNearMatch(string input);
	size_t LevenshteinDistance(const std::string &s1, const std::string &s2);


	bool isFloating();
	bool isDeadline();
	bool isTimed();

	friend ostream& operator<<(ostream& out, Task& task);
	friend istream& operator>>(istream& in, Task& task);
};

ostream& operator<<(ostream& out, Task& task);