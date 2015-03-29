#include "Storage.h"

//PUBLIC
Storage::Storage(){
	_filename = "default.txt";
	Load();
	logfile << "Storage created";
}

Storage::Storage(string filename){
	_filename = filename;
	Load();
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
		LoadFileContent();
		LoadTaskList();
	}
	catch (out_of_range){
		return _FEEDBACK_LOAD_FAILURE;
	}
	return _FEEDBACK_LOAD_SUCCESS;
}

string Storage::LoadFileContent(){
	string line;
	vector<string> all_lines;
	ifstream in(_filename.c_str());
	try{
		if (in.is_open()){
			while (getline(in, line)){
				if (line == _EMPTY_STRING){
					return _FEEDBACK_FILE_EMPTY;
				}
				//remove field description
				istringstream is(line);
				string buffer;
				is >> buffer;
				string output;
				getline(is, output);
				int length = line.length() - 1;
				output = output.substr(1, length);
				//end remove field description
				all_lines.push_back(output);
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
	Smartstring str;
	const int startfield = Smartstring::FIELD::DESCRIPTION;
	int currentfield = startfield;
	int fieldcount = Smartstring::NUMBER_OF_FIELDS;
	vector<string>::iterator iter;
	Task* taskptr = new Task();
	try{
		for (iter = _filecontent.begin(); iter != _filecontent.end(); ++iter){
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
	ostringstream out;
	ofstream of;
	of.open(_filename.c_str(), ios::app);
	vector<Task*>::iterator iter;
	try{
		for (iter = taskList.begin(); iter != taskList.end(); ++iter){
			out << (*iter)->ToString() << endl;
		}
		of << out.str();
	}
	catch (out_of_range){
		throw out_of_range(_FEEDBACK_WRITE_FAILURE);
		return _FEEDBACK_WRITE_FAILURE;
	}

	return _FEEDBACK_WRITE_SUCCESS;
}