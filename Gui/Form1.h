#pragma once

namespace CppCLRWinformsProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::ListBox^ listBox1;
	private: System::Windows::Forms::Label^ label3;



	protected:

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// start button
			// 
			this->button1->Location = System::Drawing::Point(67, 42);
			this->button1->Name = L"startButton";
			this->button1->Size = System::Drawing::Size(194, 54);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Start";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// stop button
			// 
			this->button2->Location = System::Drawing::Point(267, 42);
			this->button2->Name = L"stopButton";
			this->button2->Size = System::Drawing::Size(194, 54);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Stop";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// action notification label
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(493, 42);
			this->label1->Name = L"actionLabel";
			this->label1->Size = System::Drawing::Size(85, 17);
			this->label1->TabIndex = 2;
			this->label1->Text = L"action Label";
			// 
			// textBox for name input
			// 
			this->textBox1->Location = System::Drawing::Point(267, 12);
			this->textBox1->Name = L"nameTextBox";
			this->textBox1->Size = System::Drawing::Size(194, 22);
			this->textBox1->TabIndex = 3;
			// 
			// name label
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(64, 12);
			this->label2->Name = L"nameLabel";
			this->label2->Size = System::Drawing::Size(53, 17);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Name: ";
			// 
			// stop button
			// 
			this->button3->Location = System::Drawing::Point(482, 4);
			this->button3->Name = L"stopButton";
			this->button3->Size = System::Drawing::Size(92, 30);
			this->button3->TabIndex = 5;
			this->button3->Text = L"Safe";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// score listBox
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->ItemHeight = 16;
			this->listBox1->Location = System::Drawing::Point(1218, 77);
			this->listBox1->Name = L"scoreListBox";
			this->listBox1->Size = System::Drawing::Size(322, 276);
			this->listBox1->TabIndex = 6;
			// 
			// best score label
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(1215, 42);
			this->label3->Name = L"bestScoreLabel";
			this->label3->Size = System::Drawing::Size(82, 17);
			this->label3->TabIndex = 7;
			this->label3->Text = L"Best score";
			// 
			// Form1
			// 
			this->AccessibleDescription = L"";
			this->AccessibleName = L"";
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1597, 728);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->listBox1);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Name = L"Form1";
			this->Text = L"B1 minigame";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	}

	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	}

	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
	}

};
}
