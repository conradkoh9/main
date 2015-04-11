//@author A0094213M
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
const string DateTime::DATETYPE_TODAY1 = "today";
const string DateTime::DATETYPE_TOMORROW1 = "tomorrow";
const string DateTime::DATETYPE_TOMORROW2 = "tmr";

const string DateTime::TIMETYPE_AM = "am";
const string DateTime::TIMETYPE_PM = "pm";

const string DateTime::_MONTH_JANUARY = "January";
const string DateTime::_MONTH_FEBRUARY = "February";
const string DateTime::_MONTH_MARCH = "March";
const string DateTime::_MONTH_APRIL = "April";
const string DateTime::_MONTH_MAY = "May";
const string DateTime::_MONTH_JUNE = "June";
const string DateTime::_MONTH_JULY = "July";
const string DateTime::_MONTH_AUGUST = "August";
const string DateTime::_MONTH_SEPTEMBER = "September";
const string DateTime::_MONTH_OCTOBER = "October";
const string DateTime::_MONTH_NOVEMBER = "November";
const string DateTime::_MONTH_DECEMBER = "December";




bool DateTime::isInitialized = false;
int DateTime::numberOfDateType;
int DateTime::numberOfTimeType;
vector<string> DateTime::dateType;
vector<string> DateTime::timeType;


//@author A0094213M
DateTime::DateTime(){
	isDateSet = false;
	isTimeSet = false;
	Initialize();
}

//@author A0094213M
DateTime::DateTime(string input){
	unformattedDateTime = input;
	isValidFormat = true;
	isDateSet = false;
	isTimeSet = false;
	Initialize();
	SetDefaults();
	SetStandards();
}


DateTime::~DateTime(){
}

string DateTime::Standardized(){
	return formattedDateTime;
}


string DateTime::GetInfo(){
	ostringstream info;

	info << "Date: " << setw(2) << setfill('0') 
		<< _day << "/" << setw(2) << setfill('0')
		<< _month << "/" << setw(2) << setfill('0')
		<< _year << endl;

	info << "Time: " << setw(2) << setfill('0') 
		<< _hours << ":" << setw(2) << setfill('0') 
		<< _mins;

	return info.str();
}

string DateTime::GetDate(){
	if (isDateSet){
		ostringstream date;
		int db = _month;
		string month_s = GetMonthName(_month);
		date << _day << " " << month_s;
		return date.str();
	}
	else{
		return "";
	}
	
}

string DateTime::GetTime(){
	if (isTimeSet){
		ostringstream out;
		out << setw(2) << setfill('0') << _hours << ":" << setw(2) << setfill('0') << _mins;
		string dbg = out.str();
		return out.str();
	}
	else{
		return "";
	}
}

//string DateTime::GetTomorrowDate(DateTime* dt){
//	struct tm * tomorrow;
//	tomorrow->tm_hour = dt->_hours;
//	tomorrow->tm_mday = dt->_day;
//	tomorrow->tm_mon = dt->_month - 1;
//	tomorrow->tm_min = dt->_mins;
//	tomorrow->tm_year = dt->_year - 1900;
//}

bool DateTime::IsEarlierThan(DateTime dt){
	bool isEarlier = false;
	if (_year < dt._year){
		isEarlier = true;
	}
	else{
		if (_month < dt._month){
			isEarlier = true;
		}
		else{
			if (_day < dt._day){
				isEarlier = true;
			}
			else{
				if (_hours < dt._hours){
					isEarlier = true;
				}
				else{
					if (_mins < dt._mins){
						isEarlier = true;
					}
				}
			}
		}
	}

	return isEarlier;
}

void DateTime::SetDefaults(){
	time_t now = time(0);
	struct tm timeinfo;
	localtime_s(&timeinfo, &now);
	_day = timeinfo.tm_mday;
	_month = timeinfo.tm_mon + 1;
	_year = timeinfo.tm_year + 1900;
	_hours = 0;
	_mins = 0;
}

