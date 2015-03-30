#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Task.h"
#include "Smartstring.h"
#include "Logger.h";

using namespace std;
using namespace logging;

class Storage
{
public:
	//VARIABLES
	vector<Task*> taskList;
	vector<Task*> floatingList;
	vector<Task*> timedList;
	vector<Task*> deadlineList;
	vector<Task*> currentScope;

	//METHODS
	Storage();
	Storage(string filename);
	~Storage();
	string Add(Task* task);
	string Load();
	string Rewrite();
	string ToString();
	string ToString(vector<Task*> V);
	string Clear();
	string Delete(int position);
	vector<string> GetContent();
	vector<Task*> GetTaskList();
	string GetTimedList();
	string GetDeadlineList();
	string GetFloatingList();
	void FilterTask();

	//Power Search Method
	string search(string input);
	vector<Task*> PowerSearch(string input);
	vector<Task*> NearSearch(string input);
	//vector<string> GetEmptySlots(string input);


private:
	//VARIABLES
	string _filename;
	vector<string> _filecontent;

	const string _FEEDBACK_GENERIC_SUCCESS = "STORAGE SUCCESS";
	const string _FEEDBACK_GENERIC_FAILURE = "STORAGE FAILED";
	const string _FEEDBACK_LOAD_SUCCESS = "LOAD SUCCESS";
	const string _FEEDBACK_LOAD_FAILURE = "LOAD FAILED";
	const string _FEEDBACK_WRITE_SUCCESS = "WRITE SUCCESS";
	const string _FEEDBACK_WRITE_FAILURE = "WRITE FAILED";
	const string _FEEDBACK_CLEAR_SUCCESS = "CLEAR SUCCESS";
	const string _FEEDBACK_CLEAR_FAILURE = "CLEAR FAILED";
	const string _FEEDBACK_DELETE_SUCCESS = "DELETE SUCCESS";
	const string _FEEDBACK_DELETE_FAILURE = "DELETE FAILED";
	const string _FEEDBACK_SEARCH_FAILURE = "SEARCH FAILED";
	const string _FEEDBACK_FILE_EMPTY = "FILE EMPTY";
	const string _EMPTY_STRING = "";
	const string _FILE_EXTENSION_CSV = ".csv";
	const string _FILE_EXTENSION_TXT = ".txt";
	const string _DELIMITERS_CSV = ",\"";
	enum FILETYPE {CSV, TXT, INVALID};

	//METHODS

	string ClearFile();
	string ClearVectors();
	string LoadRawFileContent();
	string Remove(int position);
	FILETYPE IdentifyFileType();
	//write methods
	string WriteVectors();
	string WriteToCSV();
	string WriteToTXT();

	//load methods
	string LoadTaskList();
	string LoadCSVContent(); //loads _filecontent vector into taskList vector assuming CSV format
	string LoadTXTContent(); //loads _filecontent vector into taskList vector assuming TXT format

};

