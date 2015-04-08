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
	enum DAY{ SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, INVALID };
private:

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
	static const string DATETYPE_TODAY1;
	static const string DATETYPE_TOMORROW1;
	static const string DATETYPE_TOMORROW2;

	static const string TIMETYPE_AM;
	static const string TIMETYPE_PM;

	// my idea here is I have to search for the key words for day and time so 
	// as to separate the info into date and time type

public:
	DateTime();
	DateTime(string);
	~DateTime();

	//==========================================================
	//Methods suggested by Conrad
	//Note: these methods are currently used in
	//==========================================================
public:
	//Variables
	string unformattedDateTime;
	string formattedDateTime;
	bool isValidFormat;
	time_t time_in_seconds;

	//Methods
	string Standardized();
	string GetInfo();
	int GetSeconds();
	bool IsEarlierThan(DateTime dt);
private:
	void SetDefaults();
	void SetStandards();
	void SetSeconds();

	string StandardizeSingle(string input);
	string StandardizeTriple(vector<string> input);

	string StandardizeDayDate(string input); //Standardize input assuming that it is either a day, or a date
	string StandardizeDate(string input); //Standardize input assuming that it is a date
	string StandardizeDay(string input); //Standardize input assuming that it is a day
	string StandardizeTime(string input);
	bool CompareDate(string, string);
	bool CompareTime(string, string);
	bool IsValidDayDate(string input); //Check if input is a valid day or date
	bool IsValidDate(string input); //Check if input is a valid date
	bool IsValidDay(string input); //Check if input is a valid day
	bool IsValidTime(string input); //Check if input is a valid time


	DAY GetDayEnum(string input); //Gets the DAY in enum format of an input string. i.e. sunday = 0, monday = 1...
	int CalculateOffset(DAY startday, DAY endday); //Gets the offset for the next occurance of endday based on startday.

	string GetDayFromTime(time_t time); 
	string GetStandardDate(time_t time);
	string GetStandardTime(time_t time);
	time_t OffsetByDay(time_t startday, time_t offset_in_days); //given a startday and number of days to offset by, converts to a time_t value

	DAY GetToday();
	DAY GetTomorrow();

	//==========================================================
	//End section Methods suggested by Conrad
	//==========================================================


	//==========================================================
	//Methods
	//==========================================================
public:
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

private:
	int _day;
	int _month;
	int _year;
	int _hours;
	int _mins;
	//int _seconds;
	string _state; //this name needs to be redefined 

	
};

