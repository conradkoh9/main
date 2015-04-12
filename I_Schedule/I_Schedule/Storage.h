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
	enum FILETYPE { TXT, INVALID };
	string _filename;
	const string _archivefile = "archive.txt";
	//DATA STORAGE VARIABLES
	vector<string> _filecontent;
	vector<string> _archivecontent;
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
	vector<Task*> lastArchiveList;

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
	string Edit(int position, vector<string> newinfo);
	string Complete(int position);
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

	string GetTimedList();
	string GetFloatingList();
	string GetDeadlineList();

	//Formatted display methods
	string DayView();

	//ToString methods
	string ArchiveToString();
	string ToString();
	string ToString(vector<Task*> V, int firstIdx);
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
	static const string _FEEDBACK_ARCHIVE_EMPTY;
	static const string _FEEDBACK_VIEW_ARCHIVE;
	static const string _FEEDBACK_DAYVIEW;
	static const string _FEEDBACK__SORT_FAILURE;
	static const string _FEEDBACK_SORT_SUCCESS;
	static const string _FEEDBACK_UNDO_COMPLETE;
	static const string _FEEDBACK_NO_UNDO;
	//formatting variables
	static const string _rtfboldtagstart;
	static const string _rtfboldtagend;
	static const string _rtffontsizeprefix;
	static const string _rtffontsizesuffix;
	static const string _rtftab;
	static const string _rtfcolorblueprefix;
	static const string _rtfcolorbluesuffix;

	//File Details
	const string _FILE_EXTENSION_TXT = ".txt";
	const string _FILENAME_DEFAULT = "default.txt";
	const string _FILENAME_SESSION_DATA = "data.sys";


	//METHODS
	//Session methods
	string DefaultSession();

	//Update methods
	void Update(); //Updates all the vectors with the new information

	//filter methods
	string FilterTask();
	void SortListsByTime(vector<Task*> &V);
	void InitializeLists();
	string SortAllLists();
	void SortTaskList();

	//clear methods
	void ClearFile();
	void ClearFilteredLists();
	void ClearVectors();
	void ClearUndoVectors();
	string Remove(int position);
	string Erase(Task* taskptr);

	//Save methods
	string SaveSessionData();
	string WriteToFile(); 
	string WriteToTXT(); //writes tasks to TXT readable format
	string WriteToArchive(); //writes archive vector to archive

	//Load methods
	string LoadSessionData();
	string LoadRawFileContent(); //reads from a file and stores all the content into _filecontent vector
	string LoadRawArchiveContent();
	string LoadTaskList(); //Loads Tasklist from FileContent vector
	string LoadArchiveList();
	string LoadTXTContent(); //loads _filecontent vector into taskList vector assuming TXT format
	string LoadTXTArchiveContent();

	//Complete methods
	string MarkComplete(Task* taskptr);
	void Archive(Task* taskptr);

	//File analysis methods
	FILETYPE IdentifyFileType(string input);
	bool FileEmpty(string input);

	//Get Task* methods
	Task* GetTaskPtr(int position, Smartstring::LIST list);
	Task* GetTaskPtr(int position);
	Task* GetTimedTask(int position);
	Task* GetFloatingTask(int position);
	Task* GetDeadlineTask(int position);

	//Replace methods
	void ReplaceTask(Task* existing, Task* replacer);

	//Indentification of list methods
	Smartstring::LIST IdentifyListFromIndex(int index);

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


