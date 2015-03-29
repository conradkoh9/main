#include "Logic.h"

//adding functionality
//1. Add case to Execute
//2. Add function itself in header and cpp

const string Logic::_FEEDBACK_ERROR_INVALID_INDEX = "INVALID INDEX";
ostringstream Logic::fout; //floating task display stream
ostringstream Logic::tout; //timed task display stream
ostringstream Logic::dout; //deadline task display stream
ostringstream Logic::mout; //main display stream
Logic::Logic()
{
	parser = new Parser();
	storage = new Storage("default.txt");
	tout << "test timed task display";
	dout << "test deadline task display";
	fout << "test floating task display";
	mout << "test main display";
	logfile << "Logic created";
}

Logic::Logic(string input){
	parser = new Parser();
	storage = new Storage(input);
	tout << "test timed task display";
	dout << "test deadline task display";
	fout << "test floating task display";
	mout << "test main display";
	logfile << "Logic created";
}

Logic::~Logic()
{
}

string Logic::Run(string input){
	string feedback = Execute(input);
	storage->FilterTask();
	mout << feedback;
	fout << storage->GetFloatingList(); 
	dout << storage->GetDeadlineList(); 
	tout << storage->GetTimedList(); 
	return feedback;
}

string Logic::Execute(string input){
	Smartstring::COMMAND cmd = parser->IdentifyCommand(input);
	string taskInput = parser->RemoveCommand(input);
	string feedback;
	switch (cmd){
	case (Smartstring::COMMAND::ADD) : {
		feedback = Add(taskInput);
		break;
	}
	case (Smartstring::COMMAND::DELETE) : {
		feedback = Delete(taskInput);
		break;
	}
	case (Smartstring::COMMAND::DISPLAY) : {
		feedback = Display();
		break;
	}
	case(Smartstring::COMMAND::EDIT) : {
		feedback = Edit(taskInput);
		break;
	}
	case (Smartstring::COMMAND::SEARCH) : {
		feedback = Search(taskInput);
		break;
	}
	case (Smartstring::COMMAND::CLEAR) : {
		feedback = Clear();
		break;
	}

	case (Smartstring::COMMAND::EXIT) : {
		exit = true;
		break;
	}
	}
	return feedback;
}

string Logic::Add(string taskInput){
	vector<string> taskinfo = parser->IdentifyTaskFields(taskInput);
	Task* task = new Task(taskinfo);
	string feedback = storage->Add(task);

	return task->ToString();
}

string Logic::Delete(string taskInput){
	int position = atoi(taskInput.c_str());
	return storage->Delete(position);
}

string Logic::Display(){
	string output = storage->ToString();
	return output;
}

string Logic::Edit(string taskInput){
	activeTaskList.clear();
	Task* taskptr;
	string indexstr;
	//select 
	istringstream in(taskInput);
	in >> indexstr;
	int index = atoi(indexstr.c_str());
	if (index <= storage->taskList.size() && index>0){
		index = index - 1; //converting from user index to vector index
		taskptr = storage->taskList[index];
	}
	else{
		return _FEEDBACK_ERROR_INVALID_INDEX;
	}
	//end select

	//analyze string as vect and replace
	//assumption: the IdentifyTaskFields has same ordering as *taskptr
	string remainder;
	getline(in, remainder);
	vector<string> modified = parser->IdentifyTaskFields(remainder);
	for (int i = 0; i < modified.size(); ++i){
		if (modified[i] != ""){
			switch (i){
			case Smartstring::FIELD::DESCRIPTION:{
				taskptr->SetDescription(modified[i]);
				break;
			}
			case Smartstring::FIELD::STARTDATE:{
				taskptr->SetStartDate(modified[i]);
				break;
			}
			case Smartstring::FIELD::ENDDATE:{
				taskptr->SetEndDate(modified[i]);
				break;
			}
			case Smartstring::FIELD::PRIORITY:{
				taskptr->SetPriority(modified[i]);
				break;
			}
			}
		}
	}
	//end analyze string as vect and replace

	return taskptr->ToString();
}

string Logic::Search(string taskInput){
		return storage->search(taskInput);
}

string Logic::Clear(){
	string feedback = storage->Clear();
	return feedback;
}