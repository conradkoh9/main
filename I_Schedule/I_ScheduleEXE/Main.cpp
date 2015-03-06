#include "Storage.h"
#include "Parser.h"
#include <vector>
using namespace std;

void printVect(vector<string> input);

int main(){
	const string FIELD_STARTDATE = "date:";
	const string FIELD_ENDDATE = "by:";
	const string FIELD_PRIORITY = "priority:";
	const string FIELD_DESCRIPTION = "add";
	Parser* parser = new Parser();
	
	string myinput = "homework school from: Monday priority: 1 on Friday";
	myinput = "go to school on monday priority 1";
	vector<string> output = parser->Identify(myinput);
	printVect(output);
	Smartstring mys;
	Smartstring my2;
	cout << mys << endl;
	
	system("pause");
	return 0;
}

void printVect(vector<string> input){
	vector<string>::iterator iter;
	for (iter = input.begin(); iter != input.end(); ++iter){
		cout << *iter << endl;
	}
}