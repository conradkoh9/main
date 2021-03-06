#include "Storage.h"

//Constant variable declaration
const string Storage::_FEEDBACK_ADD_SUCCESS = "Successfully added. ";
const string Storage::_FEEDBACK_GENERIC_SUCCESS = "Update succeeded. ";
const string Storage::_FEEDBACK_GENERIC_FAILURE = "Update failed. ";
const string Storage::_FEEDBACK_LOAD_SUCCESS = "Load succeeded. ";
const string Storage::_FEEDBACK_LOAD_FAILURE = "Load failed. ";
const string Storage::_FEEDBACK_WRITE_SUCCESS = "Write succeeded. ";
const string Storage::_FEEDBACK_WRITE_FAILURE = "Write failed. ";
const string Storage::_FEEDBACK_CLEAR_SUCCESS = "Successfully cleared. ";
const string Storage::_FEEDBACK_CLEAR_FAILURE = "Failed to clear. ";
const string Storage::_FEEDBACK_DELETE_SUCCESS = "Successfully deleted. ";
const string Storage::_FEEDBACK_DELETE_FAILURE = "Failed to delete. ";
const string Storage::_FEEDBACK_UNDO_SUCCESS = "Undo succeeded. ";
const string Storage::_FEEDBACK_UNDO_FAILURE = "Undo failed. ";
const string Storage::_FEEDBACK_SEARCH_FAILURE = "No results found. ";
const string Storage::_FEEDBACK_FILE_EMPTY = "Specified file empty. ";
const string Storage::_FEEDBACK_FILE_NOT_EMPTY = "Specified file is not empty. ";
const string Storage::_FEEDBACK_INVALID_FILE_FORMAT = "Invalid file format entered. ";
const string Storage::_EMPTY_STRING= "";
const string Storage::_FEEDBACK_SESSION_LOAD_FAILURE = "Session failed to load. Starting default session. ";
const string Storage::_FEEDBACK_SESSION_LOAD_SUCCESS = "Session loaded. ";
const string Storage::_FEEDBACK_SESSION_SAVE_SUCCESS = "Session saved. ";
const string Storage::_FEEDBACK_SESSION_SAVE_FAILURE = "Session failed to save. ";
const string Storage::_FEEDBACK_RESET = "Storage reset. ";
const string Storage::_FEEDBACK_INVALID_INDEX = "Invalid index. ";
const string Storage::_FEEDBACK_INVALID_LIST = "Invalid list entered. ";
const string Storage::_FEEDBACK_UPDATE_SUCCESS = "Update success. ";
const string Storage::_FEEDBACK_EDIT_SUCCESS = "Edit success. ";
const string Storage::_FEEDBACK_DATA_CORRUPTED = "Data corrupted. ";
const string Storage::_FEEDBACK_FILETYPE_INVALID = "Invalid filetype. ";
const string Storage::_FEEDBACK_DEFAULT_SESSION_STARTED = "Default session started. ";
const string Storage::_FEEDBACK__SORT_FAILURE = "Sort failed. ";
const string Storage::_FEEDBACK_SORT_SUCCESS = "Sort success. ";
const string Storage::_FEEDBACK_STARTUP = "Using ";
const string Storage::_FEEDBACK_ARCHIVE_EMPTY = "Archive empty. ";
const string Storage::_FEEDBACK_VIEW_ARCHIVE = "Viewing archive. ";
const string Storage::_FEEDBACK_DAYVIEW = "Day view. ";
const string Storage::_FEEDBACK_UNDO_COMPLETE = "Undo complete. ";
const string Storage::_FEEDBACK_NO_UNDO = "Nothing to undo. ";
const string Storage::_LOG_MESSAGE_FILENAME_CHANGED = "Filename changed to: ";
//formatting variables
const string Storage::_rtfboldtagstart = "\\b ";
const string Storage::_rtfboldtagend = "\\b0 ";
const string Storage::_rtffontsizeprefix = "\\fs24 ";
const string Storage::_rtffontsizesuffix = "\\fs18 ";
//const string Storage::_rtftab = "\\tab ";
const string Storage::_rtftab = "    ";
const string Storage::_rtfcolorblueprefix = "\\cf1 ";
const string Storage::_rtfcolorbluesuffix = "\\cf0 ";
const string Storage::_MESSAGE_HELP_ADD = "\\cf1 Add: \\b0\\cf0 \"\\b\\cf1 add \\b0\\cf0 <task description> \\b\\cf1 s:\\b0\\cf0 <startdate> \\b\\cf1 at\\b0\\cf0 <starttime> \\b\\cf1 e:\\b0\\cf0 <enddate> \\b\\cf1 at\\b0\\cf0 <endtime>\"";
const string Storage::_MESSAGE_HELP_DELETE = "\\b\\cf1 Delete: \\b0\\cf0 \"\\b\\cf1 delete \\b0\\cf0 <task index>\"";
const string Storage::_MESSAGE_HELP_COMPLETE = "\\b\\cf1 Mark complete: \\b0\\cf0 \" \\b\\cf1 complete \\b0\\cf0 <task index>\"";
const string Storage::_MESSAGE_HELP_DISPLAY = "\\b\\cf1 View timed tasks: \\b0\\cf0 \"\\b\\cf1 display \\b0\\cf0\"";
const string Storage::_MESSAGE_HELP_EDIT = "\\b\\cf1 Edit: \\b0\\cf0 \"\\b\\cf1 edit \\b0\\cf0 <task index> \\b\\cf1 s:\\b0\\cf0 <startdate> \\b\\cf1 e:\\b0\\cf0 <enddate>\", similar to adding";
const string Storage::_MESSAGE_HELP_UNDO = "\\b\\cf1 Undo: \\b0\\cf0 \"undo\"";
const string Storage::_MESSAGE_HELP_LOAD = "\\b\\cf1 Load: \\b0\\cf0 \"\\b\\cf1 load \\b0\\cf0 <filename>.txt.\" Note that only TXT file formats are supported.";
const string Storage::_MESSAGE_HELP_SAVEAS = "\\b\\cf1 Save: \\b0\\cf0 \"\\b\\cf1 save \\b0\\cf0 <filename>.txt\"";
const string Storage::_MESSAGE_HELP_ARCHIVE = "\\b\\cf1 View compeleted: \\b0\\cf0 \"\\b\\cf1 archived\\b0\\cf0\"";

