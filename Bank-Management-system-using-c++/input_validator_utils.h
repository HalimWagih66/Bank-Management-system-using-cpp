#pragma once
#include "user_info.h"
#include <string>
using namespace std;

class InputValidatorUtils
{
public:
	static bool IsValidPassword(const string& password);

	static bool IsValidUsername(const string& Username);

	static bool IsValidUsernameAndPassword(const UserInfo& User);

	static bool IsValidPinCode(const string& PinCode);

	static bool IsValidName(const string& name);

	static bool IsValidPhoneNumber(const string& phoneNumber);
};



