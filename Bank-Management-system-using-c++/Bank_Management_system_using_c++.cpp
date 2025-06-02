#include <iostream>
#include "auth_manager.h"
using namespace std;

int main() {
	AuthManager::getInstance().ShowLoginScreen();
	return 0;
}