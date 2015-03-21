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
			this->SuspendLayout();
			// 
			// BUTTON_SEND
			// 
			this->BUTTON_SEND->Location = System::Drawing::Point(834, 787);
			this->BUTTON_SEND->Name = L"BUTTON_SEND";
			this->BUTTON_SEND->Size = System::Drawing::Size(190, 65);
			this->BUTTON_SEND->TabIndex = 0;
			this->BUTTON_SEND->Text = L"SEND";
			this->BUTTON_SEND->UseVisualStyleBackColor = true;
			this->BUTTON_SEND->Click += gcnew System::EventHandler(this, &GUI::BUTTON_SEND_Click);
			// 
			// INPUT_CMDLN
			// 
			this->INPUT_CMDLN->Location = System::Drawing::Point(33, 787);
			this->INPUT_CMDLN->Multiline = true;
			this->INPUT_CMDLN->Name = L"INPUT_CMDLN";
			this->INPUT_CMDLN->Size = System::Drawing::Size(758, 64);
			this->INPUT_CMDLN->TabIndex = 0;
			// 
			// DISPLAY_TASK_DEADLINE
			// 
			this->DISPLAY_TASK_DEADLINE->Location = System::Drawing::Point(748, 254);
			this->DISPLAY_TASK_DEADLINE->Multiline = true;
			this->DISPLAY_TASK_DEADLINE->Name = L"DISPLAY_TASK_DEADLINE";
			this->DISPLAY_TASK_DEADLINE->Size = System::Drawing::Size(276, 504);
			this->DISPLAY_TASK_DEADLINE->TabIndex = 2;
			// 
			// DISPLAY_TASK_FLOAT
			// 
			this->DISPLAY_TASK_FLOAT->Location = System::Drawing::Point(33, 12);
			this->DISPLAY_TASK_FLOAT->Multiline = true;
			this->DISPLAY_TASK_FLOAT->Name = L"DISPLAY_TASK_FLOAT";
			this->DISPLAY_TASK_FLOAT->Size = System::Drawing::Size(991, 220);
			this->DISPLAY_TASK_FLOAT->TabIndex = 3;
			// 
			// DISPLAY_TASK_TIMED
			// 
			this->DISPLAY_TASK_TIMED->Location = System::Drawing::Point(33, 254);
			this->DISPLAY_TASK_TIMED->Multiline = true;
			this->DISPLAY_TASK_TIMED->Name = L"DISPLAY_TASK_TIMED";
			this->DISPLAY_TASK_TIMED->Size = System::Drawing::Size(695, 504);
			this->DISPLAY_TASK_TIMED->TabIndex = 4;
			// 
			// GUI
			// 
			this->AcceptButton = this->BUTTON_SEND;
			this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1046, 864);
			this->Controls->Add(this->DISPLAY_TASK_TIMED);
			this->Controls->Add(this->DISPLAY_TASK_FLOAT);
			this->Controls->Add(this->DISPLAY_TASK_DEADLINE);
			this->Controls->Add(this->INPUT_CMDLN);
			this->Controls->Add(this->BUTTON_SEND);
			this->Name = L"GUI";
			this->Text = L"GUI";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void BUTTON_SEND_Click(System::Object^  sender, System::EventArgs^  e) {
		string input = msclr::interop::marshal_as<std::string>(INPUT_CMDLN->Text);
		DISPLAY_TASK_TIMED->Text = gcnew String(controller->Run(input).c_str());
		INPUT_CMDLN->Clear();
	}
};
}
