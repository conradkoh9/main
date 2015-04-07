#include "Storage.h"

//Constant variable declaration
const string Storage::_FEEDBACK_GENERIC_SUCCESS = "STORAGE SUCCESS";
const string Storage::_FEEDBACK_GENERIC_FAILURE = "STORAGE FAILED";
const string Storage::_FEEDBACK_LOAD_SUCCESS = "LOAD SUCCESS";
const string Storage::_FEEDBACK_LOAD_FAILURE = "LOAD FAILED";
const string Storage::_FEEDBACK_WRITE_SUCCESS = "WRITE SUCCESS";
const string Storage::_FEEDBACK_WRITE_FAILURE = "WRITE FAILED";
const string Storage::_FEEDBACK_CLEAR_SUCCESS = "CLEAR SUCCESS";
const string Storage::_FEEDBACK_CLEAR_FAILURE = "CLEAR FAILED";
const string Storage::_FEEDBACK_DELETE_SUCCESS = "DELETE SUCCESS";
const string Storage::_FEEDBACK_DELETE_FAILURE = "DELETE FAILED";
const string Storage::_FEEDBACK_SEARCH_FAILURE = "No results found.";
const string Storage::_FEEDBACK_FILE_EMPTY = "FILE EMPTY";
const string Storage::_FEEDBACK_FILE_NOT_EMPTY = "FILE NOT EMPTY";
const string Storage::_FEEDBACK_INVALID_FILE_FORMAT = "Invalid file format entered";
const string Storage::_EMPTY_STRING= "";
const string Storage::_FEEDBACK_SESSION_LOAD_FAILURE = "Session failed to load. Starting default session";
const string Storage::_FEEDBACK_SESSION_LOAD_SUCCESS = "Session loaded.";
const string Storage::_FEEDBACK_SESSION_SAVE_SUCCESS = "Session saved";
const string Storage::_FEEDBACK_SESSION_SAVE_FAILURE = "Session failed to save.";
const string Storage::_FEEDBACK_RESET = "Reset";
const string Storage::_FEEDBACK_INVALID_INDEX = "Invalid index.";
const string Storage::_FEEDBACK_UPDATE_SUCCESS = "Update success.";
//formatting variables
const string Storage::_rtfboldtagstart = "\\b ";
const string Storage::_rtfboldtagend = "\\b0 ";

//@author A0099303A
//PUBLIC =================================================================================================
Storage::Storage(){
	status << Load();
}

Storage::Storage(string input){
	_filename = input;
	Update();
}

Storage::~Storage(){
}

//@author A0099303A
string Storage::Add(Task* task){
	taskList.push_back(task);
	string feedback = Rewrite();
	Update();
	return feedback;
}

