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
const string Task::_FEEDBACK_SDATE_SET = "START DATE SET";
const string Task::_FEEDBACK_EDATE_SET = "END DATE SET";
const string Task::_FEEDBACK_STIME_SET = "START TIME SET";
const string Task::_FEEDBACK_ETIME_SET = "END TIME SET";


const string Task::_STATUS_COMPLETE = "Complete";
const string Task::_STATUS_INCOMPLETE = "Incomplete";

const int Task::numberOfFields = Smartstring::NUMBER_OF_FIELDS;

Task::Task()
{
	startdate = "";
	description = "";
	priority = "";
	enddate = "";
	sdate = "";
	edate = "";
	stime = "";
	etime = "";
	status = _STATUS_INCOMPLETE;
}

Task::Task(vector<string> input){

	standardStartdt = new DateTime(input[Smartstring::FIELD::STARTDATE]);
	standardEnddt = new DateTime(input[Smartstring::FIELD::ENDDATE]);
	standardStart = standardStartdt->Standardized();
	standardEnd = standardEnddt->Standardized();

	description = input[Smartstring::FIELD::DESCRIPTION];
	startdate = standardStart;
	enddate = standardEnd;
	priority = input[Smartstring::FIELD::PRIORITY];
	status = input[Smartstring::FIELD::STATUS];
	if (status == ""){
		status = _STATUS_INCOMPLETE;
	}
}

Task::Task(Task* task){
	startdate = "";
	description = "";
	priority = "";
	enddate = "";
	sdate = "";
	edate = "";
	stime = "";
	etime = "";
	status = _STATUS_INCOMPLETE;

	if (!task == NULL){
		description = task->GetDescription();
		startdate = task->GetStartDate();
		enddate = task->GetEndDate();
		priority = task->GetPriority();
		status = task->GetStatus();
		sdate = task->GetSDate();
		edate = task->GetEDate();
		stime = task->GetSTime();
		etime = task->GetETime();
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
					SetStartDate(newinfo[i]);
					break;
				}
				case Smartstring::FIELD::ENDDATE:{
					SetEndDate(newinfo[i]);
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

string Task::SetStartDate(string input){
	DateTime dt(input);
	startdate = dt.Standardized();
	//startdate = input;
	return _FEEDBACK_STARTDATE_SET;
}

string Task::SetEndDate(string input){
	DateTime dt(input);
	enddate = dt.Standardized();
	//enddate = input;
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

string Task::SetSDate(){
	int sPos;
	sPos = startdate.find_first_of("/");
	if (sPos != string::npos){
		sPos = sPos - 2;
		sdate = startdate.substr(sPos);
		return _FEEDBACK_SDATE_SET;
	}
	return "";
}

string Task::SetEDate(){
	int sPos;
	sPos = enddate.find_first_of("/");
	if (sPos != string::npos){
		sPos = sPos - 2;
		edate = enddate.substr(sPos);
		return _FEEDBACK_EDATE_SET;
	}
	return "";
}

string Task::SetSTime(){
	int sPos;
	sPos = stime.find_first_of(":");
	if (sPos != string::npos){
		sPos = sPos - 2;
		stime = stime.substr(sPos);
		return _FEEDBACK_STIME_SET;
	}
	return "";
}

string Task::SetETime(){
	int sPos;
	sPos = etime.find_first_of(":");
	if (sPos != string::npos){
		sPos = sPos - 2;
		etime = etime.substr(sPos);
		return _FEEDBACK_ETIME_SET;
	}
	return "";
	return "";
}

string Task::SetDefaultEnddate(){
	if (standardStart != "" && standardEnd == "")
	{
		standardEnd = standardStartdt-> GetDefaultDuration();
	}
	return _FEEDBACK_DEFAULTDATE_SET;
}


string Task::GetDescription(){
	return description;
}

string Task::GetStartDate(){
	string d1 = startdate;
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

string Task::GetSDate(){
	return sdate;
}

string Task::GetEDate(){
	return edate;
}

string Task::GetSTime(){
	return stime;
}

string Task::GetETime(){
	return etime;
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

//@author A0099303A
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
	out << "[" << enddate << "] ";
	out << description;
	return out.str();
}



ostream& operator<<(ostream& out, Task& task){
	out << task.ToString();
	return out;
}

//@author A0119491B
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
	if (dt->isValidFormat){
		string datetime = dt->Standardized();
		if (datetime == startdate || datetime == enddate){
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
	token_input = smartstring_in->Tokenize(" ");
	token_description = smartstring_des->Tokenize(" ");
	for (int i = 0; i < token_input.size(); i++){   //tokenize the input. search the token one by one to see if these words all in the description
		found = false;
		for (int j = 0; j < token_description.size(); j++){ //tokenize the description. compare each token of description with each token of the input
			if (token_input[i] == token_description[j] || isNearMatch(token_input[i], token_description[j])){
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
	size_t tolarent_diff = 3;

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

//author A0119513L
bool Task::isFloating(){
	bool floating = false;
	if (enddate == "" && startdate == "")
		floating = true;
	return floating;
}

//author A0119513L	
bool Task::isDeadline(){
	bool deadline = false;
	if (enddate != "" && startdate == "")
		deadline = true;
	return deadline;
}

//@author A0119513L
bool Task::isTimed(){
	bool timed = false;
	if (enddate != "" && startdate != "")
		timed = true;
	return timed;
}