//PUBLIC =================================================================================================
//@author A0099303A

//====================================================================
//Core Functionality
//====================================================================
Storage::Storage(){
	Load();
	status << _FEEDBACK_STARTUP << _filename;
}

Storage::Storage(string input){
	_filename = input;
	SaveSessionData();
}

Storage::~Storage(){
}

//@author A0099303A
void Storage::Add(Task* task){
	UpdateUndoVectors();
	string feedback = AddToTaskVector(task);
	Update();
	Rewrite();
	UpdateStatus(feedback);
	return;
}

//@author A0099303A
void Storage::DeleteFromList(int position, Smartstring::LIST list){
	UpdateUndoVectors();
	try{
		Task* toDelete = GetTaskPtr(position, list);
		Erase(toDelete);
		Rewrite();
		Update();
		UpdateStatus(_FEEDBACK_DELETE_SUCCESS);
	}
	catch (InvalidIndex){
		UpdateStatus(_FEEDBACK_INVALID_INDEX);
	}
	catch (InvalidList){
		UpdateStatus(_FEEDBACK_INVALID_LIST);
	}
	return;
}


//@author A0099303A
void Storage::Delete(int position){

	//Smartstring::LIST list = IdentifyListFromIndex(position);
	try{
		UpdateUndoVectors();
		string feedback = Remove(position);
		Rewrite();
		Update();
		UpdateStatus(feedback);
	}
	catch (InvalidIndex){
		UpdateStatus(_FEEDBACK_DELETE_FAILURE);
	}
	return;
}

//@author A0099303A
void Storage::Edit(int position, vector<string> newinfo){
	UpdateUndoVectors();
	try{
		Task* taskptr = GetTaskPtr(position);
		Task* newTask = EditToNewTask(*taskptr, newinfo);
		ReplaceTask(taskptr, newTask);
		Rewrite();
		Update();
		UpdateStatus(_FEEDBACK_EDIT_SUCCESS);
		return;
	}

	catch (InvalidIndex){
		UpdateStatus(_FEEDBACK_INVALID_INDEX);
	}
	catch (InvalidList){
		UpdateStatus(_FEEDBACK_INVALID_LIST);
	}
	return;
}

//@author A0099303A
void Storage::Complete(int position){

	try{
		UpdateUndoVectors();
		Task* toremove = GetTaskPtr(position);
		string feedback = MarkComplete(toremove);
		Archive(toremove);
		Rewrite();
		Update();
		UpdateStatus(feedback);
	}
	catch (InvalidIndex){
		UpdateStatus(_FEEDBACK_INVALID_INDEX);
	}
	return;
}

//@author A0099303A
void Storage::Load(){
	LoadSessionData(); //change active file
	FILETYPE filetype = IdentifyFileType(_filename);
	try{
		if (filetype != FILETYPE::INVALID){
			ClearVectors();
			ClearUndoVectors();
			LoadRawFileContent();
			LoadRawArchiveContent();
			LoadTaskList();
			LoadArchiveList();
			Update();
			UpdateStatus(_FEEDBACK_LOAD_SUCCESS);

		}
		else{
			UpdateStatus(_FEEDBACK_FILETYPE_INVALID);
			throw load_failure;
		}
	}
	
	catch (LoadFailure){
		DefaultSession();
		UpdateStatus(_FEEDBACK_LOAD_FAILURE);
	}
	return;

}

//@author A0099303A
void Storage::Load(string filename){

	FILETYPE filetype = IdentifyFileType(filename);
	string feedback;
	try{
		if (filetype != FILETYPE::INVALID){
			UpdateFileName(filename);
			ClearVectors();
			ClearUndoVectors();
			LoadRawFileContent();
			LoadTaskList();
			Update();
			UpdateStatus(_FEEDBACK_LOAD_SUCCESS);
		}
		else{
			UpdateStatus(_FEEDBACK_FILETYPE_INVALID);
		}
	}

	catch (LoadFailure){
		DefaultSession();
		UpdateStatus(_FEEDBACK_LOAD_FAILURE);
	}
	return;
}


