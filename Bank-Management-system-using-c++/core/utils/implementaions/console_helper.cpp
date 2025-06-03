#include <iostream>
#include "../headers/console_helper.h"

void ConsoleHelper::ShowMessageAndPauseThenClear(string message)
{
	cout << message;
	system("pause>nul");
	ClearScreen();
}
void ConsoleHelper::ShowScreenHeader(string screenName) {
	cout << "\n==================================================\n\n";
	cout << "\t" << screenName << endl;
	cout << "\n==================================================\n\n";
}

void ConsoleHelper::ClearBuffer()
{
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool ConsoleHelper::AreYouSure(const string Message)
{
	cout << Message;
	char areYouSure = 'N';
	cin >> areYouSure;
	ClearBuffer();
	return toupper(areYouSure) == 'Y';
}

void ConsoleHelper::PauseAndClearScreen() {
	system("pause>nul");
	ClearScreen();
}

void ConsoleHelper::ClearScreen()
{
	system("cls");
}

void ConsoleHelper::ShowUsernameInvalidMessage() {
	cout << "Invalid Username! Please follow the rules below:\n";
	cout << "- Must be between 4 and 20 characters\n";
	cout << "- Must start with a letter (A ~ Z or a ~ z)\n";
	cout << "- Cannot contain spaces or symbols (only '.' or '_' are allowed)\n";
	cout << "- '.' or '_' can be used, but only once in total\n\n";
}
void ConsoleHelper::ShowPasswordInvalidMessage() {
	cout << "Invalid Password! Your Password must meet the following requirements\n";
	cout << "At least 8 characters\n";
	cout << "At least one uppercase letter (A ~ Z)\n";
	cout << "At least one lowercase letter (a ~ z)\n";
	cout << "At least one special character (e.g. @, #, $, !)\n\n";
}