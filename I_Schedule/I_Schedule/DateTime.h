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
	void displayTime();

private:
	int _day;
	int _month;
	int _year;
	int _hours;
	int _mins;
	int _seconds;

	enum DATEKEY{ TODAY, TOMORROW };
};

