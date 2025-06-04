#include "manage_users.h"
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include "models/user_info.h"
#include "../../core/constants/file_pathes.h"
#include "../../core/utils/headers/file_operations.h"
#include "../../core/utils/headers/data_reader.h"
#include "../../core/utils/headers/input_validator_utils.h"
#include "../../core/utils/headers/console_helper.h"
#include "../auth manager/auth_manager.h"

ManageUsers* ManageUsers::instance = nullptr;

ManageUsers::ManageUsers() {}

// Finds a user by username and returns their index in the list, or -1 if not found
short ManageUsers::FindUserByUsername(string UserName)
{
	for (short counter = 0; counter < instance->Users.size(); counter++)
	{
		if (instance->Users[counter].GetUsername() == UserName) return counter;
	}
	return -1;
}

// Finds a user by username and password and returns their index, or -1 if not found
short ManageUsers::FindUserByUsernameAndPassword(const UserInfo& userInfo)
{
	for (short counter = 0; counter < instance->Users.size(); counter++)
	{
		if (instance->Users[counter].GetUsername() == userInfo.GetUsername() && instance->Users[counter].GetPassword() == userInfo.GetPassword()) return counter;
	}
	return -1;
}

// Destructor: saves the users data when the ManageUsers object is destroyed
ManageUsers::~ManageUsers()
{
	SaveUsers();
}

// Saves all users to a file by converting them to string records
void ManageUsers::SaveUsers() {
	vector<string> vRecords;
	for (UserInfo& user : instance->Users)
	{
		vRecords.push_back(UserInfo::ConvertUserToRecord(user));
	}
	FileOperations::SaveRecordsInFile(vRecords, FilePathes::Users);
}

// Restores users from file by reading records and converting them to UserInfo objects
void ManageUsers::RestoreUsersFromFile() {
	vector<string> Records = FileOperations::RestoreDataFromFile(FilePathes::Users);
	for (string Record : Records)
	{
		instance->Users.push_back(UserInfo::ConvertRecordToUser(Record));
	}
}

// Displays the manage users menu screen and handles user input until exit
void ManageUsers::ShowManageUsersScreen() {
	short ManageUsersMenuOption = 0;
	do
	{
		ConsoleHelper::ShowScreenHeader("Manage Users Menu Screen");
		cout << "\t[1] List Users\n"
			<< "\t[2] Add New User\n"
			<< "\t[3] Delete User\n"
			<< "\t[4] Update User\n"
			<< "\t[5] Find User\n"
			<< "\t[6] Save Users Changes\n"
			<< "\t[7] Return to Main Menu\n";
		cout << "===================================================\n";
		ManageUsersMenuOption = ReadManageUsersMenuOption();
		PerformManageUsersMenu((eManageUsersMenuOptions)ManageUsersMenuOption);
	} while (ManageUsersMenuOption != 7);
}

// Reads and returns the user’s choice from the manage users menu
short ManageUsers::ReadManageUsersMenuOption() {
	cout << "Choose an option [1-7]: ";
	return DataReader::ReadNumber();
}

// Checks if a user exists based on username and password
bool ManageUsers::IsUserExist(const UserInfo& UserSearch) {
	for (const UserInfo& user : instance->Users) {
		if ((UserSearch.GetUsername() == user.GetUsername()) && (UserSearch.GetPassword() == user.GetPassword())) return true;
	}
	return false;
}

// Displays the list of users with formatted columns
void ManageUsers::ShowListUsersScreen() {
	cout << "\t\t\t" << "Users List (" << instance->Users.size() << ") User(s).\n\n";
	cout << "-----------------------------------------------------------------------------" << endl;
	cout << left
		<< " |  " << setw(15) << "User Name"
		<< " | " << setw(15) << "Password"
		<< " | " << "Permissions" << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	for (const UserInfo& user : instance->Users)
	{
		UserInfo::PrintUserInfoInLine(user);
		cout << "\n-----------------------------------------------------------------------------" << endl;
	}
}

// Validates username format, then returns the index of the user if exists, or -1 if not
short ManageUsers::GetPositionUserInListByUsername(const string& username)
{
	return InputValidatorUtils::IsValidUsername(username) ? FindUserByUsername(username) : -1;
}

