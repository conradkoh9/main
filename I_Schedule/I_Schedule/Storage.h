#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Task.h"
#include "Smartstring.h"
using namespace std;

class Storage
{
public:
	//VARIABLES
	vector<Task*> taskList;
	//vector<Task*> floatingList;
	//vector<Task*> timedList;
	//vector<Task*> deadlineList;

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

	//Search Method
	string search(vector<string>& input);
	/*bool isContainedInDescription(string keyword, string description);
	bool isContainedStartdate(string keyword, string startDate);
	bool isContainedInEnddate(string keyword, string endDate);
	bool isContainedInPriority(string keyword, string priority);*/
	bool isContained(string keyword, string desreiption);
	bool isContainingKeyword(string keyword, vector<string>& tokenVector);
	string convertToLower(string str);
	void getTokens(string str, vector<string>& tokenVector, char token);
	void searchTaskList(string str, vector<Task*>& V, Smartstring::FIELD field);
	void initializeSearchingVector(vector<Task*>& searchingResult, int size_taskList);
	void searchResultVector(vector<Task*>& V, string str, Smartstring::FIELD field);

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

	//METHODS

	string ClearFile();
	string ClearVectors();
	string LoadFileContent();
	string LoadTaskList();
	string Remove(int position);
	string WriteVectors();

};