//@author A0099303A
string Storage::Delete(int position){
	string feedback = "";
	try{
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
string Storage::Complete(int position){
	string feedback = "";
	feedback = MarkComplete(position);
	Rewrite();
	Update();
	return feedback;
}

//@author A0099303A
string Storage::Load(){
	logfile << "load called.";
	string feedback;
	logfile << LoadSessionData(); //change active file
	ClearVectors();
	feedback = LoadRawFileContent();
	logfile << feedback;
	logfile << LoadTaskList();
	Update();
	logfile << "end of load.";
	return feedback;
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
	if (FileEmpty(newFileName) && filetype!= FILETYPE::INVALID){
		_filename = newFileName;
		string feedback = Rewrite();
		feedback = SaveSessionData();
		return feedback;
	}
	else{
		return _FEEDBACK_FILE_NOT_EMPTY;
	}
}

//@author A0099303A
string Storage::Rewrite(){
	ClearFile();
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
	ClearFile();
	ClearVectors();
	Update();
	return _FEEDBACK_CLEAR_SUCCESS;
}


//@author Ziqi
//please replace the tag above with your matriculation number
//====================================================================
//Power Search
//====================================================================
string Storage::Search(string input){
	vector<Task*> PowerSearch_Result = PowerSearch(input);
	vector<Task*> NearSearch_Result = NearSearch(input);
	if (PowerSearch_Result.empty() && NearSearch_Result.empty()){
		return _FEEDBACK_SEARCH_FAILURE;
	}
	else if (PowerSearch_Result.empty() && !NearSearch_Result.empty()){
		return ToString(NearSearch_Result);
	}
	else
	{
		return ToString(PowerSearch_Result);
	}
}

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

vector<Task*> Storage::NearSearch(string input){
	vector<Task*>::iterator iter;
	vector<Task*> searchResult;
	for (iter = taskList.begin(); iter != taskList.end(); ++iter){
		Task* currentTask = *iter;
		if (currentTask->isNearMatch(input)){
			searchResult.push_back(currentTask);
		}
	}
	return searchResult;
}

string Storage::SearchEmptySlots(string input){
	if (dateTime->isDateType(input)){
		string date = dateTime->ConvertDateTime(input);
		
		InitializeDayTask(date);
		SetDayCalendar();
		return GetEmptySlots();
	}else{
		return _FEEDBACK_SEARCH_FAILURE;
	}
}

void Storage::InitializeDayTask(string date){
	for (int i = 0; i < taskList.size(); i++){
		string dateTime = taskList[i]->GetStandardStartDateTime();
		size_t position = 0;
		position = dateTime.find_first_of(" ");
		if (position != string::npos){
			daytask.push_back(taskList[i]);
		}	
	}
}

void Storage::SetDayCalendar(){
	InitializeDayCalendar();
	SetSleepingTime();
	SetOccupiedSlots();
}

void Storage::InitializeDayCalendar(){
	for (int i = 0; i < 48; i++){
		daycalendar[i] = "empty";
	}
}

void Storage::SetSleepingTime(){
	int sleeping_time = 14; //from 00:00am to 7:00am 
	for (int i = 0; i < 14; i++){
		daycalendar[i] = "sleeping";
	}
	daycalendar[48] = "sleeping"; //from 23:00pm to 00:00am
	daycalendar[47] = "sleeping";
}

void Storage::SetOccupiedSlots(){
	for (int i = 0; i < daytask.size(); i++){
		string startDateTime = daytask[i]->GetStandardStartDateTime();
		string endDateTime = daytask[i]->GetStandardEndDateTime();
		size_t StartPos = 0, sPos = 0, ePos = 0;
		sPos = startDateTime.find_first_of(":");
		ePos = endDateTime.find_first_of(":");
		string startTime, endTime;
		int start_time, end_time;
		startTime = startDateTime.substr(StartPos, sPos);
		endTime = endDateTime.substr(StartPos, ePos);
		start_time = stoi(startTime.c_str());
		end_time = stoi(endTime.c_str());

		int indexStart = 2 * start_time;
		int indexEnd = 2 * end_time;

		for (int i = indexStart; i < indexEnd; i++){
			daycalendar[i] = "busy";
		}
	}
}


string Storage::GetEmptySlots(){
	for (int i = 0; i < 48; i++){
		if (daycalendar[i] == "empty"){
			if (i % 2 == 0){
				int hour = i / 2;
				ostringstream oss;
				oss << hour << ":" << "00"<<" "<<"to"<<" "<<hour<<":"<<30<<endl;
				emptyslots.push_back(oss.str());
			}else{
				int hour = i / 2 - 1;
				ostringstream oss;
				oss << hour << ":" << "30" << " " << "to" << " "<<hour+1<<":"<<00<<endl;
				emptyslots.push_back(oss.str());
			}
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

string Storage::GetFloatingList(){
	string output = ToString(floatingList);
	int size = floatingList.size();
	return ToString(floatingList);
}

string Storage::GetDeadlineList(){
	return ToString(deadlineList);
}

string Storage::GetTimedList(){
	return ToString(timedList);
}



//====================================================================
//To be refactored
//====================================================================
string Storage::ToString(){
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


//PRIVATE==========================================================================================
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

void Storage::FilterTask(){
	ClearFilteredLists();
	sortTaskListsByTime();
	initializeLists();
	return;
}

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

void Storage::sortTaskListsByTime(){
	int size_taskList = taskList.size();
	for (int i = 1; i < size_taskList; i++){
		for (int j = 1; j < size_taskList - i;++j){
			string sdStart1 = taskList[j - 1]->GetStandardStartDateTime();
			string sdStart2 = taskList[j]->GetStandardStartDateTime();
			if (dateTime->CompareDateTime(sdStart1,sdStart2)){
				Task* temp = taskList[j-1];
				taskList[j-1] = taskList[j];
				taskList[j] = temp;
			}
		}
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
string Storage::Remove(int position){
	try{
		int size_taskList = taskList.size();
		if (position > size_taskList){
			throw out_of_range("invalid index");
		}
		taskList.erase(taskList.begin() + position - 1);
	}
	catch (out_of_range){
		throw out_of_range("invalid index");
		return _FEEDBACK_DELETE_FAILURE;
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
	try{
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
	}
	catch (out_of_range){
		throw out_of_range(_FEEDBACK_WRITE_FAILURE);
		return _FEEDBACK_WRITE_FAILURE;
	}

	return _FEEDBACK_WRITE_SUCCESS;
}

//@author A0099303A
string Storage::WriteToTXT(){
	ostringstream out;
	ofstream of;
	of.open(_filename.c_str(), ios::app);
	vector<Task*>::iterator iter;
	try{
		for (iter = taskList.begin(); iter != taskList.end(); ++iter){
			if (iter + 1 != taskList.end()){
				out << (*iter)->ToTXTString() << endl;
			}
			else{
				out << (*iter)->ToTXTString();
			}
		}
		of << out.str();
	}
	catch (out_of_range){
		throw out_of_range(_FEEDBACK_WRITE_FAILURE);
		return _FEEDBACK_WRITE_FAILURE;
	}

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
			vector<string> output = str.Tokenize(_DELIMITERS_CSV);
			vector<string>::iterator iter2;
			for (iter2 = output.begin(); iter2 != output.end(); ++iter2){
				int end = (*iter2).length() - 2;
				*iter2 = (*iter2).substr(1, end);
			}
			string test = output.front();
			if (output.size() != Smartstring::NUMBER_OF_FIELDS){
				assert(false && "In Storage LoadCSVContent load failed, size does not match definition");
				return _FEEDBACK_LOAD_FAILURE;
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
string Storage::MarkComplete(int position){
	try{
		int size_taskList = taskList.size();
		if (position > size_taskList){
			throw out_of_range("invalid index");
		}
		taskList[position - 1]->MarkComplete();
	}
	catch (out_of_range){
		throw out_of_range("invalid index");
		return _FEEDBACK_INVALID_INDEX;
	}
	return _FEEDBACK_UPDATE_SUCCESS;
}

//====================================================================
//File analysis methods
//====================================================================
//@author A0099303A
Storage::FILETYPE Storage::IdentifyFileType(string input){
	if (input.find(_FILE_EXTENSION_CSV) != string::npos){
		return FILETYPE::CSV;
	}
	else{
		if (input.find(_FILE_EXTENSION_TXT) != string::npos){
			return FILETYPE::TXT;
		}
		else{
			return FILETYPE::INVALID;
		}
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