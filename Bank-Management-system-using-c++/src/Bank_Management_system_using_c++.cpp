#include <iostream>
#include "../features/auth manager/auth_manager.h"
using namespace std;

int main() {
	AuthManager::getInstance().ShowLoginScreen();
	return 0;
}