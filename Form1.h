#pragma once

#include <regex>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <msclr\marshal_cppstd.h>
#include <codecvt>
#include <locale>

#define SEND_DATA_SCRIPT_DIR "sendGooglePlayData.exe"
#define SAVED_DATA_DIR "Program files\\savedData.txt"
#define INPUT_DATA_DIR "Program files\\inputData.txt"


namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Text;
	using namespace msclr::interop;
	using namespace std;
	using namespace System::Diagnostics;


	void get_lines(vector<string>& lines) {
		try {
			std::fstream file = std::fstream(SAVED_DATA_DIR, ios::in);
			string line;
			while (getline(file, line))
			{
				lines.push_back(line);
			}
			file.close();
		}
		catch(Exception ^ e) {
			MessageBox::Show("Error loading saved data: " + e->Message);
		}
	}

	void write_saved_data(string pp = "", string cr = "",
		string e = "", string w = "", string u = "") {
		try {
			std::fstream file = std::fstream(SAVED_DATA_DIR, ios::trunc | ios::out);
			file.close();
			file = std::fstream(SAVED_DATA_DIR, ios::out);
			file << pp << "\n"
				<< cr << "\n"
				<< e << "\n"
				<< w << "\n"
				<< u << "\n";
			file.flush();
			file.close();
		}
		catch (Exception^ e) {
			MessageBox::Show("Error: " + e->Message);
		}
	}


	void update_saved_data(string& newData, int rowNum) {
		try {
			vector<string> lines;
			get_lines(lines);
			lines[rowNum] = newData;
			write_saved_data(lines[0], lines[1], lines[2], lines[3], lines[4]);
		}
		catch (Exception^ e) {
			MessageBox::Show("Error: " + e->Message);
		}
	}
	
	void removeNewlines(std::wstring& str) {
		size_t pos = 0;
		while ((pos = str.find('\n', pos)) != std::wstring::npos) {
			str.erase(pos, 1);
		}
	}

	/*int countLines(const std::string& str) {
		std::istringstream iss(str);
		return std::count(std::istreambuf_iterator<char>(iss),
			std::istreambuf_iterator<char>(), '\n') + 1;
	}*/
	int countLines(const std::wstring& str) {
		int count = 1;  // Start count at 1, since the last line may not end with '\n'

		for (auto c : str) {
			if (c == L'\n') {
				count++;
			}
		}
		return count;
	}

	void write_input_data(const vector<wstring>& vec) {
		try {
			std::wfstream file = std::wfstream(INPUT_DATA_DIR, ios::trunc | ios::out);
			file.close();
			file = std::wfstream(INPUT_DATA_DIR, ios::out);
			file.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));
			for (int i = 0; i < vec.size(); i++) {
				if (i == 5) {
					wstring line = vec[i];
					int nLinesFullDesc = countLines(line);
					removeNewlines(line);
					file << nLinesFullDesc << "\n";
					file << line << "\n";
				}
				else {
					file << vec[i] << "\n";
				}
				
			}
			file.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));
			file.flush();
			file.close();
		}
		catch (Exception^ e) {
			MessageBox::Show("Error: " + e->Message);
		}
	}


	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		int tagsCount = 0;

		Form1(void)
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
		~Form1()
		{
			
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ name;
	protected:

	private: System::Windows::Forms::Label^ Privacy_policy;
	private: System::Windows::Forms::Label^ Content_ratings;
	private: System::Windows::Forms::Label^ Short_desc;
	private: System::Windows::Forms::Label^ Full_disc;
	private: System::Windows::Forms::Label^ Tags;
	protected:

	protected:





	private: System::Windows::Forms::Label^ Category;
	private: System::Windows::Forms::Label^ Email;
	private: System::Windows::Forms::Label^ Website;





	private: System::Windows::Forms::TextBox^ nTextBox;

	private: System::Windows::Forms::RadioButton^ radioButton1;
	private: System::Windows::Forms::RadioButton^ radioButton2;
	private: System::Windows::Forms::RadioButton^ radioButton3;
	private: System::Windows::Forms::TextBox^ ppTextBox;

	private: System::ComponentModel::BackgroundWorker^ backgroundWorker1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::TextBox^ crTextBox;

	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::TextBox^ sdTextBox;
	private: System::Windows::Forms::TextBox^ fdTextBox;
	private: System::Windows::Forms::RadioButton^ radioButton4;
	private: System::Windows::Forms::RadioButton^ radioButton5;
	private: System::Windows::Forms::RadioButton^ radioButton6;
	private: System::Windows::Forms::RadioButton^ radioButton7;












	private: System::Windows::Forms::TextBox^ eTextBox;
	private: System::Windows::Forms::TextBox^ wTextBox;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Button^ button5;
	private: System::Windows::Forms::GroupBox^ languageGroupBox;
	private: System::Windows::Forms::GroupBox^ catGroupBox;
	private: System::Windows::Forms::CheckBox^ checkBox1;
	private: System::Windows::Forms::CheckBox^ checkBox2;
	private: System::Windows::Forms::CheckBox^ checkBox3;
	private: System::Windows::Forms::CheckBox^ checkBox4;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ uTextBox;

	private: System::Windows::Forms::CheckBox^ checkBox5;
	private: System::Windows::Forms::CheckBox^ checkBox6;
	private: System::Windows::Forms::CheckBox^ checkBox7;
	private: System::Windows::Forms::CheckBox^ checkBox8;
	private: System::Windows::Forms::CheckBox^ checkBox9;
	private: System::Windows::Forms::CheckBox^ checkBox10;
	private: System::Windows::Forms::CheckBox^ checkBox11;
	private: System::Windows::Forms::CheckBox^ checkBox12;
	private: System::Windows::Forms::GroupBox^ tagsGroupBox;
private: System::Windows::Forms::Button^ button6;










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
			this->name = (gcnew System::Windows::Forms::Label());
			this->Privacy_policy = (gcnew System::Windows::Forms::Label());
			this->Content_ratings = (gcnew System::Windows::Forms::Label());
			this->Short_desc = (gcnew System::Windows::Forms::Label());
			this->Full_disc = (gcnew System::Windows::Forms::Label());
			this->Tags = (gcnew System::Windows::Forms::Label());
			this->Category = (gcnew System::Windows::Forms::Label());
			this->Email = (gcnew System::Windows::Forms::Label());
			this->Website = (gcnew System::Windows::Forms::Label());
			this->nTextBox = (gcnew System::Windows::Forms::TextBox());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
			this->ppTextBox = (gcnew System::Windows::Forms::TextBox());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->crTextBox = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->sdTextBox = (gcnew System::Windows::Forms::TextBox());
			this->fdTextBox = (gcnew System::Windows::Forms::TextBox());
			this->radioButton4 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton5 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton6 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton7 = (gcnew System::Windows::Forms::RadioButton());
			this->eTextBox = (gcnew System::Windows::Forms::TextBox());
			this->wTextBox = (gcnew System::Windows::Forms::TextBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->languageGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->catGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox4 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox5 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox6 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox7 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox8 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox9 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox10 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox11 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox12 = (gcnew System::Windows::Forms::CheckBox());
			this->tagsGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->uTextBox = (gcnew System::Windows::Forms::TextBox());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->languageGroupBox->SuspendLayout();
			this->catGroupBox->SuspendLayout();
			this->tagsGroupBox->SuspendLayout();
			this->SuspendLayout();
			// 
			// name
			// 
			this->name->AutoSize = true;
			this->name->Location = System::Drawing::Point(12, 49);
			this->name->Name = L"name";
			this->name->Size = System::Drawing::Size(44, 16);
			this->name->TabIndex = 0;
			this->name->Text = L"Name";
			this->name->Click += gcnew System::EventHandler(this, &Form1::label1_Click);
			// 
			// Privacy_policy
			// 
			this->Privacy_policy->AutoSize = true;
			this->Privacy_policy->Location = System::Drawing::Point(12, 125);
			this->Privacy_policy->Name = L"Privacy_policy";
			this->Privacy_policy->Size = System::Drawing::Size(92, 16);
			this->Privacy_policy->TabIndex = 1;
			this->Privacy_policy->Text = L"Privacy Policy";
			this->Privacy_policy->Click += gcnew System::EventHandler(this, &Form1::label2_Click);
			// 
			// Content_ratings
			// 
			this->Content_ratings->AutoSize = true;
			this->Content_ratings->Location = System::Drawing::Point(12, 187);
			this->Content_ratings->Name = L"Content_ratings";
			this->Content_ratings->Size = System::Drawing::Size(101, 16);
			this->Content_ratings->TabIndex = 1;
			this->Content_ratings->Text = L"Content Ratings";
			// 
			// Short_desc
			// 
			this->Short_desc->AutoSize = true;
			this->Short_desc->Location = System::Drawing::Point(12, 246);
			this->Short_desc->Name = L"Short_desc";
			this->Short_desc->Size = System::Drawing::Size(104, 16);
			this->Short_desc->TabIndex = 1;
			this->Short_desc->Text = L"Short Discription";
			// 
			// Full_disc
			// 
			this->Full_disc->AutoSize = true;
			this->Full_disc->Location = System::Drawing::Point(12, 298);
			this->Full_disc->Name = L"Full_disc";
			this->Full_disc->Size = System::Drawing::Size(94, 16);
			this->Full_disc->TabIndex = 1;
			this->Full_disc->Text = L"Full Discription";
			this->Full_disc->Click += gcnew System::EventHandler(this, &Form1::Full_disc_Click);
			// 
			// Tags
			// 
			this->Tags->AutoSize = true;
			this->Tags->Location = System::Drawing::Point(12, 493);
			this->Tags->Name = L"Tags";
			this->Tags->Size = System::Drawing::Size(39, 16);
			this->Tags->TabIndex = 1;
			this->Tags->Text = L"Tags";
			this->Tags->Click += gcnew System::EventHandler(this, &Form1::Tags_Click);
			// 
			// Category
			// 
			this->Category->AutoSize = true;
			this->Category->Location = System::Drawing::Point(12, 443);
			this->Category->Name = L"Category";
			this->Category->Size = System::Drawing::Size(62, 16);
			this->Category->TabIndex = 1;
			this->Category->Text = L"Category";
			this->Category->Click += gcnew System::EventHandler(this, &Form1::Category_Click);
			// 
			// Email
			// 
			this->Email->AutoSize = true;
			this->Email->Location = System::Drawing::Point(12, 599);
			this->Email->Name = L"Email";
			this->Email->Size = System::Drawing::Size(41, 16);
			this->Email->TabIndex = 1;
			this->Email->Text = L"Email";
			this->Email->Click += gcnew System::EventHandler(this, &Form1::Email_Click);
			// 
			// Website
			// 
			this->Website->AutoSize = true;
			this->Website->Location = System::Drawing::Point(12, 647);
			this->Website->Name = L"Website";
			this->Website->Size = System::Drawing::Size(57, 16);
			this->Website->TabIndex = 1;
			this->Website->Text = L"Website";
			this->Website->Click += gcnew System::EventHandler(this, &Form1::Website_Click);
			// 
			// nTextBox
			// 
			this->nTextBox->Cursor = System::Windows::Forms::Cursors::IBeam;
			this->nTextBox->Location = System::Drawing::Point(122, 49);
			this->nTextBox->MaxLength = 30;
			this->nTextBox->Name = L"nTextBox";
			this->nTextBox->Size = System::Drawing::Size(186, 22);
			this->nTextBox->TabIndex = 2;
			this->nTextBox->TextChanged += gcnew System::EventHandler(this, &Form1::textBox1_TextChanged);
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Location = System::Drawing::Point(6, 7);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(67, 20);
			this->radioButton1->TabIndex = 3;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"Arabic";
			this->radioButton1->UseVisualStyleBackColor = true;
			this->radioButton1->CheckedChanged += gcnew System::EventHandler(this, &Form1::radioButton1_CheckedChanged);
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Checked = true;
			this->radioButton2->Location = System::Drawing::Point(95, 7);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(72, 20);
			this->radioButton2->TabIndex = 3;
			this->radioButton2->TabStop = true;
			this->radioButton2->Text = L"English";
			this->radioButton2->UseVisualStyleBackColor = true;
			this->radioButton2->CheckedChanged += gcnew System::EventHandler(this, &Form1::radioButton1_CheckedChanged);
			// 
			// radioButton3
			// 
			this->radioButton3->Cursor = System::Windows::Forms::Cursors::IBeam;
			this->radioButton3->Location = System::Drawing::Point(204, 7);
			this->radioButton3->Name = L"radioButton3";
			this->radioButton3->Size = System::Drawing::Size(80, 20);
			this->radioButton3->TabIndex = 3;
			this->radioButton3->Text = L"Francais";
			this->radioButton3->UseVisualStyleBackColor = true;
			this->radioButton3->CheckedChanged += gcnew System::EventHandler(this, &Form1::radioButton1_CheckedChanged);
			// 
			// ppTextBox
			// 
			this->ppTextBox->Location = System::Drawing::Point(122, 125);
			this->ppTextBox->Name = L"ppTextBox";
			this->ppTextBox->Size = System::Drawing::Size(271, 22);
			this->ppTextBox->TabIndex = 4;
			this->ppTextBox->TextChanged += gcnew System::EventHandler(this, &Form1::textBox1_TextChanged_1);
			// 
			// backgroundWorker1
			// 
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::backgroundWorker1_DoWork);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(413, 122);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 5;
			this->button1->Text = L"Save";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// crTextBox
			// 
			this->crTextBox->Location = System::Drawing::Point(122, 187);
			this->crTextBox->Name = L"crTextBox";
			this->crTextBox->Size = System::Drawing::Size(271, 22);
			this->crTextBox->TabIndex = 4;
			this->crTextBox->TextChanged += gcnew System::EventHandler(this, &Form1::textBox1_TextChanged_1);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(413, 187);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 5;
			this->button2->Text = L"Save";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// sdTextBox
			// 
			this->sdTextBox->Location = System::Drawing::Point(122, 246);
			this->sdTextBox->MaxLength = 80;
			this->sdTextBox->Name = L"sdTextBox";
			this->sdTextBox->Size = System::Drawing::Size(271, 22);
			this->sdTextBox->TabIndex = 4;
			this->sdTextBox->TextChanged += gcnew System::EventHandler(this, &Form1::textBox1_TextChanged_1);
			// 
			// fdTextBox
			// 
			this->fdTextBox->Location = System::Drawing::Point(122, 298);
			this->fdTextBox->Multiline = true;
			this->fdTextBox->Name = L"fdTextBox";
			this->fdTextBox->Size = System::Drawing::Size(274, 113);
			this->fdTextBox->TabIndex = 4;
			this->fdTextBox->TextChanged += gcnew System::EventHandler(this, &Form1::textBox1_TextChanged_1);
			// 
			// radioButton4
			// 
			this->radioButton4->AutoSize = true;
			this->radioButton4->Checked = true;
			this->radioButton4->Location = System::Drawing::Point(10, 12);
			this->radioButton4->Name = L"radioButton4";
			this->radioButton4->Size = System::Drawing::Size(72, 20);
			this->radioButton4->TabIndex = 3;
			this->radioButton4->TabStop = true;
			this->radioButton4->Text = L"Arcade";
			this->radioButton4->UseVisualStyleBackColor = true;
			this->radioButton4->CheckedChanged += gcnew System::EventHandler(this, &Form1::radioButton1_CheckedChanged);
			// 
			// radioButton5
			// 
			this->radioButton5->AutoSize = true;
			this->radioButton5->Location = System::Drawing::Point(116, 12);
			this->radioButton5->Name = L"radioButton5";
			this->radioButton5->Size = System::Drawing::Size(70, 20);
			this->radioButton5->TabIndex = 3;
			this->radioButton5->TabStop = true;
			this->radioButton5->Text = L"Casual";
			this->radioButton5->UseVisualStyleBackColor = true;
			this->radioButton5->CheckedChanged += gcnew System::EventHandler(this, &Form1::radioButton1_CheckedChanged);
			// 
			// radioButton6
			// 
			this->radioButton6->AutoSize = true;
			this->radioButton6->Location = System::Drawing::Point(214, 12);
			this->radioButton6->Name = L"radioButton6";
			this->radioButton6->Size = System::Drawing::Size(86, 20);
			this->radioButton6->TabIndex = 3;
			this->radioButton6->TabStop = true;
			this->radioButton6->Text = L"Role play";
			this->radioButton6->UseVisualStyleBackColor = true;
			this->radioButton6->CheckedChanged += gcnew System::EventHandler(this, &Form1::radioButton1_CheckedChanged);
			// 
			// radioButton7
			// 
			this->radioButton7->AutoSize = true;
			this->radioButton7->Location = System::Drawing::Point(345, 12);
			this->radioButton7->Name = L"radioButton7";
			this->radioButton7->Size = System::Drawing::Size(90, 20);
			this->radioButton7->TabIndex = 3;
			this->radioButton7->Text = L"Simulation";
			this->radioButton7->UseVisualStyleBackColor = true;
			this->radioButton7->CheckedChanged += gcnew System::EventHandler(this, &Form1::radioButton1_CheckedChanged);
			// 
			// eTextBox
			// 
			this->eTextBox->Location = System::Drawing::Point(122, 599);
			this->eTextBox->Name = L"eTextBox";
			this->eTextBox->Size = System::Drawing::Size(274, 22);
			this->eTextBox->TabIndex = 4;
			this->eTextBox->TextChanged += gcnew System::EventHandler(this, &Form1::textBox1_TextChanged_1);
			// 
			// wTextBox
			// 
			this->wTextBox->Location = System::Drawing::Point(122, 647);
			this->wTextBox->Name = L"wTextBox";
			this->wTextBox->Size = System::Drawing::Size(274, 22);
			this->wTextBox->TabIndex = 4;
			this->wTextBox->TextChanged += gcnew System::EventHandler(this, &Form1::textBox1_TextChanged_1);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(534, 699);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(101, 38);
			this->button3->TabIndex = 5;
			this->button3->Text = L"Go";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(413, 599);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(75, 23);
			this->button4->TabIndex = 5;
			this->button4->Text = L"Save";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Form1::button4_Click);
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(413, 644);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(75, 23);
			this->button5->TabIndex = 5;
			this->button5->Text = L"Save";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &Form1::button5_Click);
			// 
			// languageGroupBox
			// 
			this->languageGroupBox->Controls->Add(this->radioButton1);
			this->languageGroupBox->Controls->Add(this->radioButton2);
			this->languageGroupBox->Controls->Add(this->radioButton3);
			this->languageGroupBox->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->languageGroupBox->Location = System::Drawing::Point(122, 77);
			this->languageGroupBox->Name = L"languageGroupBox";
			this->languageGroupBox->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->languageGroupBox->Size = System::Drawing::Size(292, 33);
			this->languageGroupBox->TabIndex = 6;
			this->languageGroupBox->TabStop = false;
			this->languageGroupBox->Enter += gcnew System::EventHandler(this, &Form1::groupBox1_Enter);
			// 
			// catGroupBox
			// 
			this->catGroupBox->Controls->Add(this->radioButton6);
			this->catGroupBox->Controls->Add(this->radioButton5);
			this->catGroupBox->Controls->Add(this->radioButton7);
			this->catGroupBox->Controls->Add(this->radioButton4);
			this->catGroupBox->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->catGroupBox->Location = System::Drawing::Point(112, 431);
			this->catGroupBox->Name = L"catGroupBox";
			this->catGroupBox->Size = System::Drawing::Size(450, 37);
			this->catGroupBox->TabIndex = 6;
			this->catGroupBox->TabStop = false;
			this->catGroupBox->Enter += gcnew System::EventHandler(this, &Form1::groupBox1_Enter);
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(14, 7);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(73, 20);
			this->checkBox1->TabIndex = 7;
			this->checkBox1->Text = L"Arcade";
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->Click += gcnew System::EventHandler(this, &Form1::checkBox1_CheckedChanged);
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Location = System::Drawing::Point(110, 8);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(71, 20);
			this->checkBox2->TabIndex = 7;
			this->checkBox2->Text = L"Casual";
			this->checkBox2->UseVisualStyleBackColor = true;
			this->checkBox2->Click += gcnew System::EventHandler(this, &Form1::checkBox2_CheckedChanged);
			// 
			// checkBox3
			// 
			this->checkBox3->AutoSize = true;
			this->checkBox3->Location = System::Drawing::Point(200, 8);
			this->checkBox3->Name = L"checkBox3";
			this->checkBox3->Size = System::Drawing::Size(89, 20);
			this->checkBox3->TabIndex = 7;
			this->checkBox3->Text = L"Nail salon";
			this->checkBox3->UseVisualStyleBackColor = true;
			this->checkBox3->Click += gcnew System::EventHandler(this, &Form1::checkBox3_CheckedChanged);
			// 
			// checkBox4
			// 
			this->checkBox4->AutoSize = true;
			this->checkBox4->Location = System::Drawing::Point(331, 8);
			this->checkBox4->Name = L"checkBox4";
			this->checkBox4->Size = System::Drawing::Size(90, 20);
			this->checkBox4->TabIndex = 7;
			this->checkBox4->Text = L"Hair salon";
			this->checkBox4->UseVisualStyleBackColor = true;
			this->checkBox4->Click += gcnew System::EventHandler(this, &Form1::checkBox4_CheckedChanged);
			// 
			// checkBox5
			// 
			this->checkBox5->AutoSize = true;
			this->checkBox5->Location = System::Drawing::Point(14, 33);
			this->checkBox5->Name = L"checkBox5";
			this->checkBox5->Size = System::Drawing::Size(80, 20);
			this->checkBox5->TabIndex = 7;
			this->checkBox5->Text = L"Dressup";
			this->checkBox5->UseVisualStyleBackColor = true;
			this->checkBox5->Click += gcnew System::EventHandler(this, &Form1::checkBox5_CheckedChanged);
			// 
			// checkBox6
			// 
			this->checkBox6->AutoSize = true;
			this->checkBox6->Location = System::Drawing::Point(110, 34);
			this->checkBox6->Name = L"checkBox6";
			this->checkBox6->Size = System::Drawing::Size(78, 20);
			this->checkBox6->TabIndex = 7;
			this->checkBox6->Text = L"Makeup";
			this->checkBox6->UseVisualStyleBackColor = true;
			this->checkBox6->Click += gcnew System::EventHandler(this, &Form1::checkBox6_CheckedChanged);
			// 
			// checkBox7
			// 
			this->checkBox7->AutoSize = true;
			this->checkBox7->Location = System::Drawing::Point(200, 34);
			this->checkBox7->Name = L"checkBox7";
			this->checkBox7->Size = System::Drawing::Size(113, 20);
			this->checkBox7->TabIndex = 7;
			this->checkBox7->Text = L"Life simulation";
			this->checkBox7->UseVisualStyleBackColor = true;
			this->checkBox7->Click += gcnew System::EventHandler(this, &Form1::checkBox7_CheckedChanged);
			// 
			// checkBox8
			// 
			this->checkBox8->AutoSize = true;
			this->checkBox8->Location = System::Drawing::Point(331, 34);
			this->checkBox8->Name = L"checkBox8";
			this->checkBox8->Size = System::Drawing::Size(144, 20);
			this->checkBox8->TabIndex = 7;
			this->checkBox8->Text = L"Life style simulation";
			this->checkBox8->UseVisualStyleBackColor = true;
			this->checkBox8->Click += gcnew System::EventHandler(this, &Form1::checkBox8_CheckedChanged);
			// 
			// checkBox9
			// 
			this->checkBox9->AutoSize = true;
			this->checkBox9->Location = System::Drawing::Point(14, 59);
			this->checkBox9->Name = L"checkBox9";
			this->checkBox9->Size = System::Drawing::Size(91, 20);
			this->checkBox9->TabIndex = 7;
			this->checkBox9->Text = L"Simulation";
			this->checkBox9->UseVisualStyleBackColor = true;
			this->checkBox9->Click += gcnew System::EventHandler(this, &Form1::checkBox9_CheckedChanged);
			// 
			// checkBox10
			// 
			this->checkBox10->AutoSize = true;
			this->checkBox10->Location = System::Drawing::Point(110, 60);
			this->checkBox10->Name = L"checkBox10";
			this->checkBox10->Size = System::Drawing::Size(72, 20);
			this->checkBox10->TabIndex = 7;
			this->checkBox10->Text = L"Design";
			this->checkBox10->UseVisualStyleBackColor = true;
			this->checkBox10->Click += gcnew System::EventHandler(this, &Form1::checkBox10_CheckedChanged);
			// 
			// checkBox11
			// 
			this->checkBox11->AutoSize = true;
			this->checkBox11->Location = System::Drawing::Point(200, 60);
			this->checkBox11->Name = L"checkBox11";
			this->checkBox11->Size = System::Drawing::Size(121, 20);
			this->checkBox11->TabIndex = 7;
			this->checkBox11->Text = L"Care simulation";
			this->checkBox11->UseVisualStyleBackColor = true;
			this->checkBox11->Click += gcnew System::EventHandler(this, &Form1::checkBox11_CheckedChanged);
			// 
			// checkBox12
			// 
			this->checkBox12->AutoSize = true;
			this->checkBox12->Location = System::Drawing::Point(331, 60);
			this->checkBox12->Name = L"checkBox12";
			this->checkBox12->Size = System::Drawing::Size(130, 20);
			this->checkBox12->TabIndex = 7;
			this->checkBox12->Text = L"Social simulation";
			this->checkBox12->UseVisualStyleBackColor = true;
			this->checkBox12->Click += gcnew System::EventHandler(this, &Form1::checkBox12_CheckedChanged);
			// 
			// tagsGroupBox
			// 
			this->tagsGroupBox->Controls->Add(this->checkBox12);
			this->tagsGroupBox->Controls->Add(this->checkBox8);
			this->tagsGroupBox->Controls->Add(this->checkBox4);
			this->tagsGroupBox->Controls->Add(this->checkBox11);
			this->tagsGroupBox->Controls->Add(this->checkBox7);
			this->tagsGroupBox->Controls->Add(this->checkBox3);
			this->tagsGroupBox->Controls->Add(this->checkBox10);
			this->tagsGroupBox->Controls->Add(this->checkBox9);
			this->tagsGroupBox->Controls->Add(this->checkBox6);
			this->tagsGroupBox->Controls->Add(this->checkBox5);
			this->tagsGroupBox->Controls->Add(this->checkBox2);
			this->tagsGroupBox->Controls->Add(this->checkBox1);
			this->tagsGroupBox->Location = System::Drawing::Point(107, 476);
			this->tagsGroupBox->Name = L"tagsGroupBox";
			this->tagsGroupBox->Size = System::Drawing::Size(488, 101);
			this->tagsGroupBox->TabIndex = 8;
			this->tagsGroupBox->TabStop = false;
			this->tagsGroupBox->Enter += gcnew System::EventHandler(this, &Form1::tagsGroupBox_Enter);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 699);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(34, 16);
			this->label1->TabIndex = 1;
			this->label1->Text = L"URL";
			this->label1->Click += gcnew System::EventHandler(this, &Form1::Website_Click);
			// 
			// uTextBox
			// 
			this->uTextBox->Location = System::Drawing::Point(122, 699);
			this->uTextBox->Name = L"uTextBox";
			this->uTextBox->Size = System::Drawing::Size(274, 22);
			this->uTextBox->TabIndex = 4;
			this->uTextBox->TextChanged += gcnew System::EventHandler(this, &Form1::textBox1_TextChanged_1);
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(413, 699);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(75, 23);
			this->button6->TabIndex = 5;
			this->button6->Text = L"Save";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &Form1::button6_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->ClientSize = System::Drawing::Size(647, 755);
			this->Controls->Add(this->tagsGroupBox);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->fdTextBox);
			this->Controls->Add(this->sdTextBox);
			this->Controls->Add(this->uTextBox);
			this->Controls->Add(this->wTextBox);
			this->Controls->Add(this->eTextBox);
			this->Controls->Add(this->crTextBox);
			this->Controls->Add(this->ppTextBox);
			this->Controls->Add(this->nTextBox);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->Category);
			this->Controls->Add(this->Website);
			this->Controls->Add(this->Email);
			this->Controls->Add(this->Tags);
			this->Controls->Add(this->Full_disc);
			this->Controls->Add(this->Short_desc);
			this->Controls->Add(this->Content_ratings);
			this->Controls->Add(this->Privacy_policy);
			this->Controls->Add(this->name);
			this->Controls->Add(this->catGroupBox);
			this->Controls->Add(this->languageGroupBox);
			this->Name = L"Form1";
			this->Text = L"New Google Play Game";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->languageGroupBox->ResumeLayout(false);
			this->languageGroupBox->PerformLayout();
			this->catGroupBox->ResumeLayout(false);
			this->catGroupBox->PerformLayout();
			this->tagsGroupBox->ResumeLayout(false);
			this->tagsGroupBox->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void radioButton1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void Form1_Load(System::Object^ sender, System::EventArgs^ e) {
		try {
			// vector to store the data
			std::vector <std::string> lines;
			get_lines(lines);
			if (lines.size() >= 5)
			{
				string pp, cr, e, w, u;
				pp = lines[0];
				cr = lines[1];
				e = lines[2];
				w = lines[3];
				u = lines[4];
				// add the value to the text box 
				this->ppTextBox->Text = gcnew String(pp.c_str());
				this->crTextBox->Text = gcnew String(cr.c_str());
				this->eTextBox->Text = gcnew String(e.c_str());
				this->wTextBox->Text = gcnew String(w.c_str());
				this->uTextBox->Text = gcnew String(u.c_str());
			}
			else {
				MessageBox::Show("Error loading saved data: File is empty");
				write_saved_data();
			}
		}
		catch (Exception^ e) {
			MessageBox::Show("Error loading saved data: " + e->Message);
			write_saved_data();
		}
		catch (std::exception& e) {
			MessageBox::Show("Error loading saveData file: file damaged");
			write_saved_data();
		}

}
private: System::Void textBox1_TextChanged_1(System::Object^ sender, System::EventArgs^ e) {

}
private: System::Void backgroundWorker1_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {
}
private: System::Void radioButton4_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void Full_disc_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void Category_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void Tags_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void Website_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void Email_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void groupBox1_Enter(System::Object^ sender, System::EventArgs^ e) {
 }
