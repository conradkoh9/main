#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Storage
{
public:
	//VARIABLES

	//METHODS
	Storage();
	Storage(string filename);
	~Storage();
	string loadFile();
	string writeToFile(string input);
	string clearFile();
	vector<string> getContent();

private:
	//VARIABLES
	string _filename;
	vector<string> _content;
	const string _FEEDBACK_GENERIC_SUCCESS = "STORAGE SUCCESS";
	const string _FEEDBACK_GENERIC_FAILURE = "STORAGE FAILED";
	const string _FEEDBACK_LOAD_SUCCESS = "LOAD SUCCESS";
	const string _FEEDBACK_LOAD_FAILURE = "LOAD FAILED";
	const string _FEEDBACK_WRITE_SUCCESS = "WRITE SUCCESS";
	const string _FEEDBACK_WRITE_FAILURE = "WRITE FAILED";
	const string _FEEDBACK_CLEAR_SUCCESS = "CLEAR SUCCESS";
	const string _FEEDBACK_CLEAR_FAILURE = "CLEAR FAILED";
	const string _FEEDBACK_FILE_EMPTY = "FILE EMPTY";
	const string _EMPTY_STRING = "";

	//METHODS


};

