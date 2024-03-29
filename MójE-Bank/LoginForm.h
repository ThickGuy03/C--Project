#pragma once
#include "User.h"

namespace MójEBank {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;\
		using namespace System::Data::SqlClient;

	/// <summary>
	/// Podsumowanie informacji o LoginForm
	/// </summary>
	public ref class LoginForm : public System::Windows::Forms::Form
	{
	public:
		LoginForm(void)
		{
			InitializeComponent();
			
			this->CenterToScreen();
		}

	protected:
		/// <summary>
		/// Wyczyść wszystkie używane zasoby.
		/// </summary>
		~LoginForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ tbEmail;
	private: System::Windows::Forms::TextBox^ tbPassword;
	private: System::Windows::Forms::Button^ btnOK;
	private: System::Windows::Forms::Button^ btnCancel;
	private: System::Windows::Forms::LinkLabel^ llRegister;



	protected:

	private:
		/// <summary>
		/// Wymagana zmienna projektanta.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Metoda wymagana do obsługi projektanta — nie należy modyfikować
		/// jej zawartości w edytorze kodu.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->tbEmail = (gcnew System::Windows::Forms::TextBox());
			this->tbPassword = (gcnew System::Windows::Forms::TextBox());
			this->btnOK = (gcnew System::Windows::Forms::Button());
			this->btnCancel = (gcnew System::Windows::Forms::Button());
			this->llRegister = (gcnew System::Windows::Forms::LinkLabel());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label1->Font = (gcnew System::Drawing::Font(L"Modern No. 20", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(783, 48);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Login";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(69, 107);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(60, 25);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Email";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(51, 170);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(98, 25);
			this->label3->TabIndex = 2;
			this->label3->Text = L"Password";
			// 
			// tbEmail
			// 
			this->tbEmail->Location = System::Drawing::Point(176, 107);
			this->tbEmail->Name = L"tbEmail";
			this->tbEmail->Size = System::Drawing::Size(583, 22);
			this->tbEmail->TabIndex = 3;
			this->tbEmail->Text = L"";

			// 
			// tbPassword
			// 
			this->tbPassword->Location = System::Drawing::Point(176, 172);
			this->tbPassword->Name = L"tbPassword";
			this->tbPassword->PasswordChar = '*';
			this->tbPassword->Size = System::Drawing::Size(583, 22);
			this->tbPassword->TabIndex = 4;
			this->tbPassword->Text = L"";
			// 
			// btnOK
			// 
			this->btnOK->Location = System::Drawing::Point(176, 259);
			this->btnOK->Name = L"btnOK";
			this->btnOK->Size = System::Drawing::Size(284, 47);
			this->btnOK->TabIndex = 5;
			this->btnOK->Text = L"OK";
			this->btnOK->UseVisualStyleBackColor = true;
			this->btnOK->Click += gcnew System::EventHandler(this, &LoginForm::btnOK_Click);
			// 
			// btnCancel
			// 
			this->btnCancel->Location = System::Drawing::Point(466, 259);
			this->btnCancel->Name = L"btnCancel";
			this->btnCancel->Size = System::Drawing::Size(293, 47);
			this->btnCancel->TabIndex = 6;
			this->btnCancel->Text = L"Cancel";
			this->btnCancel->UseVisualStyleBackColor = true;
			this->btnCancel->Click += gcnew System::EventHandler(this, &LoginForm::btnCancel_Click);
			// 
			// llRegister
			// 
			this->llRegister->AutoSize = true;
			this->llRegister->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->llRegister->Location = System::Drawing::Point(395, 327);
			this->llRegister->Name = L"llRegister";
			this->llRegister->Size = System::Drawing::Size(133, 25);
			this->llRegister->TabIndex = 7;
			this->llRegister->TabStop = true;
			this->llRegister->Text = L"Zarejestruj się";
			this->llRegister->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &LoginForm::llRegister_LinkClicked);
			// 
			// LoginForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::OldLace;
			this->ClientSize = System::Drawing::Size(807, 374);
			this->Controls->Add(this->llRegister);
			this->Controls->Add(this->btnCancel);
			this->Controls->Add(this->btnOK);
			this->Controls->Add(this->tbPassword);
			this->Controls->Add(this->tbEmail);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Name = L"LoginForm";
			this->Text = L"Login Form";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void btnCancel_Click(System::Object^ sender, System::EventArgs^ e) { 
		this->Close();
	}

	public:User^ user=nullptr;

	private: System::Void btnOK_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ email = this->tbEmail->Text;
		String^ password = this->tbPassword->Text;

		if (email->Length == 0 || password->Length == 0)
		{
			MessageBox::Show("Wprowadz email i haslo", "Bledny email lub haslo",MessageBoxButtons::OKCancel);
			return;
		}

		try {
			String^ connString = "Data Source=LAPTOP-OP2NIRDL\\SQLEXPRESS;Initial Catalog=MójE-Bank;Integrated Security=True";
			SqlConnection sqlConn(connString);
			sqlConn.Open();

			String^ sqlQuery = "SELECT * FROM Users WHERE email=@email AND password=@pwd;";
			SqlCommand command(sqlQuery, % sqlConn);
			command.Parameters->AddWithValue("@email", email);
			command.Parameters->AddWithValue("@pwd", password);

			SqlDataReader^ reader = command.ExecuteReader();
			{
				if (reader->Read())
				{
					user = gcnew User;
					user->id = reader->GetInt32(0);
					user->name = reader->GetString(1);
					user->surname = reader->GetString(2);
					user->email = reader->GetString(3);
					user->phone = reader->GetString(4);
					user->password = reader->GetString(5);
					this->Close();
				}
				else {
					MessageBox::Show("Email lub haslo jest niepoprawne", "Bledny email lub haslo", MessageBoxButtons::OK);
				}
			}
		}
		catch(Exception^ e){
			MessageBox::Show("Nie udalo sie polaczyc z baza danych //Login", "Nieudane polaczenie", MessageBoxButtons::RetryCancel);
		}

	}
	
	public: bool switchToRegister = false;
	private: System::Void llRegister_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e) {
		this->switchToRegister = true;
		this->Close();
	}

};
}
