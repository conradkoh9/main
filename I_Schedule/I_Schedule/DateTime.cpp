#include "DateTime.h"

const string DateTime::DATETYPE_MONDAY1 = "Monday";
const string DateTime::DATETYPE_MONDAY2 = "Mon";
const string DateTime::DATETYPE_MONDAY3 = "monday";
const string DateTime::DATETYPE_MONDAY4 = "mon";
const string DateTime::DATETYPE_TUESDAY1 = "Tuesday";
const string DateTime::DATETYPE_TUESDAY2 = "Tues";
const string DateTime::DATETYPE_TUESDAY3 = "tuesday";
const string DateTime::DATETYPE_TUESDAY4 = "tues";
const string DateTime::DATETYPE_WEDNESDAY1 = "Wednesday";
const string DateTime::DATETYPE_WEDNESDAY2 = "Wed";
const string DateTime::DATETYPE_WEDNESDAY3 = "wednesday";
const string DateTime::DATETYPE_WEDNESDAY4 = "wed";
const string DateTime::DATETYPE_THURSDAY1 = "Thursday";
const string DateTime::DATETYPE_THURSDAY2 = "Thurs";
const string DateTime::DATETYPE_THURSDAY3 = "thursday";
const string DateTime::DATETYPE_THURSDAY4 = "thurs";
const string DateTime::DATETYPE_FRIDAY1 = "Friday";
const string DateTime::DATETYPE_FRIDAY2 = "Fri";
const string DateTime::DATETYPE_FRIDAY3 = "friday";
const string DateTime::DATETYPE_FRIDAY4 = "fri";
const string DateTime::DATETYPE_SATURDAY1 = "Saturday";
const string DateTime::DATETYPE_SATURDAY2 = "Sat";
const string DateTime::DATETYPE_SATURDAY3 = "saturday";
const string DateTime::DATETYPE_SATURDAY4 = "sat";
const string DateTime::DATETYPE_SUNDAY1 = "Sunday";
const string DateTime::DATETYPE_SUNDAY2 = "Sun";
const string DateTime::DATETYPE_SUNDAY3 = "sunday";
const string DateTime::DATETYPE_SUNDAY4 = "sun";
const string DateTime::TIMETYPE_AM = "am";
const string DateTime::TIMETYPE_PM = "pm";

bool DateTime::isInitialized = false;
int DateTime::numberOfDateType;
int DateTime::numberOfTimeType;
vector<string> DateTime::dateType;
vector<string> DateTime::timeType;

//==========================================================
//Methods suggested by Conrad
//==========================================================

DateTime::DateTime(){
	Initialize();
}

DateTime::DateTime(string input){
	unformattedDateTime = input;
	Initialize();
}

DateTime::~DateTime(){
}


string DateTime::Standardized(){
	string dbg = unformattedDateTime;
	Smartstring input_s(unformattedDateTime);
	vector<string> tokens = input_s.Tokenize(" ");
	string date;
	string time;
	int size = tokens.size();

	if (size > 3){
		isValidFormat = false;
		return unformattedDateTime;
	}
	else{
		switch (size){
			case 0:{
				return unformattedDateTime;
				break;
			}
			case 1:{
				//this case assumes only either date or time has been entered
				if (IsValidDayDate(tokens[0])){
					formattedDateTime = StandardizeDayDate(tokens[0]);
				}
				else{
					if (IsValidTime(tokens[0])){
						formattedDateTime = StandardizeTime(tokens[0]);
					}
					else{
						formattedDateTime = unformattedDateTime;
					}
				}
				break;
			}

			case 3:{
				string prefix;
				string suffix;
				if (tokens[1] == "at"){
					//at implies day prefix and time suffix. i.e. "thursday at 5pm" and not "5pm at thursday"
					if (IsValidDayDate(tokens[0])){
						date = StandardizeDayDate(tokens[0]);
						
					}
					else{
						date = tokens[0];
					}
					if (IsValidTime(tokens[2])){
						time = StandardizeTime(tokens[2]);
					}
					else{
						time = tokens[2];
					}
					
				}
				else{
					if (tokens[1] == "on"){
						//on implex time prefix and day suffix. i.e. "5pm on friday" and not "friday on 5pm"
						if (IsValidDayDate(tokens[2])){
							date = StandardizeDayDate(tokens[2]);
						}
						else{
							date = tokens[2];
						}
						if (IsValidTime(tokens[0])){
							time = StandardizeTime(tokens[0]);
						}
						else{
							time = tokens[0];
						}
					}
				}
				formattedDateTime = time + " on " + date;
				break;
			}

			default: {
				formattedDateTime = unformattedDateTime;
				break;
			}
		}
	}

	return formattedDateTime;
}

string DateTime::StandardizeDayDate(string input){
	string output = input;
	if (IsValidDay(input)){
		output = StandardizeDay(input);
	}
	else{
		if (IsValidDate(input)){
			output = StandardizeDate(input);
		}
	}
	return output;
}

string DateTime::StandardizeDate(string input){
	//this function assumes there are 2 / delimiters
	string output;
	Smartstring input_s(input);
	vector<string> tokens = input_s.Tokenize("/");
	assert(tokens.size() == 3);
	//check if the ordering of month and date is explicitly wrong
	int day = atoi(tokens[0].c_str());
	int month = atoi(tokens[1].c_str());
	if (month > 12){
		if (day > 12){
			//both day and month exceed 12, do nothing
		}
		else{
			//only one exceeds 12
			int temp = month;
			month = day;
			day = temp;
		}
	}

	ostringstream monthout;
	monthout << setw(2) << setfill('0') << month;
	ostringstream dayout;
	dayout << setw(2) << setfill('0') << day;

	output = dayout.str() + "/" + monthout.str() + "/" + tokens[2];
	return output;
}

string DateTime::StandardizeDay(string input){
	string output;
	
	//when input is a day
	time_t now = time(0);
	int offset;

	DAY endday = GetDayEnum(input); //need to check if output is valid
	string today = GetDayFromTime(now);
	DAY startday = GetDayEnum(today); //need to check if output is valid
	if (endday != DAY::INVALID && startday != DAY::INVALID){
		int offset_in_days = CalculateOffset(startday, endday);
		time_t timeresult = OffsetByDay(now, offset_in_days);
		output = GetStandardDate(timeresult);
	}
	else{
		output = input;
	}
	return output;
}

string DateTime::StandardizeTime(string input){
	string output;
	string result;
	string period;
	int found;
	int hour;
	int mins;

	//remove pm and am keywords
	found = input.find("pm");
	if (found != string::npos){
		period = "pm";
		result = input.substr(0, found);
	}
	found = result.find("am");
	if (found != string::npos){
		period = "am";
		result = result.substr(0, found);
	}
	//end remove pm and am keywords

	//check if time format specifies minutes
	found = result.find_first_of(":");
	if (found != string::npos){
		//getting hour
		string hour_s = result.substr(0, found);
		hour = stoi(hour_s.c_str());
		//getting mins
		int length = result.length();
		string min_s = result.substr(found+1, length - 1);
		mins = stoi(min_s.c_str());
	}
	else{
		//attempt to convert string to hour in case: 5pm as input
		//note that this converts invalid strings to 0 so the time will display as 00:00 if it is invalid which may seem like a valid time
		if (result.length() <= 2){
			hour = atoi(result.c_str());
			mins = 0;
		}
	}

	if (hour > 12){
		//if the hour is in 24 hour format
		hour = hour % 12;
		period = "pm";
	}

	ostringstream minout;
	minout << setw(2) << setfill('0') << mins;
	ostringstream hourout;
	hourout << setw(2) << setfill('0') << hour;

	output = hourout.str() + ":" + minout.str() + period;
	return output;
}

bool DateTime::IsValidDayDate(string input){
	if (IsValidDay(input) || IsValidDate(input)){
		return true;
	}
	else{
		return false;
	}
}

bool DateTime::IsValidDate(string input){
	string dbg = input;
	int found = 0;
	int startIdx = 0;
	int count = 0;
	bool isValid = false;
	while (found != string::npos){
		found = input.find_first_of("/", startIdx);
		if (found != string::npos){
			count++;
		}
		startIdx = found + 1;
	}


	if (count == 2){
		isValid = true;
	}

	return isValid;
}

bool DateTime::IsValidDay(string input){

	bool isValid = false;
	vector<string>::iterator iter;
	for (iter = dateType.begin(); iter != dateType.end(); ++iter){
		if (*iter == input){
			isValid = true;
		}
	}
	return isValid;
}

bool DateTime::IsValidTime(string input){
	string dbg = input;
	bool isValid = false;
	string result = input;
	int hour;
	int mins;

	int found = input.find("pm");
	if (found != string::npos){
		result = input.substr(0, found);
	}
	found = result.find("am");
	if (found != string::npos){
		result = result.substr(0, found);
	}

	found = result.find_first_of(":");
	if (found != string::npos){
		//getting hour
		string hour_s = result.substr(0, found);
		hour = atoi(hour_s.c_str());
		//getting mins
		int length = result.length();
		string min_s = result.substr(found, length - 1);
		mins = atoi(min_s.c_str());
		if (hour >= 0 && hour < 24 && mins >= 0 && mins < 60){
			isValid = true;
		}
	}
	else{
		//attempt to convert string to hour in case: 5pm as input
		if (result.length() < 3){
			hour = atoi(result.c_str());
			mins = 0;
			isValid = true;
		}
	}
	
	return isValid;
}

