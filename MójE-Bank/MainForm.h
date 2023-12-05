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

			lbClientData->Text = "ID: " + user->id + ", Imie: " + user->name + ", Nazwisko: " + user->surname + ", email: " + user->email;

			int ClientId = user->id;
			lbUserId->Text = "User Id: "+ClientId.ToString();
			try {
				String^ connString = "Data Source=LAPTOP-OP2NIRDL\\SQLEXPRESS;Initial Catalog=MójE-Bank;Integrated Security=True";
				SqlConnection sqlConn(connString);
				sqlConn.Open();

				String^ sqlQuery = "SELECT Source,BorrowedMoney,InterestRate,NumOfMonths,MonthsPaid FROM Credits WHERE ownersId=@ClientId";
				SqlCommand^ command=gcnew SqlCommand(sqlQuery, % sqlConn);
				command->Parameters->AddWithValue("@ClientId", ClientId);
				
				SqlDataAdapter^ dataAdapter = gcnew SqlDataAdapter(command);
				DataTable^ dataTable = gcnew DataTable();

				dataAdapter->Fill(dataTable);
				dgCredits->DataSource = dataTable;
				dgCredits->Refresh();
				dgCredits->ReadOnly = true;


				if (sqlConn.State == ConnectionState::Open)
				{
					sqlConn.Close();
				}
			}
			catch (Exception^ e)
			{
				MessageBox::Show("Nie udalo sie polaczyc z baza danych. Szczegoly bledu: " + e->Message, "Blad polaczenia", MessageBoxButtons::OK, MessageBoxIcon::Error);
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
	private: System::Windows::Forms::Label^ lbUserId;

	private: System::Windows::Forms::Panel^ panel2;

	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ lbClientData;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button4;

	private: System::Windows::Forms::DataGridView^ dgCredits;












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
			this->dgCredits = (gcnew System::Windows::Forms::DataGridView());
			this->lbClientData = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->lbUserId = (gcnew System::Windows::Forms::Label());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgCredits))->BeginInit();
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
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel1->Controls->Add(this->dgCredits);
			this->panel1->Controls->Add(this->lbClientData);
			this->panel1->Controls->Add(this->label4);
			this->panel1->Controls->Add(this->lbUserId);
			this->panel1->Location = System::Drawing::Point(239, 78);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(1135, 720);
			this->panel1->TabIndex = 2;
			// 
			// dgCredits
			// 
			this->dgCredits->AllowUserToDeleteRows = false;
			this->dgCredits->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::DisplayedCells;
			this->dgCredits->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgCredits->Location = System::Drawing::Point(23, 139);
			this->dgCredits->Name = L"dgCredits";
			this->dgCredits->RowHeadersWidth = 51;
			this->dgCredits->RowTemplate->Height = 24;
			this->dgCredits->Size = System::Drawing::Size(702, 319);
			this->dgCredits->TabIndex = 9;
			// 
			// lbClientData
			// 
			this->lbClientData->AutoSize = true;
			this->lbClientData->Location = System::Drawing::Point(47, 106);
			this->lbClientData->Name = L"lbClientData";
			this->lbClientData->Size = System::Drawing::Size(69, 16);
			this->lbClientData->TabIndex = 7;
			this->lbClientData->Text = L"ClientData";
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
			// lbUserId
			// 
			this->lbUserId->AutoSize = true;
			this->lbUserId->Location = System::Drawing::Point(44, 63);
			this->lbUserId->Name = L"lbUserId";
			this->lbUserId->Size = System::Drawing::Size(47, 16);
			this->lbUserId->TabIndex = 5;
			this->lbUserId->Text = L"UserId";
			// 
			// panel2
			// 
			this->panel2->Controls->Add(this->label2);
			this->panel2->Location = System::Drawing::Point(243, 74);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(1135, 720);
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
			// button1
			// 
			this->button1->Location = System::Drawing::Point(48, 257);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(149, 49);
			this->button1->TabIndex = 3;
			this->button1->Text = L"Panel 1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(48, 342);
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
			// button3
			// 
			this->button3->Location = System::Drawing::Point(48, 421);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(149, 47);
			this->button3->TabIndex = 5;
			this->button3->Text = L"Panel 2";
			this->button3->UseVisualStyleBackColor = true;
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(48, 501);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(149, 47);
			this->button4->TabIndex = 6;
			this->button4->Text = L"Panel 2";
			this->button4->UseVisualStyleBackColor = true;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1386, 810);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->label1);
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgCredits))->EndInit();
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
