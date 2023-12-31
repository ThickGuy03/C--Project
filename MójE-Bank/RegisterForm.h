 #pragma once
#include "User.h"

namespace MójEBank {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Data::SqlClient;

	/// <summary>
	/// Podsumowanie informacji o RegisterForm
	/// </summary>
	public ref class RegisterForm : public System::Windows::Forms::Form
	{
	public:
		RegisterForm(void)
		{
			InitializeComponent();
			
			this->CenterToScreen();
		}

	protected:
		/// <summary>
		/// Wyczyść wszystkie używane zasoby.
		/// </summary>
		~RegisterForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	protected:
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::TextBox^ tbName;
	private: System::Windows::Forms::TextBox^ tbSurname;
	private: System::Windows::Forms::TextBox^ tbAddress;
	private: System::Windows::Forms::TextBox^ tbEmail;
	private: System::Windows::Forms::TextBox^ tbPassword;





	private: System::Windows::Forms::TextBox^ tbPhone;

	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::TextBox^ tbConfirmPassword;

	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Button^ btnConfirm;
	private: System::Windows::Forms::Button^ btnCancel;
	private: System::Windows::Forms::LinkLabel^ linkLogin;


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
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->tbName = (gcnew System::Windows::Forms::TextBox());
			this->tbSurname = (gcnew System::Windows::Forms::TextBox());
			this->tbAddress = (gcnew System::Windows::Forms::TextBox());
			this->tbEmail = (gcnew System::Windows::Forms::TextBox());
			this->tbPassword = (gcnew System::Windows::Forms::TextBox());
			this->tbPhone = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->tbConfirmPassword = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->btnConfirm = (gcnew System::Windows::Forms::Button());
			this->btnCancel = (gcnew System::Windows::Forms::Button());
			this->linkLogin = (gcnew System::Windows::Forms::LinkLabel());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(1107, 86);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Rejestracja";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(91, 101);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(67, 32);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Imie";
			
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(57, 168);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(135, 32);
			this->label3->TabIndex = 2;
			this->label3->Text = L"Nazwisko";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(81, 309);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(88, 32);
			this->label4->TabIndex = 3;
			this->label4->Text = L"Adres";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(81, 382);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(86, 32);
			this->label5->TabIndex = 4;
			this->label5->Text = L"Email";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(81, 460);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(87, 32);
			this->label6->TabIndex = 5;
			this->label6->Text = L"Haslo";
			// 
			// tbName
			// 
			this->tbName->Location = System::Drawing::Point(256, 101);
			this->tbName->Name = L"tbName";
			this->tbName->Size = System::Drawing::Size(763, 38);
			this->tbName->TabIndex = 6;
			// 
			// tbSurname
			// 
			this->tbSurname->Location = System::Drawing::Point(256, 168);
			this->tbSurname->Name = L"tbSurname";
			this->tbSurname->Size = System::Drawing::Size(763, 38);
			this->tbSurname->TabIndex = 7;
			// 
			// tbAddress
			// 
			this->tbAddress->Location = System::Drawing::Point(256, 309);
			this->tbAddress->Name = L"tbAddress";
			this->tbAddress->Size = System::Drawing::Size(763, 38);
			this->tbAddress->TabIndex = 8;
			// 
			// tbEmail
			// 
			this->tbEmail->Location = System::Drawing::Point(256, 382);
			this->tbEmail->Name = L"tbEmail";
			this->tbEmail->Size = System::Drawing::Size(763, 38);
			this->tbEmail->TabIndex = 9;
			// 
			// tbPassword
			// 
			this->tbPassword->Location = System::Drawing::Point(256, 460);
			this->tbPassword->Name = L"tbPassword";
			this->tbPassword->PasswordChar = '*';
			this->tbPassword->Size = System::Drawing::Size(763, 38);
			this->tbPassword->TabIndex = 10;
			// 
			// tbPhone
			// 
			this->tbPhone->Location = System::Drawing::Point(256, 244);
			this->tbPhone->Name = L"tbPhone";
			this->tbPhone->Size = System::Drawing::Size(763, 38);
			this->tbPhone->TabIndex = 12;
			
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(70, 244);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(110, 32);
			this->label7->TabIndex = 11;
			this->label7->Text = L"Telefon";
			
			// 
			// tbConfirmPassword
			// 
			this->tbConfirmPassword->Location = System::Drawing::Point(256, 530);
			this->tbConfirmPassword->Name = L"tbConfirmPassword";
			this->tbConfirmPassword->PasswordChar = '*';
			this->tbConfirmPassword->Size = System::Drawing::Size(763, 38);
			this->tbConfirmPassword->TabIndex = 14;
			
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(17, 533);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(215, 32);
			this->label8->TabIndex = 13;
			this->label8->Text = L"Potwierdz haslo";
			
			// 
			// btnConfirm
			// 
			this->btnConfirm->Location = System::Drawing::Point(256, 597);
			this->btnConfirm->Name = L"btnConfirm";
			this->btnConfirm->Size = System::Drawing::Size(307, 62);
			this->btnConfirm->TabIndex = 15;
			this->btnConfirm->Text = L"Stwórz konto";
			this->btnConfirm->UseVisualStyleBackColor = true;
			this->btnConfirm->Click += gcnew System::EventHandler(this, &RegisterForm::btnConfirm_Click);
			// 
			// btnCancel
			// 
			this->btnCancel->Location = System::Drawing::Point(712, 597);
			this->btnCancel->Name = L"btnCancel";
			this->btnCancel->Size = System::Drawing::Size(307, 62);
			this->btnCancel->TabIndex = 16;
			this->btnCancel->Text = L"Cofnij";
			this->btnCancel->UseVisualStyleBackColor = true;
			this->btnCancel->Click += gcnew System::EventHandler(this, &RegisterForm::btnCancel_Click);
			// 
			// linkLogin
			// 
			this->linkLogin->AutoSize = true;
			this->linkLogin->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->linkLogin->Location = System::Drawing::Point(539, 662);
			this->linkLogin->Name = L"linkLogin";
			this->linkLogin->Size = System::Drawing::Size(182, 25);
			this->linkLogin->TabIndex = 17;
			this->linkLogin->TabStop = true;
			this->linkLogin->Text = L"Posiadam już konto";
			this->linkLogin->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &RegisterForm::linkLogin_LinkClicked);
			// 
			// RegisterForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(16, 31);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1056, 695);
			this->Controls->Add(this->linkLogin);
			this->Controls->Add(this->btnCancel);
			this->Controls->Add(this->btnConfirm);
			this->Controls->Add(this->tbConfirmPassword);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->tbPhone);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->tbPassword);
			this->Controls->Add(this->tbEmail);
			this->Controls->Add(this->tbAddress);
			this->Controls->Add(this->tbSurname);
			this->Controls->Add(this->tbName);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Margin = System::Windows::Forms::Padding(6);
			this->Name = L"RegisterForm";
			this->Text = L"Rejestracja";
			this->Load += gcnew System::EventHandler(this, &RegisterForm::RegisterForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void RegisterForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void btnCancel_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}

	public: User^ user = nullptr;

	private: System::Void btnConfirm_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ name = tbName->Text;
		String^ surname = tbSurname->Text;
		String^ phone = tbPhone->Text;
		String^ email = tbEmail->Text;
		String^ address = tbAddress->Text;
		String^ password = tbPassword->Text;
		String^ confirmPassword = tbConfirmPassword->Text;
		
		if (name->Length == 0 || surname->Length == 0 || email->Length == 0 || phone->Length == 0 || address->Length == 0 || password->Length == 0)
		{
			MessageBox::Show("Uzupelnij wszystkie pola", "Jedno lub wiecej pol jest pustych", MessageBoxButtons::OK);
			return;
		}

		if (String::Compare(password, confirmPassword) != 0)
		{
			MessageBox::Show("Hasla nie sa identyczne", "Bledne haslo", MessageBoxButtons::OK); 
			return;
		}

		try {
			String^ connString = "Data Source=LAPTOP-OP2NIRDL\\SQLEXPRESS;Initial Catalog=MójE-Bank;Integrated Security=True";
			SqlConnection sqlConn(connString);
			sqlConn.Open();

			String^ sqlQuery = "INSERT INTO Users " + "(name,surname,email,phone,address,password) VALUES " + "(@Name,@Surname,@email,@phone,@address,@password);"; 

			SqlCommand command(sqlQuery, % sqlConn);
			command.Parameters->AddWithValue("@Name", name);
			command.Parameters->AddWithValue("@Surname", surname);
			command.Parameters->AddWithValue("email", email);
			command.Parameters->AddWithValue("@phone", phone);
			command.Parameters->AddWithValue("@address", address);
			command.Parameters->AddWithValue("@password", password);

			command.ExecuteNonQuery();
			user = gcnew User;
			user->name = name;
			user->surname = surname;
			user->email = email;
			user->phone = phone;
			user->address = address;
			user->password = password;

			this->Close();
		}
		catch (Exception^ e)
		{
			MessageBox::Show("Rejestracja nieudana", "Rejestracja nieudana", MessageBoxButtons::OK);
		}
	}
	public: bool switchToLogin = false;

	private: System::Void linkLogin_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e) {
		this->switchToLogin = true;
		this->Close();
	}
	};
}
