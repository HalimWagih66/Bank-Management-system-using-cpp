#pragma once
#include "user_info.h"
using namespace std;
class AuthManager
{
private:
	UserInfo userLogged;
	static AuthManager* instance;

	AuthManager();
public:

	void ShowLoginScreen();

	void setUserLogged(const UserInfo& user);

	const UserInfo& getUserLogged()const;

	static AuthManager& getInstance();


	void destroyInstance();
};


