#include "stdafx.h"
#include "CppUnitTest.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace I_ScheduleLibraryTest{	
	Storage* storage = new Storage("Unit_test_IO.txt");
	Parser* parser = new Parser();
	
	TEST_CLASS(myLibTest)
	{
	public:
		
		TEST_METHOD(Storage){
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


		TEST_METHOD(Parser_Keywords_different_lengths){
			
			string myinput = "go to school on monday priority 1 from: today";
			vector<string> output = parser->Identify(myinput);
			Assert::AreEqual(output[Smartstring::DESCRIPTION].c_str(), "go to school");
			Assert::AreEqual(output[Smartstring::STARTDATE].c_str(), "today"); //NEED TO CHANGE FORMAT FOR FINAL TEST
			Assert::AreEqual(output[Smartstring::PRIORITY].c_str(), "1");
			Assert::AreEqual(output[Smartstring::ENDDATE].c_str(), "monday"); //NEED TO CHANGE FORMAT FOR FINAL TEST
		}

		TEST_METHOD(Parser_Keywords_length_1){
			//parser test
			string myinput = "homework from: Monday priority: 1 end: Friday";
			vector<string> output = parser->Identify(myinput);
			Assert::AreEqual(output[Smartstring::DESCRIPTION].c_str(), "homework");
			Assert::AreEqual(output[Smartstring::STARTDATE].c_str(), "Monday"); //NEED TO CHANGE FORMAT FOR FINAL TEST
			Assert::AreEqual(output[Smartstring::PRIORITY].c_str(), "1");
			Assert::AreEqual(output[Smartstring::ENDDATE].c_str(), "Friday"); //NEED TO CHANGE FORMAT FOR FINAL TEST
		}

	};
}