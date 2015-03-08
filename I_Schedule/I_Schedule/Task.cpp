#include "Task.h"

const string Task::FIELD_DESCRIPTION = "Description: ";
const string Task::FIELD_STARTDATE = "Start: ";
const string Task::FIELD_ENDDATE = "End: ";
const string Task::FIELD_PRIORITY = "Priority: ";


const string Task::_FEEDBACK_DESCRIPTION_SET = "DESCRIPTION SET";
const string Task::_FEEDBACK_STARTDATE_SET = "START DATE SET";
const string Task::_FEEDBACK_ENDDATE_SET = "END DATE SET";
const string Task::_FEEDBACK_PRIORITY_SET = "PRIORITY SET";

Task::Task()
{
	startdate = "";
	description = "";
	priority = "";
	enddate = "";
	numberOfFields = Smartstring::NUMBER_OF_FIELDS;
}

Task::Task(vector<string> input){
	description = input[Smartstring::FIELD::DESCRIPTION];
	enddate = input[Smartstring::FIELD::ENDDATE];
	startdate = input[Smartstring::FIELD::STARTDATE];
	priority = input[Smartstring::FIELD::PRIORITY];
	numberOfFields = Smartstring::NUMBER_OF_FIELDS;
}


Task::~Task()
{
}

string Task::SetDescription(string input){
	description = input;
	return _FEEDBACK_DESCRIPTION_SET;
}

string Task::SetStartDate(string input){
	startdate = input;
	return _FEEDBACK_STARTDATE_SET;
}

string Task::SetEndDate(string input){
	enddate = input;
	return _FEEDBACK_ENDDATE_SET;
}

string Task::SetPriority(string input){
	priority = input;
	return _FEEDBACK_PRIORITY_SET;
}

string Task::GetDescription(){
	return description;
}

string Task::GetStartDate(){
	return startdate;
}

string Task::GetEndDate(){
	return enddate;
}

string Task::GetPriority(){
	return priority;
}

string Task::ToString(){
	ostringstream out;
	out << FIELD_DESCRIPTION << description << endl;
	out << FIELD_STARTDATE << startdate << endl;
	out << FIELD_ENDDATE << enddate << endl;
	out << FIELD_PRIORITY << priority;
	return out.str();
}

ostream& operator<<(ostream& out, Task& task){
	out << task.ToString();
	return out;
}