//@author A0099303A
void Storage::Save(){
	Rewrite();
	SaveSessionData();
	UpdateStatus(_FEEDBACK_SESSION_SAVE_SUCCESS);
	return;
}

//@author A0099303A
void Storage::SaveAs(string newFileName){
	FILETYPE filetype = IdentifyFileType(newFileName);
	if (filetype!= FILETYPE::INVALID){
		UpdateFileName(newFileName);
		Rewrite();
		SaveSessionData();
		UpdateStatus(_FEEDBACK_SESSION_SAVE_SUCCESS);		
	}
	else{
		UpdateStatus(_FEEDBACK_FILETYPE_INVALID);
	}
	return;
}

//@author A0099303A
void Storage::Rewrite(){
	ClearFile();
	WriteToArchive();
	WriteToFile();
	return;
}

//@author A0099303A
void Storage::Reset(){
	UpdateFileName(_FILENAME_DEFAULT);
	Clear();
	UpdateStatus(_FEEDBACK_RESET);
	return;
}

//@author A0099303A
void Storage::Clear(){
	UpdateUndoVectors();
	ClearFile();
	ClearVectors();
	Update();
	UpdateStatus(_FEEDBACK_CLEAR_SUCCESS);
	return;
}

//@author A0119513L
void Storage::Undo(){
	if (!lastList.empty()){
		RestoreFromUndoVectors();
		Rewrite();
		Update();
		UpdateStatus(_FEEDBACK_UNDO_COMPLETE);
	}
	else{
		UpdateStatus(_FEEDBACK_NO_UNDO);
	}
	return;
}



//====================================================================
//Power Search
//====================================================================

//@author A0119491B
string Storage::Search(string input){
	vector<Task*> PowerSearch_Result;
	try{
		PowerSearch_Result = PowerSearch(input);
	}
	catch (InvalidList){
		return _FEEDBACK_SEARCH_FAILURE;
	}

	if (PowerSearch_Result.empty()){
		return _FEEDBACK_SEARCH_FAILURE;
	}
	else{
		return ToString(PowerSearch_Result, 1);
	}
}

//@author A0119491B
vector<Task*> Storage::PowerSearch(string input){
	vector<Task*>::iterator iter;
	vector<Task*> searchResult;

	if (taskList.size() == 0){
		throw invalid_list;
	}

	for (iter = taskList.begin(); iter != taskList.end(); ++iter){
		Task* currentTask = *iter;
		if (currentTask->isContains(input)){
			searchResult.push_back(currentTask);
		}
	}
	return searchResult;
}



//@author A0119491B
string Storage::SearchEmptySlots(string input){
		DateTime* dt = new DateTime(input);
		string stdtm = dt->Standardized();
		if (dt->isValidFormat){
			InitializeDayTask(stdtm);
			SetDayCalendar();
			return GetEmptySlots();
	   }else{
		return _FEEDBACK_SEARCH_FAILURE;
	}
}
//@author A0119491B
void Storage::InitializeDayTask(string date){
	for (int i = 0; i < taskList.size(); i++){
		string dateTime = taskList[i]->GetStartTime();
		size_t position = 0;
		position = dateTime.find_first_of(":"); // 17:00pm 07/04/2015 Only this format can be recognized
		assert(position > 0);
		if (position != string::npos){
			daytask.push_back(taskList[i]);
		}
	}
}
//@author A0119491B
void Storage::SetDayCalendar(){
	InitializeDayCalendar();
	SetSleepingTime();
	SetOccupiedSlots();
}

//@author A0119491B
void Storage::InitializeDayCalendar(){
	int timeIntervals = 48;
	for (int i = 0; i < timeIntervals; i++){
		daycalendar[i] = "empty";
	}
}

//@author A0119491B
void Storage::SetSleepingTime(){
	int sleeping_time = 14; //from 00:00am to 7:00am 
	for (int i = 0; i < sleeping_time; i++){
		daycalendar[i] = "sleeping";
	}
	daycalendar[47] = "sleeping"; //from 23:00pm to 00:00am
	daycalendar[46] = "sleeping";
}

//@author A0119491B
void Storage::SetOccupiedSlots(){
	for (int i = 0; i < daytask.size(); i++){
		string startTime = daytask[i]->GetStartTime();
		string endTime = daytask[i]->GetEndTime();
		int indexStart, indexEnd;

		if (startTime != "" && endTime != ""){
			indexStart = GetSlotIndex(startTime);
			indexEnd = GetSlotIndex(endTime);
			SetBusySlots(indexStart, indexEnd);
		}
	}
}

//@author A0119491B
int Storage::GetSlotIndex(string time){
	int hourPos = 0, minPos = 3, leghth = 2;
	string hourInt, minInt;
	int hour, min, index;
	hourInt = time.substr(hourPos, leghth);
	minInt = time.substr(minPos, leghth);
	hour = atoi(hourInt.c_str());
	min = atoi(minInt.c_str());
	if (min > 0){
		min = 1;
	}
	index = 2 * hour + min;
	return index;
}

