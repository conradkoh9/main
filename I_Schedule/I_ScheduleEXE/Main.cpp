#include "Storage.h"
#include "Parser.h"
#include "Logic.h"
#include <vector>
using namespace std;

void printVect(vector<string> input);

int main(){
	//usage guide:
	//follow the accepted commands as defined within Smartstring.cpp
	Logic* logic = new Logic();
	string myinput = "add homework from monday on tuesday priority 1";
	string feedback;
	feedback = logic->Run(myinput);
	cout << feedback << endl;

	string input;
	while (getline(cin, input)){
		string output = logic->Run(input);
		cout << output << endl;
	}

	system("pause");
	return 0;
}

void printVect(vector<string> input){
	vector<string>::iterator iter;
	for (iter = input.begin(); iter != input.end(); ++iter){
		cout << *iter << endl;
	}
}