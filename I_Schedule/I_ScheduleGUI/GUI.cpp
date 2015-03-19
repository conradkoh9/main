#include "GUI.h"

using namespace System;
using namespace System::Windows::Forms;

void main(array <String^>^ args){
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	I_ScheduleGUI::GUI mainWindow;
	Application::Run(%mainWindow);
	
}