void DateTime::SetStandards(){
	formattedDateTime = unformattedDateTime;
	string dbg = unformattedDateTime;
	string date;
	string time;
	Smartstring input_s(unformattedDateTime);
	vector<string> tokens = input_s.Tokenize(" ");
	int size = tokens.size();

	if (size > 3){
		isValidFormat = false;
	}
	else{
		switch (size){
			case 0:{
				isValidFormat = false;
				break;
			}
			case 1:{
				//this case assumes only either date or time has been entered
				formattedDateTime = StandardizeSingle(tokens[0]);
				break;
			}

			case 3:{
				formattedDateTime = StandardizeTriple(tokens);
				break;
			}

			default: {
				isValidFormat = false;
				break;
			}
		}
	}
}

string DateTime::StandardizeSingle(string input){
	string output;
	if (IsValidDayDate(input)){
		output = StandardizeDayDate(input);
	}
	else{
		if (IsValidTime(input)){
			output = StandardizeTime(input);
		}
		else{
			output = input;
			isValidFormat = false;
		}
	}
	return output;
}

string DateTime::StandardizeTriple(vector<string> input){
	string output;
	string prefix;
	string suffix;
	string date;
	string time;
	if (input[1] == "at"){
		//at implies day prefix and time suffix. i.e. "thursday at 5pm" and not "5pm at thursday"
		if (IsValidDayDate(input[0])){
			date = StandardizeDayDate(input[0]);

		}
		else{
			date = input[0];
			isValidFormat = false;
		}
		if (IsValidTime(input[2])){
			time = StandardizeTime(input[2]);
		}
		else{
			time = input[2];
			isValidFormat = false;
		}

	}
	else{
		if (input[1] == "on"){
			//on implex time prefix and day suffix. i.e. "5pm on friday" and not "friday on 5pm"
			if (IsValidDayDate(input[2])){
				date = StandardizeDayDate(input[2]);
			}
			else{
				date = input[2];
				isValidFormat = false;
			}
			if (IsValidTime(input[0])){
				time = StandardizeTime(input[0]);
			}
			else{
				time = input[0];
				isValidFormat = false;
			}
		}
	}
	output = time + " on " + date;
	return output;
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

	//setting the day month and year values in DateTime object
	_day = day;
	_month = month;
	_year = atoi(tokens[2].c_str());
	isDateSet = true;

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

		//set Day, month, year valies in DateTime object
		struct tm timeinfo;
		localtime_s(&timeinfo, &timeresult);
		_day = timeinfo.tm_mday;
		_month = timeinfo.tm_mon + 1;
		_year = timeinfo.tm_year + 1900;
		isDateSet = true;
	}
	else{
		output = input;
	}
	return output;
}

string DateTime::StandardizeTime(string input){
	assert(input != "");
	string output;
	string result = input;
	string period = "am";
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

	//set standardized hours, mins and seconds
	if (period == "pm"){
		_hours = hour % 12 + 12;
		_mins = mins % 60;
	}
	else{
		_hours = hour % 24;
		_mins = mins % 60;
	}
	isTimeSet = true;


	ostringstream minout;
	minout << setw(2) << setfill('0') << mins;
	ostringstream hourout;
	hourout << setw(2) << setfill('0') << hour;

	output = hourout.str() + ":" + minout.str() + period;
	return output;
}

string DateTime::TwentyFourHourFormat(){
	string output;
	ostringstream min;
	ostringstream hour;

	min << setw(2) << setfill('0') << _mins;
	hour << setw(2) << setfill('0') << _hours;

	output = hour.str() + ":" + min.str();
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
	assert(input != "");
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

	for (int i = 0; i < numberOfDateType; i++){
		size_t found = input.find(dateType[i]);

		if (found != string::npos){
			return true;
		}
	}

	return false;

}