//@author A0119491B
void Storage::SetBusySlots(int indexStart, int indexEnd){
	for (int i = indexStart; i < indexEnd; i++){
		daycalendar[i] = "busy";
	}
}
//@auhtor A0119491B
string Storage::GetEmptySlots(){
	int startindex = 0, endindex = 0, time_intervals = 48, starthr, endhr;

	int next = 0;
	for (int i = 0; i < time_intervals; i++)
	{
		assert(daycalendar[i] != "");
		startindex = i; 
		next = i; 
		while (daycalendar[next] == "empty" && i != 47){
			next++;
			assert(daycalendar[next] != "");
		} //get the end index of empty slots

		endindex = next;
		if (i != next){
			if (startindex % 2 == 0 && endindex % 2 == 0){ //check startindex and endindex are odd or even
				starthr = startindex / 2;
				endhr = endindex / 2;
				ostringstream oss;
				oss << setw(2) << setfill('0') << starthr << ":" << "00 to " << setw(2) << setfill('0') << endhr << ":00";
				emptyslots.push_back(oss.str());
			}
			else if (startindex % 2 != 0 && endindex % 2 == 0){
				starthr = startindex / 2;
				endhr = endindex / 2;
				ostringstream oss;
				oss << setw(2) << setfill('0') << starthr << ":" << "30 to " << setw(2) << setfill('0') << endhr << ":00";
				emptyslots.push_back(oss.str());
			}
			else if (startindex % 2 == 0 && endindex % 2 != 0){
				starthr = startindex / 2;
				endhr = endindex / 2;
				ostringstream oss;
				oss << setw(2) << setfill('0') << starthr << ":" << "00 to " << setw(2) << setfill('0') << endhr << ":30";
				emptyslots.push_back(oss.str());
			}
			else if (startindex % 2 != 0 && endindex % 2 != 0){
				starthr = startindex / 2;
				endhr = endindex / 2;
				ostringstream oss;
				oss << setw(2) << setfill('0') << starthr << ":" << "30 to " << setw(2) << setfill('0') << endhr << ":30";
				emptyslots.push_back(oss.str());
			}

			i = endindex; //let for loop continnue at endindex
		}

	}

	return ToString(emptyslots);
}


//====================================================================
//STATS
//====================================================================
int Storage::Size(){
	return taskList.size();
}

string Storage::GetTask(int index){
	return taskList[index]->ToString();
}

string Storage::GetFileName(){
	return _filename;
}


string Storage::GetTimedList(){
	int startIndex = 1;
	return ToString(timedList, startIndex);
}

string Storage::GetDeadlineList(){
	int startIndex = timedList.size() + 1;
	return ToString(deadlineList, startIndex);
}

string Storage::GetFloatingList(){
	int startIndex = timedList.size() + deadlineList.size() + 1;
	return ToString(floatingList, startIndex);
}





//@author A0099303A
//====================================================================
//ToString methods
//====================================================================

string Storage::Help(){
	ostringstream out;
	out << _MESSAGE_HELP_ADD << endl << endl;
	out << _MESSAGE_HELP_DELETE << endl << endl;
	out << _MESSAGE_HELP_COMPLETE << endl << endl;
	out << _MESSAGE_HELP_EDIT << endl << endl;
	out << _MESSAGE_HELP_UNDO << endl << endl;
	out << _MESSAGE_HELP_LOAD << endl << endl;
	out << _MESSAGE_HELP_SAVEAS << endl << endl;
	out << _MESSAGE_HELP_ARCHIVE << endl << endl;
	out << _MESSAGE_HELP_DISPLAY << endl << endl;
	return out.str();
}
string Storage::GetArchive(){
	Update();
	return ArchiveToString();
}

string Storage::ToString(){
	Update();
	return GetFormattedTaskList();
}

//@author unknown
string Storage::ToString(vector<Task*> V, int index){
	ostringstream out;
	vector<Task*>::iterator iter;
	for (iter = V.begin(); iter != V.end(); ++iter){
		if (iter + 1 != V.end()){
			out << _rtfboldtagstart << index << ": " << _rtfboldtagend << (*iter)->ToShortString() << endl;
		}
		else{
			out << _rtfboldtagstart << index << ": " << _rtfboldtagend << (*iter)->ToShortString();
		}
		index++;
	}
	return out.str();
}

string Storage::ToString(vector<string> input){
	ostringstream out;
	vector<string>::iterator iter;
	for (iter = input.begin(); iter != input.end(); iter++){
		out << *iter << endl;
	}
	return out.str();
}

