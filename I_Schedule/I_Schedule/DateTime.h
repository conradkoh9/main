#pragma once
#include <string>
#include <time.h>
using namespace std;
class DateTime
{
public:
	DateTime();
	DateTime(string);
	~DateTime();
	string Now();
	string Today();


	string ConvertDate();
	string ConvertDateTime(string);
	string ConvertTime();
	string GetType(string);
	bool CompareDateTime(string, string);

	static const string DATETYPE_MONDAY1;
	static const string DATETYPE_MONDAY2;
	static const string DATETYPE_TUESDAY1;
	static const string DATETYPE_TUESDAY2;
	static const string DATETYPE_WEDNESDAY1;
	static const string DATETYPE_WEDNESDAY2;
	static const string DATETYPE_THURSDAY1;
	static const string DATETYPE_THURSDAY2;
	static const string DATETYPE_FRIDAY1;
	static const string DATETYPE_FRIDAY2;
	static const string DATETYPE_SATURDAY1;
	static const string DATETYPE_SATURDAY2;
	static const string DATETYPE_SUNDAY1;
	static const string DATETYPE_SUNDAY2;

	static const string TIMETYPE_AM;
	static const string TIMETYPE_PM;

	// my idea here is I have to search for the key words for day and time so 
	// as to separate the info into date and time type
private:
	int _day;
	int _month;
	int _year;
	int _hours;
	int _mins;
	int _seconds;

	enum DATEKEY{ TODAY, TOMORROW };
};

