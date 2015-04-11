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

	DateTime* standardStartdt;
	DateTime* standardEnddt;
	string startDateTime;
	string endDateTime;
	string startdate;
	string starttime;
	string enddate;
	string endtime;

	string priority;
	string status;

	//not clear what these are
	string sdate;
	string edate;
	string stime;
	string etime;



public:
	Task();
	Task(vector<string> input);
	Task(Task* task);
	~Task();

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
	static const string _FEEDBACK_DEFAULTDATE_SET;
	static const string _FEEDBACK_STANDARD_START_DATE_SET;
	static const string _FEEDBACK_STANDARD_END_DATE_SET;
	static const string _FEEDBACK_SDATE_SET;
	static const string _FEEDBACK_EDATE_SET;
	static const string _FEEDBACK_STIME_SET;
	static const string _FEEDBACK_ETIME_SET;

	static const string _STATUS_COMPLETE;
	static const string _STATUS_INCOMPLETE;

	static const int numberOfFields;

	string Edit(vector<string> newinfo);

	string SetDescription(string input);
	string SetStartDateTime(string input);
	string SetEndDateTime(string input);
	string SetPriority(string input);
	string SetStatus(string input);
	string SetSDate();
	string SetEDate();
	string SetSTime();
	string SetETime();
	string SetDefaultEnddate();
	void SetUpdate();

	string GetDescription();
	string GetStartDateTime();
	string GetStartDate();
	string GetStartTime();
	string GetEndDateTime();
	string GetEndDate();
	string GetEndTime();
	string GetPriority();
	string GetStatus();
	string GetSDate();
	string GetEDate();
	string GetSTime();
	string GetETime();

	string MarkComplete();

	//ToString methods
	string ToString();
	string ToShortString(); //used for display
	string ToFloatingString();
	string ToDeadlineString();
	string ToTimedString();
	string ToTXTString(); //used to write to txt files
	string ToCSVString(); //used to write to csv files

	//Dateless ToString methods
	string ToDatelessString();
	string ToDatelessFloatingString();
	string ToDatelessDeadlineString();
	string ToDatelessTimedString();

	TASKTYPE GetType();
	bool isContains(string input);
	bool isContainInDate(string input);
	bool isContainPriority(string input);
	bool isContainDescription(string input);
	bool isNearMatch(string input, string des);
	size_t LevenshteinDistance(const std::string &s1, const std::string &s2);


	bool isFloating();
	bool isDeadline();
	bool isTimed();


	friend ostream& operator<<(ostream& out, Task& task);
	friend istream& operator>>(istream& in, Task& task);
};

ostream& operator<<(ostream& out, Task& task);