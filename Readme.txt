//=============================================================================
[08/04] Delete, Complete, Edit, Command Update
//=============================================================================
[1]
To delete from default view instead of internal vector
Old:
1. display
2. delete 4

Now:
1. delete float: 1
2. delete timed: 1
3. delete deadline: 1
3. Edit float: 1 homework
4. Edit float: 2 homework 2 s: 07/04/2015
5. Complete deadline: 1

[2]

Allow user to remove a field with - as the description
Old: impossible to remove a field

New: edit timed: 1 s: - (removes the start date from task)


//=============================================================================
[03/04] Displaying bold text in UI
//=============================================================================

Sample code to stream within storage class:

out << _rtfboldtagstart << index << ": " << _rtfboldtagend << (*iter)->ToShortString();

Sample output: 1: [monday][thursday] Homework

//author's note:
1. Try to bold text as close to when it goes to the UI as possible. i.e. In the following sequence of classes, choose the right most class as is possible to bold text in

Smartstring >> Task >> Parser >> Storage >> Logic >> UI_Controller


//=============================================================================
[28/03] Logging feature 
//=============================================================================
Added logging feature:

Sample code:

#include "Logger.h"
using namespace logging;

int main(){
    logfile << "this is a test log output";
}

Sample output:
[28/03/2015] [03:34AM]: this is a test log output

open the file debug.log in the folder [main\I_Schedule\I_ScheduleGUI] to outputs, and begin to use this feature
to score more marks in the grading! (:

