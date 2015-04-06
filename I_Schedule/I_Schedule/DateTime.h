#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <cassert>
#include <iomanip>
#include "Smartstring.h"

using namespace std;
class DateTime
{
	enum DATEKEY{ TODAY, TOMORROW };
	enum DAY{ SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, INVALID
};

public:
	DateTime();
	DateTime(string);
	~DateTime();


	//Variables
	string unformattedDateTime;
	string formattedDateTime;
	bool isValidFormat;

	//Methods
	string Standardized();
	string StandardizeTime(string input);

	string StandardizeDayDate(string input);
	string StandardizeDate(string input);
	string StandardizeDay(string input);

	bool IsValidDayDate(string input);
	bool IsValidDate(string input);
	bool IsValidDay(string input);
	bool IsValidTime(string input);

	time_t OffsetByDay(time_t timeReference, time_t offset);
	
	DAY GetDayEnum(string input);
	int CalculateOffset(DAY startday, DAY endday);

	string GetDayFromTime(time_t time);
	string GetStandardDate(time_t time);
	string GetStandardTime(time_t time);
	//======================================
	//Methods

	string Now();
	string Today();
	string ConvertDate();
	string ConvertDateTime(string);
	string ConvertTime();
	string GetType(string);
	void Initialize();
	bool CompareDateTime(string, string);
	bool isDateType(string);
	bool isTimeType(string);


	static bool isInitialized;
	static int numberOfDateType;
	static int numberOfTimeType;

	static vector<string> dateType;
	static vector<string> timeType;

	static const string DATETYPE_MONDAY1;
	static const string DATETYPE_MONDAY2;
	static const string DATETYPE_MONDAY3;
	static const string DATETYPE_MONDAY4;
	static const string DATETYPE_TUESDAY1;
	static const string DATETYPE_TUESDAY2;
	static const string DATETYPE_TUESDAY3;
	static const string DATETYPE_TUESDAY4;
	static const string DATETYPE_WEDNESDAY1;
	static const string DATETYPE_WEDNESDAY2;
	static const string DATETYPE_WEDNESDAY3;
	static const string DATETYPE_WEDNESDAY4;
	static const string DATETYPE_THURSDAY1;
	static const string DATETYPE_THURSDAY2;
	static const string DATETYPE_THURSDAY3;
	static const string DATETYPE_THURSDAY4;
	static const string DATETYPE_FRIDAY1;
	static const string DATETYPE_FRIDAY2;
	static const string DATETYPE_FRIDAY3;
	static const string DATETYPE_FRIDAY4;
	static const string DATETYPE_SATURDAY1;
	static const string DATETYPE_SATURDAY2;
	static const string DATETYPE_SATURDAY3;
	static const string DATETYPE_SATURDAY4;
	static const string DATETYPE_SUNDAY1;
	static const string DATETYPE_SUNDAY2;
	static const string DATETYPE_SUNDAY3;
	static const string DATETYPE_SUNDAY4;

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
	string _state; //this name needs to be redefined 

	
};

