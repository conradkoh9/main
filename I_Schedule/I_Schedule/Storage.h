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
	const string _archivefile = "archive.csv";

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
	vector<Task*> lastList;
	vector<Task*> archiveList;

	//
	DateTime* dateTime;
	vector<Task*> daytask;
	string daycalendar[48];
	vector<string> emptyslots;


	//CONSTRUCTORS
	Storage();
	Storage(string filename);
	~Storage();

	//METHODS
	//FUNCTIONS
	string Add(Task* task);
	string DeleteFromList(int position, Smartstring::LIST list);
	string Delete(int position);
	string Edit(int position, Smartstring::LIST list, vector<string> newinfo);
	string Complete(int position, Smartstring::LIST list);
	string Load();
	string Load(string filename);

	string Save();
	string SaveAs(string newFileName);
	string Rewrite();

	string Reset();
	string Clear();
	string Undo();

	//Power Search Method
	string Search(string input);
	vector<Task*> PowerSearch(string input);
	string SearchEmptySlots(string input);
	void InitializeDayTask(string input);
	void SetDayCalendar();
	void InitializeDayCalendar();
	void SetSleepingTime();
	void SetOccupiedSlots();
	string GetEmptySlots();
	
	//STATS
	int Size();
	string GetTask(int index);
	string GetFileName();

	string GetFloatingList();
	string GetDeadlineList();
	string GetTimedList();


	//Formatted display methods
	string DayView();

	//To be refactored because it is not apparent what storage->ToString should give
	string ToString();
	string ToString(vector<Task*> V);
	string ToString(vector<string> v);

private:

	//Feedback Variables
	static const string _FEEDBACK_ADD_SUCCESS;
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
	static const string _FEEDBACK_UNDO_SUCCESS;
	static const string _FEEDBACK_UNDO_FAILURE;
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
	static const string _FEEDBACK_INVALID_INDEX;
	static const string _FEEDBACK_INVALID_LIST;
	static const string _FEEDBACK_UPDATE_SUCCESS;
	static const string _FEEDBACK_EDIT_SUCCESS;
	static const string _FEEDBACK_DATA_CORRUPTED;
	static const string _FEEDBACK_FILETYPE_INVALID;
	static const string _FEEDBACK_DEFAULT_SESSION_STARTED;
	static const string _FEEDBACK_STARTUP;
	//formatting variables
	static const string _rtfboldtagstart;
	static const string _rtfboldtagend;
	static const string _rtffontsizeprefix;
	static const string _rtffontsizesuffix;
	static const string _rtftab;
	static const string _rtfcolorblueprefix;
	static const string _rtfcolorbluesuffix;

	//File Details
	const string _FILE_EXTENSION_CSV = ".csv";
	const string _FILE_EXTENSION_TXT = ".txt";
	const string _DELIMITERS_CSV = "\"";
	const string _FILENAME_DEFAULT = "default.txt";
	const string _FILENAME_SESSION_DATA = "data.sys";


	//METHODS
	//Session methods
	string DefaultSession();

	//Update methods
	void Update(); //Updates all the vectors with the new information

	//filter methods
	void FilterTask();
	void sortListsByTime(vector<Task*> &V);
	void initializeLists();
	void sortTask();
	void rearrangeTaskList();

	//clear methods
	void ClearFile();
	void ClearFilteredLists();
	void ClearVectors();
	void ClearUndoVector();
	string Remove(int position);
	string Erase(Task* taskptr);

	//Save methods
	string SaveSessionData();
	string WriteToFile(); //chooses whether to write using WriteToCSV method or WriteToTXT method
	string WriteToCSV(); //writes tasks to CSV readable format
	string WriteToTXT(); //writes tasks to TXT readable format
	string WriteToArchive(); //writes archive vector to archive

	//Load methods
	string LoadSessionData();
	string LoadRawFileContent(); //reads from a file and stores all the content into _filecontent vector
	string LoadTaskList(); //chooses whether LoadCSVContent is called or LoadTXTContent is called, or that the current file has an invalid format
	string LoadCSVContent(); //loads _filecontent vector into taskList vector assuming CSV format
	string LoadTXTContent(); //loads _filecontent vector into taskList vector assuming TXT format

	//Complete methods
	string MarkComplete(Task* taskptr);
	void Archive(Task* taskptr);

	//File analysis methods
	FILETYPE IdentifyFileType(string input);
	bool FileEmpty(string input);

	//Get Task* methods
	Task* GetTask(int position, Smartstring::LIST list);
	Task* GetTimedTask(int position);
	Task* GetFloatingTask(int position);
	Task* GetDeadlineTask(int position);

	//Replace methods
	void ReplaceTask(Task* existing, Task* replacer);


	//exceptions
	class InvalidIndex : public exception{
	} invalid_index;

	class InvalidList : public exception{

	} invalid_list;

	class InvalidInput : public exception{
	} invalid_input;

	class LoadFailure : public exception{
	} load_failure;

	class FirstRun : public LoadFailure{
	} first_run;

	class CorruptedData : public LoadFailure{
	} corrupted_data;

};


