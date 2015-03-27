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

string Task::ToShortString(){
	ostringstream out;
	out << description << "; ";
	out << startdate << "; ";
	out << enddate << "; ";
	out << priority;
	return out.str();
}

ostream& operator<<(ostream& out, Task& task){
	out << task.ToString();
	return out;
}

Task::TASKTYPE Task::GetType(){     
	if (enddate == "" && startdate == ""){
		return Task::TASKTYPE::TIMED;
	}
	else if (startdate == "" && enddate.size()>0){
		return Task::TASKTYPE::DEADLINE;
	}
	else{
		return Task::TASKTYPE::FLOATING;
	}
}

bool Task::Contains(string input){
	bool found = false;
	int pos;
	vector<string> taskVect;
	//initialization 
	for (int fields = 0; fields < numberOfFields; fields++){
		taskVect.push_back("");
	}
	taskVect[Smartstring::FIELD::DESCRIPTION] = description;
	taskVect[Smartstring::FIELD::STARTDATE] = startdate;
	taskVect[Smartstring::FIELD::ENDDATE] = enddate;
	taskVect[Smartstring::FIELD::PRIORITY] = priority;

	//end initialization
	for (int i = 0; i < numberOfFields; ++i){
		if (!found){
			pos = taskVect[i].find(input);
			if (pos != string::npos){
				found = true;
			}
		}
	}
	return found;
}


bool Task::isFloating(){
	bool floating = false;
	if (enddate == "" && startdate == "")
		floating = true;
	return floating;
}

bool Task::isDeadline(){
	bool deadline = false;
	if (enddate != "" && startdate == "")
		deadline = true;
	return deadline;
}

bool Task::isTimed(){
	bool timed = false;
	if (enddate != "" && startdate != "")
		timed = true;
	return timed;
}