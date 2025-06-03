#include "user_info.h"
#include <iomanip>
#include <iostream>
#include <array>
#include "../../../core/utils/headers/string_operations.h"
#include "../../../core/utils/headers/input_validator_utils.h"
#include "../../../core/utils/headers/console_helper.h"

// Converts a user object to a string record.
string UserInfo::ConvertUserToRecord(const UserInfo& user, string seprete) {
	string Record = "";

	Record = user.Username + seprete;
	Record += user.Password + seprete;
	Record += to_string(user.Permissions);
	return Record;
}

// Converts a string record back into a user object.
UserInfo UserInfo::ConvertRecordToUser(const string& Record, string delim)
{
	vector<string> PartsOfRecord = StringOperations::SplitString(Record, delim);
	UserInfo user;

	user.Username = PartsOfRecord[0];
	user.Password = PartsOfRecord[1];
	user.Permissions = stoi(PartsOfRecord[2]);

	return user;
}


// Reads and validates the username from user input.
void UserInfo::ReadUsername() {
	cout << "Please Enter Username : ";
	string username;
	getline(cin >> ws, username);
	while (!InputValidatorUtils::IsValidUsername(username)) {
		ConsoleHelper::ShowUsernameInvalidMessage();
		cout << "Please Enter Username : ";
		getline(cin >> ws, username);
	}
	Username = username;

	cout << "\n\n";
}

// Reads and validates the password from user input.
void UserInfo::ReadPassword() {
	cout << "Please Enter Your Password : ";
	string pass;
	getline(cin >> ws, pass);
	while (!InputValidatorUtils::IsValidPassword(pass)) {
		ConsoleHelper::ShowPasswordInvalidMessage();
		cout << "Please Enter Your Password : ";
		getline(cin >> ws, pass);
	}
	Password = pass;
}

// Reads permissions from the user interactively.
void UserInfo::ReadPermissions() {
	char giveFullAccess;
	do {
		cout << "Do you want to give full access? Y/N? ";
		ConsoleHelper::ClearBuffer();
		cin >> giveFullAccess;
		giveFullAccess = toupper(giveFullAccess);
	} while (giveFullAccess != 'Y' && giveFullAccess != 'N');

	if (giveFullAccess == 'Y') {
		Permissions = -1;
		return;
	}
	cout << "Do You Want to give access to : \n\n";
	Permissions = CollectPermissionFlags();
}

// Displays user info in a detailed card format.
void UserInfo::PrintUserInfoCard(const UserInfo& user)
{
	cout << "The Following are the client details : \n";
	cout << "\n\n";
	cout << "------------------------------------------------------------------------\n";
	cout << left << setw(14) << "Username" << " : " << user.Username << "\n";
	cout << left << setw(14) << "Password" << " : " << user.Password << "\n";
	cout << left << setw(14) << "Permissions" << " : " << user.Permissions << "\n";
	cout << "------------------------------------------------------------------------\n";
}

// Displays user info in a line format.
void UserInfo::PrintUserInfoInLine(const UserInfo& user)
{
	cout << left
		<< " |  " << setw(15) << user.Username
		<< " | " << setw(15) << user.Password
		<< " | " << PermissionToString(user.Permissions) << endl;
}

// Converts permission bits to readable string.
string UserInfo::PermissionToString(int perm)
{
	if (perm == -1) {
		return "Show List | Add | Delete | Update | Find | Transaction | Save | Manage Users";
	}

	std::string result;
	if (perm & 1)     result += "Show List | ";
	if (perm & 2)     result += "Add | ";
	if (perm & 4)     result += "Delete | ";
	if (perm & 8)     result += "Update | ";
	if (perm & 16)    result += "Find | ";
	if (perm & 32)    result += "Transaction | ";
	if (perm & 64)    result += "Save | ";
	if (perm & 128)   result += "Manage Users | ";

	if (result.empty()) return "None";

	return result.substr(0, result.size() - 3);
}

void UserInfo::ReadPasswordAndUsername()
{
	ReadUsername();
	ReadPassword();
}

string UserInfo::ReadPasswordForSearch()
{
	cout << "Please Enter Password : ";
	string password;
	getline(cin >> ws, password);
	return password;
}

string UserInfo::ReadUsernameForSearch(const string message)
{
	cout << message;
	string Username;
	getline(cin >> ws, Username);
	return Username;
}

UserInfo UserInfo::ReadPassAndUsernameForSearch() {
	UserInfo user;
	user.Username = ReadUsernameForSearch();
	user.Password = ReadPasswordForSearch();
	return user;
}
bool UserInfo::IsValidPasswordAndUsername(const UserInfo& user) {
	if (InputValidatorUtils::IsValidUsername(user.Username) && InputValidatorUtils::IsValidPassword(user.Password))
	{
		return true;
	}
	return false;
}
void UserInfo::ReadFullInfoUser(string userName)
{

	Username = userName;
	cout << "\n";
	ReadPassword();
	cout << "\n";
	ReadPermissions();
}


void UserInfo::EditPassword()
{
	ReadPassword();
}

void UserInfo::EditPermissions()
{

	if (ConsoleHelper::AreYouSure("Do you want to give full access? Y/N? "))
	{
		Permissions = -1;
		return;
	}
	if (ConsoleHelper::AreYouSure("Are You Sure you want update this user? Y/N? "))
	{
		Permissions = CollectPermissionFlags();
	}
}

// Reads permissions as bit flags based on user confirmation.
short UserInfo::CollectPermissionFlags()
{
	array<string, 8> listOfQuestions = {
	"Show Client List? Y/N? ",
	"Add New Client? Y/N? ",
	"Delete Client? Y/N? ",
	"Update Client? Y/N? ",
	"Find Client? Y/N? ",
	"Transaction? Y/N? ",
	"Save Changes? Y/N? ",
	"Manage Users? Y/N? "
	};
	char isAccept = 'Y';
	short permissionsValue = 0;
	for (size_t i = 0; i < listOfQuestions.size(); i++)
	{
		do {
			cout << listOfQuestions[i];
			ConsoleHelper::ClearBuffer();
			cin >> isAccept;
			isAccept = toupper(isAccept);
		} while (toupper(isAccept) != 'Y' && toupper(isAccept) != 'N');

		if (isAccept == 'Y') {
			permissionsValue += static_cast<short>(pow(2, i));
		}

		std::cout << "\n\n";
	}
	return permissionsValue;
}

// Checks whether the logged user has the required permission.
bool UserInfo::HasPermission(const UserInfo& userLogged, short selectedOptionFromMainMenu)
{
	return ((userLogged.Permissions == -1) || (userLogged.Permissions & (int)pow(2, (selectedOptionFromMainMenu - 1))));
}

string UserInfo::ReadValidUsername()
{
	string username = ReadUsernameForSearch();
	while (!InputValidatorUtils::IsValidUsername(username)) {
		ConsoleHelper::ShowUsernameInvalidMessage();
		username = ReadUsernameForSearch("Please enter a valid username: ");
	}
	return username;
}
