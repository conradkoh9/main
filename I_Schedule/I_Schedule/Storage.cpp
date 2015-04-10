#include "Storage.h"

//Constant variable declaration
const string Storage::_FEEDBACK_ADD_SUCCESS = "Successfull added.";
const string Storage::_FEEDBACK_GENERIC_SUCCESS = "Update succeeded.";
const string Storage::_FEEDBACK_GENERIC_FAILURE = "Update failed.";
const string Storage::_FEEDBACK_LOAD_SUCCESS = "Load succeeded.";
const string Storage::_FEEDBACK_LOAD_FAILURE = "Load failed.";
const string Storage::_FEEDBACK_WRITE_SUCCESS = "Write succeeded.";
const string Storage::_FEEDBACK_WRITE_FAILURE = "Write failed.";
const string Storage::_FEEDBACK_CLEAR_SUCCESS = "Successfully cleared.";
const string Storage::_FEEDBACK_CLEAR_FAILURE = "Failed to clear.";
const string Storage::_FEEDBACK_DELETE_SUCCESS = "Successfully deleted.";
const string Storage::_FEEDBACK_DELETE_FAILURE = "Failed to delete.";
const string Storage::_FEEDBACK_UNDO_SUCCESS = "Undo succeeded.";
const string Storage::_FEEDBACK_UNDO_FAILURE = "Undo failed.";
const string Storage::_FEEDBACK_SEARCH_FAILURE = "No results found.";
const string Storage::_FEEDBACK_FILE_EMPTY = "Specified file empty.";
const string Storage::_FEEDBACK_FILE_NOT_EMPTY = "Specified file is not empty.";
const string Storage::_FEEDBACK_INVALID_FILE_FORMAT = "Invalid file format entered.";
const string Storage::_EMPTY_STRING= "";
const string Storage::_FEEDBACK_SESSION_LOAD_FAILURE = "Session failed to load. Starting default session.";
const string Storage::_FEEDBACK_SESSION_LOAD_SUCCESS = "Session loaded.";
const string Storage::_FEEDBACK_SESSION_SAVE_SUCCESS = "Session saved.";
const string Storage::_FEEDBACK_SESSION_SAVE_FAILURE = "Session failed to save.";
const string Storage::_FEEDBACK_RESET = "Storage reset.";
const string Storage::_FEEDBACK_INVALID_INDEX = "Invalid index.";
const string Storage::_FEEDBACK_INVALID_LIST = "Invalid list entered";
const string Storage::_FEEDBACK_UPDATE_SUCCESS = "Update success.";
const string Storage::_FEEDBACK_EDIT_SUCCESS = "Edit success.";
const string Storage::_FEEDBACK_DATA_CORRUPTED = "Data corrupted.";
const string Storage::_FEEDBACK_FILETYPE_INVALID = "Invalid filetype.";
const string Storage::_FEEDBACK_DEFAULT_SESSION_STARTED = "Default session started.";
const string Storage::_FEEDBACK_STARTUP = "Using ";
//formatting variables
const string Storage::_rtfboldtagstart = "\\b ";
const string Storage::_rtfboldtagend = "\\b0 ";
const string Storage::_rtffontsizeprefix = "\\fs24 ";
const string Storage::_rtffontsizesuffix = "\\fs18 ";
//const string Storage::_rtftab = "\\tab ";
const string Storage::_rtftab = "    ";
const string Storage::_rtfcolorblueprefix = "\\cf1 ";
const string Storage::_rtfcolorbluesuffix = "\\cf0 ";

//@author A0099303A
//PUBLIC =================================================================================================
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
string Storage::Add(Task* task){
	lastList = taskList;
	taskList.push_back(task);
	Update();
	Rewrite();
	string feedback = _FEEDBACK_ADD_SUCCESS;
	return feedback;
}

//@author A0099303A
string Storage::DeleteFromList(int position, Smartstring::LIST list){
	lastList = taskList;
	try{
		Task* toDelete = GetTask(position, list);
		Erase(toDelete);
		Rewrite();
		Update();
		return _FEEDBACK_DELETE_SUCCESS;
	}
	catch (InvalidIndex){
		return _FEEDBACK_INVALID_INDEX;
	}
	catch (InvalidList){
		return _FEEDBACK_INVALID_LIST;
	}
}


