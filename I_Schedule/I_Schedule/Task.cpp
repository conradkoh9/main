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
const string Task::_FEEDBACK_DEFAULTDATE_SET = "DEFAULT END DATE SET";
const string Task::_FEEDBACK_STANDARD_START_DATE_SET = "STANDARD FORMAT OF START DATE SET";
const string Task::_FEEDBACK_STANDARD_END_DATE_SET = "STAMDARD FORMAT OF END DATE SET";


const string Task::_STATUS_COMPLETE = "Complete";
const string Task::_STATUS_INCOMPLETE = "Incomplete";

const string Task::_rtfcolorredprefix = "\\cf2 ";
const string Task::_rtfcolorredsuffix = "\\cf0 ";

const int Task::numberOfFields = Smartstring::NUMBER_OF_FIELDS;

Task::Task()
{
	startDateTime = "";
	description = "";
	priority = "";
	endDateTime = "";
	startDateTime = "";
	startdate = "";
	enddate = "";
	starttime = "";
	endtime = "";
	status = _STATUS_INCOMPLETE;
}

Task::Task(vector<string> input){

	description = input[Smartstring::FIELD::DESCRIPTION];
	priority = input[Smartstring::FIELD::PRIORITY];
	status = input[Smartstring::FIELD::STATUS];
	standardStartdt = new DateTime(input[Smartstring::FIELD::STARTDATE]);
	standardEnddt = new DateTime(input[Smartstring::FIELD::ENDDATE]);

	startDateTime = standardStartdt->Standardized();
	endDateTime = standardEnddt->Standardized();
	//set default enddate if timed task
	if (startDateTime != "" && endDateTime == "")
	{
		standardEnddt = standardStartdt->GetDefaultEndDate();
		endDateTime = standardEnddt->Standardized();
		enddate = standardEnddt->GetDate();
		endtime = standardStartdt->GetTime();
	}
	//end set default enddate if timed task

	startdate = standardStartdt->GetDateWithoutYear();
	starttime = standardStartdt->GetTime();
	enddate = standardEnddt->GetDateWithoutYear();
	endtime = standardEnddt->GetTime();

	if (status == ""){
		status = _STATUS_INCOMPLETE;
	}

	//this takes care of the cases here the user inputs start at 5pm and end at 6pm but doesn't specify the date
	if (standardStartdt->isTimeSet && !standardStartdt->isDateSet){
		startdate = standardStartdt->GetDateWithoutYear();
		startDateTime = standardStartdt->GetTime() + " on " + standardStartdt->GetDate();
	}
	if (standardEnddt->isTimeSet && !standardEnddt->isDateSet){
		enddate = startdate;
		endDateTime = standardEnddt->GetTime() + " on " + standardStartdt->GetDate();
	}
}

Task::Task(Task* task){
	startDateTime = "";
	startdate = "";
	starttime = "";
	description = "";
	priority = "";
	endDateTime = "";
	enddate = "";
	endtime = "";

	status = _STATUS_INCOMPLETE;

	if (!task == NULL){
		description = task->GetDescription();
		startDateTime = task->GetStartDateTime();
		endDateTime = task->GetEndDateTime();
		priority = task->GetPriority();
		status = task->GetStatus();
		startdate = task->GetStartDate();
		enddate = task->GetEndDate();
		starttime = task->GetStartTime();
		endtime = task->GetEndTime();
	}
}

Task::~Task()
{
}

string Task::Edit(vector<string> newinfo){
	for (int i = 0; i < newinfo.size(); ++i){
		if (newinfo[i] != ""){
			if (newinfo[i] == "-"){
				newinfo[i] = "";
			}
			switch (i){
			case Smartstring::FIELD::DESCRIPTION:{
				SetDescription(newinfo[i]);
				break;
			}
			case Smartstring::FIELD::STARTDATE:{
				SetStartDateTime(newinfo[i]);
				break;
			}
			case Smartstring::FIELD::ENDDATE:{
				SetEndDateTime(newinfo[i]);
				break;
			}
			case Smartstring::FIELD::PRIORITY:{
				SetPriority(newinfo[i]);
				break;
			}
			}
		}
	}
	return ToString();
}

