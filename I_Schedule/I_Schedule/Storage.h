#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Storage
{
public:
	Storage();
	Storage(string filename);
	~Storage();

private:
	string _filename;
	vector<string> loadFile();
	string writeToFile();
	string clearFile();

};

