#include "input_validator_utils.h"
#include "string_operations.h"

bool InputValidatorUtils::IsValidPassword(const string& password)
{
	if (password.size() < 8 || password.size() > 16) return false;
	if (!(StringOperations::HasLowerCase(password) && StringOperations::HasUpperCase(password)))return false;
	if (!StringOperations::HasSpecialCharacter(password))return false;
	if (!StringOperations::HasNumber(password))return false;


	return true;
}

bool InputValidatorUtils::IsValidUsername(const string& Username)
{
	if (Username.size() < 4 || Username.size() > 20)return false;
	if (!(isalpha(Username[0])))return false;
	if (StringOperations::HasSpace(Username))return false;
	if (!StringOperations::IsAlphaNameWithOneDotOrUnderscore(Username))return false;

	return true;
}

bool InputValidatorUtils::IsValidUsernameAndPassword(const UserInfo& User)
{
	return (InputValidatorUtils::IsValidPassword(User.Password) && InputValidatorUtils::IsValidUsername(User.Password));
}

bool InputValidatorUtils::IsValidPinCode(const string& PinCode)
{
	if (PinCode.length() != 4 && PinCode.length() != 6) {
		return false;
	}
	if (!StringOperations::IsWordAllDigits(PinCode))
	{
		return false;
	}
	return true;
}

bool InputValidatorUtils::IsValidName(const string& fullName)
{
	// Check length between 7 and 50 characters
	if (fullName.length() < 7 || fullName.length() > 50) {
		return false;
	}
	// Check that the name contains at least two words
	if (StringOperations::CountEachWordInTheString(fullName) < 2)
	{
		return false;
	}
	// Check that the name contains only letters and spaces
	if (!StringOperations::ContainsOnlyLettersAndSpaces(fullName))
	{
		return false;
	}
	return true;
}

bool InputValidatorUtils::IsValidPhoneNumber(const string& phoneNumber)
{
	// Must be exactly 11 characters
	if (phoneNumber.size() != 11)
		return false;

	// Must contain only digits
	if (!StringOperations::IsWordAllDigits(phoneNumber))
		return false;

	// Must start with "01"
	if (!(phoneNumber[0] == '0' && phoneNumber[1] == '1'))
		return false;

	// Third digit must be one of the valid operator codes: 0, 1, 2, or 5
	if (!(phoneNumber[2] == '0' || phoneNumber[2] == '1' ||
		phoneNumber[2] == '2' || phoneNumber[2] == '5'))
		return false;

	return true; // All checks passed
}