string Task::SetDescription(string input){
	description = input;
	return _FEEDBACK_DESCRIPTION_SET;
}

//@author A0119491B
string Task::SetStartDateTime(string dt){
	startDateTime = dt;
	standardStartdt = new DateTime(startDateTime);
	startDateTime = standardStartdt->Standardized();
	startdate = standardStartdt->GetDateWithoutYear();
	starttime = standardStartdt->GetTime();
	return _FEEDBACK_STARTDATE_SET;
}

//@author A0119491B
string Task::SetEndDateTime(string dt){
	endDateTime = dt;
	standardEnddt = new DateTime(endDateTime);
	endDateTime = standardEnddt->Standardized();
	enddate = standardEnddt->GetDateWithoutYear();
	endtime = standardEnddt->GetTime();
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

//@author A0119491B
string Task::SetDefaultEnddate(){
	if (startDateTime != "" && endDateTime == "")
	{
		standardEnddt = standardStartdt->GetDefaultEndDate();
		endDateTime = standardEnddt->Standardized();
		enddate = standardEnddt->GetDate();
		endtime = standardStartdt->GetTime();
	}
	return _FEEDBACK_DEFAULTDATE_SET;
}

//@author A0119491B
string Task::MarkComplete(){
	status = _STATUS_COMPLETE;
	return status;
}

//@author A0119491B
string Task::GetDescription(){
	return description;
}

//@author A0119491B
string Task::GetPriority(){
	return priority;
}

//@author A0119491B
string Task::GetStartDateTime(){
	return startDateTime;
}

//@author A0119491B
string Task::GetStartDate(){
	return startdate;
}

//@author A0119491B
string Task::GetStartTime(){
	return starttime;
}

//@author A0119491B
string Task::GetEndDateTime(){
	return endDateTime;
}

//@author A0119491B
string Task::GetEndDate(){
	return enddate;
}
//@author A0119491B
string Task::GetEndTime(){
	return endtime;
}


//@author A0119491B
string Task::GetStatus(){
	return status;
}


string Task::ToString(){
	ostringstream out;
	out << FIELD_DESCRIPTION << description << endl;
	out << FIELD_STARTDATE << startDateTime << endl;
	out << FIELD_ENDDATE << endDateTime << endl;
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

//@author A0099303A
string Task::ToDeadlineString(){
	ostringstream out;
	out << "[" << enddate;
	if (standardEnddt->isTimeSet){
		out << "," << endtime;
	}
	out << "] ";
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

	if (standardEnddt->IsEarlierThan(*standardStartdt)){

		out << "[" << startdate;
		if (standardStartdt->isTimeSet){
			out << "," << starttime;
		}
		out << "]";
		out << "[" << _rtfcolorredprefix << enddate << _rtfcolorredsuffix;
		if (standardEnddt->isTimeSet){
			out << "," << _rtfcolorredprefix << endtime << _rtfcolorredsuffix;
		}
		out << "] ";
		out << description;

	}
	else{

		out << "[" << startdate;
		if (standardStartdt->isTimeSet){
			out << "," << starttime;
		}
		out << "]";
		out << "[" << enddate;
		if (standardEnddt->isTimeSet){
			out << "," << endtime;
		}
		out << "] ";
		out << description;

	}

	return out.str();
}

string Task::ToTXTString(){
	//this to string method is used in storage to write to txt files
	ostringstream out;
	out << FIELD_DESCRIPTION << description << endl;
	out << FIELD_STARTDATE << startDateTime << endl;
	out << FIELD_ENDDATE << endDateTime << endl;
	out << FIELD_PRIORITY << priority << endl;
	out << FIELD_STATUS << status;
	return out.str();
}

string Task::ToCSVString(){
	ostringstream out;
	out << "\"" << description << "\",";
	out << "\"" << startDateTime << "\",";
	out << "\"" << endDateTime << "\",";
	out << "\"" << priority << "\",";
	out << "\"" << status << "\"";
	return out.str();
}

string Task::ToDatelessString(){
	string output = "";
	TASKTYPE tasktype = GetType();
	switch (tasktype){
	case(TASKTYPE::DEADLINE) : {
		output = ToDatelessDeadlineString();
		break;
	}
	case(TASKTYPE::FLOATING) : {
		output = ToDatelessFloatingString();
		break;
	}
	case(TASKTYPE::TIMED) : {
		output = ToDatelessTimedString();
		break;
	}
	default:{
		output = ToDatelessTimedString();
		break;
	}
	}
	return output;
}

string Task::ToDatelessDeadlineString(){
	ostringstream out;
	out << description;
	return out.str();
}

string Task::ToDatelessFloatingString(){
	ostringstream out;
	out << description;
	return out.str();
}

string Task::ToDatelessTimedString(){

	ostringstream out;
	out << "[" << enddate;
	if (standardEnddt->isTimeSet){
		out << "," << endtime;
	}
	out << "] ";
	out << description;
	return out.str();
}



ostream& operator<<(ostream& out, Task& task){
	out << task.ToString();
	return out;
}

//@author A0119491B
Task::TASKTYPE Task::GetType(){     
	if (endDateTime == "" && startDateTime == ""){
		return Task::TASKTYPE::FLOATING;
	}
	else if (startDateTime == "" && endDateTime!=""){
		return Task::TASKTYPE::DEADLINE;
	}
	else{
		return Task::TASKTYPE::TIMED;
	}
}

//@author A0119491B
bool Task::isContains(string input){
	bool found = false;

	//search start date and end date
	found = isContainInDate(input);  // need a method to get date without time 
	//search priority
	if (!found){
		found = isContainPriority(input);
	}
	//search description
	if (!found){
		found = isContainDescription(input);
	}

	return found;
}

//@author A0119491B
bool Task::isContainInDate(string input){
	DateTime* dt = new DateTime(input);
	int pos_start, pos_end; 
	if (dt->isValidFormat){
		string datetime = dt->Standardized();
		pos_start = startDateTime.find(datetime);
		pos_end = endDateTime.find(datetime);
			if (pos_start != string::npos || pos_end != string::npos){
				return true;
			}
	}
	return false;
}

//@author A0119491B
bool Task::isContainPriority(string input){
	string keyword, prio;
	istringstream in(input);
	in >> keyword;
	in >> prio;
	if (keyword == "priority" && prio == priority){
		return true;
	}
	return false;
}

//@author A0119491B
bool Task::isContainDescription(string input){
	vector<string> token_description;
	vector<string> token_input;
	Smartstring* smartstring_in = new Smartstring(input);
	Smartstring* smartstring_des = new Smartstring(description);
	bool found;
	int pos;
	
	token_input = smartstring_in->Tokenize(" ");
	token_description = smartstring_des->Tokenize(" ");
	for (int i = 0; i < token_input.size(); i++){   //tokenize the input. search the token one by one to see if these words all in the description
		found = false;
		for (int j = 0; j < token_description.size(); j++){ //tokenize the description. compare each token of description with each token of the input
				pos = token_description[j].find(token_input[i]);
				if (pos != string::npos || isNearMatch(token_input[i], token_description[j])){
					found = true;
				}
		}

		if (!found){  //after comparison, the token of input is not contained in description. then return false
			return false;
		}
	}

	return true;

}

//@auhtor A0119491B
bool Task::isNearMatch(string input, string des){
	bool match = false;
	size_t difference;
	size_t tolarent_diff = 2; //Only two wrong letters in one word can be accepted  

	for (int i = 0; i < numberOfFields; ++i){
		if (!match){
			difference = LevenshteinDistance(input, des);
			if (difference <= tolarent_diff)
				match = true;
			}
		}

	return match;
}

//@author A0119491B
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

