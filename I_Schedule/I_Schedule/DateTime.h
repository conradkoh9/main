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
	string now();
	string today();
	string tomorrow();

	string convertDate();
	string convertDateTime(string);
	string convertTime();
	string getType(string);

	static const string DATETYPE_MONDAY1;
	static const string DATETYPE_MONDAY2;
	static const string DATETYPE_TUESDAY1;
	static const string DATETYPE_TUESDAY2;
	static const string DATETYPE_WENESDAY1;
	static const string DATETYPE_WENESDAY2;
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

