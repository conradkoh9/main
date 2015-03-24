#include "Storage.h"
#include "Smartstring.h"
#include "Parser.h"

//PUBLIC
Storage::Storage(){
	_filename = "default.txt";
	Load();
}

Storage::Storage(string filename){
	_filename = filename;
	Load();
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

string Storage::search(vector<string>& input){
	int size_taskList = taskList.size();
	vector<Task*> searchingResult;
	initializeSearchingVector(searchingResult, size_taskList);
	string resultString;
	Smartstring::FIELD field;

	if (!input[Smartstring::FIELD::DESCRIPTION].empty()){
		field = Smartstring::FIELD::DESCRIPTION;
		if (searchingResult.empty()){
			searchTaskList(input[Smartstring::FIELD::DESCRIPTION], searchingResult, field);
		}
		else{
			searchResultVector(searchingResult, input[Smartstring::FIELD::DESCRIPTION], field);
		}
		if (searchingResult.empty()){
			return _FEEDBACK_SEARCH_FAILURE;
		}
	}

		if (!input[Smartstring::FIELD::STARTDATE].empty()){
			field = Smartstring::FIELD::STARTDATE;
			if (searchingResult.empty()){
				searchTaskList(input[Smartstring::FIELD::STARTDATE], searchingResult, field);
			}else{
				searchResultVector(searchingResult, input[Smartstring::FIELD::STARTDATE], field);
			}
			if (searchingResult.empty()){
				return _FEEDBACK_SEARCH_FAILURE;
			}
		}
	
	
	if (!input[Smartstring::FIELD::ENDDATE].empty()){
		field = Smartstring::FIELD::ENDDATE;
		if (searchingResult.empty()){
			searchTaskList(input[Smartstring::FIELD::ENDDATE], searchingResult, field);
		}else{
			searchResultVector(searchingResult, input[Smartstring::FIELD::ENDDATE], field);
		}
		if (searchingResult.empty()){
			return _FEEDBACK_SEARCH_FAILURE;
		}
	}

	if (!input[Smartstring::FIELD::PRIORITY].empty()){
		field = Smartstring::FIELD::PRIORITY;
		if (searchingResult.empty()){
			searchTaskList(input[Smartstring::FIELD::PRIORITY], searchingResult, field);
		}else{
			searchResultVector(searchingResult, input[Smartstring::FIELD::PRIORITY], field);
		}
		if (searchingResult.empty()){
			return _FEEDBACK_SEARCH_FAILURE;
		}
	}

	//To display result 
	resultString = ToString(searchingResult);

	return resultString;
}

void Storage::initializeSearchingVector(vector<Task*>& searchingResult, int size_taskList){
	for (int i = 0; i < size_taskList; i++)
	{
		searchingResult[i]->Task::Task();
	}
}

void Storage::searchTaskList(string keyword, vector<Task*>& searchingResult, Smartstring::FIELD field){
	int size_taskList = taskList.size();
	for (int i = 0; i < size_taskList; i++)
	{
		if (field == Smartstring::FIELD::DESCRIPTION){
			string description = taskList[i]->GetDescription();
			if (isContained(keyword, description)){
				searchingResult.push_back(taskList[i]);
			}

		}
		else if (field == Smartstring::FIELD::STARTDATE){
			string startDate = taskList[i]->GetStartDate();
			if (isContained(keyword, startDate)){
				searchingResult.push_back(taskList[i]);
			}

		}
		else if (field == Smartstring::FIELD::ENDDATE){
			string endDate = taskList[i]->GetEndDate();
			if (isContained(keyword, endDate)){
				searchingResult.push_back(taskList[i]);
			}

		}
		else{
			string priority = taskList[i]->GetPriority();
			if (isContained(keyword, priority)){
				searchingResult.push_back(taskList[i]);
			}
		}
	}
}

void Storage::searchResultVector(vector<Task*>& searchingResult, string keyword, Smartstring::FIELD field){
	int size_resultVector = searchingResult.size();

	for (int i = 0; i < size_resultVector; i++)
	{
		if (field == Smartstring::FIELD::DESCRIPTION){
			string description = searchingResult[i]->GetDescription();
			if (!isContained(keyword, description)){
				searchingResult.erase(searchingResult.begin() + i);
			}

		}
		else if (field == Smartstring::FIELD::STARTDATE){
			string startDate = searchingResult[i]->GetStartDate();
			if (isContained(keyword, startDate)){
				searchingResult.erase(searchingResult.begin() + i);
			}

		}
		else if (field == Smartstring::FIELD::ENDDATE){
			string endDate = searchingResult[i]->GetEndDate();
			if (isContained(keyword, endDate)){
				searchingResult.erase(searchingResult.begin() + i);
			}

		}
		else{
			string priority = searchingResult[i]->GetPriority();
			if (isContained(keyword, priority)){
				searchingResult.erase(searchingResult.begin() + i);
			}
		}
	}
}



bool Storage::isContained(string keyword, string description){
	//do we need convert to lower?
	int sizeOfDescription = description.size();
	char token = ' ';
	string newKeyword = convertToLower(keyword);
	string newDescription = convertToLower(description);
	for (int i = 0; i < sizeOfDescription; i++){
		vector<string> tokenVector;
		getTokens(newDescription, tokenVector, token);
		if (isContainingKeyword(keyword, tokenVector)){
			return true;
		}
	}
	return false;
}

string Storage::convertToLower(string str){
	int legthOfString = str.length();
	for (int i = 0; i < legthOfString; i++)
	{
		//If the character is not a space
		if (str[i] != ' '){
			//Reset the value of the array position to the new lower case letter
			str[i] = tolower(str[i]);
		}
	}
	return str;
}

void Storage::getTokens(string str, vector<string>& tokenVector, char token){
	int lastPosition = str.find_first_not_of(token, 0);
	int position = str.find_first_of(token, lastPosition);
	while (position != string::npos || lastPosition != string::npos){
		tokenVector.push_back(str.substr(lastPosition, position - lastPosition));
		lastPosition = str.find_first_not_of(token, position);
		position = str.find_first_of(token, lastPosition);
	};
	return;
}

bool Storage::isContainingKeyword(string keyword, vector<string>& tokenVector){
	int sizeOfTokenVector = tokenVector.size();

	for (int i = 0; i < sizeOfTokenVector; i++){
		if (keyword == tokenVector[i]){
			return true;
		}
	}
	return false;
}

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
		if (position > taskList.size()){
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