private: System::Void checkBox1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	check_max_tags();
}
private: System::Void checkBox2_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	check_max_tags();

}
private: System::Void checkBox3_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	check_max_tags();

}
private: System::Void checkBox4_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	check_max_tags();

}
private: System::Void checkBox5_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	check_max_tags();

}
private: System::Void checkBox6_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	check_max_tags();

}
private: System::Void checkBox7_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	check_max_tags();
}
private: System::Void checkBox8_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	check_max_tags();
}
private: System::Void checkBox9_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	check_max_tags();
}
private: System::Void checkBox10_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	check_max_tags();
}
private: System::Void checkBox11_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	check_max_tags();
}
private: System::Void checkBox12_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	check_max_tags();
}
private: System::Void tagsGroupBox_Enter(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	try {
		string cr = msclr::interop::marshal_as<std::string>(this->crTextBox->Text->ToString());
		update_saved_data(cr, 1);
	}
	catch (Exception^ e) {
		MessageBox::Show("Error saving data: " + e->Message);
	}
}
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	try {
		
		string pp = msclr::interop::marshal_as<std::string>(this->ppTextBox->Text->ToString());
		update_saved_data(pp, 0);
	}
	catch (Exception^ e) {
		MessageBox::Show("Error saving data: " + e->Message);
	}
}
private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
	try {
		
		string e = msclr::interop::marshal_as<std::string>(this->eTextBox->Text->ToString());
		update_saved_data(e, 2);
	}
	catch (Exception^ e) {
		MessageBox::Show("Error saving data: " + e->Message);
	}
}
private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) {
	try {
		string w = msclr::interop::marshal_as<std::string>(this->wTextBox->Text->ToString());
		update_saved_data(w, 3);
	}
	catch (Exception^ e) {
		MessageBox::Show("Error saving data: " + e->Message);
	}
}
private: System::Void button6_Click(System::Object^ sender, System::EventArgs^ e) {
	try {
		string u = msclr::interop::marshal_as<std::string>(this->uTextBox->Text->ToString());
		update_saved_data(u, 4);
	}
	catch (Exception^ e) {
		MessageBox::Show("Error saving data: " + e->Message);
	}
}
private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
	try {
		
		write_input_data(get_input_data());		
		Process::Start(SEND_DATA_SCRIPT_DIR);

	}
	catch (Exception^ e) {
		MessageBox::Show("Error saving data: " + e->Message);
	}
}
private: 
	// return string of the selected language en, ar, or fr
	wstring get_selected_lan() {
		if (this->radioButton1->Checked)
		{
			return L"Arabic";
		}
		else if (this->radioButton2->Checked)
		{
			return L"English (United States) – en-US";
		}
		else if (this->radioButton3->Checked)
		{
			return L"French (France) – fr-FR";
		}
		else
		{
			return L"English (United States) – en-US";
		}
	}
