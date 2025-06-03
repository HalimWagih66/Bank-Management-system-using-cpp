#pragma once
#include <string>
using namespace std;
class ConsoleHelper
{
public:

	static void ShowMessageAndPauseThenClear(string message);

	static void ShowScreenHeader(string screenName);

	static void ClearBuffer();

	static bool AreYouSure(const string Message);

	static void PauseAndClearScreen();

	static void ClearScreen();

	static void ShowUsernameInvalidMessage();

	static void ShowPasswordInvalidMessage();
};

