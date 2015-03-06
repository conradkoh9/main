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
	string myinput = "add homework from: Monday priority: 1 end: Friday";
	vector<string> output = parser->Identify(myinput);
	printVect(output);
	Smartstring mys;
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