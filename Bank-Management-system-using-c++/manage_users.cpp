#include "manage_users.h"
#include <string>
#include <vector>
#include "input_validator_utils.h"
#include "console_helper.h"
#include <iostream>
#include "file_operations.h"
#include "data_reader.h"
#include "bank_system.h"
#include "file_names.h"
#include <iomanip>

ManageUsers* ManageUsers::instance = nullptr;

ManageUsers::ManageUsers() {

}

short ManageUsers::FindUserByUsername(string UserName)
{
	for (short counter = 0; counter < instance->Users.size(); counter++)
	{
		if (instance->Users[counter].Username == UserName)return counter;
	}
	return -1;
}
short ManageUsers::FindUserByUsernameAndPassword(const UserInfo& userInfo)
{
	for (short counter = 0; counter < instance->Users.size(); counter++)
	{
		if (instance->Users[counter].Username == userInfo.Username && instance->Users[counter].Password == userInfo.Password)return counter;
	}
	return -1;
}

ManageUsers::~ManageUsers()
{
	SaveUsers();
}

void ManageUsers::SaveUsers() {
	vector<string> vRecords;
	for (UserInfo& user : instance->Users)
	{
		vRecords.push_back(UserInfo::ConvertUserToRecord(user));
	}
	FileOperations::SaveRecordsInFile(vRecords, FileNames::Users);
}
void ManageUsers::RestoreUsersFromFile() {
	vector<string> Records = FileOperations::RestoreDataFromFile(FileNames::Users);
	for (string Record : Records)
	{
		instance->Users.push_back(UserInfo::ConvertRecordToUser(Record));
	}
}
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

short ManageUsers::ReadManageUsersMenuOption() {
	cout << "Choose an option [1-7]: ";
	return DataReader::ReadNumber();
}


bool ManageUsers::IsUserExist(const UserInfo& UserSearch) {
	for (const UserInfo& user : instance->Users) {
		if ((UserSearch.Username == user.Username) && (UserSearch.Password == user.Password))return true;
	}
	return false;
}
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

short ManageUsers::GetPositionUserInListByUsername(const string& username)
{
	return InputValidatorUtils::IsValidUsername(username) ? FindUserByUsername(username) : -1;
}

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
	if (instance->Users[UserIndex].Username == "Admin") {
		cout << "You Cannot Delete This User\n";
		return;
	}
	if (Username == AuthManager::getInstance().getUserLogged().Username) {
		cout << "You cannot delete the currently logged-in user.\n";
		return;
	}
	UserInfo::PrintUserInfoCard(Users[UserIndex]);

	cout << "\n\n";

	if (ConsoleHelper::AreYouSure("Are you sure you want to delete this user? Y/N? ")) {
		instance->Users.erase(instance->Users.begin() + UserIndex);
		cout << "User Deleted Successfully\n";
		cout << "Remaining Users: " << instance->Users.size() << "\n";
		cout << "-------------------------------\n";
	}
}
void ManageUsers::ShowUpdateUserScreen()
{

	ConsoleHelper::ShowScreenHeader("Update User Screen");
	short remainingAttempts = 3;
	short tempRemainingAttempts = remainingAttempts;
	string username = UserInfo::ReadValidUsername();
	short userIndex = FindUserByUsername(username);
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
	UserInfo::PrintUserInfoCard(instance->Users[userIndex]);
	if (ConsoleHelper::AreYouSure("Are you sure you want to update this user? Y/N? "))
	{
		EditUserFields(instance->Users[userIndex]);
		cout << "\n\nData review and modification completed. Here's the updated info:\n\n";
		UserInfo::PrintUserInfoCard(instance->Users[userIndex]);
	}
	else
		cout << "\nNo worries, take a break and come back ready!\n";
}
void ManageUsers::ShowFindUserScreen()
{
	ConsoleHelper::ShowScreenHeader("Find User Screen");

	string username = UserInfo::ReadValidUsername();
	cout << "\n";

	short UserIndex = FindUserByUsername(username);

	if (UserIndex != -1) {
		UserInfo::PrintUserInfoCard(instance->Users[UserIndex]);
		cout << "\n";
	}
	else
		cout << "User with username [" << username << "] was not found.\n";
}
ManageUsers& ManageUsers::getInstance()
{
	if (instance == nullptr)
	{
		instance = new ManageUsers();
		instance->RestoreUsersFromFile();
	}
	return *instance;
}
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


void ManageUsers::SaveChanges() {
	cout << "Saving..." << endl;
	SaveUsers();
	cout << "All changes have been saved successfully.\n";
}


string ManageUsers::ReadUsername(string message) {
	cout << message;
	string UserName = "";
	getline(cin >> ws, UserName);
	return UserName;
}

const vector<UserInfo>& ManageUsers::getUsers()
{
	return Users;
}

void ManageUsers::destroyInstance() {
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

short ManageUsers::GetPositionUserInListByUsernameAndPassword(const UserInfo& user)
{
	return (InputValidatorUtils::IsValidPassword(user.Password) && InputValidatorUtils::IsValidUsername(user.Username)) ? FindUserByUsernameAndPassword(user) : -1;
}

void ManageUsers::EditUserFields(UserInfo& user)
{
	if (ConsoleHelper::AreYouSure("Do you want to edit the username? (Y/N): ")) {
		string username = UserInfo::ReadValidUsername();
		do
		{
			if (FindUserByUsername(username) == -1) {
				user.Username = username;
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
	if (ConsoleHelper::AreYouSure("Do you want to edit the user password? (Y/N): ")) {
		user.ReadPassword();
	}
	if (ConsoleHelper::AreYouSure("Do you want to edit the permissions? (Y/N): ")) {
		user.ReadPermissions();
	}
}
