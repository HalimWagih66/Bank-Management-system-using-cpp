#pragma once
#include <string>
#include <vector>
using namespace std;
class UserInfo
{
private:
	string Username;
	string Password;
	short Permissions;
public:
	UserInfo() {
		Username = "";
		Password = "";
		Permissions = 0;
	}

	UserInfo(string username, string password, short permissions) {
		Username = username;
		Password = password;
		Permissions = permissions;
	}

	void SetUsername(const string& username) {
		Username = username;
	}

	void SetPassword(const string& password) {
		Password = password;
	}

	void SetPermissions(const short& permissions) {
		Permissions = permissions;
	}

	string GetUsername() const {
		return Username;
	}

	string GetPassword() const {
		return Password;
	}

	short GetPermissions() const {
		return Permissions;
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

	void ReadFullInfoUser(const string& UserName);

	void EditPassword();

	void EditPermissions();

	short CollectPermissionFlags();

	static bool HasPermission(const UserInfo& userLogged, short selectedOptionFromMainMenu);

	static string ReadValidUsername();
};