bool DateTime::IsValidTime(string input){
	assert(input != "");
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
		//getting min
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
	if (input == DATETYPE_TODAY1){
		return GetToday();
	}
	if (input == DATETYPE_TOMORROW1 || input == DATETYPE_TOMORROW2){
		return GetTomorrow();
	}
	return DAY::INVALID;
}

string DateTime::GetMonthName(int input){
	switch (input){
		case 1:{
			return _MONTH_JANUARY;
			break;
		}
		case 2:{
			return _MONTH_FEBRUARY;
			break;
		}
		case 3:{
			return _MONTH_MARCH;
			break;
		}
		case 4:{
			return _MONTH_APRIL;
			break;
		}
		case 5:{
			return _MONTH_MAY;
			break;
		}
		case 6:{
			return _MONTH_JUNE;
			break;
		}
		case 7:{
			return _MONTH_JULY;
			break;
		}
		case 8:{
			return _MONTH_AUGUST;
			break;
		}
		case 9:{
			return _MONTH_SEPTEMBER;
			break;
		}
		case 10:{
			return _MONTH_OCTOBER;
			break;
		}
		case 11:{
			return _MONTH_NOVEMBER;
			break;
		}
		case 12:{
			return _MONTH_DECEMBER;
			break;
		}

		default:{
			return _MONTH_JANUARY;
		}


	}
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

DateTime::DAY DateTime::GetToday(){
	time_t now = time(0);
	struct tm timeinfo;
	localtime_s(&timeinfo, &now);
	int day = timeinfo.tm_wday;
	switch (day){
		case DAY::SUNDAY:{
			return DAY::SUNDAY;
		}
		case DAY::MONDAY:{
			return DAY::MONDAY;
		}
		case DAY::TUESDAY:{
			return DAY::TUESDAY;
		}
		case DAY::WEDNESDAY:{
			return DAY::WEDNESDAY;
		}
		case DAY::THURSDAY:{
			return DAY::THURSDAY;
		}
		case DAY::FRIDAY:{
			return DAY::FRIDAY;
		}
		case DAY::SATURDAY:{
			return DAY::SATURDAY;
		}
		default:{
			return DAY::INVALID;
		}
	}
	assert(false && "in DateTime::GetToday function");
}

DateTime::DAY DateTime::GetTomorrow(){
	time_t now = time(0);
	struct tm timeinfo;
	localtime_s(&timeinfo, &now);
	int day = timeinfo.tm_wday;
	switch (day){
		case DAY::SUNDAY:{
			return DAY::MONDAY;
		}
		case DAY::MONDAY:{
			return DAY::TUESDAY;
		}
		case DAY::TUESDAY:{
			return DAY::WEDNESDAY;
		}
		case DAY::WEDNESDAY:{
			return DAY::THURSDAY;
		}
		case DAY::THURSDAY:{
			return DAY::FRIDAY;
		}
		case DAY::FRIDAY:{
			return DAY::SATURDAY;
		}
		case DAY::SATURDAY:{
			return DAY::SUNDAY;
		}
		default:{
			return DAY::INVALID;
		}
	}
	assert(false && "in DateTime::GetTomorrow function");
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

string DateTime::Tomorrow(){
	time_t now = time(0);
	time_t tomorrow = now + 24 * 60 * 60;
	struct tm timeinfo;
	localtime_s(&timeinfo, &tomorrow);
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
	bool isGreater = true;
	Smartstring input_1(input1);
	vector<string> tokens1 = input_1.Tokenize(" ");
	int size1 = tokens1.size();

	Smartstring input_2(input2);
	vector<string> tokens2 = input_2.Tokenize(" ");
	int size2 = tokens2.size();


	switch (size1){
	case 1:{
		if (IsValidDate(tokens1[0])){
			if (IsValidTime(tokens2[0])){
				isGreater = false;
			}
			else if (IsValidDate(tokens2[0])){
				isGreater = CompareDate(tokens1[0], tokens2[0]);
			}
		}

		if (IsValidTime(tokens1[0])){
			if (IsValidTime(tokens2[0])){
				isGreater = CompareTime(tokens1[0], tokens2[0]);
			}

		}

		break;
	}

	case 3:{
		if (size2 == 1){
			if (IsValidTime(tokens2[0])){
				isGreater = CompareTime(tokens1[0], tokens2[0]);
			}
			else if (IsValidDate(tokens2[0])){
				isGreater = CompareDate(tokens1[2], tokens2[0]);
			}
		}

		if (size2 == 3){
			if (!CompareDate(tokens1[2], tokens2[2])){
				isGreater = false;
			}
			else if (tokens1[2] == tokens2[2]){
				isGreater = CompareTime(tokens1[0], tokens2[0]);
			}
		}
		break;
	}

	default:
		break;
	}


	return isGreater;
}

bool DateTime::CompareDate(string date1, string date2){
	int day1, day2;
	int mon1, mon2;
	int year1, year2;
	int length;
	string day_s, mon_s, year_s;
	size_t start, end;
	bool isGreater = true;

	// tokenize first string date 
	start = 0;
	end = date1.find_first_of("/");
	day_s = date1.substr(start, end - start);
	day1 = atoi(day_s.c_str());

	start = end + 1;
	end = date1.find_first_of("/", start);
	mon_s = date1.substr(start, end - start);
	mon1 = atoi(mon_s.c_str());

	start = end + 1;
	length = date1.length();
	year_s = date1.substr(start, length - start);
	year1 = atoi(mon_s.c_str());


	//tokenize second string date

	start = 0;
	end = date1.find_first_of("/");
	day_s = date2.substr(start, end - start);
	day2 = atoi(day_s.c_str());

	start = end + 1;
	end = date2.find_first_of("/", start);
	mon_s = date2.substr(start, end - start);
	mon2 = atoi(mon_s.c_str());

	start = end + 1;
	length = date2.length();
	year_s = date2.substr(start, length - start);
	year2 = atoi(mon_s.c_str());

	//compare
	if (year1 == year2){
		if (mon1 == mon2){
			if (day1 < day2){
				isGreater = false;
			}
		}
		else if (mon1 < mon2){
			isGreater = false;
		}
	}
	else if (year1 < year2){
		isGreater = false;
	}



	return isGreater;
}

bool DateTime::CompareTime(string time1, string time2){
	int hour1, hour2;
	int min1, min2;
	int length;
	string hour_s;
	string min_s;
	size_t found;
	bool isGreater = true;


	found = time1.find_first_of(":");
	hour_s = time1.substr(0, found);
	hour1 = atoi(hour_s.c_str());
	length = time1.length();
	min_s = time1.substr(found + 1, length);
	min1 = atoi(min_s.c_str());

	found = time2.find_first_of(":");
	hour_s = time2.substr(0, found);
	hour2 = atoi(hour_s.c_str());
	length = time2.length();
	min_s = time2.substr(found + 1, length);
	min2 = atoi(min_s.c_str());

	if (hour1 == hour2){
		if (min1 < min2){
			isGreater = false;
		}
	}

	if (hour1 < hour2){
		isGreater = false;
	}

	return isGreater;
}

DateTime* DateTime::GetDefaultEndDate(){
	DateTime* dt = new DateTime();
	*dt = *this;
	dt->_hours++;
	return dt;
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
		dateType.push_back(DATETYPE_TODAY1);
		dateType.push_back(DATETYPE_TOMORROW1);
		dateType.push_back(DATETYPE_TOMORROW2);
		timeType.push_back(TIMETYPE_AM);
		timeType.push_back(TIMETYPE_PM);

		numberOfDateType = dateType.size();
		numberOfTimeType = timeType.size();
		isInitialized = true;
	}

}



