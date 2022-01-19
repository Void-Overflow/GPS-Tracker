#pragma once

#include "COM_Selector.h"

using namespace System::Threading;
using namespace System::Media;
using namespace System::Diagnostics;

namespace GPSTracker {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
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
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	protected:
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::PictureBox^ pictureBox3;
	private: System::Windows::Forms::WebBrowser^ webBrowser1;

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->webBrowser1 = (gcnew System::Windows::Forms::WebBrowser());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(1512, 27);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(77, 72);
			this->pictureBox1->TabIndex = 2;
			this->pictureBox1->TabStop = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(1494, 11);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(110, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Receiver Connection:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(1494, 124);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(119, 13);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Transmitter Connection:";
			// 
			// pictureBox2
			// 
			this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.Image")));
			this->pictureBox2->Location = System::Drawing::Point(1512, 140);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(77, 72);
			this->pictureBox2->TabIndex = 4;
			this->pictureBox2->TabStop = false;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(1494, 237);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(127, 13);
			this->label3->TabIndex = 7;
			this->label3->Text = L"GPS Module Connection:";
			// 
			// pictureBox3
			// 
			this->pictureBox3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox3.Image")));
			this->pictureBox3->Location = System::Drawing::Point(1512, 253);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(77, 72);
			this->pictureBox3->TabIndex = 6;
			this->pictureBox3->TabStop = false;
			// 
			// webBrowser1
			// 
			this->webBrowser1->Location = System::Drawing::Point(12, 11);
			this->webBrowser1->MinimumSize = System::Drawing::Size(20, 20);
			this->webBrowser1->Name = L"webBrowser1";
			this->webBrowser1->Size = System::Drawing::Size(1476, 810);
			this->webBrowser1->TabIndex = 8;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1616, 833);
			this->Controls->Add(this->webBrowser1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->pictureBox3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	Thread^ received_thread;
	Thread^ COM_check_thread;

	COM_Selector^ port;

	private: bool refresh_flag = false;
	private: bool first_refresh = false;

	private: void Navigate_URL(String^ address) {
		if (String::IsNullOrEmpty(address)) return;
		if (address->Equals("about:blank")) return;
		if (!address->StartsWith("http://") &&
			!address->StartsWith("https://")) {
			address = Convert::ToString("http://") + address;
		}
		try{
			webBrowser1->Navigate(gcnew Uri(address));
		}
		catch (System::UriFormatException^ e){
			Console::WriteLine(e);
			return;
		}
	}

	void timer_Elapsed(Object^ sender, System::Timers::ElapsedEventArgs^ e){
		Console::WriteLine("Timer elapsed");
		refresh_flag = true;
	}

	public: void read_input_thread(Object^ data) {

		while (received_thread->IsAlive) {
			if (port->connection_status == true) {
				String^ incomingString = port->readCOM(port->selected_port);

				if (String::Compare(incomingString, "world") != 0)
					Console::WriteLine("Data Received: " + incomingString);

				if (incomingString->Contains("world")) {
					pictureBox1->Image = Image::FromFile(Environment::CurrentDirectory + "\\Images\\green_led.png");
				}
				 else if (incomingString->Contains("COM_FAIL")) {
					pictureBox2->Image = Image::FromFile(Environment::CurrentDirectory + "\\Images\\red_led.png");
					pictureBox3->Image = Image::FromFile(Environment::CurrentDirectory + "\\Images\\red_led.png");
				}
				else if (incomingString->Contains("LatFail") || incomingString->Contains("LonFail")){
					pictureBox2->Image = Image::FromFile(Environment::CurrentDirectory + "\\Images\\green_led.png");
					pictureBox3->Image = Image::FromFile(Environment::CurrentDirectory + "\\Images\\red_led.png");
				}
				else if (port->connection_status == false) {
					pictureBox2->Image = Image::FromFile(Environment::CurrentDirectory + "\\Images\\red_led.png");
					pictureBox3->Image = Image::FromFile(Environment::CurrentDirectory + "\\Images\\red_led.png");
				}
				else {
					pictureBox2->Image = Image::FromFile(Environment::CurrentDirectory + "\\Images\\green_led.png");
					pictureBox3->Image = Image::FromFile(Environment::CurrentDirectory + "\\Images\\green_led.png");

					if (refresh_flag == true || first_refresh == false){
						if (first_refresh == false) {
							System::Timers::Timer^ timer = gcnew System::Timers::Timer();
							timer->Interval = 30000;
							timer->Elapsed += gcnew System::Timers::ElapsedEventHandler(this, &MyForm::timer_Elapsed);
							timer->Start();

							first_refresh = true;
						}

						Navigate_URL("https://www.google.com/maps/place/" + incomingString);
						refresh_flag = false;
					}
				}
			}
			else {
				pictureBox2->Image = Image::FromFile(Environment::CurrentDirectory + "\\Images\\red_led.png");
				pictureBox3->Image = Image::FromFile(Environment::CurrentDirectory + "\\Images\\red_led.png");
			}

			received_thread->Sleep(3000);
		}
	}


	public: void COM_check_method(Object^ data) {
		while (COM_check_thread->IsAlive) {
			port->checkConnection(COM_check_thread, pictureBox1);
		}
	}

	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {

		pictureBox1->BackColor = Color::Transparent;
		pictureBox1->SizeMode = PictureBoxSizeMode::StretchImage;
		pictureBox1->Image = Image::FromFile(Environment::CurrentDirectory + "\\Images\\red_led.png");

		pictureBox2->BackColor = Color::Transparent;
		pictureBox2->SizeMode = PictureBoxSizeMode::StretchImage;
		pictureBox2->Image = Image::FromFile(Environment::CurrentDirectory + "\\Images\\red_led.png");

		pictureBox3->BackColor = Color::Transparent;
		pictureBox3->SizeMode = PictureBoxSizeMode::StretchImage;
		pictureBox3->Image = Image::FromFile(Environment::CurrentDirectory + "\\Images\\red_led.png");
		
		webBrowser1->ScriptErrorsSuppressed = true;

		COM_check_thread = gcnew Thread(gcnew ParameterizedThreadStart(this, &MyForm::COM_check_method));
		try {
			if (!COM_check_thread->IsAlive) {
				COM_check_thread->IsBackground = true;
				COM_check_thread->Start();
			}
			else {
				COM_check_thread->IsBackground = true;
			}
		}
		catch (Exception^ ex) {
			Console::WriteLine(ex);
		}

		received_thread = gcnew Thread(gcnew ParameterizedThreadStart(this, &MyForm::read_input_thread));
		try {
			if (!received_thread->IsAlive) {
				received_thread->IsBackground = true;
				received_thread->Start();
			}
			else {
				received_thread->IsBackground = true;
			}
		}
		catch (Exception^ ex) {
			Console::WriteLine(ex);
		}
	}
	};
}
