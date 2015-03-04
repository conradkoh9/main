#include "stdafx.h"
#include "Storage.h"
#include "CppUnitTest.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace I_ScheduleLibraryTest
{	Storage* storage = new Storage("Unit_test_IO.txt");
	
	TEST_CLASS(myLibTest)
	{
	public:
		
		TEST_METHOD(Storage)
		{
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

	};
}