//@author A0119513L
string Storage::Delete(int position){
	string feedback = "";
	try{
		lastList = taskList;
		feedback = Remove(position);
		Rewrite();
		Update();
		return feedback;
	}
	catch (out_of_range){
		return _FEEDBACK_DELETE_FAILURE;
	}
}

//@author A0099303A
string Storage::Edit(int position, Smartstring::LIST list, vector<string> newinfo){
	lastList = taskList;
	try{
		Task* taskptr = GetTask(position, list);
		Task* newTask = new Task(taskptr);
	//	(*newTask) = (*taskptr);
		newTask->Edit(newinfo);
		ReplaceTask(taskptr, newTask);
		Rewrite();
		Update();

		string feedback = _FEEDBACK_EDIT_SUCCESS;
		return feedback;
	}

	catch (InvalidIndex){
		return _FEEDBACK_INVALID_INDEX;
	}
	catch (InvalidList){
		return _FEEDBACK_INVALID_LIST;
	}
}

//@author A0099303A
string Storage::Complete(int position, Smartstring::LIST list){

	string feedback = "";
	lastList = taskList;

	try{
		Task* toComplete = GetTask(position, list);
		MarkComplete(toComplete);
		Archive(toComplete);
		Rewrite();
		Update();
		return _FEEDBACK_GENERIC_SUCCESS;
	}
	catch (InvalidIndex){
		return _FEEDBACK_INVALID_INDEX;
	}
	catch (InvalidList){
		return _FEEDBACK_INVALID_LIST;
	}


	//feedback = MarkComplete(position);
	//Archive(position);
	//Rewrite();
	//Update();
	return feedback;
}

//@author A0099303A
string Storage::Load(){
	logfile << LoadSessionData(); //change active file
	FILETYPE filetype = IdentifyFileType(_filename);
	string feedback;
	try{
		if (filetype != FILETYPE::INVALID){
			logfile << "load called.";
			ClearVectors();
			ClearUndoVector();
			logfile << LoadRawFileContent();
			feedback = LoadTaskList();
			logfile << feedback;
			Update();
			logfile << "end of load.";

		}
		else{
			logfile << _FEEDBACK_FILETYPE_INVALID;
			throw load_failure;
		}
	}
	
	catch (LoadFailure){
		logfile << DefaultSession();
		feedback = _FEEDBACK_LOAD_FAILURE;
	}
	return feedback;

}

//@author A0099303A
string Storage::Load(string filename){

	FILETYPE filetype = IdentifyFileType(filename);
	string feedback;
	try{
		if (filetype != FILETYPE::INVALID){
			_filename = filename;
			logfile << "load called.";
			ClearVectors();
			ClearUndoVector();
			logfile << LoadRawFileContent();
			feedback = LoadTaskList();
			logfile << feedback;
			Update();
			logfile << "end of load.";

		}
		else{
			logfile << _FEEDBACK_FILETYPE_INVALID;
		}
	}

	catch (LoadFailure){
		logfile << DefaultSession();
		feedback = _FEEDBACK_LOAD_FAILURE;
	}
	return feedback;
/*

	FILETYPE filetype = IdentifyFileType(filename);
	if (filetype != FILETYPE::INVALID){
		string feedback;
		_filename = filename;
		ClearVectors();
		ClearUndoVector();
		feedback = LoadRawFileContent();
		feedback = LoadTaskList();
		Update();
		logfile << _FEEDBACK_LOAD_SUCCESS << " " << filename;
		return feedback;
	}
	else{
		logfile << _FEEDBACK_FILETYPE_INVALID;
		return _FEEDBACK_FILETYPE_INVALID;
	}
*/
}


//@author A0099303A
string Storage::Save(){
	string feedback;
	feedback = Rewrite();
	feedback = SaveSessionData();
	return feedback;
}

//@author A0099303A
string Storage::SaveAs(string newFileName){
	FILETYPE filetype = IdentifyFileType(newFileName);
	if (filetype!= FILETYPE::INVALID){
		if (FileEmpty(newFileName)){
			_filename = newFileName;
			string feedback = Rewrite();
			feedback = SaveSessionData();
			return feedback;
		}
		else{
			return _FEEDBACK_FILE_NOT_EMPTY;
		}
		
	}
	else{
		return _FEEDBACK_FILETYPE_INVALID;
	}
}