private:
	// return string of the selected category
	wstring get_selected_cat() {
		if (this->radioButton4->Checked)
		{
			return L"Arcade";
		}
		else if (this->radioButton5->Checked)
		{
			return L"Casual";
		}
		else if (this->radioButton6->Checked)
		{
			return L"Role Playing";
		}
		else if (this->radioButton7->Checked)
		{
			return L"Simulation";
		}
	}
private:
	// return string of the selected tags
	wstring get_selected_tags() {
		wstring tags = L"";
		if (this->checkBox1->Checked)
		{
			tags += L"Arcade,";
		}
		if (this->checkBox2->Checked)
		{
			tags += L"Casual,";
		}
		if (this->checkBox3->Checked)
		{
			tags += L"Nail salon,";
		}
		if (this->checkBox4->Checked)
		{
			tags += L"Hair salon,";
		}
		if (this->checkBox5->Checked)
		{
			tags += L"Dress-up,";
		}
		if (this->checkBox6->Checked)
		{
			tags += L"Make up,";
		}
		if (this->checkBox7->Checked)
		{
			tags += L"Life simulation,";
		}
		if (this->checkBox8->Checked)
		{
			tags += L"Lifestyle simulation,";
		}
		if (this->checkBox9->Checked)
		{
			tags += L"Simulation,";
		}
		if (this->checkBox10->Checked)
		{
			tags += L"Design,";
		}
		if (this->checkBox11->Checked)
		{
			tags += L"Care simulation,";
		}
		if (this->checkBox12->Checked)
		{
			tags += L"Social simulation,";
		}
		return tags;
	}
