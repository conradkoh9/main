#include "Task.h"

const string Task::FIELD_DESCRIPTION = "Description: ";
const string Task::FIELD_STARTDATE = "Start: ";
const string Task::FIELD_ENDDATE = "End: ";
const string Task::FIELD_PRIORITY = "Priority: ";
const string Task::FIELD_STATUS = "Status: ";


const string Task::_FEEDBACK_DESCRIPTION_SET = "DESCRIPTION SET";
const string Task::_FEEDBACK_STARTDATE_SET = "START DATE SET";
const string Task::_FEEDBACK_ENDDATE_SET = "END DATE SET";
const string Task::_FEEDBACK_PRIORITY_SET = "PRIORITY SET";
const string Task::_FEEDBACK_STATUS_SET = "STATUS SET";
const string Task::_FEEDBACK_STANDARD_START_DATE_SET = "STANDARD FORMAT OF START DATE SET";
const string Task::_FEEDBACK_STANDARD_END_DATE_SET = "STAMDARD FORMAT OF END DATE SET";

const string Task::_STATUS_COMPLETE = "Complete";
const string Task::_STATUS_INCOMPLETE = "Incomplete";


Task::Task()
{
	startdate = "";
	description = "";
	priority = "";
	enddate = "";
	status = _STATUS_INCOMPLETE;
	numberOfFields = Smartstring::NUMBER_OF_FIELDS;
}

Task::Task(vector<string> input){
	description = input[Smartstring::FIELD::DESCRIPTION];
	enddate = input[Smartstring::FIELD::ENDDATE];
	startdate = input[Smartstring::FIELD::STARTDATE];
	priority = input[Smartstring::FIELD::PRIORITY];
	status = input[Smartstring::FIELD::STATUS];
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

string Task::SetStatus(string input){
	status = input;
	return _FEEDBACK_STATUS_SET;
}

string Task::SetStandardStartDate(){
	string FormatToBeConverted = startdate;
	standardStart=standardStartdt->ConvertDateTime(FormatToBeConverted);
	return _FEEDBACK_STANDARD_START_DATE_SET;
}


string Task::SetStandardEndDate(){
	string FormatToBeConverted = startdate;
	standardEnd=standardEnddt->ConvertDateTime(FormatToBeConverted);
	return _FEEDBACK_STANDARD_END_DATE_SET;
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

string Task::GetStatus(){
	return status;
}

string Task::GetStandardStartDate(){
	return standardStart;
}

string Task::GetStandardEndDate(){
	return standardEnd;
}

string Task::MarkComplete(){
	status = _STATUS_COMPLETE;
	return status;
}

string Task::ToString(){
	ostringstream out;
	out << FIELD_DESCRIPTION << description << endl;
	out << FIELD_STARTDATE << startdate << endl;
	out << FIELD_ENDDATE << enddate << endl;
	out << FIELD_PRIORITY << priority << endl;
	out << FIELD_STATUS << status;
	return out.str();
}

string Task::ToShortString(){
	string output = "";
	TASKTYPE tasktype = GetType();
	switch (tasktype){
		case(TASKTYPE::DEADLINE) : {
			output = ToDeadlineString();
			break;
		}
		case(TASKTYPE::FLOATING) : {
			output = ToFloatingString();
			break;
		}
		case(TASKTYPE::TIMED) : {
			output = ToTimedString();
			break;
		}
		default:{
			output = ToTimedString();
			break;
		}
	}
	return output;
}

string Task::ToDeadlineString(){
	ostringstream out;
	out << "[" << enddate << "] ";
	out << description;
	return out.str();
}

string Task::ToFloatingString(){
	ostringstream out;
	out << description;
	return out.str();
}

string Task::ToTimedString(){
	ostringstream out;
	out << "[" << startdate << "]";
	out << "[" << enddate << "] ";
	out << description;
	return out.str();
}

string Task::ToTXTString(){
	//this to string method is used in storage to write to txt files
	ostringstream out;
	out << FIELD_DESCRIPTION << description << endl;
	out << FIELD_STARTDATE << startdate << endl;
	out << FIELD_ENDDATE << enddate << endl;
	out << FIELD_PRIORITY << priority << endl;
	out << FIELD_STATUS << status;
	return out.str();
}

string Task::ToCSVString(){
	ostringstream out;
	out << "\"" << description << "\",";
	out << "\"" << startdate << "\",";
	out << "\"" << enddate<< "\",";
	out << "\"" << priority << "\",";
	out << "\"" << status << "\"";
	return out.str();
}

ostream& operator<<(ostream& out, Task& task){
	out << task.ToString();
	return out;
}

Task::TASKTYPE Task::GetType(){     
	if (enddate == "" && startdate == ""){
		return Task::TASKTYPE::FLOATING;
	}
	else if (startdate == "" && enddate!=""){
		return Task::TASKTYPE::DEADLINE;
	}
	else{
		return Task::TASKTYPE::TIMED;
	}
}

bool Task::isContains(string input){
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

bool Task::isNearMatch(string input){
	bool match = false;
	size_t difference;
	size_t tolarent_diff = 3;

	for (int i = 0; i < numberOfFields; ++i){
		if (!match){
			difference = LevenshteinDistance(input, description);
			if (difference <= tolarent_diff)
				match = true;
			}
		}

	return match;
}

size_t Task::LevenshteinDistance(const std::string &s1, const std::string &s2){
	const size_t m(s1.size());
	const size_t n(s2.size());

	if (m == 0) return n;
	if (n == 0) return m;

	size_t *costs = new size_t[n + 1];

	for (size_t k = 0; k <= n; k++) {
		costs[k] = k;
	}

	size_t i = 0;
	for (std::string::const_iterator it1 = s1.begin(); it1 != s1.end(); ++it1, ++i){
		costs[0] = i + 1;
		size_t corner = i;
		size_t j = 0;
		for (std::string::const_iterator it2 = s2.begin(); it2 != s2.end(); ++it2, ++j){
			size_t upper = costs[j + 1];
			if (*it1 == *it2){
				costs[j + 1] = corner;
			}
			else{
				size_t t(upper<corner ? upper : corner);
				costs[j + 1] = (costs[j]<t ? costs[j] : t) + 1;
			}
			corner = upper;
		}
	}

	size_t result = costs[n];
	delete[] costs;

	return result;
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