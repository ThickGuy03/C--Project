#pragma once
#include "User.h"
#include "Credit.h"
#include <math.h>
#include <vector>

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
		int currentWeek = 1;
		int currentMonth = 1;
		int currentYear = 2024;
		int numOfTicks = 0;
		double currentBalance = 0.0f;
	private: System::Windows::Forms::Button^ btnDeleteP3;
	private: System::Windows::Forms::Label^ lblCreditMonth;
	private: System::Windows::Forms::TextBox^ txbBalance;
	private: System::Windows::Forms::TextBox^ txbCredits;

	public:
		Timer^ timer = gcnew Timer();

		MainForm(User^ user)
		{
			InitializeComponent();
			this->CenterToScreen();

			panel1->Visible = true;

			timer->Interval = 800;
			timer->Tick += gcnew EventHandler(this, &MainForm::CalculateOnTick);

			SimulationDate->Text = currentWeek + " tyg. " + currentMonth + " msc. " + currentYear;

			lbClientData->Text =  "Imie: " + user->name + ", Nazwisko: " + user->surname + ", email: " + user->email;

			int ClientId = user->id;
			lbUserId->Text = ClientId.ToString();

			try {
				String^ connString = "Data Source=LAPTOP-OP2NIRDL\\SQLEXPRESS;Initial Catalog=MójE-Bank;Integrated Security=True";
				SqlConnection sqlConn(connString);
				sqlConn.Open();

				//Credits
				String^ sqlQuery = "SELECT Id,Source,BorrowedMoney,InterestRate,NumOfMonths,MonthsPaid FROM Credits WHERE ownersId=@ClientId";
				SqlCommand^ command=gcnew SqlCommand(sqlQuery, % sqlConn);
				command->Parameters->AddWithValue("@ClientId", ClientId);
				
				SqlDataAdapter^ dataAdapter = gcnew SqlDataAdapter(command);
				DataTable^ dataTable = gcnew DataTable();

				dataAdapter->Fill(dataTable);
				dgCredits->DataSource = dataTable;
				dgCredits->Refresh();
				dgCredits->ReadOnly = true;
				dgCredits->Columns["Id"]->Visible = false;

				//Income
				String^ sqlQueryIncome = "SELECT Id,Source,Amount,Frequency FROM Income WHERE ownersId=@ClientId";
				SqlCommand^ commandIncome = gcnew SqlCommand(sqlQueryIncome, % sqlConn);
				commandIncome->Parameters->AddWithValue("@ClientId", ClientId);

				SqlDataAdapter^ dataAdapterIncome = gcnew SqlDataAdapter(commandIncome);
				DataTable^ dataTableIncome = gcnew DataTable();

				dataAdapterIncome->Fill(dataTableIncome);
				dgIncome->DataSource = dataTableIncome;
				dgIncome->Refresh();
				dgIncome->ReadOnly = true;
				dgIncome->Columns["Id"]->Visible = false;

				//Expenses
				String^ sqlQueryExpenses = "SELECT Id,OwnersId,Source,Amount,Frequency FROM Expenses WHERE ownersId=@ClientId";
				SqlCommand^ commandExpenses = gcnew SqlCommand(sqlQueryExpenses, % sqlConn);
				commandExpenses->Parameters->AddWithValue("@ClientId", ClientId);

				SqlDataAdapter^ dataAdapterExpenses = gcnew SqlDataAdapter(commandExpenses);
				DataTable^ dataTableExpenses = gcnew DataTable();

				dataAdapterExpenses->Fill(dataTableExpenses);
				dgExpenses->DataSource = dataTableExpenses;
				dgExpenses->Refresh();
				dgExpenses->ReadOnly = true;
				dgExpenses->Columns["Id"]->Visible = false;

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
	private: System::Windows::Forms::Button^ btnPanel3Add;
	private: System::Windows::Forms::Panel^ panel2;
	private: System::Windows::Forms::Label^ lblSourceP3;
	private: System::Windows::Forms::Label^ lblFrequencyP3;
	private: System::Windows::Forms::Label^ lblAmountP3;
	private: System::Windows::Forms::Label^ lblFrequencyP2;
	private: System::Windows::Forms::Label^ lblAmountP2;
	private: System::Windows::Forms::Label^ lblSourceP2;

	private: System::Windows::Forms::Label^ label3;


	private: System::Windows::Forms::Label^ lbClientData;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::DataGridView^ dgCredits;
	private: System::Windows::Forms::Panel^ panel3;

	private: System::Windows::Forms::Panel^ panel4;
private: System::Windows::Forms::Label^ lblBalance;


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
	private: System::Windows::Forms::DataGridView^ dgIncome;
	private: System::Windows::Forms::TextBox^ txbP3Amount;
	private: System::Windows::Forms::TextBox^ txbP3Source;
	private: System::Windows::Forms::TextBox^ txbP3Frequency;
	private: System::Windows::Forms::Button^ btnStart;
	private: System::Windows::Forms::Button^ btnStop;
	private: System::Windows::Forms::Label^ SimulationDate;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::ComponentModel::IContainer^ components;
	protected:
	private:
		/// <summary>
		/// Wymagana zmienna projektanta.
		/// </summary>
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Metoda wymagana do obsługi projektanta — nie należy modyfikować
		/// jej zawartości w edytorze kodu.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
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
			this->lbUserId = (gcnew System::Windows::Forms::Label());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->btnDeleteP3 = (gcnew System::Windows::Forms::Button());
			this->lblFrequencyP3 = (gcnew System::Windows::Forms::Label());
			this->lblAmountP3 = (gcnew System::Windows::Forms::Label());
			this->lblSourceP3 = (gcnew System::Windows::Forms::Label());
			this->btnPanel3Add = (gcnew System::Windows::Forms::Button());
			this->txbP3Frequency = (gcnew System::Windows::Forms::TextBox());
			this->txbP3Amount = (gcnew System::Windows::Forms::TextBox());
			this->txbP3Source = (gcnew System::Windows::Forms::TextBox());
			this->dgIncome = (gcnew System::Windows::Forms::DataGridView());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->txbCredits = (gcnew System::Windows::Forms::TextBox());
			this->txbBalance = (gcnew System::Windows::Forms::TextBox());
			this->lblCreditMonth = (gcnew System::Windows::Forms::Label());
			this->lblBalance = (gcnew System::Windows::Forms::Label());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->lblFrequencyP2 = (gcnew System::Windows::Forms::Label());
			this->lblAmountP2 = (gcnew System::Windows::Forms::Label());
			this->lblSourceP2 = (gcnew System::Windows::Forms::Label());
			this->btnP2Delete = (gcnew System::Windows::Forms::Button());
			this->btnP2Add = (gcnew System::Windows::Forms::Button());
			this->txbP2Frequency = (gcnew System::Windows::Forms::TextBox());
			this->txbP2Amount = (gcnew System::Windows::Forms::TextBox());
			this->txbP2Source = (gcnew System::Windows::Forms::TextBox());
			this->dgExpenses = (gcnew System::Windows::Forms::DataGridView());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->btnStart = (gcnew System::Windows::Forms::Button());
			this->btnStop = (gcnew System::Windows::Forms::Button());
			this->SimulationDate = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgCredits))->BeginInit();
			this->panel3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgIncome))->BeginInit();
			this->panel4->SuspendLayout();
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
			this->panel1->Controls->Add(this->lbUserId);
			this->panel1->Location = System::Drawing::Point(213, 92);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(1135, 758);
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
			this->txbSource->Location = System::Drawing::Point(45, 605);
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
			this->dgCredits->Size = System::Drawing::Size(702, 357);
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
			// lbUserId
			// 
			this->lbUserId->AutoSize = true;
			this->lbUserId->Location = System::Drawing::Point(44, 63);
			this->lbUserId->Name = L"lbUserId";
			this->lbUserId->Size = System::Drawing::Size(47, 16);
			this->lbUserId->TabIndex = 5;
			this->lbUserId->Text = L"UserId";
			this->lbUserId->Visible = false;
			// 
			// panel3
			// 
			this->panel3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel3->Controls->Add(this->btnDeleteP3);
			this->panel3->Controls->Add(this->lblFrequencyP3);
			this->panel3->Controls->Add(this->lblAmountP3);
			this->panel3->Controls->Add(this->lblSourceP3);
			this->panel3->Controls->Add(this->btnPanel3Add);
			this->panel3->Controls->Add(this->txbP3Frequency);
			this->panel3->Controls->Add(this->txbP3Amount);
			this->panel3->Controls->Add(this->txbP3Source);
			this->panel3->Controls->Add(this->dgIncome);
			this->panel3->Location = System::Drawing::Point(237, 78);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(1135, 720);
			this->panel3->TabIndex = 2;
			this->panel3->Visible = false;
			// 
			// btnDeleteP3
			// 
			this->btnDeleteP3->Location = System::Drawing::Point(821, 299);
			this->btnDeleteP3->Name = L"btnDeleteP3";
			this->btnDeleteP3->Size = System::Drawing::Size(137, 72);
			this->btnDeleteP3->TabIndex = 9;
			this->btnDeleteP3->Text = L"Usuń";
			this->btnDeleteP3->UseVisualStyleBackColor = true;
			this->btnDeleteP3->Click += gcnew System::EventHandler(this, &MainForm::btnDeleteP3_Click);
			// 
			// lblFrequencyP3
			// 
			this->lblFrequencyP3->AutoSize = true;
			this->lblFrequencyP3->Location = System::Drawing::Point(499, 508);
			this->lblFrequencyP3->Name = L"lblFrequencyP3";
			this->lblFrequencyP3->Size = System::Drawing::Size(88, 16);
			this->lblFrequencyP3->TabIndex = 8;
			this->lblFrequencyP3->Text = L"Częstotliwość";
			// 
			// lblAmountP3
			// 
			this->lblAmountP3->AutoSize = true;
			this->lblAmountP3->Location = System::Drawing::Point(248, 509);
			this->lblAmountP3->Name = L"lblAmountP3";
			this->lblAmountP3->Size = System::Drawing::Size(35, 16);
			this->lblAmountP3->TabIndex = 7;
			this->lblAmountP3->Text = L"Ilość";
			// 
			// lblSourceP3
			// 
			this->lblSourceP3->AutoSize = true;
			this->lblSourceP3->Location = System::Drawing::Point(130, 509);
			this->lblSourceP3->Name = L"lblSourceP3";
			this->lblSourceP3->Size = System::Drawing::Size(49, 16);
			this->lblSourceP3->TabIndex = 6;
			this->lblSourceP3->Text = L"Źródło";
			// 
			// btnPanel3Add
			// 
			this->btnPanel3Add->Location = System::Drawing::Point(296, 607);
			this->btnPanel3Add->Name = L"btnPanel3Add";
			this->btnPanel3Add->Size = System::Drawing::Size(149, 57);
			this->btnPanel3Add->TabIndex = 5;
			this->btnPanel3Add->Text = L"Dodaj";
			this->btnPanel3Add->UseVisualStyleBackColor = true;
			this->btnPanel3Add->Click += gcnew System::EventHandler(this, &MainForm::btnPanel3Add_Click);
			// 
			// txbP3Frequency
			// 
			this->txbP3Frequency->Location = System::Drawing::Point(456, 530);
			this->txbP3Frequency->Name = L"txbP3Frequency";
			this->txbP3Frequency->Size = System::Drawing::Size(100, 22);
			this->txbP3Frequency->TabIndex = 4;
			// 
			// txbP3Amount
			// 
			this->txbP3Amount->Location = System::Drawing::Point(255, 531);
			this->txbP3Amount->Name = L"txbP3Amount";
			this->txbP3Amount->Size = System::Drawing::Size(100, 22);
			this->txbP3Amount->TabIndex = 3;
			// 
			// txbP3Source
			// 
			this->txbP3Source->Location = System::Drawing::Point(94, 531);
			this->txbP3Source->Name = L"txbP3Source";
			this->txbP3Source->Size = System::Drawing::Size(100, 22);
			this->txbP3Source->TabIndex = 2;
			// 
			// dgIncome
			// 
			this->dgIncome->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgIncome->Location = System::Drawing::Point(58, 167);
			this->dgIncome->Name = L"dgIncome";
			this->dgIncome->RowHeadersWidth = 51;
			this->dgIncome->RowTemplate->Height = 24;
			this->dgIncome->Size = System::Drawing::Size(644, 309);
			this->dgIncome->TabIndex = 1;
			// 
			// panel4
			// 
			this->panel4->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel4->Controls->Add(this->txbCredits);
			this->panel4->Controls->Add(this->txbBalance);
			this->panel4->Controls->Add(this->lblCreditMonth);
			this->panel4->Controls->Add(this->lblBalance);
			this->panel4->Location = System::Drawing::Point(259, 74);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(1135, 720);
			this->panel4->TabIndex = 3;
			this->panel4->Visible = false;
			// 
			// txbCredits
			// 
			this->txbCredits->Location = System::Drawing::Point(163, 138);
			this->txbCredits->Name = L"txbCredits";
			this->txbCredits->ReadOnly = true;
			this->txbCredits->Size = System::Drawing::Size(155, 22);
			this->txbCredits->TabIndex = 20;
			// 
			// txbBalance
			// 
			this->txbBalance->Location = System::Drawing::Point(113, 100);
			this->txbBalance->Name = L"txbBalance";
			this->txbBalance->ReadOnly = true;
			this->txbBalance->Size = System::Drawing::Size(155, 22);
			this->txbBalance->TabIndex = 19;
			// 
			// lblCreditMonth
			// 
			this->lblCreditMonth->AutoSize = true;
			this->lblCreditMonth->Location = System::Drawing::Point(47, 141);
			this->lblCreditMonth->Name = L"lblCreditMonth";
			this->lblCreditMonth->Size = System::Drawing::Size(110, 16);
			this->lblCreditMonth->TabIndex = 1;
			this->lblCreditMonth->Text = L"Ostatnie Kredyty :";
			// 
			// lblBalance
			// 
			this->lblBalance->AutoSize = true;
			this->lblBalance->Location = System::Drawing::Point(47, 103);
			this->lblBalance->Name = L"lblBalance";
			this->lblBalance->Size = System::Drawing::Size(60, 16);
			this->lblBalance->TabIndex = 0;
			this->lblBalance->Text = L"Balance:";
			// 
			// panel2
			// 
			this->panel2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->panel2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel2->Controls->Add(this->lblFrequencyP2);
			this->panel2->Controls->Add(this->lblAmountP2);
			this->panel2->Controls->Add(this->lblSourceP2);
			this->panel2->Controls->Add(this->btnP2Delete);
			this->panel2->Controls->Add(this->btnP2Add);
			this->panel2->Controls->Add(this->txbP2Frequency);
			this->panel2->Controls->Add(this->txbP2Amount);
			this->panel2->Controls->Add(this->txbP2Source);
			this->panel2->Controls->Add(this->dgExpenses);
			this->panel2->Location = System::Drawing::Point(221, 82);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(1135, 716);
			this->panel2->TabIndex = 1;
			this->panel2->Visible = false;
			// 
			// lblFrequencyP2
			// 
			this->lblFrequencyP2->AutoSize = true;
			this->lblFrequencyP2->Location = System::Drawing::Point(408, 478);
			this->lblFrequencyP2->Name = L"lblFrequencyP2";
			this->lblFrequencyP2->Size = System::Drawing::Size(88, 16);
			this->lblFrequencyP2->TabIndex = 9;
			this->lblFrequencyP2->Text = L"Częstotliwość";
			// 
			// lblAmountP2
			// 
			this->lblAmountP2->AutoSize = true;
			this->lblAmountP2->Location = System::Drawing::Point(264, 479);
			this->lblAmountP2->Name = L"lblAmountP2";
			this->lblAmountP2->Size = System::Drawing::Size(35, 16);
			this->lblAmountP2->TabIndex = 8;
			this->lblAmountP2->Text = L"Ilość";
			// 
			// lblSourceP2
			// 
			this->lblSourceP2->AutoSize = true;
			this->lblSourceP2->Location = System::Drawing::Point(64, 485);
			this->lblSourceP2->Name = L"lblSourceP2";
			this->lblSourceP2->Size = System::Drawing::Size(49, 16);
			this->lblSourceP2->TabIndex = 7;
			this->lblSourceP2->Text = L"Źródło";
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
			// button1
			// 
			this->button1->Location = System::Drawing::Point(45, 395);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(149, 49);
			this->button1->TabIndex = 3;
			this->button1->Text = L"Kredyty";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(45, 480);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(149, 47);
			this->button2->TabIndex = 4;
			this->button2->Text = L"Wydatki";
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
			this->button3->Location = System::Drawing::Point(45, 559);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(149, 47);
			this->button3->TabIndex = 5;
			this->button3->Text = L"Przychody";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MainForm::button3_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(45, 639);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(149, 47);
			this->button4->TabIndex = 6;
			this->button4->Text = L"Panel Ogólny";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MainForm::button4_Click);
			// 
			// btnStart
			// 
			this->btnStart->Location = System::Drawing::Point(31, 138);
			this->btnStart->Name = L"btnStart";
			this->btnStart->Size = System::Drawing::Size(75, 23);
			this->btnStart->TabIndex = 7;
			this->btnStart->Text = L"Start";
			this->btnStart->UseVisualStyleBackColor = true;
			this->btnStart->Click += gcnew System::EventHandler(this, &MainForm::btnStart_Click);
			// 
			// btnStop
			// 
			this->btnStop->Location = System::Drawing::Point(135, 138);
			this->btnStop->Name = L"btnStop";
			this->btnStop->Size = System::Drawing::Size(75, 23);
			this->btnStop->TabIndex = 8;
			this->btnStop->Text = L"Stop";
			this->btnStop->UseVisualStyleBackColor = true;
			this->btnStop->Click += gcnew System::EventHandler(this, &MainForm::btnStop_Click);
			// 
			// SimulationDate
			// 
			this->SimulationDate->AutoSize = true;
			this->SimulationDate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->SimulationDate->Location = System::Drawing::Point(17, 92);
			this->SimulationDate->Name = L"SimulationDate";
			this->SimulationDate->Size = System::Drawing::Size(190, 29);
			this->SimulationDate->TabIndex = 9;
			this->SimulationDate->Text = L"0 tyg 0 msc 0000";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1386, 810);
			this->Controls->Add(this->SimulationDate);
			this->Controls->Add(this->panel3);
			this->Controls->Add(this->btnStop);
			this->Controls->Add(this->btnStart);
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
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgIncome))->EndInit();
			this->panel4->ResumeLayout(false);
			this->panel4->PerformLayout();
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgExpenses))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		panel1->Visible = true;
		panel2->Visible = false;
		panel3->Visible = false;
		panel4->Visible = false;
		
		try {
			int ClientId;
			if (int::TryParse(lbUserId->Text, ClientId)) {

				String^ connString = "Data Source=LAPTOP-OP2NIRDL\\SQLEXPRESS;Initial Catalog=MójE-Bank;Integrated Security=True";
				SqlConnection sqlConn(connString);
				sqlConn.Open();

				String^ sqlQuery = "SELECT Id,Source,BorrowedMoney,InterestRate,NumOfMonths,MonthsPaid FROM Credits WHERE ownersId=@ClientId";
				SqlCommand^ command = gcnew SqlCommand(sqlQuery, % sqlConn);
				command->Parameters->AddWithValue("@ClientId", ClientId);

				SqlDataAdapter^ dataAdapter = gcnew SqlDataAdapter(command);
				DataTable^ dataTable = gcnew DataTable();

				dataAdapter->Fill(dataTable);
				dgCredits->DataSource = dataTable;
				dgCredits->Refresh();
				dgCredits->ReadOnly = true;
				dgCredits->Columns["Id"]->Visible = false;


				if (sqlConn.State == ConnectionState::Open)
				{
					sqlConn.Close();
				}
			}
		}
		catch (Exception^ e)
		{
			MessageBox::Show("Nie udalo sie polaczyc z baza danych. Szczegoly bledu: " + e->Message, "Blad polaczenia", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
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

				String^ sqlQuery = "SELECT Id,OwnersId,Source,Amount,Frequency FROM Expenses WHERE ownersId=@ClientId";
				SqlCommand^ command = gcnew SqlCommand(sqlQuery, % sqlConn);
				command->Parameters->AddWithValue("@ClientId", ClientId);

				SqlDataAdapter^ dataAdapter = gcnew SqlDataAdapter(command);
				DataTable^ dataTable = gcnew DataTable();

				dataAdapter->Fill(dataTable);
				dgExpenses->DataSource = dataTable;
				dgExpenses->Refresh();
				dgExpenses->ReadOnly = true;
				dgExpenses->Columns["OwnersId"]->Visible = false;
				dgExpenses->Columns["Id"]->Visible = false;

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

		try {
			int ClientId;
			if (int::TryParse(lbUserId->Text, ClientId)) {

				String^ connString = "Data Source=LAPTOP-OP2NIRDL\\SQLEXPRESS;Initial Catalog=MójE-Bank;Integrated Security=True";
				SqlConnection sqlConn(connString);
				sqlConn.Open();

				String^ sqlQuery = "SELECT Id,OwnersId,Source,Amount,Frequency FROM Income WHERE ownersId=@ClientId";
				SqlCommand^ command = gcnew SqlCommand(sqlQuery, % sqlConn);
				command->Parameters->AddWithValue("@ClientId", ClientId);

				SqlDataAdapter^ dataAdapter = gcnew SqlDataAdapter(command);
				DataTable^ dataTable = gcnew DataTable();

				dataAdapter->Fill(dataTable);
				dgIncome->DataSource = dataTable;
				dgIncome->Refresh();
				dgIncome->ReadOnly = true;
				dgIncome->Columns["Id"]->Visible = false;
				dgIncome->Columns["OwnersId"]->Visible = false;

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
	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
		panel1->Visible = false;
		panel2->Visible = false;
		panel3->Visible = false;
		panel4->Visible = true;
	}
	private: System::Void btnStart_Click(System::Object^ sender, System::EventArgs^ e) {
		timer->Start();
	}
	private: System::Void btnStop_Click(System::Object^ sender, System::EventArgs^ e) {
		timer->Stop();
	}
		// Panel 1
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

			String^ sqlQueryRefresh = "SELECT Id,Source,BorrowedMoney,InterestRate,NumOfMonths,MonthsPaid FROM Credits WHERE ownersId=@ClientId";
			SqlCommand^ commandRefresh = gcnew SqlCommand(sqlQueryRefresh, % sqlConn);
			commandRefresh->Parameters->AddWithValue("@ClientId", clientId);
			SqlDataAdapter^ dataAdapterRefresh = gcnew SqlDataAdapter(commandRefresh);
			DataTable^ dataTableRefresh = gcnew DataTable();
			dataAdapterRefresh->Fill(dataTableRefresh);
			dgCredits->DataSource = dataTableRefresh;
			dgCredits->Columns["Id"]->Visible = false;

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
	   // Panel 2

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

			String^ sqlQueryRefresh = "SELECT Id,OwnersId,Source,Amount,Frequency FROM Expenses WHERE ownersId=@ClientId";
			SqlCommand^ commandRefresh = gcnew SqlCommand(sqlQueryRefresh, % sqlConn);
			commandRefresh->Parameters->AddWithValue("@ClientId", clientId);
			SqlDataAdapter^ dataAdapterRefresh = gcnew SqlDataAdapter(commandRefresh);
			DataTable^ dataTableRefresh = gcnew DataTable();
			dataAdapterRefresh->Fill(dataTableRefresh);
			dgExpenses->DataSource = dataTableRefresh;
			dgExpenses->Columns["Id"]->Visible = false;
			dgExpenses->Columns["OwnersId"]->Visible = false;

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
	
	try{
		int selectedRowIndex = dgExpenses->CurrentRow->Index;
		if(selectedRowIndex>=0)
		{
			int ownerId = Convert::ToInt32(dgExpenses->Rows[selectedRowIndex]->Cells["OwnersId"]->Value);
			int Id = Convert::ToInt32(dgExpenses->Rows[selectedRowIndex]->Cells["Id"]->Value);

			String^ connString = "Data Source=LAPTOP-OP2NIRDL\\SQLEXPRESS;Initial Catalog=MójE-Bank;Integrated Security=True";
			SqlConnection sqlConn(connString);
			sqlConn.Open();

			String^ sqlQuery = "DELETE FROM Expenses WHERE Id = @Id;";
			SqlCommand command(sqlQuery, % sqlConn);
			command.Parameters->AddWithValue("@Id", Id);
			command.ExecuteNonQuery();

			String^ sqlQueryRefresh = "SELECT Id,OwnersId,Source,Amount,Frequency FROM Expenses WHERE OwnersId=@OwnersId";
			SqlCommand^ commandRefresh = gcnew SqlCommand(sqlQueryRefresh, % sqlConn);
			commandRefresh->Parameters->AddWithValue("@OwnersId", ownerId);
			SqlDataAdapter^ dataAdapterRefresh = gcnew SqlDataAdapter(commandRefresh);
			DataTable^ dataTableRefresh = gcnew DataTable();
			dataAdapterRefresh->Fill(dataTableRefresh);
			dgExpenses->DataSource = dataTableRefresh;
			dgExpenses->Columns["Id"]->Visible = false;
			dgExpenses->Columns["OwnersId"]->Visible = false;

			txbP2Source->Text = "";
			txbP2Amount->Text = "";
			txbP2Frequency->Text = "";

			if (sqlConn.State == ConnectionState::Open)
			{
				sqlConn.Close(); 
			}
		}
		
	}
	catch (Exception^ ex)
	{
		MessageBox::Show("Szczegoly bledu: " + ex->Message, "Blad", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
	
}
	// Panel 3

	private: System::Void btnPanel3Add_Click(System::Object^ sender, System::EventArgs^ e) {
	try {
		int clientId;
		if (int::TryParse(lbUserId->Text, clientId)) {

		}
		else {
			MessageBox::Show("Bledny format klienta ID", "Blad", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}
		String^ source = txbP3Source->Text;
		Decimal expensesAmount;
		if (Decimal::TryParse(txbP3Amount->Text, expensesAmount)) {

		}
		else {
			MessageBox::Show("Bledny format borrowed money", "Blad", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}
		int frequency;
		if (int::TryParse(txbP3Frequency->Text, frequency)) {

		}
		else {
			MessageBox::Show("Bledny format interestRate", "Blad", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		String^ connString = "Data Source=LAPTOP-OP2NIRDL\\SQLEXPRESS;Initial Catalog=MójE-Bank;Integrated Security=True";
		SqlConnection sqlConn(connString);
		sqlConn.Open();

		String^ sqlQuery = "INSERT INTO Income(OwnersId,Source,Amount,Frequency) VALUES (@ClientId,@Source,@Amount,@Frequency);";

		SqlCommand command(sqlQuery, % sqlConn);

		command.Parameters->AddWithValue("@ClientId", clientId);
		command.Parameters->AddWithValue("@Source", source);
		command.Parameters->AddWithValue("@Amount", expensesAmount);
		command.Parameters->AddWithValue("@Frequency", frequency);
		command.ExecuteNonQuery();

		String^ sqlQueryRefresh = "SELECT Id,OwnersId,Source,Amount,Frequency FROM Income WHERE ownersId=@ClientId";
		SqlCommand^ commandRefresh = gcnew SqlCommand(sqlQueryRefresh, % sqlConn);
		commandRefresh->Parameters->AddWithValue("@ClientId", clientId);
		SqlDataAdapter^ dataAdapterRefresh = gcnew SqlDataAdapter(commandRefresh);
		DataTable^ dataTableRefresh = gcnew DataTable();
		dataAdapterRefresh->Fill(dataTableRefresh);
		dgIncome->DataSource = dataTableRefresh;
		dgIncome->Columns["Id"]->Visible = false;
		dgIncome->Columns["OwnersId"]->Visible = false;

		txbP3Source->Text = "";
		txbP3Amount->Text = "";
		txbP3Frequency->Text = "";

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
	private: System::Void btnDeleteP3_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			int selectedRowIndex = dgIncome->CurrentRow->Index;
			if (selectedRowIndex >= 0)
			{
				int ownerId = Convert::ToInt32(dgIncome->Rows[selectedRowIndex]->Cells["OwnersId"]->Value);
				int Id = Convert::ToInt32(dgIncome->Rows[selectedRowIndex]->Cells["Id"]->Value);

				String^ connString = "Data Source=LAPTOP-OP2NIRDL\\SQLEXPRESS;Initial Catalog=MójE-Bank;Integrated Security=True";
				SqlConnection sqlConn(connString);
				sqlConn.Open();

				String^ sqlQuery = "DELETE FROM Income WHERE Id = @Id;";
				SqlCommand command(sqlQuery, % sqlConn);
				command.Parameters->AddWithValue("@Id", Id);
				command.ExecuteNonQuery();

				String^ sqlQueryRefresh = "SELECT Id,OwnersId,Source,Amount,Frequency FROM Income WHERE ownersId=@OwnersId";
				SqlCommand^ commandRefresh = gcnew SqlCommand(sqlQueryRefresh, % sqlConn);
				commandRefresh->Parameters->AddWithValue("@OwnersId", ownerId);
				SqlDataAdapter^ dataAdapterRefresh = gcnew SqlDataAdapter(commandRefresh);
				DataTable^ dataTableRefresh = gcnew DataTable();
				dataAdapterRefresh->Fill(dataTableRefresh);
				dgIncome->DataSource = dataTableRefresh;
				dgIncome->Columns["Id"]->Visible = false;
				dgIncome->Columns["OwnersId"]->Visible = false;

				txbP3Source->Text = "";
				txbP3Amount->Text = "";
				txbP3Frequency->Text = "";

				if (sqlConn.State == ConnectionState::Open)
				{
					sqlConn.Close();
				}
			}

		}
		catch (Exception^ ex)
		{
			MessageBox::Show("Szczegoly bledu: " + ex->Message, "Blad", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
	void MainForm::CalculateOnTick(System::Object^ sender, System::EventArgs^ e)
	{
		numOfTicks++;

		// Modifie Date
		currentWeek++;
		if (currentWeek > 4)
		{
			currentWeek = 1;
			currentMonth++;
			if (currentMonth > 12)
			{
				currentMonth = 1;
				currentYear++;
			}
		}
		SimulationDate->Text = currentWeek + " tyg. " + currentMonth + " msc. " + currentYear;

		//Calculations
		
		// Tabela Income
		int IncomeRowCount = dgIncome->RowCount;
		for (int i = 0; i < IncomeRowCount; i++)
		{
			int frequencyValue = Convert::ToInt32(dgIncome->Rows[i]->Cells["Frequency"]->Value);
			if (frequencyValue != 0 && numOfTicks % frequencyValue == 0)
			{
				float balanceDeducted = Convert::ToInt32(dgIncome->Rows[i]->Cells["Amount"]->Value);
				currentBalance += balanceDeducted;
			}
		}

		//Tabela Expenses
		int ExpensesRowCount = dgExpenses->RowCount;
		for (int i = 0; i < ExpensesRowCount; i++)
		{
			int fCheck = Convert::ToInt32(dgExpenses->Rows[i]->Cells["Frequency"]->Value);
			if (fCheck != 0 && numOfTicks % fCheck == 0)
			{
				float balanceDeducted = Convert::ToInt32(dgExpenses->Rows[i]->Cells["Amount"]->Value);
				currentBalance -= balanceDeducted;

			}
		}
			
		try 
		{
			int OwnersId;
			std::vector<long float>TotalDivider;
			int frequencyValue = 4;
			long float creditMonth = 0.0f;
			if (int::TryParse(lbUserId->Text, OwnersId)) 
			{
				TotalDivider.clear();
				int CreditsRowCount = dgCredits->RowCount;
				for (int i = 0; i < CreditsRowCount; i++)
				{
					float bMoney = Convert::ToDouble(dgCredits->Rows[i]->Cells["BorrowedMoney"]->Value);
					float rate = Convert::ToDouble(dgCredits->Rows[i]->Cells["InterestRate"]->Value);
					int nMonthsPaid = Convert::ToInt32(dgCredits->Rows[i]->Cells["MonthsPaid"]->Value);
					int nOfMonths = Convert::ToInt32(dgCredits->Rows[i]->Cells["NumOfMonths"]->Value);
					float summ  = 0.0;
					int Id = Convert::ToInt32(dgCredits->Rows[i]->Cells["Id"]->Value);

					if(TotalDivider.size()==CreditsRowCount){}
					else
					{
						for (int j = 1;j <= nOfMonths;j++)
						{
							summ += roundf(pow((1 + ((rate / 100) / 12)), ((-1) * j))*100)/100;
						}
					}

					TotalDivider.push_back(summ);

					if (numOfTicks % frequencyValue == 0)
					{
						nMonthsPaid++;
						
						String^ connString = "Data Source=LAPTOP-OP2NIRDL\\SQLEXPRESS;Initial Catalog=MójE-Bank;Integrated Security=True";
						SqlConnection sqlConn(connString);
						sqlConn.Open();

						String^ sqlQuery = "UPDATE Credits SET MonthsPaid="+nMonthsPaid+" Where Id=@Id";
						SqlCommand command(sqlQuery, % sqlConn);
						command.Parameters->AddWithValue("@Id", Id);
						command.ExecuteNonQuery();
						
						if (rate != 0)
						{
							creditMonth += bMoney / TotalDivider[i];
						}
						else {
							creditMonth += bMoney/ TotalDivider[i];
						}

						if (nMonthsPaid >= Convert::ToInt32(dgCredits->Rows[i]->Cells["NumOfMonths"]->Value))
						{
							String^ sqlQueryDelete = "DELETE FROM Credits WHERE Id = @Id;";
							SqlCommand command(sqlQueryDelete, % sqlConn);
							command.Parameters->AddWithValue("@Id", Id);
							command.ExecuteNonQuery();
						}

						currentBalance -= Convert::ToInt64(creditMonth);
					    txbBalance->Text = ""+ currentBalance;
						txbCredits->Text = ""+Convert::ToUInt64(creditMonth);

						String^ sqlQueryRefresh = "SELECT Id,OwnersId,Source,BorrowedMoney,InterestRate,NumOfMonths,MonthsPaid FROM Credits WHERE ownersId=@OwnersId";
						SqlCommand^ commandRefresh = gcnew SqlCommand(sqlQueryRefresh, % sqlConn);
						commandRefresh->Parameters->AddWithValue("@OwnersId", OwnersId);
						SqlDataAdapter^ dataAdapterRefresh = gcnew SqlDataAdapter(commandRefresh);
						DataTable^ dataTableRefresh = gcnew DataTable();
						dataAdapterRefresh->Fill(dataTableRefresh);
						dgCredits->DataSource = dataTableRefresh;
						dgCredits->Columns["Id"]->Visible = false;
						dgCredits->Columns["OwnersId"]->Visible = false;

						
						if (sqlConn.State == ConnectionState::Open)
						{
							sqlConn.Close();
						}
					}
				}
				currentBalance -= creditMonth;
				txbBalance->Text = "" + currentBalance;
				txbCredits->Text = "" + creditMonth;
			}
		}
		catch (Exception^ e)
		{
			MessageBox::Show("Nie udalo sie polaczyc z baza danych. Szczegoly bledu: " + e->Message, "Blad polaczenia", MessageBoxButtons::OK, MessageBoxIcon::Error);

		}	
		
	}
};
}
