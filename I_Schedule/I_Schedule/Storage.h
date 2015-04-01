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
private:
	enum FILETYPE { CSV, TXT, INVALID };
	string _filename;

	//DATA STORAGE VARIABLES
	vector<string> _filecontent;
public:
	//INFORMATION STREAMS
	ostringstream status;

	//DATA STORAGE VARIABLES
	vector<Task*> taskList;
	vector<Task*> floatingList;
	vector<Task*> timedList;
	vector<Task*> deadlineList;

	//
	DateTime* dateTime;

	//CONSTRUCTORS
	Storage();
	Storage(string filename);
	~Storage();

	//METHODS
	//FUNCTIONS
	string Add(Task* task);
	string Delete(int position);
	string Load();

	string Save();
	string SaveAs(string newFileName);
	string Rewrite();

	string Reset();
	string Clear();

	//Power Search Method
	string Search(string input);
	vector<Task*> PowerSearch(string input);
	vector<Task*> NearSearch(string input);
	//vector<string> GetEmptySlots(string input);

	//STATS
	int Size();
	string GetTask(int index);
	string GetFileName();

	string GetFloatingList();
	string GetDeadlineList();
	string GetTimedList();

	//To be refactored because it is not apparent what storage->ToString should give
	string ToString();
	string ToString(vector<Task*> V);

private:

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
	static const string _FEEDBACK_RESET;

	//File Details
	const string _FILE_EXTENSION_CSV = ".csv";
	const string _FILE_EXTENSION_TXT = ".txt";
	const string _DELIMITERS_CSV = ",";
	const string _FILENAME_DEFAULT = "default.csv";
	const string _FILENAME_SESSION_DATA = "data.sys";


	//METHODS
	//Update methods
	void Update(); //Updates all the vectors with the new information

	//filter methods
	void FilterTask();
	void sortTaskListsByTime();
	void initializeLists();

	//clear methods
	void ClearFile();
	void ClearVectors();
	string Remove(int position);

	//Save methods
	string SaveSessionData();
	string WriteToFile(); //chooses whether to write using WriteToCSV method or WriteToTXT method
	string WriteToCSV(); //writes tasks to CSV readable format
	string WriteToTXT(); //writes tasks to TXT readable format

	//Load methods
	string LoadSessionData();
	string LoadRawFileContent(); //reads from a file and stores all the content into _filecontent vector
	string LoadTaskList(); //chooses whether LoadCSVContent is called or LoadTXTContent is called, or that the current file has an invalid format
	string LoadCSVContent(); //loads _filecontent vector into taskList vector assuming CSV format
	string LoadTXTContent(); //loads _filecontent vector into taskList vector assuming TXT format

	//File analysis methods
	FILETYPE IdentifyFileType(string input);
	bool FileEmpty(string input);

};