string Storage::DayView(){
	Update();
	ostringstream out;
	int index = 0;
	vector<Task*>::iterator iter;
	string currentday;
	DateTime* dt = new DateTime();
	for (iter = taskList.begin(); iter != taskList.end(); ++iter){
		if (currentday != (*iter)->GetStartDate()){
			currentday = (*iter)->GetStartDate();
			string representative = currentday;
			if (currentday == dt->Today()){
				representative = "Today";
			}
			if (currentday == dt->Tomorrow()){
				representative = "Tomorrow";
			}
			string prefixes = _rtfcolorblueprefix + _rtfboldtagstart + _rtffontsizeprefix;
			string suffixes = _rtffontsizesuffix + _rtfboldtagend + _rtfcolorbluesuffix;
			string	formattedDay = prefixes + representative + suffixes;
			out << formattedDay << endl;
		}

		if ((*iter)->GetType() == Task::TIMED){
			++index;
			if (iter + 1 != taskList.end()){
				out << _rtftab << _rtfboldtagstart << index << ": " << _rtfboldtagend << (*iter)->ToDatelessString() << endl;
			}
			else{
				out << _rtftab << _rtfboldtagstart << index << ": " << _rtfboldtagend << (*iter)->ToDatelessString();
			}
		}
	}
	status << _FEEDBACK_DAYVIEW;
	return out.str();
}


//PRIVATE==========================================================================================
//====================================================================
//Session Methods
//====================================================================
//@author A0099303A
string Storage::DefaultSession(){
	_filename = _FILENAME_DEFAULT;
	Update();
	status << _FEEDBACK_DEFAULT_SESSION_STARTED;
	return _FEEDBACK_DEFAULT_SESSION_STARTED;
}


//====================================================================
//Update Methods
//====================================================================
//@author A0099303A
void Storage::Update(){
	FilterTask();
	SaveSessionData();
	return;
}

void Storage::UpdateStatus(string status_m){
	status << status_m;
	return;
}

//====================================================================
//Undo Methods
//====================================================================
//@author A0099303A

void Storage::UpdateUndoVectors(){
	lastList = taskList;
	lastArchiveList = archiveList;
	return;
}

//@author A0099303A
void Storage::RestoreFromUndoVectors(){
	taskList = lastList;
	archiveList = lastArchiveList;
	return;
}

//@author Ziqi
//====================================================================
//Filter Methods
//====================================================================

string Storage::FilterTask(){
	ClearFilteredLists();
	InitializeLists();
	return SortAllLists();
}
//@author A0119491B
void Storage::InitializeLists(){
	int size_taskList = taskList.size();

	for (int i = 0; i < size_taskList; i++){
		string dbg = taskList[i]->ToShortString();
		if (taskList[i]->GetType() == Task::TASKTYPE::TIMED){
			timedList.push_back(taskList[i]);
		}
		else if (taskList[i]->GetType() == Task::TASKTYPE::DEADLINE){
			deadlineList.push_back(taskList[i]);
		}
		else if (taskList[i]->GetType() == Task::TASKTYPE::FLOATING){
			floatingList.push_back(taskList[i]);
		}
		else{
		}
	}
}
//@author A0119491B
string Storage::SortAllLists(){
	try{
		SortListsByTime(timedList);
	}
	catch (InvalidList){
		return _FEEDBACK__SORT_FAILURE;
	}

	try{
		SortListsByTime(deadlineList);
	}
	catch (InvalidList){
		return _FEEDBACK__SORT_FAILURE;
	}
	SortTaskList();
	return _FEEDBACK_SORT_SUCCESS;
}
//@author A0119491B
void Storage::SortListsByTime(vector <Task*> &V){
	int size_V = V.size();
	string dt1, dt2, datetime1, datetime2;
	for (int i = 0; i < size_V; i++){
		for (int j = i; j < size_V; ++j){
			dt1 = V[i]->GetStartDateTime();
			dt2 = V[j]->GetStartDateTime();


			if (dt1 != "" && dt2 != "")
			{
				datetime1 = dt1;
				datetime2 = dt2;
			}
			else if (dt1 == "" && dt2 == ""){
				dt1 = V[i]->GetEndDateTime();
				dt2 = V[j]->GetEndDateTime();
				datetime1 = dt1;
				datetime2 = dt2;
			}
			else{
				throw invalid_list;
			}

			DateTime dt1(datetime1);
			DateTime dt2(datetime2);
			if (dt2.IsEarlierThan(dt1)){
				Task* temp = V[i];
				V[i] = V[j];
				V[j] = temp;
			}
		}
	}
}
//@author A0119491B
void Storage::SortTaskList(){
	taskList.clear();
	assert(taskList.size() == 0);
	vector<Task*>::iterator iter;
	for (iter = timedList.begin(); iter != timedList.end(); iter++){
		taskList.push_back(*iter);
	}
	for (iter = deadlineList.begin(); iter != deadlineList.end(); iter++){
		taskList.push_back(*iter);
	}
	for (iter = floatingList.begin(); iter != floatingList.end(); iter++)
	{
		taskList.push_back(*iter);
	}

}
//@author A0099303A
//====================================================================
//Clear Methods
//====================================================================

string Storage::AddToTaskVector(Task* taskptr){
	taskList.push_back(taskptr);
	return _FEEDBACK_ADD_SUCCESS;
}

//@author A0099303A
//====================================================================
//Clear Methods
//====================================================================
void Storage::ClearFile(){
	ofstream out(_filename, ofstream::trunc);
	return;
}

//@author A0099303A
void Storage::ClearFilteredLists(){
	timedList.clear();
	floatingList.clear();
	deadlineList.clear();
	return;
}

