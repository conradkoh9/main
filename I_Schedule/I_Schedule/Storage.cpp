#include "Storage.h"

//PUBLIC
Storage::Storage(){
	_filename = "default.txt";
	Load();
	FilterTask();
	logfile << "Storage created";
}

Storage::Storage(string filename){
	_filename = filename;
	Load();
	FilterTask();
	logfile << "Storage created with filename: " + filename;
}

Storage::~Storage(){
}
string Storage::Add(Task* task){
	taskList.push_back(task);
	string feedback = Rewrite();
	return feedback;
}

string Storage::Load(){
	try{
		ClearVectors();
		LoadRawFileContent();
		LoadTaskList();
	}
	catch (out_of_range){
		return _FEEDBACK_LOAD_FAILURE;
	}
	return _FEEDBACK_LOAD_SUCCESS;
}

string Storage::Save(string newFileName){
	if (FileEmpty(newFileName)){
		_filename = newFileName;
		string feedback = Rewrite();
		return feedback;
	}
	else{
		return _FEEDBACK_FILE_NOT_EMPTY;
	}
	
}

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

string Storage::LoadTaskList(){
	FILETYPE filetype = IdentifyFileType();
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

	//=======
	
}
string Storage::LoadCSVContent(){
	Smartstring str;
	const int startfield = Smartstring::FIELD::DESCRIPTION;
	int currentfield = startfield;
	int fieldcount = Smartstring::NUMBER_OF_FIELDS;
	vector<string>::iterator iter;
	Task* taskptr = new Task();
	try{
		for (iter = _filecontent.begin(); iter != _filecontent.end(); ++iter){
			str = (*iter);
			vector<string> output = str.Tokenize(_DELIMITERS_CSV);
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

			}
			currentfield = (currentfield + 1) % fieldcount;
		}
	}

	catch (out_of_range){
		return _FEEDBACK_LOAD_FAILURE;
	}
	return _FEEDBACK_LOAD_SUCCESS;
}

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
string Storage::Rewrite(){
	ClearFile();
	string feedback = WriteVectors();
	return feedback;
}

string Storage::ToString(){
	ostringstream out;
	int index = 0;
	vector<Task*>::iterator iter;
	for (iter = taskList.begin(); iter != taskList.end(); ++iter){
		++index;
		if (iter + 1 != taskList.end()){
			out << index << ": " << (*iter)->ToShortString() << endl;
		}
		else{
			out << index << ": " << (*iter)->ToShortString();
		}
	}
	return out.str();
}

void Storage::FilterTask(){
	timedList.clear();
	deadlineList.clear();
	floatingList.clear();
	int size_taskList = taskList.size();

	for (int i = 0; i < size_taskList; i++){
		if (taskList[i]->GetType() == Task::TASKTYPE::TIMED){
			timedList.push_back(taskList[i]);
		}else if (taskList[i]->GetType() == Task::TASKTYPE::DEADLINE){
			deadlineList.push_back(taskList[i]);
		}else if (taskList[i]->GetType() == Task::TASKTYPE::FLOATING){
			floatingList.push_back(taskList[i]);
		}else{
		}
	}
}

string Storage::Clear(){
	ClearFile();
	ClearVectors();
	return _FEEDBACK_CLEAR_SUCCESS;
}

string Storage::ClearFile(){
	ofstream out(_filename, ofstream::trunc);
	return _FEEDBACK_CLEAR_SUCCESS;
}
vector<string> Storage::GetContent(){
	return _filecontent;
}

string Storage::ClearVectors(){
	taskList.clear();
	timedList.clear();
	floatingList.clear();
	deadlineList.clear();
	_filecontent.clear();
	return _FEEDBACK_CLEAR_SUCCESS;
}

string Storage::Delete(int position){
	string feedback = "";
	try{
		feedback = Remove(position);
		Rewrite();
		return feedback;
	}
	catch (out_of_range){
		return _FEEDBACK_DELETE_FAILURE;
	}
}

vector<Task*> Storage::GetTaskList(){
	return taskList;
}

string Storage::GetTimedList(){
	return ToString(timedList);
}

string Storage::GetDeadlineList(){
	return ToString(deadlineList);
}

string Storage::GetFloatingList(){
	string output = ToString(floatingList);
	int size = floatingList.size();
	return ToString(floatingList);
}

string Storage::search(string input){
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
		if (currentTask->Contains(input)){
			searchResult.push_back(currentTask);
		}
	}
	currentScope = searchResult;
	return searchResult;
}

vector<Task*> Storage::NearSearch(string input){
	vector<Task*>::iterator iter;
	vector<Task*> searchResult;
	for (iter = taskList.begin(); iter != taskList.end(); ++iter){
		Task* currentTask = *iter;
		if (currentTask->NearMatch(input)){
			searchResult.push_back(currentTask);
		}
	}
	return searchResult;
}

/*vector<string> Storage::GetEmptySlots(string input){
	vector<string> wholeDay;
	string startTime;
	string endTime; //use DateTime class to convert input
	for (int i = 0; i < 24; i++){
		wholeDay.push_back(""); //Use DateTime class to initialize 
	}

}*/

string Storage::ToString(vector<Task*> V){
	ostringstream out;
	int index = 0;
	vector<Task*>::iterator iter;
	for (iter = V.begin(); iter != V.end(); ++iter){
		++index;
		if (iter + 1 != V.end()){
			out << index << ": " << (*iter)->ToShortString() << endl;
		}
		else{
			out << index << ": " << (*iter)->ToShortString();
		}
	}
	return out.str();
}



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
string Storage::WriteVectors(){
	FILETYPE filetype = IdentifyFileType();
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

string Storage::WriteToCSV(){
	ostringstream out;
	ofstream of;
	of.open(_filename.c_str(), ios::app);
	vector<Task*>::iterator iter;
	try{
		for (iter = taskList.begin(); iter != taskList.end(); ++iter){
			if (iter + 1 != taskList.end()){
				out << (*iter)->ToCSVString() << endl;
			}
			else{
				out << (*iter)->ToCSVString();
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

string Storage::WriteToTXT(){
	ostringstream out;
	ofstream of;
	of.open(_filename.c_str(), ios::app);
	vector<Task*>::iterator iter;
	try{
		for (iter = taskList.begin(); iter != taskList.end(); ++iter){
			if (iter + 1 != taskList.end()){
				out << (*iter)->ToString() << endl;
			}
			else{
				out << (*iter)->ToString();
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

Storage::FILETYPE Storage::IdentifyFileType(){
	if (_filename.find(_FILE_EXTENSION_CSV) != string::npos){
		return FILETYPE::CSV;
	}
	else{
		if (_filename.find(_FILE_EXTENSION_TXT) != string::npos){
			return FILETYPE::TXT;
		}
		else{
			return FILETYPE::INVALID;
		}
	}
}