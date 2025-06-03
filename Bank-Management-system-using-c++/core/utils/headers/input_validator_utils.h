#pragma once
#include <string>
#include "../../../features/manage users/models/user_info.h"
using namespace std;

class InputValidatorUtils
{
public:
	static bool IsValidPassword(const string& password);

	static bool IsValidUsername(const string& Username);

	static bool IsValidUsernameAndPassword(const string& Username,const string& password);

	static bool IsValidPinCode(const string& PinCode);

	static bool IsValidName(const string& name);

	static bool IsValidPhoneNumber(const string& phoneNumber);
};



