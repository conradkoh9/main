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
			DISPLAY_TASK_TIMED->Text = gcnew String(controller->DISPLAY_TASK_TIMED.c_str());
			DISPLAY_TASK_DEADLINE->Text = gcnew String(controller->DISPLAY_TASK_DEADLINE.c_str());
			DISPLAY_TASK_FLOAT->Text = gcnew String(controller->DISPLAY_TASK_FLOAT.c_str());
			DISPLAY_MAIN->Text = gcnew String(controller->DISPLAY_MAIN.c_str());
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

	protected:
	private: System::Windows::Forms::TextBox^  INPUT_CMDLN;
	private: System::Windows::Forms::TextBox^  DISPLAY_TASK_DEADLINE;
	private: System::Windows::Forms::TextBox^  DISPLAY_TASK_FLOAT;
	private: System::Windows::Forms::TextBox^  DISPLAY_TASK_TIMED;
	private: System::Windows::Forms::TextBox^  DISPLAY_MAIN;
	private: System::Windows::Forms::TextBox^  LABEL_MAIN;
	private: System::Windows::Forms::TextBox^  LABEL_TIMED_TASKS;
	private: System::Windows::Forms::TextBox^  LABEL_DEADLINE_TASKS;




	private: System::Windows::Forms::TextBox^  LABEL_FLOATING_TASK;



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
			this->DISPLAY_TASK_DEADLINE = (gcnew System::Windows::Forms::TextBox());
			this->DISPLAY_TASK_FLOAT = (gcnew System::Windows::Forms::TextBox());
			this->DISPLAY_TASK_TIMED = (gcnew System::Windows::Forms::TextBox());
			this->DISPLAY_MAIN = (gcnew System::Windows::Forms::TextBox());
			this->LABEL_MAIN = (gcnew System::Windows::Forms::TextBox());
			this->LABEL_TIMED_TASKS = (gcnew System::Windows::Forms::TextBox());
			this->LABEL_DEADLINE_TASKS = (gcnew System::Windows::Forms::TextBox());
			this->LABEL_FLOATING_TASK = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// BUTTON_SEND
			// 
			this->BUTTON_SEND->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->BUTTON_SEND->Location = System::Drawing::Point(626, 567);
			this->BUTTON_SEND->Margin = System::Windows::Forms::Padding(2);
			this->BUTTON_SEND->Name = L"BUTTON_SEND";
			this->BUTTON_SEND->Size = System::Drawing::Size(142, 47);
			this->BUTTON_SEND->TabIndex = 0;
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
			this->INPUT_CMDLN->Location = System::Drawing::Point(9, 564);
			this->INPUT_CMDLN->Margin = System::Windows::Forms::Padding(2);
			this->INPUT_CMDLN->Multiline = true;
			this->INPUT_CMDLN->Name = L"INPUT_CMDLN";
			this->INPUT_CMDLN->Size = System::Drawing::Size(585, 47);
			this->INPUT_CMDLN->TabIndex = 0;
			// 
			// DISPLAY_TASK_DEADLINE
			// 
			this->DISPLAY_TASK_DEADLINE->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->DISPLAY_TASK_DEADLINE->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->DISPLAY_TASK_DEADLINE->Location = System::Drawing::Point(524, 203);
			this->DISPLAY_TASK_DEADLINE->Margin = System::Windows::Forms::Padding(2);
			this->DISPLAY_TASK_DEADLINE->Multiline = true;
			this->DISPLAY_TASK_DEADLINE->Name = L"DISPLAY_TASK_DEADLINE";
			this->DISPLAY_TASK_DEADLINE->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->DISPLAY_TASK_DEADLINE->Size = System::Drawing::Size(245, 344);
			this->DISPLAY_TASK_DEADLINE->TabIndex = 2;
			this->DISPLAY_TASK_DEADLINE->TextChanged += gcnew System::EventHandler(this, &GUI::DISPLAY_TASK_DEADLINE_TextChanged);
			// 
			// DISPLAY_TASK_FLOAT
			// 
			this->DISPLAY_TASK_FLOAT->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->DISPLAY_TASK_FLOAT->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->DISPLAY_TASK_FLOAT->Location = System::Drawing::Point(270, 204);
			this->DISPLAY_TASK_FLOAT->Margin = System::Windows::Forms::Padding(2);
			this->DISPLAY_TASK_FLOAT->Multiline = true;
			this->DISPLAY_TASK_FLOAT->Name = L"DISPLAY_TASK_FLOAT";
			this->DISPLAY_TASK_FLOAT->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->DISPLAY_TASK_FLOAT->Size = System::Drawing::Size(249, 343);
			this->DISPLAY_TASK_FLOAT->TabIndex = 3;
			this->DISPLAY_TASK_FLOAT->TextChanged += gcnew System::EventHandler(this, &GUI::DISPLAY_TASK_FLOAT_TextChanged);
			// 
			// DISPLAY_TASK_TIMED
			// 
			this->DISPLAY_TASK_TIMED->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->DISPLAY_TASK_TIMED->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->DISPLAY_TASK_TIMED->Location = System::Drawing::Point(9, 203);
			this->DISPLAY_TASK_TIMED->Margin = System::Windows::Forms::Padding(2);
			this->DISPLAY_TASK_TIMED->Multiline = true;
			this->DISPLAY_TASK_TIMED->Name = L"DISPLAY_TASK_TIMED";
			this->DISPLAY_TASK_TIMED->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->DISPLAY_TASK_TIMED->Size = System::Drawing::Size(258, 344);
			this->DISPLAY_TASK_TIMED->TabIndex = 4;
			this->DISPLAY_TASK_TIMED->TextChanged += gcnew System::EventHandler(this, &GUI::DISPLAY_TASK_TIMED_TextChanged);
			// 
			// DISPLAY_MAIN
			// 
			this->DISPLAY_MAIN->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->DISPLAY_MAIN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->DISPLAY_MAIN->Location = System::Drawing::Point(9, 24);
			this->DISPLAY_MAIN->Margin = System::Windows::Forms::Padding(2);
			this->DISPLAY_MAIN->Multiline = true;
			this->DISPLAY_MAIN->Name = L"DISPLAY_MAIN";
			this->DISPLAY_MAIN->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->DISPLAY_MAIN->Size = System::Drawing::Size(759, 149);
			this->DISPLAY_MAIN->TabIndex = 5;
			this->DISPLAY_MAIN->TextChanged += gcnew System::EventHandler(this, &GUI::DISPLAY_MAIN_TextChanged);
			// 
			// LABEL_MAIN
			// 
			this->LABEL_MAIN->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->LABEL_MAIN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->LABEL_MAIN->Location = System::Drawing::Point(11, -2);
			this->LABEL_MAIN->Margin = System::Windows::Forms::Padding(2);
			this->LABEL_MAIN->Multiline = true;
			this->LABEL_MAIN->Name = L"LABEL_MAIN";
			this->LABEL_MAIN->ReadOnly = true;
			this->LABEL_MAIN->Size = System::Drawing::Size(75, 22);
			this->LABEL_MAIN->TabIndex = 6;
			this->LABEL_MAIN->Text = L"Main";
			// 
			// LABEL_TIMED_TASKS
			// 
			this->LABEL_TIMED_TASKS->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->LABEL_TIMED_TASKS->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->LABEL_TIMED_TASKS->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->LABEL_TIMED_TASKS->Location = System::Drawing::Point(271, 178);
			this->LABEL_TIMED_TASKS->Margin = System::Windows::Forms::Padding(2);
			this->LABEL_TIMED_TASKS->Multiline = true;
			this->LABEL_TIMED_TASKS->Name = L"LABEL_TIMED_TASKS";
			this->LABEL_TIMED_TASKS->ReadOnly = true;
			this->LABEL_TIMED_TASKS->Size = System::Drawing::Size(157, 22);
			this->LABEL_TIMED_TASKS->TabIndex = 7;
			this->LABEL_TIMED_TASKS->Text = L"Timed Tasks";
			// 
			// LABEL_DEADLINE_TASKS
			// 
			this->LABEL_DEADLINE_TASKS->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->LABEL_DEADLINE_TASKS->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->LABEL_DEADLINE_TASKS->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->LABEL_DEADLINE_TASKS->Location = System::Drawing::Point(550, 177);
			this->LABEL_DEADLINE_TASKS->Margin = System::Windows::Forms::Padding(2);
			this->LABEL_DEADLINE_TASKS->Multiline = true;
			this->LABEL_DEADLINE_TASKS->Name = L"LABEL_DEADLINE_TASKS";
			this->LABEL_DEADLINE_TASKS->ReadOnly = true;
			this->LABEL_DEADLINE_TASKS->Size = System::Drawing::Size(164, 22);
			this->LABEL_DEADLINE_TASKS->TabIndex = 8;
			this->LABEL_DEADLINE_TASKS->Text = L"Deadline Tasks";
			// 
			// LABEL_FLOATING_TASK
			// 
			this->LABEL_FLOATING_TASK->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->LABEL_FLOATING_TASK->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->LABEL_FLOATING_TASK->Location = System::Drawing::Point(11, 177);
			this->LABEL_FLOATING_TASK->Margin = System::Windows::Forms::Padding(2);
			this->LABEL_FLOATING_TASK->Multiline = true;
			this->LABEL_FLOATING_TASK->Name = L"LABEL_FLOATING_TASK";
			this->LABEL_FLOATING_TASK->ReadOnly = true;
			this->LABEL_FLOATING_TASK->Size = System::Drawing::Size(209, 22);
			this->LABEL_FLOATING_TASK->TabIndex = 9;
			this->LABEL_FLOATING_TASK->Text = L"Floating Tasks";
			// 
			// GUI
			// 
			this->AcceptButton = this->BUTTON_SEND;
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 18);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(784, 622);
			this->Controls->Add(this->LABEL_FLOATING_TASK);
			this->Controls->Add(this->LABEL_DEADLINE_TASKS);
			this->Controls->Add(this->LABEL_TIMED_TASKS);
			this->Controls->Add(this->LABEL_MAIN);
			this->Controls->Add(this->DISPLAY_MAIN);
			this->Controls->Add(this->DISPLAY_TASK_TIMED);
			this->Controls->Add(this->DISPLAY_TASK_FLOAT);
			this->Controls->Add(this->DISPLAY_TASK_DEADLINE);
			this->Controls->Add(this->INPUT_CMDLN);
			this->Controls->Add(this->BUTTON_SEND);
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"GUI";
			this->Text = L"GUI";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void BUTTON_SEND_Click(System::Object^  sender, System::EventArgs^  e) {
		string input = msclr::interop::marshal_as<std::string>(INPUT_CMDLN->Text);
		controller->Run(input);
		DISPLAY_TASK_TIMED->Text = gcnew String(controller->DISPLAY_TASK_TIMED.c_str());
		DISPLAY_TASK_DEADLINE->Text = gcnew String(controller->DISPLAY_TASK_DEADLINE.c_str());
		DISPLAY_TASK_FLOAT->Text = gcnew String(controller->DISPLAY_TASK_FLOAT.c_str());
		DISPLAY_MAIN->Text = gcnew String(controller->DISPLAY_MAIN.c_str());
		INPUT_CMDLN->Clear();
	}
	private: System::Void DISPLAY_TASK_DEADLINE_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		//this section allows the text box to scroll to the end automatically
		DISPLAY_TASK_DEADLINE->SelectionStart = DISPLAY_TASK_DEADLINE->TextLength;
		DISPLAY_TASK_DEADLINE->ScrollToCaret();
		//end section

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
	};
}
