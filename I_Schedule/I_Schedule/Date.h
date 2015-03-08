#pragma once
#include <string>
using namespace std;
class Date
{
public:
	Date();
	Date(string input);
	~Date();
	string Now();

private:
	int _day;
	int _month;
	int _year;
	int _hours;
	int _mins;
	int _seconds;

	enum DATEKEY{TODAY, TOMORROW};
};

