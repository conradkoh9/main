#include "stdafx.h"
#include "CppUnitTest.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace I_ScheduleLibraryTest{

	TEST_CLASS(myLibTest)
	{
	public:
		//@author A0099303A
		TEST_METHOD(STORAGE_TXT_ADD){
			string expected[2];
			vector<Task*> tasklist;
			//testing the partiton n>0; boundary case n = 1; where n is the number of tasks added
			Storage* storage = new Storage("Storage_Add.txt");
			storage->Clear();
			Task* task = new Task();
			task->SetDescription("do homework");
			task->SetEndDate("07/06/2015");
			task->SetStartDate("05/06/2015");
			task->SetPriority("1");
			task->SetStatus("Incomplete");
			storage->Add(task);

			expected[0] = "Description: do homework\nStart: 05/06/2015\nEnd: 07/06/2015\nPriority: 1\nStatus: Incomplete";
			Assert::AreEqual(expected[0], storage->GetTask(0));

			//testing the partition when n>1; boundary case n = 2; where n is the number of tasks added
			Task* task2 = new Task();
			task2->SetDescription("do homework 2");
			task2->SetEndDate("07/06/2015");
			task2->SetStartDate("05/06/2015");
			task2->SetPriority("12");
			task2->SetStatus("Complete");
			storage->Add(task2);
			//tasklist = storage->GetTaskList();

			expected[1] = "Description: do homework 2\nStart: 05/06/2015\nEnd: 07/06/2015\nPriority: 12\nStatus: Complete";
			Assert::AreEqual(expected[1], storage->GetTask(1));
			tasklist.clear();

		}
		//@author A0119491B
			TEST_METHOD(STORAGE_FILTER){
			vector<Task*> tasklist;
			Storage* storage = new Storage("Storage_Filter.txt");
			//set new task
			storage->Clear();
			Task* task = new Task();
			task->SetDescription("do homework");
			task->SetEndDate("16/04/2015");
			task->SetStartDate("13/04/2015");
			task->SetPriority("1");
			task->SetStatus("Incomplete");
			storage->Add(task);

			string timedTask = storage->GetTimedList();
			string deadlinedTask = storage->GetDeadlineList();
			string floatingTask = storage->GetFloatingList();
			string expected[2];

			expected[0] = "\\b 1: \\b0 [13/04/2015][16/04/2015] do homework";
			expected[1] = "";
			Assert::AreEqual(expected[0], timedTask);
			Assert::AreEqual(expected[1], deadlinedTask);
			Assert::AreEqual(expected[1], floatingTask);
			tasklist.clear();

		}


		//@author A0119491B
		TEST_METHOD(STORAGE_SEARCH){
			Storage* storage = new Storage("Storage_PowerSearch.txt");
			storage->Clear();
			//Setting a task to be seached
			Task* task = new Task();
			task->SetDescription("homework");
			task->SetEndDate("08/04/2015");
			task->SetStartDate("07/04/2015");
			task->SetPriority("1");
			task->SetStatus("Incomplete");
			storage->Add(task);

			vector<Task*> RESULT;
			vector<string> input(10);
			string expected[2], result;
			expected[0] = "\\b 1: \\b0 [07/04/2015][08/04/2015] homework";
			expected[1] = "No results found.";

			//Testing search by description
			input[Smartstring::FIELD::DESCRIPTION] = "homework";
			result = storage->Search(input[Smartstring::FIELD::DESCRIPTION]);
			Assert::AreEqual(expected[0], result);

			//Testing search by start date
			input[Smartstring::FIELD::STARTDATE] = "07/04/2015";
			result = storage->Search(input[Smartstring::FIELD::STARTDATE]);
			Assert::AreEqual(expected[0], result);

			//Testing search by end date
			input[Smartstring::FIELD::ENDDATE] = "08/04/2015";
			result = storage->Search(input[Smartstring::FIELD::ENDDATE]);
			Assert::AreEqual(expected[0], result);

			//Testing search by priority
			input[Smartstring::FIELD::PRIORITY] = "1";
			result = storage->Search(input[Smartstring::FIELD::PRIORITY]);
			Assert::AreEqual(expected[0], result);

			//Testing Failure case
			input[Smartstring::FIELD::DESCRIPTION] = "shopping";
			result = storage->Search(input[Smartstring::FIELD::DESCRIPTION]);
			Assert::AreEqual(expected[1], result);

			//Testing Close Search
			input[Smartstring::FIELD::DESCRIPTION] = "howork";
			RESULT = storage->NearSearch(input[Smartstring::FIELD::DESCRIPTION]);
			result = storage->ToString(RESULT);
			Assert::AreEqual(expected[0], result);

		}

		//@author A0099303A
		TEST_METHOD(STORAGE_TXT_LOAD_REWRITE){
			//Testing the Load() and Rewrite() functions in storage
			//testing the partition when n > 1; boundary case n = 1; where n is the number of entries to be loaded and rewritten

			Storage* storage = new Storage("Unit_test_IO2.txt");
			storage->Clear();
			Task* task = new Task();
			task->SetDescription("do homework");
			task->SetEndDate("07/06/2015 at 4pm");
			task->SetStartDate("06/06/2015 at 3pm");
			task->SetPriority("1");
			task->SetStatus("Complete");
			storage->Add(task);

			task = new Task();
			task->SetDescription("do homework 2");
			task->SetEndDate("05/02/2015 at 1pm");
			task->SetStartDate("01/02/2015 at 1pm");
			task->SetPriority("1234");
			task->SetStatus("Incomplete");
			storage->Add(task);

			storage->Rewrite();

			delete storage;
			storage = new Storage();

			int size = storage->Size();
			Assert::IsTrue(size > 0);
			string expected[2];
			expected[1] = "Description: do homework\nStart: 03:00pm on 06/06/2015\nEnd: 04:00pm on 07/06/2015\nPriority: 1\nStatus: Complete";
			expected[0] = "Description: do homework 2\nStart: 01:00pm on 01/02/2015\nEnd: 01:00pm on 05/02/2015\nPriority: 1234\nStatus: Incomplete";

			for (int i = 0; i < size; i++){
				Assert::AreEqual(expected[i], storage->GetTask(i));
			}

		}

		//@author A0099303A
		TEST_METHOD(STORAGE_CSV_ADD_LOAD_REWRITE){

			//Testing the Load() and Rewrite() functions in storage
			//testing the partition when n > 1; boundary case n = 1; where n is the number of entries to be loaded and rewritten
			Storage* storage = new Storage("UNIT_TEST_CSV_ADD_LOAD_REWRITE.csv");
			storage->Clear();
			Task* task = new Task();
			task->SetDescription("do homework");
			task->SetEndDate("08/04/2015");
			task->SetStartDate("07/04/2015");
			task->SetPriority("1");
			task->SetStatus("Complete");
			storage->Add(task);

			task = new Task();
			task->SetDescription("do homework 2");
			task->SetEndDate("10/04/2015");
			task->SetStartDate("09/04/2015");
			task->SetPriority("123");
			storage->Add(task);

			storage->Save();

			delete storage;
			storage = new Storage();


			int size = storage->Size();
			Assert::IsTrue(size > 0);
			string expected[2];
			expected[0] = "Description: do homework\nStart: 07/04/2015\nEnd: 08/04/2015\nPriority: 1\nStatus: Complete";
			expected[1] = "Description: do homework 2\nStart: 09/04/2015\nEnd: 10/04/2015\nPriority: 123\nStatus: Incomplete";

			for (int i = 0; i < size; i++){
				Assert::AreEqual(expected[i], storage->GetTask(i));
			}

		}

		//@author A0099303A
		TEST_METHOD(PARSER_IdentifyTaskFields){
			Parser* parser = new Parser();
			//Case: fields with varied length
			string input = "go to school till: monday p: 1 from: today";
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

		//@author A0099303A
		TEST_METHOD(PARSER_IdentifyCommand){
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

		//@author A0099303A
		TEST_METHOD(PARSER_RemoveCommand){
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
			testinput.push_back("09/10/2015");
			testinput.push_back("10/10/2015");
			testinput.push_back("1");
			testinput.push_back("Incomplete");

			Task* vectTask = new Task(testinput);
			Assert::AreEqual("do my homework", vectTask->GetDescription().c_str());
			Assert::AreEqual("09/10/2015", vectTask->GetStartDate().c_str());
			Assert::AreEqual("10/10/2015", vectTask->GetEndDate().c_str());
			Assert::AreEqual("1", vectTask->GetPriority().c_str());
			Assert::AreEqual("Incomplete", vectTask->GetStatus().c_str());

			string actual = vectTask->ToCSVString();
			string expected = "\"do my homework\",\"09/10/2015\",\"10/10/2015\",\"1\",\"Incomplete\"";
			Assert::AreEqual(expected, actual);

		}

		TEST_METHOD(TASK_INTEGRATED){
			//default constructor test
			Task* task = new Task();
			Assert::AreEqual("", task->GetDescription().c_str());
			Assert::AreEqual("", task->GetStartDate().c_str());
			Assert::AreEqual("", task->GetEndDate().c_str());
			Assert::AreEqual("", task->GetPriority().c_str());

			//vector constructor test
			vector<string> testinput;
			testinput.push_back("do my homework");
			testinput.push_back("09/10/2015 at 5pm");
			testinput.push_back("10/10/2015 at 6pm");
			testinput.push_back("1");
			testinput.push_back("Incomplete");
			
			Task* vectTask = new Task(testinput);

			Assert::AreEqual("do my homework", vectTask->GetDescription().c_str());
			Assert::AreEqual("05:00pm on 09/10/2015", vectTask->GetStartDate().c_str());
			Assert::AreEqual("06:00pm on 10/10/2015", vectTask->GetEndDate().c_str());
			Assert::AreEqual("1", vectTask->GetPriority().c_str());
			Assert::AreEqual("Incomplete", vectTask->GetStatus().c_str());
			
		}

		//@author A0099303A
		TEST_METHOD(LOGIC){
			Logic* logic = new Logic();
			logic->mout.clear();
			logic->mout.str("");
			logic->Clear();
			logic->storage->Reset();
			string file = logic->storage->GetFileName();
			string myinput = "add homework from: 07/04/2015 till: 08/04/2015 p: 1";
			string expected = "Description: homework\nStart: 07/04/2015\nEnd: 08/04/2015\nPriority: 1\nStatus: Incomplete";
			string feedback;
			feedback = logic->Run(myinput);
			string output = logic->mout.str();

			Assert::AreEqual(expected, output);
		}

		//@author unknown
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
			string expected = "Invalid index.";
			Assert::AreEqual(expected, logic->Edit("timed: -1 description: meet my clients"));

			//case index error2
			Assert::AreEqual(expected, logic->Edit("timed: 4 description: meet my clients"));

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

		//@author A0099303A
		TEST_METHOD(SMARTSTRING_TOKENIZE){
			//testing the partition inpult length > 0
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

			//testing partition input length 0
			input = "";
			str = Smartstring(input);
			result = str.Tokenize(" ");
			size = result.size();
			Assert::AreEqual(size, 0);
		}

		//@author A0099303A
		TEST_METHOD(DATETIME_USER_INPUTS){
			string input;
			string expected;
			string actual;
			//testing the partition where no day reset is crossed
			input = "Tuesday at 5pm";
			DateTime dt(input);
			actual = dt.Standardized();
			expected = "05:00pm on 14/04/2015";
			Assert::AreEqual(expected, actual);

			input = "5pm on Tuesday";
			dt = DateTime(input);
			actual = dt.Standardized();
			expected = "05:00pm on 14/04/2015";
			Assert::AreEqual(expected, actual);

			input = "Friday at 10pm";
			dt = DateTime(input);
			actual = dt.Standardized();
			expected = "10:00pm on 10/04/2015";
			Assert::AreEqual(expected, actual);

			//testing the partition where a day reset is crossed e.g today is wednesday, appointment on monday
			input = "Monday at 6pm";
			dt = DateTime(input);
			actual = dt.Standardized();
			expected = "06:00pm on 13/04/2015";
			Assert::AreEqual(expected, actual);

			//testing that Standardized() does not change empty strings
			input = "";
			dt = DateTime(input);
			actual = dt.Standardized();
			expected = "";
			Assert::AreEqual(expected, actual);

			//test the partition where only a time is set
			input = "5pm";
			dt = DateTime(input);
			actual = dt.Standardized();
			expected = "05:00pm";
			Assert::AreEqual(expected, actual);

			//testing today and tomorrow keywords
			input = "today";
			dt = DateTime(input);
			actual = dt.Standardized();
			expected = "08/04/2015";
			Assert::AreEqual(expected, actual);

			input = "tomorrow";
			dt = DateTime(input);
			actual = dt.Standardized();
			expected = "09/04/2015";
			Assert::AreEqual(expected, actual);

			//important lacking test: testing when month is crossed

		}

		//@author A0099303A
		TEST_METHOD(DATETIME_STANDARD_INPUTS){
			string input;
			string expected[10];
			string actual[10];
			DateTime dt;

			//testing that standard inputs can be reconstructed
			input = "06:00pm on 13/04/2015";
			dt = DateTime(input);
			actual[0] = dt.Standardized();
			expected[0] = "06:00pm on 13/04/2015";
			Assert::AreEqual(expected[0], actual[0]);

			input = "13/04/2015 at 06:00pm";
			dt = DateTime(input);
			actual[3] = dt.Standardized();
			expected[3] = "06:00pm on 13/04/2015";
			Assert::AreEqual(expected[3], actual[3]);

			//testing date only input
			input = "13/04/2015";
			dt = DateTime(input);
			actual[1] = dt.Standardized();
			expected[1] = "13/04/2015";
			Assert::AreEqual(expected[1], actual[1]);

			//testing time only input
			input = "05:30pm";
			dt = DateTime(input);
			actual[2] = dt.Standardized();
			expected[2] = "05:30pm";
			Assert::AreEqual(expected[2], actual[2]);

		}

		//@author A0099303A
		TEST_METHOD(DATETIME_INTERNAL_INFO){
			string input;
			string expected[10];
			string actual[10];
			DateTime dt;

			input = "13/04/2015";
			dt = DateTime(input);
			actual[0] = dt.GetInfo();
			expected[0] = "Date: 13/04/2015\nTime: 00:00";
			Assert::AreEqual(expected[0], actual[0]);

			input = "13/04/2015 at 5pm";
			dt = DateTime(input);
			actual[1] = dt.GetInfo();
			expected[1] = "Date: 13/04/2015\nTime: 17:00";
			Assert::AreEqual(expected[1], actual[1]);

			input = "13/04/2014 at 7:30am";
			dt = DateTime(input);
			actual[2] = dt.GetInfo();
			expected[2] = "Date: 13/04/2014\nTime: 07:30";
			Assert::AreEqual(expected[2], actual[2]);

			input = "8:09pm";
			dt = DateTime(input);
			actual[3] = dt.GetInfo();
			expected[3] = "Date: 08/04/2015\nTime: 20:09";
			Assert::AreEqual(expected[3], actual[3]);

		}

		//@author A0099303A
		TEST_METHOD(DATETIME_ISEARLIERTHAN){
			string date1;
			string date2;
			DateTime dt1;
			DateTime dt2;
			
			//testing the partition where only dates are inputs
			date1 = "07/04/2014";
			date2 = "08/04/2014";
			dt1 = DateTime(date1);
			dt2 = DateTime(date2);
			Assert::IsTrue(dt1.IsEarlierThan(dt2));

			//testing the partition where only times are inputs
			date1 = "5pm";
			date2 = "6pm";
			dt1 = DateTime(date1);
			dt2 = DateTime(date2);
			Assert::IsTrue(dt1.IsEarlierThan(dt2));

			//testing the partition where dates are equal but time is greater
			date1 = "07/04/2014 at 5pm";
			date2 = "07/04/2014 at 6pm";
			dt1 = DateTime(date1);
			dt2 = DateTime(date2);
			Assert::IsTrue(dt1.IsEarlierThan(dt2));

			//testing the function returning false when condition is not satisfied
			date1 = "07/04/2014 at 6pm";
			date2 = "07/04/2014 at 5pm";
			dt1 = DateTime(date1);
			dt2 = DateTime(date2);
			Assert::IsFalse(dt1.IsEarlierThan(dt2));

			//testing the partition where dates are different but time is equal
			date1 = "07/04/2014 at 5pm";
			date2 = "08/04/2014 at 5pm";
			dt1 = DateTime(date1);
			dt2 = DateTime(date2);
			Assert::IsTrue(dt1.IsEarlierThan(dt2));
		}

		TEST_METHOD(DATETIME_ISVALIDFORMAT){
			string date;
			DateTime dt;

			//testing the partition input is valid
			date = "07/04/2014";
			dt = DateTime(date);
			Assert::IsTrue(dt.isValidFormat);

			//testing the partition where input is not valid
			date = "owkdowkdow";
			dt = DateTime(date);
			Assert::AreEqual(dt.Standardized(), date);
			Assert::IsFalse(dt.isValidFormat);
		}

		TEST_METHOD(DATETIME_INVALIDINPUTS_UNCHANGED){
			string date;
			DateTime dt;
			date = "owkdowkdowdkowdww";
			dt = DateTime(date);
			Assert::AreEqual(dt.Standardized(), date);
		}


		TEST_METHOD(SMARTSTRING){
			Smartstring test("add");
			bool isCommand_Expected;
			bool isCommand_Actual;

			isCommand_Expected = true;
			isCommand_Actual = test.IsCommand();

			Assert::AreEqual(isCommand_Expected, isCommand_Actual);

		}
	};
}