#include "DateTime.h"

const string DATETYPE_MONDAY1 = "Monday";
const string DATETYPE_MONDAY2 = "Mon";
const string DATETYPE_TUESDAY1 = "Tuesday";
const string DATETYPE_TUESDAY2 = "Tues";
const string DATETYPE_WEDNESDAY1 = "Wednesday";
const string DATETYPE_WEDNESDAY2 = "Wed";
const string DATETYPE_THURSDAY1 = "Thursday";
const string DATETYPE_THURSDAY2 = "Thurs";
const string DATETYPE_FRIDAY1 = "Friday";
const string DATETYPE_FRIDAY2 = "Fri";
const string DATETYPE_SATURDAY1 = "Saturday";
const string DATETYPE_SATURDAY2 = "Sat";
const string DATETYPE_SUNDAY1 = "Sunday";
const string DATETYPE_SUNDAY2 = "Sun";

const string TIMETYPE_AM = "am";
const string TIMETYPE_PM = "pm";


DateTime::DateTime()
{
}

DateTime::DateTime(string input){	
}

DateTime::~DateTime(){
}

string DateTime::Now(){
	time_t now = time(0); //raw time -> this is generally implemented as an integer offset from 00:00hours, jan1, 2970 UTC. This leads me to the assumption
	//that you can use (time_t time + 60) to offset by 1 minute, (time_t time + 3600) to offset by 1 hour etc
	struct tm timeinfo; //this struct is defined by the system
	localtime_s(&timeinfo, &now); //converts the raw time into a struct
	char output[80];
	strftime(output, 80, "%I:%M%p", &timeinfo); //to refer to more ways to access time format, refer to http://cplusplus.com/reference/ctime/strftime/
	//under strftime, yellow boxes indicate certain formats that are not supported on visual studio
	return output;
}

string DateTime::Today(){
	time_t now = time(0);
	struct tm timeinfo;
	localtime_s(&timeinfo, &now);
	char output[80];
	strftime(output, 80, "%d/%m/%Y", &timeinfo);
	return output;
}



string DateTime::ConvertDateTime(string input){
	string task_date;
	string task_time;
	string output;
	
	GetType(input); //this method is used to classify the input info into Date and Time for conversion 
	task_date = ConvertDate(); //convert user's date to the proper one
	task_time = ConvertTime();  //convert time to proper one 
	
	output = task_date + task_time;

	return output;
}


string DateTime::GetType(string input){


	//here i want to use the find. function to search whether the input contains any date or time keyword
	string feedback = "";
	return feedback;

}

string DateTime::ConvertDate(){
	//make use of today() function, compare and add more days to get the supposed date 
	string feedback = "";
	return feedback;
}

string DateTime::ConvertTime(){
	//this function is simply change the format e.g if they key in 2pm, here we change it to 0200pm
	string feedback = "";
	return feedback;
}

bool DateTime::CompareDateTime(string input1, string input2){
	return true;
}




