#include "auth_manager.h"
#include <iostream>
#include "../manage users/models/user_info.h"
#include "../manage users/manage_users.h"
#include "../../core/utils/headers/console_helper.h"
#include "../bank system/bank_system.h"
#include "../../core/system utilities/memory_cleaner.h"

AuthManager* AuthManager::instance = nullptr;

AuthManager::AuthManager() {}

// Sets the currently logged-in user in the singleton instance
void AuthManager::setUserLogged(const UserInfo& user) {
    instance->userLogged = user;
}

// Returns a constant reference to the currently logged-in user
const UserInfo& AuthManager::getUserLogged() const {
    return instance->userLogged;
}

// Returns the singleton instance of AuthManager, creates it if not existing
AuthManager& AuthManager::getInstance() {
    if (instance == nullptr)
    {
        // Create a new instance and initialize userLogged with a default UserInfo object
        instance = new AuthManager();
        instance->userLogged = UserInfo();
    }
    return *instance;
}

// Destroys the singleton instance, freeing memory
void AuthManager::destroyInstance()
{
    if (instance != nullptr)
    {
        delete instance;
        instance = nullptr;
    }
}
 
void AuthManager::ShowLoginScreen() {
    short UserIndex = -2;  // Index of the user in the user list; initialized with an invalid value
    UserInfo user;         // Variable to hold user input (username and password)
    ManageUsers& manageUsers = ManageUsers::getInstance();  // Get the singleton instance managing users

    do
    {
        ConsoleHelper::ShowScreenHeader("Login Screen");  // Display the login screen header

        if (UserIndex == -1) {  // If UserIndex is -1, it means invalid username/password was entered
            cout << "Invalid Username/Password!\n\n";    // Show error message to the user
            ConsoleHelper::PauseAndClearScreen();        // Pause for user to read message, then clear screen
            ConsoleHelper::ShowScreenHeader("Login Screen"); // Re-display login screen header
        }

        user = UserInfo::ReadPassAndUsernameForSearch();  // Read username and password from user input

        // Check if the user exists with the given username and password
        UserIndex = manageUsers.GetPositionUserInListByUsernameAndPassword(user);

        ConsoleHelper::ClearScreen();  // Clear the screen after each attempt
    } while (UserIndex == -1);  // Repeat until valid login credentials are entered

    // Set the logged-in user in the AuthManager singleton
    setUserLogged(manageUsers.getUsers()[UserIndex]);

    // Show the main menu of the bank system after successful login
    BankSystem::getInstance().ShowMainMenu();

    // Clean up any singletons or resources that need releasing
    MemoryCleaner::CleanUpSingleton();
}