private:
	void check_max_tags() {
		// Get the GroupBox control
		GroupBox^ groupBox1 = dynamic_cast<GroupBox^>(this->Controls->Find("tagsGroupBox", true)[0]);

		int checkedCount = 0;

		// Iterate over all the controls inside the GroupBox
		for each (Control ^ control in groupBox1->Controls)
		{
			// Check if the control is a CheckBox
			if (dynamic_cast<CheckBox^>(control))
			{
				// Cast the control to a CheckBox object
				CheckBox^ checkBox = dynamic_cast<CheckBox^>(control);

				// Check if the CheckBox is checked
				if (checkBox->Checked)
				{
					checkedCount++;
				}
				else
				{
					// Disable the CheckBox if it is unchecked
					checkBox->Enabled = false;
				}
			}
		}

		// Re-enable all the CheckBoxes if there are less than 5 checked
		if (checkedCount < 5)
		{
			for each (Control ^ control in groupBox1->Controls)
			{
				// Check if the control is a CheckBox
				if (dynamic_cast<CheckBox^>(control))
				{
					// Cast the control to a CheckBox object
					CheckBox^ checkBox = dynamic_cast<CheckBox^>(control);

					// Enable the CheckBox if it is disabled and unchecked
					if (!checkBox->Enabled && !checkBox->Checked)
					{
						checkBox->Enabled = true;
					}
				}
			}
		}

	}
private:
	// get input data from the form and return it as a vector of strings
	vector<wstring> get_input_data() {
		vector<wstring> vec;
		auto tmp = msclr::interop::marshal_as<std::wstring>(this->nTextBox->Text);
		vec.push_back(tmp);
		vec.push_back(get_selected_lan());
		vec.push_back(msclr::interop::marshal_as<std::wstring>(this->ppTextBox->Text->ToString()));
		vec.push_back(msclr::interop::marshal_as<std::wstring>(this->crTextBox->Text->ToString()));
		vec.push_back(msclr::interop::marshal_as<std::wstring>(this->sdTextBox->Text->ToString()));
		vec.push_back(msclr::interop::marshal_as<std::wstring>(this->fdTextBox->Text->ToString()));
		vec.push_back(get_selected_cat());
		vec.push_back(get_selected_tags());
		vec.push_back(msclr::interop::marshal_as<std::wstring>(this->eTextBox->Text->ToString()));
		vec.push_back(msclr::interop::marshal_as<std::wstring>(this->wTextBox->Text->ToString()));
		vec.push_back(msclr::interop::marshal_as<std::wstring>(this->uTextBox->Text->ToString()));
		return vec;
	}
};
}