// Shows the screen to add new users, with username validation and retry attempts
void ManageUsers::ShowAddNewUsersScreen()
{
	char addMoreUsers = 'Y';
	string username = "";
	short remainingAttempts = 5;
	short userIndex = 0;
	do
	{
		ConsoleHelper::ShowScreenHeader("Add New Users Screen");
		remainingAttempts = 5;

		username = UserInfo::ReadValidUsername();

		userIndex = FindUserByUsername(username);

		// Allow up to 5 attempts to enter a unique username
		while (userIndex != -1 && remainingAttempts > 0) {

			cout << "Number of attempts remaining " << remainingAttempts << "\n\n";

			remainingAttempts--;

			cout << "User With [" << username << "] already exists.\n";

			username = UserInfo::ReadValidUsername();

			userIndex = FindUserByUsername(username);
		}
		if (userIndex != -1) {
			ConsoleHelper::ShowMessageAndPauseThenClear("No valid username entered after 5 attempts.");
			return;
		}
		UserInfo user;

		user.ReadFullInfoUser(username);

		instance->Users.push_back(user);

		cout << "User Added Successfully, do you want more Users? Y/N? ";

		cin >> addMoreUsers;

		ConsoleHelper::ClearBuffer();

	} while (toupper(addMoreUsers) == 'Y');
}

// Shows the delete user screen, prevents deleting "Admin" and currently logged-in user
void ManageUsers::ShowDeleteUserScreen()
{
	ConsoleHelper::ShowScreenHeader("Delete User Screen");
	string Username = UserInfo::ReadValidUsername();
	cout << "\n";
	short UserIndex = FindUserByUsername(Username);

	if (UserIndex == -1) {
		cout << "User Not Found!\n";
		return;
	}
	// Prevent deletion of Admin user
	if (instance->Users[UserIndex].GetUsername() == "Admin") {
		cout << "You Cannot Delete This User\n";
		return;
	}
	// Prevent deletion of currently logged-in user
	if (Username == AuthManager::getInstance().getUserLogged().GetUsername()) {
		cout << "You cannot delete the currently logged-in user.\n";
		return;
	}
	UserInfo::PrintUserInfoCard(Users[UserIndex]);

	cout << "\n\n";

	// Ask for confirmation before deletion
	if (ConsoleHelper::AreYouSure("Are you sure you want to delete this user? Y/N? ")) {
		instance->Users.erase(instance->Users.begin() + UserIndex);
		cout << "User Deleted Successfully\n";
		cout << "Remaining Users: " << instance->Users.size() << "\n";
		cout << "-------------------------------\n";
	}
}

// Shows update user screen, allows retry if username not found, and confirmation before editing
void ManageUsers::ShowUpdateUserScreen()
{
	ConsoleHelper::ShowScreenHeader("Update User Screen");
	short remainingAttempts = 3;
	short tempRemainingAttempts = remainingAttempts;
	string username = UserInfo::ReadValidUsername();
	short userIndex = FindUserByUsername(username);

	// Allow up to 3 attempts to enter an existing username
	while (userIndex == -1 && remainingAttempts > 0) {
		remainingAttempts--;
		cout << "User with username [" + username + "] not found. \n";
		cout << "Number of attempts remaining " << remainingAttempts << "\n\n";
		username = UserInfo::ReadValidUsername();
		userIndex = FindUserByUsername(username);
	}

	if (userIndex == -1) {
		ConsoleHelper::ShowMessageAndPauseThenClear("No valid username entered after " + to_string(tempRemainingAttempts) + " attempts.");
		return;
	}

	// Show user info before editing
	UserInfo::PrintUserInfoCard(instance->Users[userIndex]);

	// Confirm before editing
	if (ConsoleHelper::AreYouSure("Are you sure you want to update this user? Y/N? "))
	{
		EditUserFields(instance->Users[userIndex]);
		cout << "\n\nData review and modification completed. Here's the updated info:\n\n";
		UserInfo::PrintUserInfoCard(instance->Users[userIndex]);
	}
	else
		cout << "\nNo worries, take a break and come back ready!\n";
}
// Displays the screen to find a user by username and shows user details if found
void ManageUsers::ShowFindUserScreen()
{
	ConsoleHelper::ShowScreenHeader("Find User Screen");

	// Prompt for username input
	string username = UserInfo::ReadValidUsername();
	cout << "\n";

	// Search for user index by username
	short UserIndex = FindUserByUsername(username);

	// If found, display user info card, else show not found message
	if (UserIndex != -1) {
		UserInfo::PrintUserInfoCard(instance->Users[UserIndex]);
		cout << "\n";
	}
	else
		cout << "User with username [" << username << "] was not found.\n";
}

