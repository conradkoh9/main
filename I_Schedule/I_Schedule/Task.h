#pragma once
#include <string>
using namespace std;

class Task
{
public:
	Task();
	~Task();
	
	string date;
	string desription;
	string priority;
	string duedate;
	string ToString();
	string SetDate();
	string SetDescription();
	string SetPriority();
	string SetDueDate();

};

