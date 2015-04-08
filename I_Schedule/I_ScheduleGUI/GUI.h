#pragma once
#include "UI_Controller.h";
#include <msclr\marshal_cppstd.h>
namespace I_ScheduleGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for GUI
	/// </summary>
	public ref class GUI : public System::Windows::Forms::Form
	{
	public:
		UI_Controller* controller = new UI_Controller;
		GUI(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			Welcome();

		}
		void Welcome(){
			DISPLAY_STATUS->Text = gcnew String(controller->DISPLAY_STATUS.c_str());

			DISPLAY_TASK_TIMED->LoadFile(gcnew String(controller->rtf_timed.c_str()));
			DISPLAY_TASK_DEADLINE->LoadFile(gcnew String(controller->rtf_deadline.c_str()));
			DISPLAY_TASK_FLOAT->LoadFile(gcnew String(controller->rtf_float.c_str()));
			DISPLAY_MAIN->LoadFile(gcnew String(controller->rtf_main.c_str()));

			//this section scrolls to the bottom of textboxes on load
			DISPLAY_TASK_TIMED->SelectionStart = DISPLAY_TASK_TIMED->TextLength;
			DISPLAY_TASK_TIMED->ScrollToCaret();
			DISPLAY_TASK_FLOAT->SelectionStart = DISPLAY_TASK_FLOAT->TextLength;
			DISPLAY_TASK_FLOAT->ScrollToCaret();
			DISPLAY_MAIN->SelectionStart = DISPLAY_MAIN->TextLength;
			DISPLAY_MAIN->ScrollToCaret();
			DISPLAY_TASK_DEADLINE->SelectionStart = DISPLAY_TASK_DEADLINE->TextLength;
			DISPLAY_TASK_DEADLINE->ScrollToCaret();
			//end section
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~GUI()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  BUTTON_SEND;
	protected:
	private: System::Windows::Forms::TextBox^  INPUT_CMDLN;




	private: System::Windows::Forms::TextBox^  LABEL_MAIN;
	private: System::Windows::Forms::TextBox^  LABEL_TIMED_TASKS;
	private: System::Windows::Forms::TextBox^  LABEL_DEADLINE_TASKS;
	private: System::Windows::Forms::TextBox^  LABEL_FLOATING_TASK;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::StatusStrip^  STATUS_BAR;
	private: System::Windows::Forms::ToolStripStatusLabel^  DISPLAY_STATUS;
	private: System::Windows::Forms::RichTextBox^  DISPLAY_TASK_FLOAT;
	private: System::Windows::Forms::RichTextBox^  DISPLAY_TASK_TIMED;

	private: System::Windows::Forms::RichTextBox^  DISPLAY_MAIN;
	private: System::Windows::Forms::RichTextBox^  DISPLAY_TASK_DEADLINE;



	protected:

	protected:


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->BUTTON_SEND = (gcnew System::Windows::Forms::Button());
			this->INPUT_CMDLN = (gcnew System::Windows::Forms::TextBox());
			this->LABEL_MAIN = (gcnew System::Windows::Forms::TextBox());
			this->LABEL_TIMED_TASKS = (gcnew System::Windows::Forms::TextBox());
			this->LABEL_DEADLINE_TASKS = (gcnew System::Windows::Forms::TextBox());
			this->LABEL_FLOATING_TASK = (gcnew System::Windows::Forms::TextBox());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->DISPLAY_TASK_DEADLINE = (gcnew System::Windows::Forms::RichTextBox());
			this->DISPLAY_TASK_TIMED = (gcnew System::Windows::Forms::RichTextBox());
			this->DISPLAY_MAIN = (gcnew System::Windows::Forms::RichTextBox());
			this->DISPLAY_TASK_FLOAT = (gcnew System::Windows::Forms::RichTextBox());
			this->STATUS_BAR = (gcnew System::Windows::Forms::StatusStrip());
			this->DISPLAY_STATUS = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->panel1->SuspendLayout();
			this->STATUS_BAR->SuspendLayout();
			this->SuspendLayout();
			// 
			// BUTTON_SEND
			// 
			this->BUTTON_SEND->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->BUTTON_SEND->Location = System::Drawing::Point(740, 601);
			this->BUTTON_SEND->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->BUTTON_SEND->Name = L"BUTTON_SEND";
			this->BUTTON_SEND->Size = System::Drawing::Size(142, 29);
			this->BUTTON_SEND->TabIndex = 1;
			this->BUTTON_SEND->Text = L"SEND";
			this->BUTTON_SEND->UseVisualStyleBackColor = true;
			this->BUTTON_SEND->Click += gcnew System::EventHandler(this, &GUI::BUTTON_SEND_Click);
			// 
			// INPUT_CMDLN
			// 
			this->INPUT_CMDLN->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->INPUT_CMDLN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->INPUT_CMDLN->Location = System::Drawing::Point(9, 604);
			this->INPUT_CMDLN->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->INPUT_CMDLN->Multiline = true;
			this->INPUT_CMDLN->Name = L"INPUT_CMDLN";
			this->INPUT_CMDLN->Size = System::Drawing::Size(704, 30);
			this->INPUT_CMDLN->TabIndex = 0;
			this->INPUT_CMDLN->TextChanged += gcnew System::EventHandler(this, &GUI::INPUT_CMDLN_TextChanged);
			// 
			// LABEL_MAIN
			// 
			this->LABEL_MAIN->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->LABEL_MAIN->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->LABEL_MAIN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->LABEL_MAIN->Location = System::Drawing::Point(9, 321);
			this->LABEL_MAIN->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->LABEL_MAIN->Multiline = true;
			this->LABEL_MAIN->Name = L"LABEL_MAIN";
			this->LABEL_MAIN->ReadOnly = true;
			this->LABEL_MAIN->Size = System::Drawing::Size(75, 22);
			this->LABEL_MAIN->TabIndex = 6;
			this->LABEL_MAIN->Text = L"Main";
			// 
			// LABEL_TIMED_TASKS
			// 
			this->LABEL_TIMED_TASKS->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->LABEL_TIMED_TASKS->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->LABEL_TIMED_TASKS->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->LABEL_TIMED_TASKS->Location = System::Drawing::Point(9, 9);
			this->LABEL_TIMED_TASKS->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->LABEL_TIMED_TASKS->Multiline = true;
			this->LABEL_TIMED_TASKS->Name = L"LABEL_TIMED_TASKS";
			this->LABEL_TIMED_TASKS->ReadOnly = true;
			this->LABEL_TIMED_TASKS->Size = System::Drawing::Size(254, 22);
			this->LABEL_TIMED_TASKS->TabIndex = 7;
			this->LABEL_TIMED_TASKS->Text = L"Timed Tasks";
			// 
			// LABEL_DEADLINE_TASKS
			// 
			this->LABEL_DEADLINE_TASKS->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->LABEL_DEADLINE_TASKS->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->LABEL_DEADLINE_TASKS->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->LABEL_DEADLINE_TASKS->Location = System::Drawing::Point(540, 9);
			this->LABEL_DEADLINE_TASKS->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->LABEL_DEADLINE_TASKS->Multiline = true;
			this->LABEL_DEADLINE_TASKS->Name = L"LABEL_DEADLINE_TASKS";
			this->LABEL_DEADLINE_TASKS->ReadOnly = true;
			this->LABEL_DEADLINE_TASKS->Size = System::Drawing::Size(164, 22);
			this->LABEL_DEADLINE_TASKS->TabIndex = 8;
			this->LABEL_DEADLINE_TASKS->Text = L"Deadline Tasks";
			// 
			// LABEL_FLOATING_TASK
			// 
			this->LABEL_FLOATING_TASK->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->LABEL_FLOATING_TASK->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->LABEL_FLOATING_TASK->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->LABEL_FLOATING_TASK->Location = System::Drawing::Point(540, 321);
			this->LABEL_FLOATING_TASK->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->LABEL_FLOATING_TASK->Multiline = true;
			this->LABEL_FLOATING_TASK->Name = L"LABEL_FLOATING_TASK";
			this->LABEL_FLOATING_TASK->ReadOnly = true;
			this->LABEL_FLOATING_TASK->Size = System::Drawing::Size(164, 22);
			this->LABEL_FLOATING_TASK->TabIndex = 9;
			this->LABEL_FLOATING_TASK->Text = L"Floating Tasks";
			// 
			// panel1
			// 
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel1->Controls->Add(this->DISPLAY_TASK_DEADLINE);
			this->panel1->Controls->Add(this->DISPLAY_TASK_TIMED);
			this->panel1->Controls->Add(this->DISPLAY_MAIN);
			this->panel1->Controls->Add(this->DISPLAY_TASK_FLOAT);
			this->panel1->Controls->Add(this->STATUS_BAR);
			this->panel1->Controls->Add(this->LABEL_FLOATING_TASK);
			this->panel1->Controls->Add(this->BUTTON_SEND);
			this->panel1->Controls->Add(this->INPUT_CMDLN);
			this->panel1->Controls->Add(this->LABEL_MAIN);
			this->panel1->Controls->Add(this->LABEL_DEADLINE_TASKS);
			this->panel1->Controls->Add(this->LABEL_TIMED_TASKS);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel1->Location = System::Drawing::Point(0, 0);
			this->panel1->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(896, 677);
			this->panel1->TabIndex = 10;
			// 
			// DISPLAY_TASK_DEADLINE
			// 
			this->DISPLAY_TASK_DEADLINE->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->DISPLAY_TASK_DEADLINE->Location = System::Drawing::Point(540, 35);
			this->DISPLAY_TASK_DEADLINE->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->DISPLAY_TASK_DEADLINE->Name = L"DISPLAY_TASK_DEADLINE";
			this->DISPLAY_TASK_DEADLINE->ReadOnly = true;
			this->DISPLAY_TASK_DEADLINE->Size = System::Drawing::Size(342, 282);
			this->DISPLAY_TASK_DEADLINE->TabIndex = 15;
			this->DISPLAY_TASK_DEADLINE->Text = L"";
			this->DISPLAY_TASK_DEADLINE->TextChanged += gcnew System::EventHandler(this, &GUI::DISPLAY_TASK_DEADLINE_TextChanged);
			// 
			// DISPLAY_TASK_TIMED
			// 
			this->DISPLAY_TASK_TIMED->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->DISPLAY_TASK_TIMED->Location = System::Drawing::Point(10, 35);
			this->DISPLAY_TASK_TIMED->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->DISPLAY_TASK_TIMED->Name = L"DISPLAY_TASK_TIMED";
			this->DISPLAY_TASK_TIMED->ReadOnly = true;
			this->DISPLAY_TASK_TIMED->Size = System::Drawing::Size(515, 282);
			this->DISPLAY_TASK_TIMED->TabIndex = 14;
			this->DISPLAY_TASK_TIMED->Text = L"";
			this->DISPLAY_TASK_TIMED->TextChanged += gcnew System::EventHandler(this, &GUI::DISPLAY_TASK_TIMED_TextChanged);
			// 
			// DISPLAY_MAIN
			// 
			this->DISPLAY_MAIN->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->DISPLAY_MAIN->Location = System::Drawing::Point(10, 349);
			this->DISPLAY_MAIN->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->DISPLAY_MAIN->Name = L"DISPLAY_MAIN";
			this->DISPLAY_MAIN->ReadOnly = true;
			this->DISPLAY_MAIN->Size = System::Drawing::Size(515, 244);
			this->DISPLAY_MAIN->TabIndex = 13;
			this->DISPLAY_MAIN->Text = L"";
			this->DISPLAY_MAIN->TextChanged += gcnew System::EventHandler(this, &GUI::DISPLAY_MAIN_TextChanged);
			// 
			// DISPLAY_TASK_FLOAT
			// 
			this->DISPLAY_TASK_FLOAT->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->DISPLAY_TASK_FLOAT->Location = System::Drawing::Point(540, 349);
			this->DISPLAY_TASK_FLOAT->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->DISPLAY_TASK_FLOAT->Name = L"DISPLAY_TASK_FLOAT";
			this->DISPLAY_TASK_FLOAT->ReadOnly = true;
			this->DISPLAY_TASK_FLOAT->Size = System::Drawing::Size(342, 244);
			this->DISPLAY_TASK_FLOAT->TabIndex = 11;
			this->DISPLAY_TASK_FLOAT->Text = L"";
			this->DISPLAY_TASK_FLOAT->TextChanged += gcnew System::EventHandler(this, &GUI::DISPLAY_TASK_FLOAT_TextChanged);
			// 
			// STATUS_BAR
			// 
			this->STATUS_BAR->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->DISPLAY_STATUS });
			this->STATUS_BAR->Location = System::Drawing::Point(0, 644);
			this->STATUS_BAR->Name = L"STATUS_BAR";
			this->STATUS_BAR->Padding = System::Windows::Forms::Padding(1, 0, 10, 0);
			this->STATUS_BAR->Size = System::Drawing::Size(892, 29);
			this->STATUS_BAR->TabIndex = 10;
			this->STATUS_BAR->Text = L"Welcome to I_Schedule.";
			// 
			// DISPLAY_STATUS
			// 
			this->DISPLAY_STATUS->Name = L"DISPLAY_STATUS";
			this->DISPLAY_STATUS->Size = System::Drawing::Size(96, 24);
			this->DISPLAY_STATUS->Text = L"Status Bar";
			// 
			// GUI
			// 
			this->AcceptButton = this->BUTTON_SEND;
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 18);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(896, 677);
			this->Controls->Add(this->panel1);
			this->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
			this->MinimumSize = System::Drawing::Size(808, 732);
			this->Name = L"GUI";
			this->Text = L"GUI";
			this->Load += gcnew System::EventHandler(this, &GUI::GUI_Load);
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->STATUS_BAR->ResumeLayout(false);
			this->STATUS_BAR->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	//@author A0099303A
	private: System::Void BUTTON_SEND_Click(System::Object^  sender, System::EventArgs^  e) {
		string input = msclr::interop::marshal_as<std::string>(INPUT_CMDLN->Text);
		controller->Run(input);
		//update displays from file
		DISPLAY_TASK_TIMED->LoadFile(gcnew String(controller->rtf_timed.c_str()));
		DISPLAY_TASK_DEADLINE->LoadFile(gcnew String(controller->rtf_deadline.c_str()));
		DISPLAY_TASK_FLOAT->LoadFile(gcnew String(controller->rtf_float.c_str()));
		DISPLAY_MAIN->LoadFile(gcnew String(controller->rtf_main.c_str()));
		//end update displays from file

		//update status bar
		DISPLAY_STATUS->Text = gcnew String(controller->DISPLAY_STATUS.c_str());
		//end update status bar

		//clear the text in command line
		INPUT_CMDLN->Clear();
	}

	private: System::Void DISPLAY_TASK_FLOAT_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		//this section allows the text box to scroll to the end automatically
		DISPLAY_TASK_FLOAT->SelectionStart = DISPLAY_TASK_FLOAT->TextLength;
		DISPLAY_TASK_FLOAT->ScrollToCaret();
		//end section

	}
	private: System::Void DISPLAY_MAIN_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		//this section allows the text box to scroll to the end automatically
		DISPLAY_MAIN->SelectionStart = DISPLAY_MAIN->TextLength;
		DISPLAY_MAIN->ScrollToCaret();
		//end section
	}	
	private: System::Void DISPLAY_TASK_TIMED_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		//this section allows the text box to scroll to the end automatically
		DISPLAY_TASK_TIMED->SelectionStart = DISPLAY_TASK_TIMED->TextLength;
		DISPLAY_TASK_TIMED->ScrollToCaret();
		//end section
	}
	private: System::Void GUI_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void INPUT_CMDLN_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		string input = msclr::interop::marshal_as<std::string>(INPUT_CMDLN->Text);
		controller->QuickSearch(input);
		DISPLAY_MAIN->LoadFile(gcnew String(controller->rtf_main.c_str()));
	}

private: System::Void DISPLAY_TASK_DEADLINE_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	//this section allows the text box to scroll to the end automatically
	DISPLAY_TASK_DEADLINE->SelectionStart = DISPLAY_TASK_DEADLINE->TextLength;
	DISPLAY_TASK_DEADLINE->ScrollToCaret();
	//end section
}
};
}
