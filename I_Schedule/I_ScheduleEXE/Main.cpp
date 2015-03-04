#include "Storage.h"
#include <vector>
using namespace std;

void printVect(vector<string> input);

int main(){
	Storage* storage = new Storage();
	cout << "created storage" << endl;
	vector<string> all_feedback;
	string feedback;
	feedback = storage->clearFile();
	all_feedback.push_back(feedback);
	feedback = storage->writeToFile("hello world");
	all_feedback.push_back(feedback);
	feedback = storage->loadFile();
	all_feedback.push_back(feedback);
	
	vector<string>::iterator iter;
	vector<string> content = storage->getContent();
	for (iter = content.begin(); iter != content.end(); ++iter){
		cout << "content: " << *iter << endl;
	}

	printVect(all_feedback);

	system("pause");
	return 0;
}

void printVect(vector<string> input){
	vector<string>::iterator iter;
	for (iter = input.begin(); iter != input.end(); ++iter){
		cout << *iter << endl;
	}
}