// Singleton getter: returns the single instance of ManageUsers,
// creates it and loads users from file if not already created
ManageUsers& ManageUsers::getInstance()
{
	if (instance == nullptr)
	{
		instance = new ManageUsers();
		instance->RestoreUsersFromFile();
	}
	return *instance;
}

// Performs action based on user choice in Manage Users menu
void ManageUsers::PerformManageUsersMenu(eManageUsersMenuOptions ManageUsersMenuOptions) {
	ConsoleHelper::ClearScreen();
	switch (ManageUsersMenuOptions) {
	case enListUsers:
		ShowListUsersScreen();
		break;
	case enAddNewUser:
		ShowAddNewUsersScreen();
		break;
	case enDeleteUser:
		ShowDeleteUserScreen();
		break;
	case enUpdateUser:
		ShowUpdateUserScreen();
		break;
	case enFindUser:
		ShowFindUserScreen();
		break;
	case eSaveUsers:
		SaveChanges();
		break;
	case enMainMenu:
		return;
	default:
		ConsoleHelper::ClearScreen();
		cout << "Invalid Choice! Please choose between [1-7]\n\n";
	}
	cout << "\n";
	ConsoleHelper::ShowMessageAndPauseThenClear("Press any key to return to the Manage Users menu...");
	cout << "\n";
}

// Saves all changes to users and notifies the user
void ManageUsers::SaveChanges() {
	cout << "Saving..." << endl;
	SaveUsers();
	cout << "All changes have been saved successfully.\n";
}

// Reads a username from user input with a custom prompt message
string ManageUsers::ReadUsername(string message) {
	cout << message;
	string UserName = "";
	getline(cin >> ws, UserName);  // ws to consume any leading whitespace
	return UserName;
}

// Returns a const reference to the vector of all users
const vector<UserInfo>& ManageUsers::getUsers()
{
	return Users;
}

// Destroys the singleton instance to free resources
void ManageUsers::destroyInstance() {
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

// Returns the index of a user matching username and password if both are valid,
// otherwise returns -1
short ManageUsers::GetPositionUserInListByUsernameAndPassword(const UserInfo& user)
{
	return (InputValidatorUtils::IsValidPassword(user.GetPassword()) && InputValidatorUtils::IsValidUsername(user.GetUsername()))
		? FindUserByUsernameAndPassword(user)
		: -1;
}

// Allows editing fields of a user with confirmation prompts
void ManageUsers::EditUserFields(UserInfo& user)
{
	// Edit username with check to avoid duplicates
	if (ConsoleHelper::AreYouSure("Do you want to edit the username? (Y/N): ")) {
		string username = UserInfo::ReadValidUsername();
		do
		{
			if (FindUserByUsername(username) == -1) {
				user.SetUsername(username);
				break;
			}
			else {
				cout << "User With [" << username << "] already exists\n";
				if (ConsoleHelper::AreYouSure("Do you still want to change your username? (Y/N): ")) {
					username = UserInfo::ReadValidUsername();
				}
				else
					break;
			}

		} while (true);
	}
	// Edit password with confirmation
	if (ConsoleHelper::AreYouSure("Do you want to edit the user password? (Y/N): ")) {
		user.ReadPassword();
	}
	// Edit permissions with confirmation
	if (ConsoleHelper::AreYouSure("Do you want to edit the permissions? (Y/N): ")) {
		user.ReadPermissions();
	}
}
