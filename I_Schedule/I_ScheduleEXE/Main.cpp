#include "Storage.h"
#include "Parser.h"
#include <vector>
using namespace std;

void printVect(vector<string> input);

int main(){
	
	return 0;
}

void printVect(vector<string> input){
	vector<string>::iterator iter;
	for (iter = input.begin(); iter != input.end(); ++iter){
		cout << *iter << endl;
	}
}