//@author A0099303A
void Storage::ClearVectors(){
	taskList.clear();
	timedList.clear();
	floatingList.clear();
	deadlineList.clear();
	_filecontent.clear();
	_archivecontent.clear();
	archiveList.clear();
	return;
}

//@author A0099303A
void Storage::ClearUndoVectors(){
	lastList.clear();
	lastArchiveList.clear();
	return;
}

//@author A0099303A
string Storage::Remove(int position){
	try{
		int size_taskList = taskList.size();
		if (position > size_taskList || position < 1){
			throw invalid_index;
		}
		taskList.erase(taskList.begin() + position - 1);
	}
	catch (InvalidIndex){
		throw invalid_index;
		return _FEEDBACK_DELETE_FAILURE;
	}
	return _FEEDBACK_DELETE_SUCCESS;
}

//@author A0099303A
string Storage::Erase(Task* taskptr){
	vector<Task*>::iterator iter;
	for (iter = taskList.begin(); iter != taskList.end();){
		if (taskptr == (*iter)){
			iter = taskList.erase(iter);
		}
		else{
			++iter;
		}
	}
	return _FEEDBACK_DELETE_SUCCESS;
}


//====================================================================
//Edit methods
//====================================================================
//@author A0099303A
Task* Storage::EditToNewTask(Task task, vector<string> newinfo){
	Task* newTask = new Task();
	*newTask = task;
	newTask->Edit(newinfo);
	return newTask;
}

//====================================================================
//Save methods
//====================================================================
//@author A0099303A
void Storage::UpdateFileName(string newFileName){
	_filename = newFileName;
	logfile << _LOG_MESSAGE_FILENAME_CHANGED << newFileName;
	return;
}

//@author A0099303A
string Storage::SaveSessionData(){
	ofstream of;
	string feedback;
	of.open(_FILENAME_SESSION_DATA.c_str(), ios::trunc);
	of << _filename;
	of.close();
	ifstream file;
	file.open(_FILENAME_SESSION_DATA.c_str());
	string buffer;
	file >> buffer;
	file.close();
	if (buffer.empty()){
		feedback = _FEEDBACK_SESSION_SAVE_FAILURE;
	}
	else{
		feedback = _FEEDBACK_SESSION_SAVE_SUCCESS + " " + buffer;
	}
	return feedback;
}

//@author A0099303A
string Storage::WriteToFile(){
	FILETYPE filetype = IdentifyFileType(_filename);
	string feedback;
	switch (filetype){
	case(FILETYPE::TXT) : {
		feedback = WriteToTXT();
		break;
	}
	default : {
		UpdateStatus(_FEEDBACK_INVALID_FILE_FORMAT);
		return _FEEDBACK_INVALID_FILE_FORMAT;
		break;
	}
	}
	return feedback;

}

//@author A0099303A
string Storage::WriteToTXT(){
	ostringstream out;
	ofstream of;
	of.open(_filename.c_str(), ios::app);
	vector<Task*>::iterator iter;
	for (iter = taskList.begin(); iter != taskList.end(); ++iter){
		if (iter + 1 != taskList.end()){
			out << (*iter)->ToTXTString() << endl;
		}
		else{
			out << (*iter)->ToTXTString();
		}
	}
	of << out.str();

	return _FEEDBACK_WRITE_SUCCESS;
}

string Storage::WriteToArchive(){
	ostringstream out;
	ofstream of;
	of.open(_archivefile.c_str(), ios::trunc);
	vector<Task*>::iterator iter;
	int size = archiveList.size();
	for (iter = archiveList.begin(); iter != archiveList.end(); ++iter){
		out << (*iter)->ToTXTString() << endl;
	}
	of << out.str();
	return _FEEDBACK_WRITE_SUCCESS;
}

//====================================================================
//Load methods
//====================================================================
//@author A0099303A
string Storage::LoadSessionData(){
	ifstream file;
	file.open(_FILENAME_SESSION_DATA);
	getline(file, _filename);
	string feedback;
	if (_filename.empty()){
		feedback = _FEEDBACK_LOAD_FAILURE;
	}
	else{
		feedback = _FEEDBACK_LOAD_SUCCESS;
	}
	logfile << _filename;
	logfile << feedback;

	return feedback;
}

//@author A0099303A
string Storage::LoadRawFileContent(){
	string line;
	vector<string> all_lines;
	ifstream in(_filename.c_str());
	try{
		if (in.is_open()){
			while (getline(in, line)){
				if (line == _EMPTY_STRING){
					return _FEEDBACK_FILE_EMPTY;
				}

				all_lines.push_back(line);
			}
			_filecontent = all_lines;
			return _FEEDBACK_LOAD_SUCCESS;
		}
	}
	catch (out_of_range){
		logfile << _FEEDBACK_LOAD_FAILURE;
		return _FEEDBACK_LOAD_FAILURE;
	}
	return _FEEDBACK_LOAD_FAILURE;
}

