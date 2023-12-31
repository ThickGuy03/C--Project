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
			panel1->Visible = true;

			lbClientData->Text = "ID: " + user->id + ", Imie: " + user->name + ", Nazwisko: " + user->surname + ", email: " + user->email;

			int ClientId = user->id;
			lbUserId->Text = ClientId.ToString();
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
	private: System::Windows::Forms::Panel^ panel3;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Panel^ panel4;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::TextBox^ txbSource;
	private: System::Windows::Forms::Button^ btnAddCredit;

	private: System::Windows::Forms::ComboBox^ cbDuration;

	private: System::Windows::Forms::TextBox^ txbInterestRate;

	private: System::Windows::Forms::TextBox^ txbAmount;
	private: System::Windows::Forms::Label^ lblAmount;
	private: System::Windows::Forms::Label^ lblSource;
	private: System::Windows::Forms::Label^ lblDuration;
	private: System::Windows::Forms::Label^ lblInterestRate;
	private: System::Windows::Forms::DataGridView^ dgExpenses;
	private: System::Windows::Forms::Button^ btnP2Add;
	private: System::Windows::Forms::TextBox^ txbP2Frequency;
	private: System::Windows::Forms::TextBox^ txbP2Amount;
	private: System::Windows::Forms::TextBox^ txbP2Source;
	private: System::Windows::Forms::Button^ btnP2Delete;















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
			this->lblDuration = (gcnew System::Windows::Forms::Label());
			this->lblInterestRate = (gcnew System::Windows::Forms::Label());
			this->lblAmount = (gcnew System::Windows::Forms::Label());
			this->lblSource = (gcnew System::Windows::Forms::Label());
			this->btnAddCredit = (gcnew System::Windows::Forms::Button());
			this->cbDuration = (gcnew System::Windows::Forms::ComboBox());
			this->txbInterestRate = (gcnew System::Windows::Forms::TextBox());
			this->txbAmount = (gcnew System::Windows::Forms::TextBox());
			this->txbSource = (gcnew System::Windows::Forms::TextBox());
			this->dgCredits = (gcnew System::Windows::Forms::DataGridView());
			this->lbClientData = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->lbUserId = (gcnew System::Windows::Forms::Label());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->btnP2Delete = (gcnew System::Windows::Forms::Button());
			this->btnP2Add = (gcnew System::Windows::Forms::Button());
			this->txbP2Frequency = (gcnew System::Windows::Forms::TextBox());
			this->txbP2Amount = (gcnew System::Windows::Forms::TextBox());
			this->txbP2Source = (gcnew System::Windows::Forms::TextBox());
			this->dgExpenses = (gcnew System::Windows::Forms::DataGridView());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgCredits))->BeginInit();
			this->panel4->SuspendLayout();
			this->panel3->SuspendLayout();
			this->panel2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgExpenses))->BeginInit();
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
			this->panel1->Controls->Add(this->lblDuration);
			this->panel1->Controls->Add(this->lblInterestRate);
			this->panel1->Controls->Add(this->lblAmount);
			this->panel1->Controls->Add(this->lblSource);
			this->panel1->Controls->Add(this->btnAddCredit);
			this->panel1->Controls->Add(this->cbDuration);
			this->panel1->Controls->Add(this->txbInterestRate);
			this->panel1->Controls->Add(this->txbAmount);
			this->panel1->Controls->Add(this->txbSource);
			this->panel1->Controls->Add(this->dgCredits);
			this->panel1->Controls->Add(this->lbClientData);
			this->panel1->Controls->Add(this->label4);
			this->panel1->Controls->Add(this->lbUserId);
			this->panel1->Location = System::Drawing::Point(208, 106);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(1135, 720);
			this->panel1->TabIndex = 0;
			// 
			// lblDuration
			// 
			this->lblDuration->AutoSize = true;
			this->lblDuration->Location = System::Drawing::Point(684, 586);
			this->lblDuration->Name = L"lblDuration";
			this->lblDuration->Size = System::Drawing::Size(96, 16);
			this->lblDuration->TabIndex = 18;
			this->lblDuration->Text = L"Długość (msc)";
			// 
			// lblInterestRate
			// 
			this->lblInterestRate->AutoSize = true;
			this->lblInterestRate->Location = System::Drawing::Point(484, 586);
			this->lblInterestRate->Name = L"lblInterestRate";
			this->lblInterestRate->Size = System::Drawing::Size(105, 16);
			this->lblInterestRate->TabIndex = 17;
			this->lblInterestRate->Text = L"Oprocentowanie";
			// 
			// lblAmount
			// 
			this->lblAmount->AutoSize = true;
			this->lblAmount->Location = System::Drawing::Point(277, 586);
			this->lblAmount->Name = L"lblAmount";
			this->lblAmount->Size = System::Drawing::Size(104, 16);
			this->lblAmount->TabIndex = 16;
			this->lblAmount->Text = L"Pożyczona ilość";
			// 
			// lblSource
			// 
			this->lblSource->AutoSize = true;
			this->lblSource->Location = System::Drawing::Point(100, 587);
			this->lblSource->Name = L"lblSource";
			this->lblSource->Size = System::Drawing::Size(49, 16);
			this->lblSource->TabIndex = 15;
			this->lblSource->Text = L"Źródło";
			// 
			// btnAddCredit
			// 
			this->btnAddCredit->Location = System::Drawing::Point(356, 661);
			this->btnAddCredit->Name = L"btnAddCredit";
			this->btnAddCredit->Size = System::Drawing::Size(152, 34);
			this->btnAddCredit->TabIndex = 14;
			this->btnAddCredit->Text = L"Dodaj";
			this->btnAddCredit->UseVisualStyleBackColor = true;
			this->btnAddCredit->Click += gcnew System::EventHandler(this, &MainForm::btnAddCredit_Click_1);
			// 
			// cbDuration
			// 
			this->cbDuration->FormattingEnabled = true;
			this->cbDuration->Items->AddRange(gcnew cli::array< System::Object^  >(5) { L"12", L"24", L"36", L"48", L"60" });
			this->cbDuration->Location = System::Drawing::Point(671, 605);
			this->cbDuration->Name = L"cbDuration";
			this->cbDuration->Size = System::Drawing::Size(121, 24);
			this->cbDuration->TabIndex = 13;
			// 
			// txbInterestRate
			// 
			this->txbInterestRate->Location = System::Drawing::Point(464, 605);
			this->txbInterestRate->Name = L"txbInterestRate";
			this->txbInterestRate->Size = System::Drawing::Size(141, 22);
			this->txbInterestRate->TabIndex = 12;
			// 
			// txbAmount
			// 
			this->txbAmount->Location = System::Drawing::Point(262, 605);
			this->txbAmount->Name = L"txbAmount";
			this->txbAmount->Size = System::Drawing::Size(132, 22);
			this->txbAmount->TabIndex = 11;
			// 
			// txbSource
			// 
			this->txbSource->Location = System::Drawing::Point(47, 606);
			this->txbSource->Name = L"txbSource";
			this->txbSource->Size = System::Drawing::Size(155, 22);
			this->txbSource->TabIndex = 10;
			// 
			// dgCredits
			// 
			this->dgCredits->AllowUserToDeleteRows = false;
			this->dgCredits->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->dgCredits->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->dgCredits->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCells;
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
			// panel4
			// 
			this->panel4->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel4->Controls->Add(this->label6);
			this->panel4->Location = System::Drawing::Point(1083, 58);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(1135, 720);
			this->panel4->TabIndex = 3;
			this->panel4->Visible = false;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(55, 103);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(52, 16);
			this->label6->TabIndex = 0;
			this->label6->Text = L"Panel 4";
			// 
			// panel3
			// 
			this->panel3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel3->Controls->Add(this->label5);
			this->panel3->Location = System::Drawing::Point(1129, 36);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(1135, 720);
			this->panel3->TabIndex = 2;
			this->panel3->Visible = false;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(55, 103);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(52, 16);
			this->label5->TabIndex = 0;
			this->label5->Text = L"Panel 3";
			// 
			// panel2
			// 
			this->panel2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->panel2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel2->Controls->Add(this->btnP2Delete);
			this->panel2->Controls->Add(this->btnP2Add);
			this->panel2->Controls->Add(this->txbP2Frequency);
			this->panel2->Controls->Add(this->txbP2Amount);
			this->panel2->Controls->Add(this->txbP2Source);
			this->panel2->Controls->Add(this->dgExpenses);
			this->panel2->Controls->Add(this->label2);
			this->panel2->Location = System::Drawing::Point(239, 78);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(1135, 720);
			this->panel2->TabIndex = 1;
			this->panel2->Visible = false;
			// 
			// btnP2Delete
			// 
			this->btnP2Delete->Location = System::Drawing::Point(594, 225);
			this->btnP2Delete->Name = L"btnP2Delete";
			this->btnP2Delete->Size = System::Drawing::Size(123, 65);
			this->btnP2Delete->TabIndex = 6;
			this->btnP2Delete->Text = L"Usuń";
			this->btnP2Delete->UseVisualStyleBackColor = true;
			this->btnP2Delete->Click += gcnew System::EventHandler(this, &MainForm::btnP2Delete_Click);
			// 
			// btnP2Add
			// 
			this->btnP2Add->Location = System::Drawing::Point(215, 544);
			this->btnP2Add->Name = L"btnP2Add";
			this->btnP2Add->Size = System::Drawing::Size(124, 42);
			this->btnP2Add->TabIndex = 5;
			this->btnP2Add->Text = L"Dodaj";
			this->btnP2Add->UseVisualStyleBackColor = true;
			this->btnP2Add->Click += gcnew System::EventHandler(this, &MainForm::btnP2Add_Click);
			// 
			// txbP2Frequency
			// 
			this->txbP2Frequency->Location = System::Drawing::Point(392, 507);
			this->txbP2Frequency->Name = L"txbP2Frequency";
			this->txbP2Frequency->Size = System::Drawing::Size(100, 22);
			this->txbP2Frequency->TabIndex = 4;
			// 
			// txbP2Amount
			// 
			this->txbP2Amount->Location = System::Drawing::Point(225, 507);
			this->txbP2Amount->Name = L"txbP2Amount";
			this->txbP2Amount->Size = System::Drawing::Size(100, 22);
			this->txbP2Amount->TabIndex = 3;
			// 
			// txbP2Source
			// 
			this->txbP2Source->Location = System::Drawing::Point(59, 507);
			this->txbP2Source->Name = L"txbP2Source";
			this->txbP2Source->Size = System::Drawing::Size(100, 22);
			this->txbP2Source->TabIndex = 2;
			// 
			// dgExpenses
			// 
			this->dgExpenses->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->dgExpenses->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->dgExpenses->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCells;
			this->dgExpenses->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgExpenses->Location = System::Drawing::Point(58, 143);
			this->dgExpenses->Name = L"dgExpenses";
			this->dgExpenses->RowHeadersWidth = 51;
			this->dgExpenses->RowTemplate->Height = 24;
			this->dgExpenses->Size = System::Drawing::Size(434, 301);
			this->dgExpenses->TabIndex = 1;
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
			this->button1->Location = System::Drawing::Point(36, 78);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(149, 49);
			this->button1->TabIndex = 3;
			this->button1->Text = L"Panel 1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(36, 163);
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
			this->button3->Location = System::Drawing::Point(36, 242);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(149, 47);
			this->button3->TabIndex = 5;
			this->button3->Text = L"Panel 3";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MainForm::button3_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(36, 322);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(149, 47);
			this->button4->TabIndex = 6;
			this->button4->Text = L"Panel 4";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MainForm::button4_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1386, 810);
			this->Controls->Add(this->panel3);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->panel4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->panel2);
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgCredits))->EndInit();
			this->panel4->ResumeLayout(false);
			this->panel4->PerformLayout();
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgExpenses))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		panel1->Visible = true;
		panel2->Visible = false;
		panel3->Visible = false;
		panel4->Visible = false;
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		panel1->Visible = false;
		panel2->Visible = true;
		panel3->Visible = false;
		panel4->Visible = false;

		try {
			int ClientId;
			if (int::TryParse(lbUserId->Text, ClientId)) {

				String^ connString = "Data Source=LAPTOP-OP2NIRDL\\SQLEXPRESS;Initial Catalog=MójE-Bank;Integrated Security=True";
				SqlConnection sqlConn(connString);
				sqlConn.Open();

				String^ sqlQuery = "SELECT Source,Amount,Frequency FROM Expenses WHERE ownersId=@ClientId";
				SqlCommand^ command = gcnew SqlCommand(sqlQuery, % sqlConn);
				command->Parameters->AddWithValue("@ClientId", ClientId);

				SqlDataAdapter^ dataAdapter = gcnew SqlDataAdapter(command);
				DataTable^ dataTable = gcnew DataTable();

				dataAdapter->Fill(dataTable);
				dgExpenses->DataSource = dataTable;
				dgExpenses->Refresh();
				dgExpenses->ReadOnly = true;

				if (sqlConn.State == ConnectionState::Open)
				{
					sqlConn.Close();
				}
			}
			else {
				MessageBox::Show("Bledny format klienta ID", "Blad", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}
		}
		catch (Exception^ e)
		{
			MessageBox::Show("Nie udalo sie polaczyc z baza danych. Szczegoly bledu: " + e->Message, "Blad polaczenia", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		panel1->Visible = false;
		panel2->Visible = false;
		panel3->Visible = true;
		panel4->Visible = false;
	}
	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
		panel1->Visible = false;
		panel2->Visible = false;
		panel3->Visible = false;
		panel4->Visible = true;
	}

private: System::Void btnAddCredit_Click_1(System::Object^ sender, System::EventArgs^ e) {
	
	try {
		int clientId;
		if (int::TryParse(lbUserId->Text, clientId)) {

		}
		else {
			MessageBox::Show("Bledny format klienta ID", "Blad", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}
		String^ source = txbSource->Text;
		Decimal borrowedMoney;
		if(Decimal::TryParse(txbAmount->Text,borrowedMoney)){

		}
		else {
			MessageBox::Show("Bledny format borrowed money", "Blad", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}
		Decimal interestRate;
		if (Decimal::TryParse(txbInterestRate->Text, interestRate)) {

		}
		else {
			MessageBox::Show("Bledny format interestRate", "Blad", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}
		int duration = Convert::ToInt32(cbDuration->SelectedItem->ToString());

		if (cbDuration != __nullptr)
		{
			String^ connString = "Data Source=LAPTOP-OP2NIRDL\\SQLEXPRESS;Initial Catalog=MójE-Bank;Integrated Security=True";
			SqlConnection sqlConn(connString);
			sqlConn.Open();

			String^ sqlQuery = "INSERT INTO Credits (OwnersId,Source,BorrowedMoney,InterestRate,NumOfMonths) VALUES (@ClientId,@Source,@BorrowedMoney,@InterestRate,@NumofMonths);";

			SqlCommand command(sqlQuery, % sqlConn);

			command.Parameters->AddWithValue("@ClientId", clientId);
			command.Parameters->AddWithValue("@Source", source);
			command.Parameters->AddWithValue("@BorrowedMoney", borrowedMoney);
			command.Parameters->AddWithValue("@InterestRate", interestRate);
			command.Parameters->AddWithValue("@NumOfMonths", duration);
			command.ExecuteNonQuery();

			String^ sqlQueryRefresh = "SELECT Source,BorrowedMoney,InterestRate,NumOfMonths,MonthsPaid FROM Credits WHERE ownersId=@ClientId";
			SqlCommand^ commandRefresh = gcnew SqlCommand(sqlQueryRefresh, % sqlConn);
			commandRefresh->Parameters->AddWithValue("@ClientId", clientId);
			SqlDataAdapter^ dataAdapterRefresh = gcnew SqlDataAdapter(commandRefresh);
			DataTable^ dataTableRefresh = gcnew DataTable();
			dataAdapterRefresh->Fill(dataTableRefresh);
			dgCredits->DataSource = dataTableRefresh;

			txbSource->Text = "";
			txbAmount->Text = "";
			txbInterestRate->Text = "";
			cbDuration->SelectedIndex = -1;

			if (sqlConn.State == ConnectionState::Open)
			{
				sqlConn.Close();
			}
		}
		else
		{
			MessageBox::Show("Nie wybrano dlugosci kredytu! ", "Bledne dane", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
	catch (Exception^ ex)
	{
		MessageBox::Show("Nie udalo sie polaczyc z baza danych. Szczegoly bledu: " + ex->Message, "Blad polaczenia", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}
private: System::Void btnP2Add_Click(System::Object^ sender, System::EventArgs^ e) {

	try {
		int clientId;
		if (int::TryParse(lbUserId->Text, clientId)) {

		}
		else {
			MessageBox::Show("Bledny format klienta ID", "Blad", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}
		String^ source = txbP2Source->Text;
		Decimal expensesAmount;
		if (Decimal::TryParse(txbP2Amount->Text,expensesAmount)) {

		}
		else {
			MessageBox::Show("Bledny format borrowed money", "Blad", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}
		int frequency;
		if (int::TryParse(txbP2Frequency->Text, frequency)) {

		}
		else {
			MessageBox::Show("Bledny format interestRate", "Blad", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}
		
			String^ connString = "Data Source=LAPTOP-OP2NIRDL\\SQLEXPRESS;Initial Catalog=MójE-Bank;Integrated Security=True";
			SqlConnection sqlConn(connString);
			sqlConn.Open();

			String^ sqlQuery = "INSERT INTO Expenses(OwnersId,Source,Amount,Frequency) VALUES (@ClientId,@Source,@Amount,@Frequency);";

			SqlCommand command(sqlQuery, % sqlConn);

			command.Parameters->AddWithValue("@ClientId", clientId);
			command.Parameters->AddWithValue("@Source", source);
			command.Parameters->AddWithValue("@Amount", expensesAmount);
			command.Parameters->AddWithValue("@Frequency", frequency);
			command.ExecuteNonQuery();

			String^ sqlQueryRefresh = "SELECT Source,Amount,Frequency FROM Expenses WHERE ownersId=@ClientId";
			SqlCommand^ commandRefresh = gcnew SqlCommand(sqlQueryRefresh, % sqlConn);
			commandRefresh->Parameters->AddWithValue("@ClientId", clientId);
			SqlDataAdapter^ dataAdapterRefresh = gcnew SqlDataAdapter(commandRefresh);
			DataTable^ dataTableRefresh = gcnew DataTable();
			dataAdapterRefresh->Fill(dataTableRefresh);
			dgExpenses->DataSource = dataTableRefresh;

			txbP2Source->Text = "";
			txbP2Amount->Text = "";
			txbP2Frequency->Text = "";

			if (sqlConn.State == ConnectionState::Open)
			{
				sqlConn.Close();
			}
	}
	catch (Exception^ ex)
	{
		MessageBox::Show("Nie udalo sie polaczyc z baza danych. Szczegoly bledu: " + ex->Message, "Blad polaczenia", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}

}
private: System::Void btnP2Delete_Click(System::Object^ sender, System::EventArgs^ e) {
	
	/*//TO-DO\\*/

}
};
}
