#pragma once
#include "User.h"
#include "Credit.h"

namespace MójEBank {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Data::SqlClient;

	/// <summary>
	/// Podsumowanie informacji o MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		Credit^ credit = nullptr;

		MainForm(User^ user)
		{
			InitializeComponent();
			this->CenterToScreen();

			//lblUserInfo->Text = "ID: " + user->id + ", Imie: " + user->name + ", Nazwisko: " + user->surname + ", email: " + user->email;

			int ClientId = user->id;
			try {
				String^ connString = "Data Source=LAPTOP-OP2NIRDL\\SQLEXPRESS;Initial Catalog=MójE-Bank;Integrated Security=True";
				SqlConnection sqlConn(connString);
				sqlConn.Open();

				String^ sqlQuery = "SELECT * FROM Credits WHERE ClientId=@ownersId";
				SqlCommand command(sqlQuery, % sqlConn);
				command.Parameters->AddWithValue("@ownersID", ClientId);
			
				SqlDataReader^ reader = command.ExecuteReader();
				{
					if (reader->Read())
					{
						MessageBox::Show("Znaleziono wystapienie", "Znaleziono", MessageBoxButtons::OK);
						credit = gcnew Credit;
						credit->id = reader->GetInt32(0);
						credit->ownersId = reader->GetInt32(1);
						credit->source = reader->GetString(2);
						credit->borrowedMoney = reader->GetFloat(3);
						credit->interestRate = reader->GetFloat(4);
						credit->numOfMonths = reader->GetInt32(5);
						credit->monthsPaid = reader->GetInt32(6);
					}
					else {
						MessageBox::Show("Nie znaleziono pasujacego wystapienia", "Brak wynikow", MessageBoxButtons::OK);
					}
				}
			}
			catch (Exception^ e)
			{
				MessageBox::Show("Nie udalo sie polaczyc do bazy danych //Main", "Nieudane polaczenie", MessageBoxButtons::OK);
			}
			
		}

	protected:
		/// <summary>
		/// Wyczyść wszystkie używane zasoby.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ lblUserInfo;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Label^ lblCredit;
	private: System::Windows::Forms::Panel^ panel2;

	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label4;

	protected:


	private:
		/// <summary>
		/// Wymagana zmienna projektanta.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Metoda wymagana do obsługi projektanta — nie należy modyfikować
		/// jej zawartości w edytorze kodu.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->lblCredit = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->panel1->SuspendLayout();
			this->panel2->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(1344, 66);
			this->label1->TabIndex = 0;
			this->label1->Text = L" Witaj w MyE-Bank";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->label4);
			this->panel1->Controls->Add(this->lblCredit);
			this->panel1->Location = System::Drawing::Point(448, 89);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(851, 662);
			this->panel1->TabIndex = 2;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(44, 32);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(52, 16);
			this->label4->TabIndex = 6;
			this->label4->Text = L"Panel 1";
			// 
			// panel2
			// 
			this->panel2->Controls->Add(this->label2);
			this->panel2->Location = System::Drawing::Point(448, 89);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(851, 662);
			this->panel2->TabIndex = 0;
			this->panel2->Visible = false;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(55, 103);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(52, 16);
			this->label2->TabIndex = 0;
			this->label2->Text = L"Panel 2";
			// 
			// lblCredit
			// 
			this->lblCredit->AutoSize = true;
			this->lblCredit->Location = System::Drawing::Point(44, 63);
			this->lblCredit->Name = L"lblCredit";
			this->lblCredit->Size = System::Drawing::Size(72, 16);
			this->lblCredit->TabIndex = 5;
			this->lblCredit->Text = L"labelCredit";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(159, 216);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(149, 49);
			this->button1->TabIndex = 3;
			this->button1->Text = L"Panel 1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(159, 301);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(149, 47);
			this->button2->TabIndex = 4;
			this->button2->Text = L"Panel 2";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MainForm::button2_Click);
			// 
			// label3
			// 
			this->label3->Location = System::Drawing::Point(0, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(100, 23);
			this->label3->TabIndex = 0;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1386, 810);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->label1);
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		panel2->Visible = false;
		panel1->Visible = true;
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		panel1->Visible = false;
		panel2->Visible = true;
	}


};
}
