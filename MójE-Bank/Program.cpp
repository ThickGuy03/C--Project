#include "LoginForm.h"

using namespace System;
using namespace System::Windows::Forms;

void main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	MójEBank::LoginForm loginForm;

	loginForm.ShowDialog();
	User^ user = loginForm.user;

	if (user != nullptr)
	{
		MessageBox::Show("Udana weryfikacja " + user->name+" "+user->surname, "Program.cpp", MessageBoxButtons::OK);
	}
	else {
		MessageBox::Show("Weryfikacja nieudana", "Program.cpp", MessageBoxButtons::OK);
	}
}