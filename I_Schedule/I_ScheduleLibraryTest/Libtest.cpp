#include "stdafx.h"
#include "CppUnitTest.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace I_ScheduleLibraryTest{		
	TEST_CLASS(myLibTest)
	{
	public:
		Logic* logic = new Logic();
		Storage* storage = new Storage("Unit_test_IO.txt");
		Parser* parser = new Parser();
		Task* task = new Task();

		TEST_METHOD(STORAGE_ADD){
			Storage* storage = new Storage("Storage_Add.txt");
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
			task2->SetPriority("12");
			storage->Add(task2);

			vector<Task*> tasklist = storage->GetTaskList();
			string expected[2];
			expected[0] = "Description: do homework\nStart: today\nEnd: tomorrow\nPriority: 1";
			expected[1] = "Description: do homework 2\nStart: today2\nEnd: tomorrow2\nPriority: 12";
			Assert::AreEqual(tasklist[0]->ToString(), expected[0]);
			Assert::AreEqual(tasklist[1]->ToString(), expected[1]);
			tasklist.clear();
						
		}
		
		TEST_METHOD(STORAGE_SEARCH){
		}

		TEST_METHOD(STORAGE_REWRITE_LOAD){

			//Load(), Rewrite()
			Storage* storage = new Storage("Unit_test_IO2.txt");
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

			storage->Rewrite();

			delete storage;
			storage = new Storage("Unit_test_IO2.txt");
		
			vector<Task*>::iterator tIter;
			vector<Task*> taskList = storage->GetTaskList();
			if (taskList.empty()){
				Assert::AreEqual(1, 0);
			}
			string expected[2];
			expected[0] = "Description: do homework\nStart: today\nEnd: tomorrow\nPriority: 1";
			expected[1] = "Description: do homework 2\nStart: today2\nEnd: tomorrow2\nPriority: 12";
			int i = 0;

			for (tIter = (storage->taskList).begin(); tIter != storage->taskList.end(); ++tIter){
				Task* taskptr;
				taskptr = *tIter;
				string actual = taskptr->ToString();
				Assert::AreEqual(expected[i], actual);
				i++;
			}

		}


		TEST_METHOD(Parser_IdentifyTaskFields){
			
			//Case: fields with varied length 1
			string input = "go to school on: monday priority 1 from: today";
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

		}

		TEST_METHOD(LOGIC){
			Logic* logic = new Logic();
			string myinput = "add homework from monday on: tuesday priority 1";
			string expected = "Description: homework\nStart: monday\nEnd: tuesday\nPriority: 1";
			string feedback;
			feedback = logic->Run(myinput);

			Assert::AreEqual(expected, feedback);
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



	};
}