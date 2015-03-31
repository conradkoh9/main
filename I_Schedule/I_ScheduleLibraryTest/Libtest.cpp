#include "stdafx.h"
#include "CppUnitTest.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace I_ScheduleLibraryTest{		
	TEST_CLASS(myLibTest)
	{
	public:
		TEST_METHOD(STORAGE_TXT_ADD){
			string expected[2];
			vector<Task*> tasklist;
			//testing the partiton n>0; boundary case n = 1; where n is the number of tasks added
			Storage* storage = new Storage("Storage_Add.txt");
			storage->Clear();
			Task* task = new Task();
			task->SetDescription("do homework");
			task->SetEndDate("tomorrow");
			task->SetStartDate("today");
			task->SetPriority("1");
			storage->Add(task);

			expected[0] = "Description: do homework\nStart: today\nEnd: tomorrow\nPriority: 1";
			Assert::AreEqual(expected[0], storage->GetTask(0));

			//testing the partition when n>1; boundary case n = 2; where n is the number of tasks added
			Task* task2 = new Task();
			task2->SetDescription("do homework 2");
			task2->SetEndDate("tomorrow2");
			task2->SetStartDate("today2");
			task2->SetPriority("12");
			storage->Add(task2);
			//tasklist = storage->GetTaskList();

			expected[1] = "Description: do homework 2\nStart: today2\nEnd: tomorrow2\nPriority: 12";
			Assert::AreEqual(expected[1], storage->GetTask(1));
			tasklist.clear();

		}

		TEST_METHOD(STORAGE_SEARCH){
			//Storage* storage = new Storage("Storage_Search.txt");
			//
			////Testing FilterTask function
			//storage->FilterTask();
			//string timedTask = storage->ToString(storage->timedList);
			//string deadlineTask = storage->ToString(storage->deadlineList);
			//string floatingTask = storage->ToString(storage->floatingList);
			///*cout<< "Timed Task List:" << "\n" << timedTask << endl;
			//cout<< "Deadline Task List:" << "\n" << deadlineTask << endl;
			//cout<< "Floating Task List:" << "\n" << floatingTask << endl;*/
			//
			//string expected[5];
			//
			//string result;
			//expected[3] = "homework from monday to tuesday priority 1 ";
			//expected[4] = "cannot find";
			//
			////Testing seach by description
			//vector<string> input;
			//input[Smartstring::FIELD::DESCRIPTION] = "homework";
			//result=storage->search(input);
			//Assert::AreEqual(expected[3], result);
			//
			////Testing search by start date
			//input.clear();
			//input[Smartstring::FIELD::STARTDATE] = "monday";
			//result = storage->search(input);
			//Assert::AreEqual(expected[3], result);
			//
			////Testing search by end date
			//input.clear();
			//input[Smartstring::FIELD::ENDDATE] = "friday";
			//result = storage->search(input);
			//Assert::AreEqual(expected[3], result);
			//
			////Testing search by priority
			//input.clear();
			//input[Smartstring::FIELD::PRIORITY] = "1";
			//result = storage->search(input);
			//Assert::AreEqual(expected[3], result);
			//
			////Testing failure case
			//input.clear();
			//input[Smartstring::FIELD::PRIORITY] = "1000";
			//result = storage->search(input);
			//Assert::AreEqual(expected[4], result);

		}

		TEST_METHOD(STORAGE_TXT_LOAD_REWRITE){
			//Testing the Load() and Rewrite() functions in storage
			//testing the partition when n > 1; boundary case n = 1; where n is the number of entries to be loaded and rewritten

			Storage* storage = new Storage("Unit_test_IO2.txt");
			storage->Reset();
			Task* task = new Task();
			task->SetDescription("do homework");
			task->SetEndDate("tomorrow");
			task->SetStartDate("today");
			task->SetPriority("1");
			storage->Add(task);

			task = new Task();
			task->SetDescription("do homework 2");
			task->SetEndDate("tomorrow2");
			task->SetStartDate("today2");
			task->SetPriority("12");
			storage->Add(task);

			storage->Rewrite();

			delete storage;
			storage = new Storage();

			int size = storage->Size();
			Assert::IsTrue(size > 0);
			string expected[2];
			expected[0] = "Description: do homework\nStart: today\nEnd: tomorrow\nPriority: 1";
			expected[1] = "Description: do homework 2\nStart: today2\nEnd: tomorrow2\nPriority: 12";

			for (int i = 0; i < size; i++){
				Assert::AreEqual(expected[i], storage->GetTask(i));
			}

		}

		TEST_METHOD(STORAGE_CSV_ADD_LOAD_REWRITE){

			//Testing the Load() and Rewrite() functions in storage
			//testing the partition when n > 1; boundary case n = 1; where n is the number of entries to be loaded and rewritten
			Storage* storage = new Storage("UNIT_TEST_CSV_ADD_LOAD_REWRITE.csv");
			storage->Clear();
			Task* task = new Task();
			task->SetDescription("do homework");
			task->SetEndDate("tomorrow");
			task->SetStartDate("today");
			task->SetPriority("1");
			storage->Add(task);

			task = new Task();
			task->SetDescription("do homework 2");
			task->SetEndDate("tomorrow2");
			task->SetStartDate("today2");
			task->SetPriority("12");
			storage->Add(task);

			storage->Save();

			delete storage;
			storage = new Storage();


			int size = storage->Size();
			Assert::IsTrue(size > 0);
			string expected[2];
			expected[0] = "Description: do homework\nStart: today\nEnd: tomorrow\nPriority: 1";
			expected[1] = "Description: do homework 2\nStart: today2\nEnd: tomorrow2\nPriority: 12";

			for (int i = 0; i < size; i++){
				Assert::AreEqual(expected[i], storage->GetTask(i));
			}

		}

		TEST_METHOD(Parser_IdentifyTaskFields){
			Parser* parser = new Parser();
			//Case: fields with varied length 1
			string input = "go to school on: monday p: 1 from: today";
			vector<string> output = parser->IdentifyTaskFields(input);
			Assert::AreEqual(output[Smartstring::DESCRIPTION].c_str(), "go to school");
			Assert::AreEqual(output[Smartstring::STARTDATE].c_str(), "today"); //NEED TO CHANGE FORMAT FOR FINAL TEST
			Assert::AreEqual(output[Smartstring::PRIORITY].c_str(), "1");
			Assert::AreEqual(output[Smartstring::ENDDATE].c_str(), "monday"); //NEED TO CHANGE FORMAT FOR FINAL TEST

			//Case: fields with length 1
			input = "homework from: Monday priority: 1 end: Friday";
			output.clear();
			output = parser->IdentifyTaskFields(input);
			Assert::AreEqual(output[Smartstring::DESCRIPTION].c_str(), "homework");
			Assert::AreEqual(output[Smartstring::STARTDATE].c_str(), "Monday"); //NEED TO CHANGE FORMAT FOR FINAL TEST
			Assert::AreEqual(output[Smartstring::PRIORITY].c_str(), "1");
			Assert::AreEqual(output[Smartstring::ENDDATE].c_str(), "Friday"); //NEED TO CHANGE FORMAT FOR FINAL TEST
		}


		TEST_METHOD(Parser_IdentifyCommand){
			Parser* parser = new Parser();
			//Case: ADD
			string input = "add homework from: Monday priority: 1 end: Friday";
			int expected = Smartstring::COMMAND::ADD;
			int actual = parser->IdentifyCommand(input);
			Assert::AreEqual(expected, actual);

			//Case: CLEAR
			input = "clear file";
			expected = Smartstring::COMMAND::CLEAR;
			actual = parser->IdentifyCommand(input);
			Assert::AreEqual(expected, actual);

			//Case: DELETE
			input = "delete homework everyday";
			expected = Smartstring::COMMAND::DELETE;
			actual = parser->IdentifyCommand(input);
			Assert::AreEqual(expected, actual);

			//Case: DISPLAY
			input = "display all items";
			expected = Smartstring::COMMAND::DISPLAY;
			actual = parser->IdentifyCommand(input);
			Assert::AreEqual(expected, actual);

			//Case: EDIT
			input = "edit this item";
			expected = Smartstring::COMMAND::EDIT;
			actual = parser->IdentifyCommand(input);
			Assert::AreEqual(expected, actual);


			//Case: SEARCH
			input = "search homework";
			expected = Smartstring::COMMAND::SEARCH;
			actual = parser->IdentifyCommand(input);
			Assert::AreEqual(expected, actual);

		}

		TEST_METHOD(Parser_RemoveCommand){
			Parser* parser = new Parser();
			//Case: Test empty
			string input = "";
			string expected = "";
			string actual = parser->RemoveCommand(input);
			Assert::AreEqual(expected, actual);

			//Case: Test one word input
			input = "search";
			expected = "";
			actual = parser->RemoveCommand(input);
			Assert::AreEqual(expected, actual);

			//Case: Test more than one word input
			input = "search for homework";
			expected = "for homework";
			actual = parser->RemoveCommand(input);
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(TASK){
			//default constructor test
			Task* task = new Task();
			Assert::AreEqual("", task->GetDescription().c_str());
			Assert::AreEqual("", task->GetStartDate().c_str());
			Assert::AreEqual("", task->GetEndDate().c_str());
			Assert::AreEqual("", task->GetPriority().c_str());

			//vector constructor test
			vector<string> testinput;
			testinput.push_back("do my homework");
			testinput.push_back("today");
			testinput.push_back("tomorrow");
			testinput.push_back("1");

			Task* vectTask = new Task(testinput);
			Assert::AreEqual("do my homework", vectTask->GetDescription().c_str());
			Assert::AreEqual("today", vectTask->GetStartDate().c_str());
			Assert::AreEqual("tomorrow", vectTask->GetEndDate().c_str());
			Assert::AreEqual("1", vectTask->GetPriority().c_str());

			string actual = vectTask->ToCSVString();
			string expected = "\"do my homework\",\"today\",\"tomorrow\",\"1\"";
			Assert::AreEqual(expected, actual);

		}

		TEST_METHOD(LOGIC){
			Logic* logic = new Logic();
			logic->mout.clear();
			logic->mout.str("");
			logic->Clear();
			logic->storage->Reset();
			string file = logic->storage->GetFileName();
			string myinput = "add homework from: monday on: tuesday p: 1";
			string expected = "Description: homework\nStart: monday\nEnd: tuesday\nPriority: 1";
			string feedback;
			feedback = logic->Run(myinput);
			string output = logic->mout.str();

			Assert::AreEqual(expected, output);
		}
		TEST_METHOD(LOGIC_EDIT){
			Logic* logic = new Logic();
			Storage* storage = new Storage("Storage_Edit.txt");
			storage->Clear();
			Task* task = new Task();
			task->SetDescription("do homework");
			task->SetEndDate("tomorrow");
			task->SetStartDate("today");
			task->SetPriority("1");
			storage->Add(task);

			Task* task2 = new Task();
			task2->SetDescription("do homework 2");
			task2->SetEndDate("tomorrow2");
			task2->SetStartDate("today2");
			task2->SetPriority("2");
			storage->Add(task2);

			//case index error1
			string expected = "INVALID INDEX";
			Assert::AreEqual(expected, logic->Edit("-1 description: meet my clients"));

			//case index error2
			Assert::AreEqual(expected, logic->Edit("4 description: meet my clients"));

			//case edit the description
			//string feedback;
			//feedback = "meet my clients today tomorrow2 12";
			//Assert::AreEqual(feedback, logic->Edit("1 description: meet my clients"));

			//case change saved to storage
			/*string update;
			update = "meet my clients today tomorrow2 12";
			Assert::AreEqual(update, logic->Display("2 description: meet my clients"));
			*/
		}

		TEST_METHOD(SMARTSTRING_TOKENIZE){
			string input = "\"hello\",\"how\",\"are\",\"you\",\"doing\",\"today\"";
			Smartstring str(input);
			vector<string> result = str.Tokenize(",\"");
			int size = result.size();
			Assert::AreEqual(6, size);
			Assert::AreEqual("hello", result[0].c_str());
			Assert::AreEqual("how", result[1].c_str());
			Assert::AreEqual("are", result[2].c_str());
			Assert::AreEqual("you", result[3].c_str());
			Assert::AreEqual("doing", result[4].c_str());
			Assert::AreEqual("today", result[5].c_str());

		}



	};
}