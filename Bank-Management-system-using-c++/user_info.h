#pragma once
#include <string>
#include <vector>
using namespace std;
class UserInfo
{
public:
	string Username;
	string Password;
	short Permissions;
	UserInfo() {
		Username = "";
		Password = "";
		Permissions = 0;
	}
	static string ConvertUserToRecord(const UserInfo& userInfo, string seprete = "#//#");

	static UserInfo ConvertRecordToUser(const string& Record, string Seprete = "#//#");

	void ReadUsername();

	void ReadPassword();

	void ReadPermissions();

	static void PrintUserInfoCard(const UserInfo& user);

	static void PrintUserInfoInLine(const UserInfo& user);

	static string PermissionToString(int perm);

	void ReadPasswordAndUsername();

	static string ReadPasswordForSearch();

	static string ReadUsernameForSearch(const string message  = "Please Enter Username : ");

	static UserInfo ReadPassAndUsernameForSearch();

	static bool IsValidPasswordAndUsername(const UserInfo& user);

	void ReadFullInfoUser(string UserName);

	void EditPassword();

	void EditPermissions();

	short CollectPermissionFlags();

	static bool HasPermission(const UserInfo& userLogged, short selectedOptionFromMainMenu);

	static string ReadValidUsername();
};