//@author A0099303A
string Storage::LoadRawArchiveContent(){
	string line;
	vector<string> all_lines;
	ifstream in(_archivefile.c_str());
	try{
		if (in.is_open()){
			while (getline(in, line)){
				if (line == _EMPTY_STRING){
					return _FEEDBACK_FILE_EMPTY;
				}

				all_lines.push_back(line);
			}
			_archivecontent = all_lines;
			return _FEEDBACK_LOAD_SUCCESS;
		}
	}
	catch (out_of_range){
		logfile << _FEEDBACK_LOAD_FAILURE;
		return _FEEDBACK_LOAD_FAILURE;
	}
	return _FEEDBACK_LOAD_FAILURE;
}

//@author A0099303A
string Storage::LoadTaskList(){
	FILETYPE filetype = IdentifyFileType(_filename);
	string feedback;
	switch (filetype){
		case(FILETYPE::TXT) : {
			feedback = LoadTXTContent();
			break;
		}
		default : {
			logfile << _FEEDBACK_LOAD_FAILURE;
			return _FEEDBACK_LOAD_FAILURE;
			break;
		}
	}
	return feedback;
	
}

//@author A0099303A
string Storage::LoadArchiveList(){
	FILETYPE filetype = IdentifyFileType(_filename);
		string feedback;
			switch (filetype){
			case(FILETYPE::TXT) : {
				feedback = LoadTXTArchiveContent();
				break;
			}
			default : {
				logfile << _FEEDBACK_LOAD_FAILURE;
				return _FEEDBACK_LOAD_FAILURE;
				break;
		}
	}
	return feedback;

}

//@author A0099303A
string Storage::LoadTXTContent(){
	Smartstring str;
	const int startfield = Smartstring::FIELD::DESCRIPTION;
	int currentfield = startfield;
	int fieldcount = Smartstring::NUMBER_OF_FIELDS;
	vector<string>::iterator iter;
	Task* taskptr = new Task();
	//remove field description from _filecontent
	vector<string> taskContent;
	for (iter = _filecontent.begin(); iter != _filecontent.end(); ++iter){
		string line = (*iter);
		istringstream is(line);
		string buffer;
		is >> buffer;
		string output;
		getline(is, output);
		int length = line.length() - 1;
		output = output.substr(1, length);
		taskContent.push_back(output);
	}
	
	//end remove field description from _filecontent
	try{
		for (iter = taskContent.begin(); iter != taskContent.end(); ++iter){
			if (currentfield == Smartstring::FIELD::DESCRIPTION){
				taskptr = new Task();
				taskList.push_back(taskptr);
			}
			switch (currentfield){
			case Smartstring::FIELD::DESCRIPTION:{
				taskptr->SetDescription(*iter);
				break;
			}
			case Smartstring::FIELD::STARTDATE:{
				taskptr->SetStartDateTime(*iter);
				break;
			}
			case Smartstring::FIELD::ENDDATE:{
				taskptr->SetEndDateTime(*iter);
				break;
			}
			case Smartstring::FIELD::PRIORITY:{
				taskptr->SetPriority(*iter);
				break;
			}
			case Smartstring::FIELD::STATUS:{
				taskptr->SetStatus(*iter);
			}

			}
			currentfield = (currentfield + 1) % fieldcount;
		}
	}

	catch (out_of_range){
		logfile << _FEEDBACK_LOAD_FAILURE;
		return _FEEDBACK_LOAD_FAILURE;
	}
	logfile << _FEEDBACK_LOAD_SUCCESS;
	return _FEEDBACK_LOAD_SUCCESS;
}

//@author A0099303A
string Storage::LoadTXTArchiveContent(){
	Smartstring str;
	const int startfield = Smartstring::FIELD::DESCRIPTION;
	int currentfield = startfield;
	int fieldcount = Smartstring::NUMBER_OF_FIELDS;
	vector<string>::iterator iter;
	Task* taskptr = new Task();
	//remove field description from _filecontent
	vector<string> taskContent;
	for (iter = _archivecontent.begin(); iter != _archivecontent.end(); ++iter){
		string line = (*iter);
		istringstream is(line);
		string buffer;
		is >> buffer;
		string output;
		getline(is, output);
		int length = line.length() - 1;
		output = output.substr(1, length);
		taskContent.push_back(output);
	}

	//end remove field description from _filecontent
	try{
		for (iter = taskContent.begin(); iter != taskContent.end(); ++iter){
			if (currentfield == Smartstring::FIELD::DESCRIPTION){
				taskptr = new Task();
				archiveList.push_back(taskptr);
			}
			switch (currentfield){
			case Smartstring::FIELD::DESCRIPTION:{
				taskptr->SetDescription(*iter);
				break;
			}
			case Smartstring::FIELD::STARTDATE:{
				taskptr->SetStartDateTime(*iter);
				break;
			}
			case Smartstring::FIELD::ENDDATE:{
				taskptr->SetEndDateTime(*iter);
				break;
			}
			case Smartstring::FIELD::PRIORITY:{
				taskptr->SetPriority(*iter);
				break;
			}
			case Smartstring::FIELD::STATUS:{
				taskptr->SetStatus(*iter);
			}

			}
			currentfield = (currentfield + 1) % fieldcount;
		}
	}

	catch (out_of_range){
		logfile << _FEEDBACK_LOAD_FAILURE;
		return _FEEDBACK_LOAD_FAILURE;
	}
	logfile << _FEEDBACK_LOAD_SUCCESS;
	return _FEEDBACK_LOAD_SUCCESS;
}



