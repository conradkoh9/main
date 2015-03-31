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
	ostringstream status;
	//METHODS
	Storage();
	Storage(string filename);
	~Storage();
	string Add(Task* task);
	string Load();
	string Save(string newFileName);
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

	bool FileEmpty(string filename);
private:
	//VARIABLES
	string _filename;
	vector<string> _filecontent;
	//Feedback Variables
	static const string _FEEDBACK_GENERIC_SUCCESS;
	static const string _FEEDBACK_GENERIC_FAILURE;
	static const string _FEEDBACK_LOAD_SUCCESS;
	static const string _FEEDBACK_LOAD_FAILURE;
	static const string _FEEDBACK_WRITE_SUCCESS;
	static const string _FEEDBACK_WRITE_FAILURE;
	static const string _FEEDBACK_CLEAR_SUCCESS;
	static const string _FEEDBACK_CLEAR_FAILURE;
	static const string _FEEDBACK_DELETE_SUCCESS;
	static const string _FEEDBACK_DELETE_FAILURE;
	static const string _FEEDBACK_SEARCH_FAILURE;
	static const string _FEEDBACK_FILE_EMPTY;
	static const string _FEEDBACK_FILE_NOT_EMPTY;
	static const string _FEEDBACK_INVALID_FILE_FORMAT;
	static const string _EMPTY_STRING;
	static const string _FEEDBACK_SESSION_LOAD_SUCCESS;
	static const string _FEEDBACK_SESSION_LOAD_FAILURE;
	static const string _FEEDBACK_SESSION_SAVE_SUCCESS;
	static const string _FEEDBACK_SESSION_SAVE_FAILURE;

	//File Details
	const string _FILE_EXTENSION_CSV = ".csv";
	const string _FILE_EXTENSION_TXT = ".txt";
	const string _DELIMITERS_CSV = ",";
	const string _FILENAME_DEFAULT = "default.csv";
	const string _FILENAME_SESSION_DATA = "data.sys";
	enum FILETYPE {CSV, TXT, INVALID};

	//METHODS

	string ClearFile();
	string ClearVectors();
	string LoadRawFileContent();
	string Remove(int position);
	FILETYPE IdentifyFileType(string input);

	//session info storage methods
	string SaveSessionData();
	string LoadSessionData();

	//write methods
	string WriteVectors();
	string WriteToCSV();
	string WriteToTXT();

	//load methods
	string LoadTaskList();
	string LoadCSVContent(); //loads _filecontent vector into taskList vector assuming CSV format
	string LoadTXTContent(); //loads _filecontent vector into taskList vector assuming TXT format

};

