#include "Storage.h"

//PUBLIC
Storage::Storage(){
	_filename = "default.txt";
}

Storage::Storage(string filename){
	_filename = filename;
}


Storage::~Storage(){
}

string Storage::loadFile(){
	string line;
	vector<string> all_lines;
	ifstream in(_filename.c_str());
	if (in.is_open()){
		while (getline(in, line)){
			if (line == _EMPTY_STRING){
				return _FEEDBACK_FILE_EMPTY;
			}
			all_lines.push_back(line);
		}
		_content = all_lines;
		return _FEEDBACK_LOAD_SUCCESS;
	}

	return _FEEDBACK_LOAD_FAILURE;
	
}
string Storage::writeToFile(string input){
	ofstream out;
	out.open(_filename.c_str(), ofstream::out | ofstream::app);
	if (out.is_open()){
		out << input;
		out.close();
		return _FEEDBACK_WRITE_SUCCESS;
	}
	
	return _FEEDBACK_WRITE_FAILURE;
}
string Storage::clearFile(){
	ofstream out(_filename);
	if (out.is_open()){
		return _FEEDBACK_CLEAR_SUCCESS;
	}
	return _FEEDBACK_CLEAR_FAILURE;
}
vector<string> Storage::getContent(){
	return _content;
}