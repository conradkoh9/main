#include "Storage.h"
#include <vector>
using namespace std;

void printVect(vector<string> input);

int main(){
	Storage* storage = new Storage();
	system("pause");
	return 0;
}

void printVect(vector<string> input){
	vector<string>::iterator iter;
	for (iter = input.begin(); iter != input.end(); ++iter){
		cout << *iter << endl;
	}
}