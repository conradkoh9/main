#include "stdafx.h"
#include "CppUnitTest.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace I_ScheduleLibraryTest{		
	TEST_CLASS(myLibTest)
	{
	public:
		Storage* storage = new Storage("Unit_test_IO.txt");
		Parser* parser = new Parser();
		Task* task = new Task();

		TEST_METHOD(STORAGE){
			
			const string _FEEDBACK_GENERIC_SUCCESS = "STORAGE SUCCESS";
			const string _FEEDBACK_GENERIC_FAILURE = "STORAGE FAILED";
			const string _FEEDBACK_LOAD_SUCCESS = "LOAD SUCCESS";
			const string _FEEDBACK_LOAD_FAILURE = "LOAD FAILED";
			const string _FEEDBACK_WRITE_SUCCESS = "WRITE SUCCESS";
			const string _FEEDBACK_WRITE_FAILURE = "WRITE FAILED";
			const string _FEEDBACK_CLEAR_SUCCESS = "CLEAR SUCCESS";
			const string _FEEDBACK_CLEAR_FAILURE = "CLEAR FAILED";
			const string _FEEDBACK_FILE_EMPTY = "FILE EMPTY";
			const string _EMPTY_STRING = "";

			vector<string> expected_all_feedback;
			expected_all_feedback.push_back("hello world");

			vector<string> all_feedback;
			string feedback;
			feedback = storage->clearFile();
			Assert::AreEqual(feedback, _FEEDBACK_CLEAR_SUCCESS);
			all_feedback.push_back(feedback);
			feedback = storage->writeToFile("hello world");
			Assert::AreEqual(feedback, _FEEDBACK_WRITE_SUCCESS);
			all_feedback.push_back(feedback);
			feedback = storage->loadFile();
			Assert::AreEqual(feedback, _FEEDBACK_LOAD_SUCCESS);
			all_feedback.push_back(feedback);

			vector<string>::iterator iter, iter2;
			iter2 = expected_all_feedback.begin();
			vector<string> content = storage->getContent();
			for (iter = content.begin(); iter != content.end(); ++iter){
				Assert::AreEqual(*iter ,*iter2);
				++iter2;
			}

		}


		TEST_METHOD(Parser_IdentifyTaskFields){
			
			//Case: fields with varied length 1
			string input = "go to school on monday priority 1 from: today";
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

			//Case: SEARCH
			input = "search homework";
			expected = Smartstring::COMMAND::SEARCH;
			actual  = parser->IdentifyCommand(input);
			Assert::AreEqual(expected, actual);

			//Case: DISPLAY
			input = "display all items";
			expected = Smartstring::COMMAND::DISPLAY;
			actual  = parser->IdentifyCommand(input);
			Assert::AreEqual(expected, actual);

			//Case: CLEAR
			input = "clear file";
			expected = Smartstring::COMMAND::CLEAR;
			actual  = parser->IdentifyCommand(input);
			Assert::AreEqual(expected, actual);

			//Case: Delete
			input = "delete homework everyday";
			expected = Smartstring::COMMAND::DELETE;
			actual  = parser->IdentifyCommand(input);
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

	};
}