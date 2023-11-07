#include "LoginForm.h"
#include "MainForm.h"
#include "RegisterForm.h"

using namespace System;
using namespace System::Windows::Forms;

void main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	
	User^ user = nullptr;
	while (true) {

		MójEBank::LoginForm loginForm;
		loginForm.ShowDialog();

		if (loginForm.switchToRegister) {
			MójEBank::RegisterForm registerForm;
			registerForm.ShowDialog();

			if (registerForm.switchToLogin) {
				continue;
			}
			else {
				user = registerForm.user;
				break;
			}
		}
		else {
			user = loginForm.user;
			break;
		}

	}

	if (user != nullptr)
	{
		MójEBank::MainForm mainForm(user);
		Application::Run(% mainForm);
	}
	else {
		//MessageBox::Show("Weryfikacja nieudana", "Program.cpp", MessageBoxButtons::OK);
	}
}