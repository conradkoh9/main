//@author A0094213M
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <cassert>
#include <iomanip>
#include <exception>
#include "Smartstring.h"
#include "assert.h"

using namespace std;
class DateTime
{

private:
	int _day;
	int _month;
	int _year;
	int _hours;
	int _mins;
	string _period;

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
	static const string _MONTH_JANUARY;
	static const string _MONTH_FEBRUARY;
	static const string _MONTH_MARCH;
	static const string _MONTH_APRIL;
	static const string _MONTH_MAY;
	static const string _MONTH_JUNE;
	static const string _MONTH_JULY;
	static const string _MONTH_AUGUST;
	static const string _MONTH_SEPTEMBER;
	static const string _MONTH_OCTOBER;
	static const string _MONTH_NOVEMBER;
	static const string _MONTH_DECEMBER;



	static const string TIMETYPE_AM;
	static const string TIMETYPE_PM;

	enum DATEKEY{ TODAY, TOMORROW };
	enum DAY{ SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, INVALID };

	//methods
	void SetDefaultDateTime();
	void SetStandards();
	void SetSeconds();

	string StandardizeSingle(string);
	string StandardizeTriple(vector<string>);
	string StandardizeDayDate(string); //Standardize input assuming that it is either a day, or a date
	string StandardizeDate(string); //Standardize input assuming that it is a date
	string StandardizeDay(string); //Standardize input assuming that it is a day
	string StandardizeTime(string);
	string TwentyFourHourFormat();// this method returns time in 24 hour format

	bool IsValidDayDate(string); //Check if input is a valid day or date
	bool IsValidDate(string); //Check if input is a valid date
	bool IsValidDay(string); //Check if input is a valid day
	bool IsValidTime(string); //Check if input is a valid time


	DAY GetDayEnum(string); //Gets the DAY in enum format of an input string. i.e. sunday = 0, monday = 1...
	DAY GetTomorrow();
	DAY GetToday();
	string GetMonthName(int); //converts month to string
	int CalculateOffset(DAY, DAY); //Gets the offset for the next occurance of endday based on startday.

	string GetDayFromTime(time_t);
	string GetStandardDate(time_t);
	string GetStandardTime(time_t);
	time_t OffsetByDay(time_t, time_t); //given a startday and number of days to offset by, converts to a time_t value





public:
	string unformattedDateTime;
	string formattedDateTime;
	bool isValidFormat;
	bool isDateSet;
	bool isTimeSet;
	time_t time_in_seconds;

	DateTime();
	DateTime(string);
	~DateTime();

	string Now();
	string Today();
	string Tomorrow();
	string Standardized();
	string GetInfo();
	string GetDate();
	string GetDateWithoutYear();//omit the year if the date&time is in the current year
	string GetTime();
	int GetSeconds();
	bool IsEarlierThan(DateTime);
	bool CompareDateTime(string, string);
	bool CompareDate(string, string);
	bool CompareTime(string, string);
	DateTime* GetDefaultEndDate();
	void Initialize();





};

