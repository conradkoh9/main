#pragma once
#include <string>
#include <vector>
#include "Smartstring.h"
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
	string ToShortString();
	string ToCSVString();

	TASKTYPE GetType();
	bool Contains(string input);
	bool NearMatch(string input);
	size_t LevenshteinDistance(const std::string &s1, const std::string &s2);
	//template<class T> unsigned int levenshtein_distance(const T &s1, const T & s2);

	bool isFloating();
	bool isDeadline();
	bool isTimed();

	friend ostream& operator<<(ostream& out, Task& task);
	friend istream& operator>>(istream& in, Task& task);
};

ostream& operator<<(ostream& out, Task& task);