DateTime::DAY DateTime::GetDayEnum(string input){
	if (input == DATETYPE_SUNDAY1 || input == DATETYPE_SUNDAY2 || input == DATETYPE_SUNDAY3 || input == DATETYPE_SUNDAY4){
		return DAY::SUNDAY;
	}
	if (input == DATETYPE_MONDAY1 || input == DATETYPE_MONDAY2 || input == DATETYPE_MONDAY3 || input == DATETYPE_MONDAY4){
		return DAY::MONDAY;
	}
	if (input == DATETYPE_TUESDAY1 || input == DATETYPE_TUESDAY2 || input == DATETYPE_TUESDAY3 || input == DATETYPE_TUESDAY4){
		return DAY::TUESDAY;
	}
	if (input == DATETYPE_WEDNESDAY1 || input == DATETYPE_WEDNESDAY2 || input == DATETYPE_WEDNESDAY3 || input == DATETYPE_WEDNESDAY4){
		return DAY::WEDNESDAY;
	}
	if (input == DATETYPE_THURSDAY1 || input == DATETYPE_THURSDAY2 || input == DATETYPE_THURSDAY3 || input == DATETYPE_THURSDAY4){
		return DAY::THURSDAY;
	}
	if (input == DATETYPE_FRIDAY1 || input == DATETYPE_FRIDAY2 || input == DATETYPE_FRIDAY3 || input == DATETYPE_FRIDAY4){
		return DAY::FRIDAY;
	}
	if (input == DATETYPE_SATURDAY1 || input == DATETYPE_SATURDAY2 || input == DATETYPE_SATURDAY3 || input == DATETYPE_SATURDAY4){
		return DAY::SATURDAY;
	}

	return DAY::INVALID;
}

int DateTime::CalculateOffset(DAY startday, DAY endday){
	int result;

	if (startday > endday){
		//this means that we have crossed a saturday, and the enum is reset
		result = endday - startday + 7;
	}
	else{
		result = endday - startday;
	}

	return result;
}

string DateTime::GetDayFromTime(time_t time){
	struct tm timeinfo;
	localtime_s(&timeinfo, &time);
	char output[80];
	strftime(output, 80, "%A", &timeinfo);
	return output;
}

string DateTime::GetStandardDate(time_t time){
	struct tm timeinfo;
	localtime_s(&timeinfo, &time);
	char output[80];
	strftime(output, 80, "%d/%m/%Y", &timeinfo);
	return output;
}

string DateTime::GetStandardTime(time_t time){
	struct tm timeinfo;
	localtime_s(&timeinfo, &time);
	char output[80];
	strftime(output, 80, "%I:%M%p", &timeinfo);
	return output;
}


time_t DateTime::OffsetByDay(time_t timeReference, time_t offset_in_days){
	time_t output;
	time_t offset_in_seconds = offset_in_days * 24 * 60 * 60;
	output = timeReference + offset_in_seconds;
	return output;
}

//==========================================================
//End section Methods suggested by Conrad
//==========================================================

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
	string day;
	string time;
	string description;

	description = input;

	if (isDateType(description)){

	}

	if (isTimeType(description)){

	}



	string feedback = "";
	return feedback;

}


bool DateTime::isDateType(string input){
	string userDateTime = input;

	for (int i = 0; i < numberOfDateType; i++){
		size_t found = userDateTime.find(dateType[i]);

		if (found != string::npos){
			return true;
		}
	}

	return false;
}

bool DateTime::isTimeType(string input){
	string userDateTime = input;

	for (int i = 0; i < numberOfTimeType; i++){
		size_t found = userDateTime.find(timeType[i]);

		if (found != string::npos){
			return true;
		}
	}

	return false;
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

void DateTime::Initialize(){
	if (!isInitialized){
		dateType.push_back(DATETYPE_MONDAY1);
		dateType.push_back(DATETYPE_MONDAY2);
		dateType.push_back(DATETYPE_MONDAY3);
		dateType.push_back(DATETYPE_MONDAY4);
		dateType.push_back(DATETYPE_TUESDAY1);
		dateType.push_back(DATETYPE_TUESDAY2);
		dateType.push_back(DATETYPE_TUESDAY3);
		dateType.push_back(DATETYPE_TUESDAY4);
		dateType.push_back(DATETYPE_WEDNESDAY1);
		dateType.push_back(DATETYPE_WEDNESDAY2);
		dateType.push_back(DATETYPE_WEDNESDAY4);
		dateType.push_back(DATETYPE_WEDNESDAY3);
		dateType.push_back(DATETYPE_THURSDAY1);
		dateType.push_back(DATETYPE_THURSDAY2);
		dateType.push_back(DATETYPE_THURSDAY3);
		dateType.push_back(DATETYPE_THURSDAY4);
		dateType.push_back(DATETYPE_FRIDAY1);
		dateType.push_back(DATETYPE_FRIDAY2);
		dateType.push_back(DATETYPE_FRIDAY3);
		dateType.push_back(DATETYPE_FRIDAY4);
		dateType.push_back(DATETYPE_SATURDAY1);
		dateType.push_back(DATETYPE_SATURDAY2);
		dateType.push_back(DATETYPE_SATURDAY3);
		dateType.push_back(DATETYPE_SATURDAY4);
		dateType.push_back(DATETYPE_SUNDAY1);
		dateType.push_back(DATETYPE_SUNDAY2);
		dateType.push_back(DATETYPE_SUNDAY3);
		dateType.push_back(DATETYPE_SUNDAY4);
		timeType.push_back(TIMETYPE_AM);
		timeType.push_back(TIMETYPE_PM);

		numberOfDateType = dateType.size();
		numberOfTimeType = timeType.size();
		isInitialized = true;
	}

}



