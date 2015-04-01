#include "DateTime.h"


DateTime::DateTime()
{
}

DateTime::DateTime(string input){
	
}

DateTime::~DateTime(){


}

string DateTime::now(){
	time_t now = time(0); //raw time -> this is generally implemented as an integer offset from 00:00hours, jan1, 2970 UTC. This leads me to the assumption
	//that you can use (time_t time + 60) to offset by 1 minute, (time_t time + 3600) to offset by 1 hour etc
	struct tm timeinfo; //this struct is defined by the system
	localtime_s(&timeinfo, &now); //converts the raw time into a struct
	char output[80];
	strftime(output, 80, "%I:%M%p", &timeinfo); //to refer to more ways to access time format, refer to http://cplusplus.com/reference/ctime/strftime/
	//under strftime, yellow boxes indicate certain formats that are not supported on visual studio
	return output;
}

string DateTime::today(){
	time_t now = time(0);
	struct tm timeinfo;
	localtime_s(&timeinfo, &now);
	char output[80];
	strftime(output, 80, "%d/%m/%Y", &timeinfo);
	return output;
}


string DateTime::tomorrow(){
	time_t now = time(0);
	struct tm *ltm = localtime(&now);

	char output[80];
	strftime(output, 80, "%d/%m/%Y", &timeinfo);
	return output;


}

string DateTime::convertTime(string input){


}

void DateTime::displayTime(){


}