//@author A0099303A
string Storage::Rewrite(){
	ClearFile();
	WriteToArchive();
	string feedback = WriteToFile();
	return feedback;
}

//@author A0099303A
string Storage::Reset(){
	_filename = _FILENAME_DEFAULT;
	Clear();
	return _FEEDBACK_RESET;
}

//@author A0099303A
string Storage::Clear(){
	lastList = taskList;
	ClearFile();
	ClearVectors();
	Update();
	return _FEEDBACK_CLEAR_SUCCESS;
}

//@author yizhi
string Storage::Undo(){
	if (!lastList.empty()){
		taskList = lastList;
		Rewrite();
		Update();
		return "success";
	}
	else{
		return "nothing to undo";
	}
	
}



//====================================================================
//Power Search
//====================================================================
//@author a0119491B
string Storage::Search(string input){
	vector<Task*> PowerSearch_Result = PowerSearch(input);
	if (PowerSearch_Result.empty()){
		return _FEEDBACK_SEARCH_FAILURE;
	}else{
		return ToString(PowerSearch_Result);
	}
}

//@author A0119491B
vector<Task*> Storage::PowerSearch(string input){
	vector<Task*>::iterator iter;
	vector<Task*> searchResult;
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
	try{
		DateTime* dt = new DateTime(input);
		string stdtm = dt->Standardized();
		if (dt->isValidFormat){
			InitializeDayTask(stdtm);
			SetDayCalendar();
			return GetEmptySlots();
		}
		else{
			throw invalid_input;
		}
	}
	catch (InvalidInput){
		return _FEEDBACK_SEARCH_FAILURE;
	}
}
//@author A0119491B
void Storage::InitializeDayTask(string date){
	for (int i = 0; i < taskList.size(); i++){
		string dateTime = taskList[i]->GetStartDate();
		size_t position = 0;
		position = dateTime.find_first_of(":"); // 17:00pm 07/04/2015 Only this format can be recognized
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
		string startDateTime = daytask[i]->GetStartDate();
		string endDateTime = daytask[i]->GetEndDate();
		size_t StartPos = 0, sPos = 2, ePos = 2;
		string startTime, endTime;
		int start_time, end_time;
		startTime = startDateTime.substr(StartPos, sPos); //17:00pm 07/04/2015    This is to get integer 17
		endTime = endDateTime.substr(StartPos, ePos);
		start_time = atoi(startTime.c_str());
		end_time = atoi(endTime.c_str());

		int indexStart = 2 * start_time;
		int indexEnd = 2 * end_time;

		for (int i = indexStart; i < indexEnd; i++){
			daycalendar[i] = "busy";
		}
	}
}