//====================================================================
//Mark methods
//====================================================================
//@author A0099303A
string Storage::MarkComplete(Task* taskptr){

	vector<Task*>::iterator iter;
	for (iter = taskList.begin(); iter != taskList.end(); ++iter){
		if (taskptr == (*iter)){
			(*iter)->MarkComplete();
		}
	}

	return _FEEDBACK_UPDATE_SUCCESS;
}

void Storage::Archive(Task* taskptr){
	archiveList.push_back(taskptr);
	Erase(taskptr);
	return;
}

//====================================================================
//File analysis methods
//====================================================================
//@author A0099303A
Storage::FILETYPE Storage::IdentifyFileType(string input){
	if (input.find(_FILE_EXTENSION_TXT) != string::npos){
		return FILETYPE::TXT;
	}
	else{
		return FILETYPE::INVALID;
	}

}

//@author A0099303A
bool Storage::FileEmpty(string filename){
	ifstream ifs;
	ifs.open(filename);
	string test;
	ifs >> test;
	if (test.empty()){
		ifs.close();
		return true;
	}
	else{
		ifs.close();
		return false;
	}
}

//====================================================================
//Get Task* methods
//====================================================================
//@author A0099303A
Task* Storage::GetTaskPtr(int position, Smartstring::LIST list){
	Task* taskptr;
	switch (list){
		case Smartstring::LIST::TIMED:{
			taskptr = GetTimedTask(position);
			break;
		}
		case Smartstring::LIST::DEADLINE:{
			taskptr = GetDeadlineTask(position);
			break;
		}
		case Smartstring::LIST::FLOAT:{
			taskptr = GetFloatingTask(position);
			break;
		}

		default:{
			throw invalid_list;
		}
	}
	return taskptr;
}

Task* Storage::GetTaskPtr(int position){
	if (position <= taskList.size() && position > 0){
		return taskList[position - 1];
	}
	else{
		throw invalid_index;
	}
}
//@author A0099303A
Task* Storage::GetTimedTask(int position){
	int size = timedList.size();
	if (position > size || position < 1){
		throw invalid_index;
	}
	else{
		return timedList[position - 1];
	}
	assert(false && "GetTimedTask failure");
	return NULL;
}

//@author A0099303A
Task* Storage::GetDeadlineTask(int position){
	int size = deadlineList.size();
	if (position > size || position < 1){
		throw invalid_index;
	}
	else{
		return deadlineList[position - 1];
	}

	assert(false && "GetDeadlineTask failure");
	return NULL;
}

//@author A0099303A
Task* Storage::GetFloatingTask(int position){
	int size = floatingList.size();
	if (position > size || position < 1){
		throw invalid_index;
	}
	else{
		return floatingList[position - 1];
	}

	assert(false && "GetFloatingTask failure");
	return NULL;
}

void Storage::ReplaceTask(Task* taskptr, Task* replacer){
	vector<Task*>::iterator iter;
	for (iter = taskList.begin(); iter != taskList.end(); ++iter){
		if ((*iter) == taskptr){
			(*iter) = replacer;
		}
	}

	return;
}
//====================================================================
//Get Archive Methods
//====================================================================

string Storage::ArchiveToString(){
	ostringstream out;
	int index = 0;
	vector<Task*>::iterator iter;
	if (archiveList.size() != 0){
		for (iter = archiveList.begin(); iter != archiveList.end(); ++iter){
			++index;
			if (iter + 1 != archiveList.end()){
				out << _rtfboldtagstart << index << ": " << _rtfboldtagend << (*iter)->ToShortString() << endl;
			}
			else{
				out << _rtfboldtagstart << index << ": " << _rtfboldtagend << (*iter)->ToShortString();
			}
		}
		status << _FEEDBACK_VIEW_ARCHIVE;
		return out.str();
	}
	else{
		status << _FEEDBACK_ARCHIVE_EMPTY;
		return "";
	}


}

string Storage::GetFormattedTaskList(){
	ostringstream out;
	int index = 0;
	vector<Task*>::iterator iter;
	for (iter = taskList.begin(); iter != taskList.end(); ++iter){
		++index;
		if (iter + 1 != taskList.end()){
			out << _rtfboldtagstart << index << ": " << _rtfboldtagend << (*iter)->ToShortString() << endl;
		}
		else{
			out << _rtfboldtagstart << index << ": " << _rtfboldtagend << (*iter)->ToShortString();
		}
	}
	return out.str();
}

//====================================================================
//Identification of List methods
//====================================================================

//@author A0099303A
Smartstring::LIST Storage::IdentifyListFromIndex(int index){

	Smartstring::LIST list;
	if (index < deadlineList.size()){
		return Smartstring::LIST::TIMED;
	}
	else{
		if (index > deadlineList.size()){
			return Smartstring::LIST::FLOAT;
		}
		else{
			return Smartstring::LIST::DEADLINE;
		}
	}
}
