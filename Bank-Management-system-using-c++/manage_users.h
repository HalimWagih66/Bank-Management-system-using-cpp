#pragma once
#include <vector>
#include "user_info.h"
using namespace std;
enum eManageUsersMenuOptions
{
	enListUsers = 1, enAddNewUser, enDeleteUser, enUpdateUser, enFindUser, eSaveUsers, enMainMenu
};

class ManageUsers
{
private:

	vector<UserInfo> Users;

	static ManageUsers* instance;

	ManageUsers();

public:

	~ManageUsers();

	void SaveUsers();

	short FindUserByUsername(string UserName);

	short FindUserByUsernameAndPassword(const UserInfo& User);

	void RestoreUsersFromFile();

	void ShowManageUsersScreen();

	short ReadManageUsersMenuOption();

	void PerformManageUsersMenu(eManageUsersMenuOptions ManageUsersMenuOptions);

	void ShowLoginScreen();

	bool IsUserExist(const UserInfo& user);

	void ShowListUsersScreen();

	short GetPositionUserInListByUsername(const string& username);

	void ShowAddNewUsersScreen();

	void ShowDeleteUserScreen();

	void ShowUpdateUserScreen();

	void ShowFindUserScreen();

	void SaveChanges();

	static ManageUsers& getInstance();

	string ReadUsername(string message = "Please Enter Username? ");

	const vector<UserInfo>& getUsers();

	void destroyInstance();

	short GetPositionUserInListByUsernameAndPassword(const UserInfo& user);

	void EditUserFields(UserInfo& user);
};