//@auhtor A0119491B
string Storage::GetEmptySlots(){
	int starthr = 0, endhr = 0, i = 0, time_intervals = 48;
	int sthour = 0, endhour = 0;
	while (i < time_intervals)
	{
		if (daycalendar[i] == "empty")
		{
			endhr++;
		}
		else if (daycalendar[i] == "busy" )
		{
			if ((starthr%2==0) && (endhr%2 == 0) && (starthr!=endhr))
			{
				ostringstream oss;
				sthour = starthr / 2;
				endhour = endhr / 2;
				oss << setw(2) << setfill('0') << sthour << ":" << "00" << " " << "to" << " " << setw(2) << setfill('0') << endhour << ":" << "00";
				string dbg = oss.str();
				emptyslots.push_back(oss.str());
			}
			else if ((starthr % 2 == 0) && (endhr % 2 != 0) && (starthr != endhr))
			{
				ostringstream oss;
				sthour = starthr / 2;
				endhour = endhr / 2;
				oss << setw(2) << setfill('0') << sthour << ":" << "00" << " " << "to" << " " << setw(2) << setfill('0') << endhour << ":" << "30";
				string dbg = oss.str();
				emptyslots.push_back(oss.str());
			}
			else if ((starthr%2 != 0) && (endhr%2 == 0) && (starthr != endhr)){
				ostringstream oss;
				sthour = starthr / 2;
				endhour = endhr / 2;
				oss << setw(2) << setfill('0') << sthour << ":" << "30" << " " << "to" << " " << setw(2) << setfill('0') << endhour << ":" << "00";
				string dbg = oss.str();
				emptyslots.push_back(oss.str());
			}
			else if ((starthr%2 != 0) && (endhr%2 != 0) && (starthr != endhr))
			{
				ostringstream oss;
				sthour = starthr / 2;
				endhour = endhr / 2;
				oss << setw(2) << setfill('0') << sthour << ":" << "30" << " " << "to" << " " << setw(2) << setfill('0') << endhour << ":" << "30";
				string dbg = oss.str();
				emptyslots.push_back(oss.str());
			}
			else{}
			
			starthr= i;
			endhr = starthr;
		}
		else{}

		i++;
	}
	
	/*for (int i = 0; i < 48; i++){
		starthr = endhr;
		while (daycalendar[i] == "empty"){
			endhr++;
		}

		if (starthr % 2 == 0 ){
			int hour = i / 2;
			ostringstream oss;
			oss << setw(2) << setfill('0') << hour << ":" << "00" << " " << "to" << " " << setw(2) << setfill('0') << hour << ":" << "30";
			string dbg = oss.str();
			emptyslots.push_back(oss.str());
		}else{
			int hour = i / 2;
			ostringstream oss;
			oss << setw(2) << setfill('0') << hour << ":" << "30" << " " << "to" << " " << setw(2) << setfill('0') << hour + 1 << ":" << "00";
			string dbg = oss.str();
			emptyslots.push_back(oss.str());
		}


		if (daycalendar[i] == "empty"){
			if (i % 2 == 0){
				int hour = i / 2;
				ostringstream oss;
				oss << setw(2) << setfill('0') << hour << ":" << "00" << " " << "to" << " " << setw(2) << setfill('0') << hour << ":" << "30";
				string dbg = oss.str();
				emptyslots.push_back(oss.str());
			}
			else{
				int hour = i / 2;
				ostringstream oss;
				oss << setw(2) << setfill('0') << hour << ":" << "30" << " " << "to" << " " << setw(2) << setfill('0') << hour + 1 << ":" << "00";
				string dbg = oss.str();
				emptyslots.push_back(oss.str());
			}
		}
	}*/
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

string Storage::GetFloatingList(){
	string output = ToString(floatingList);
	int size = floatingList.size();
	return ToString(floatingList);
}

string Storage::GetDeadlineList(){
	//string dbg = deadlineList.front()->Task::ToShortString();
	return ToString(deadlineList);
}

string Storage::GetTimedList(){
	return ToString(timedList);
}



//@author unknown
//====================================================================
//To be refactored
//====================================================================
string Storage::ToString(){
	Update();
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

string Storage::ToString(vector<Task*> V){
	ostringstream out;
	int index = 0;
	vector<Task*>::iterator iter;
	for (iter = V.begin(); iter != V.end(); ++iter){
		++index;
		if (iter + 1 != V.end()){
			out << _rtfboldtagstart << index << ": " << _rtfboldtagend << (*iter)->ToShortString() << endl;
		}
		else{
			out << _rtfboldtagstart << index << ": " << _rtfboldtagend << (*iter)->ToShortString();
		}
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
		++index;
		if (iter + 1 != taskList.end()){
			out <<_rtftab << _rtfboldtagstart << index << ": " << _rtfboldtagend << (*iter)->ToDatelessString() << endl;
		}
		else{
			out <<_rtftab << _rtfboldtagstart << index << ": " << _rtfboldtagend << (*iter)->ToDatelessString();
		}
	}
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


//@author Ziqi
//====================================================================
//Filter Methods
//====================================================================

//@author A0119491B
void Storage::FilterTask(){
	ClearFilteredLists();
	initializeLists();
	sortTask();
	rearrangeTaskList();
	return;
}
//@author A0119491B
void Storage::initializeLists(){
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
void Storage::sortTask(){
	sortListsByTime(timedList);
	sortListsByTime(deadlineList);
}
//@author A0119491B
void Storage::sortListsByTime(vector <Task*> &V){
	int size_V = V.size();
	string datetime1, datetime2;
	for (int i = 0; i < size_V; i++){
		for (int j = i; j < size_V; ++j){
			datetime1 = V[i]->GetStartDate();
			datetime2 = V[j]->GetStartDate();

			if (datetime1 == "" && datetime2 == ""){
				datetime1 = V[i]->GetEndDate();
				datetime2 = V[j]->GetEndDate();
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
void Storage::rearrangeTaskList(){
	taskList.clear();
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
	return;
}

//@author A0099303A
void Storage::ClearUndoVector(){
	lastList.clear();
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
//Save methods
//====================================================================
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
	case (FILETYPE::CSV) : {
		feedback = WriteToCSV();
		break;
	}
	case(FILETYPE::TXT) : {
		feedback = WriteToTXT();
		break;
	}
	case(FILETYPE::INVALID) : {
		return _FEEDBACK_INVALID_FILE_FORMAT;
		break;
	}
	}
	return feedback;

}

//@author A0099303A
string Storage::WriteToCSV(){
	ostringstream out;
	ofstream of;
	of.open(_filename.c_str(), ios::app);
	vector<Task*>::iterator iter;
	int size = taskList.size();
	for (iter = taskList.begin(); iter != taskList.end(); ++iter){
		if (iter + 1 != taskList.end()){
			out << (*iter)->ToCSVString() << endl;
		}
		else{
			out << (*iter)->ToCSVString();
		}
	}
	string str = out.str();
	of << out.str();
	return _FEEDBACK_WRITE_SUCCESS;
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
	of.open(_archivefile.c_str(), ios::app);
	vector<Task*>::iterator iter;
	int size = archiveList.size();
	for (iter = archiveList.begin(); iter != archiveList.end(); ++iter){
		out << (*iter)->ToCSVString() << endl;
	}
	archiveList.clear();
	string str = out.str();
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
		return _FEEDBACK_LOAD_FAILURE;
	}
	return _FEEDBACK_LOAD_FAILURE;
}

//@author A0099303A
string Storage::LoadTaskList(){
	FILETYPE filetype = IdentifyFileType(_filename);
	string feedback;
	switch (filetype){
	case (FILETYPE::CSV) : {
		feedback = LoadCSVContent();
		break;
	}
	case(FILETYPE::TXT) : {
		feedback = LoadTXTContent();
		break;
	}
	case(FILETYPE::INVALID) : {
		return _FEEDBACK_LOAD_FAILURE;
		break;
	}
	}
	return feedback;
	
}

//@author A0099303A
string Storage::LoadCSVContent(){
	Smartstring str;
	const int startfield = Smartstring::FIELD::DESCRIPTION;
	int currentfield = startfield;
	int fieldcount = Smartstring::NUMBER_OF_FIELDS;
	vector<string>::iterator iter;
	Task* taskptr = new Task();
	try{
		int msize = _filecontent.size();
		for (iter = _filecontent.begin(); iter != _filecontent.end(); ++iter){
			str = (*iter);
			vector<string> output = str.ContainedTokenize(_DELIMITERS_CSV);
			vector<string>::iterator iter2;

			string test = output.front();
			if (output.size() != Smartstring::NUMBER_OF_FIELDS){
				throw corrupted_data;
				return _FEEDBACK_DATA_CORRUPTED;
			}
			taskptr = new Task(output);
			taskList.push_back(taskptr);
		}
	}

	catch (out_of_range){
		return _FEEDBACK_LOAD_FAILURE;
	}
	return _FEEDBACK_LOAD_SUCCESS;
	return _FEEDBACK_LOAD_FAILURE;
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
				taskptr->SetStartDate(*iter);
				break;
			}
			case Smartstring::FIELD::ENDDATE:{
				taskptr->SetEndDate(*iter);
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
		return _FEEDBACK_LOAD_FAILURE;
	}
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
	//else{
	//	if (input.find(_FILE_EXTENSION_CSV) != string::npos){
	//		return FILETYPE::INVALID;
	//		return FILETYPE::CSV;
	//	}
	//	else{
	//		return FILETYPE::INVALID;
	//	}
	//}
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
Task* Storage::GetTask(int position, Smartstring::LIST list){
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