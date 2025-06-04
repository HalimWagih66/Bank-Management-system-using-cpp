#include "bank_system.h"
#include <vector>
#include <string>
#include <iostream>
#include "models/client_info.h"
#include "../../core/utils/headers/file_operations.h"
#include "../../core/constants/file_pathes.h"
#include "../../core/utils/headers/string_operations.h"
#include "../../core/utils/headers/console_helper.h"
#include "../../core/utils/headers/data_reader.h"
#include "../../core/utils/headers/big_number_utils.h"
#include <iomanip>
#include "../manage users/manage_users.h"
#include "../auth manager/auth_manager.h"
#include "../manage users/models/user_info.h"


BankSystem* BankSystem::instance = nullptr;

BankSystem::BankSystem() {
	RestoreUsersFromFile();
}
BankSystem::~BankSystem() {
	SaveClients();
}
BankSystem& BankSystem::getInstance() {
	if (instance == nullptr)
	{
		instance = new BankSystem();
	}
	return *instance;
}

void BankSystem::destroyInstance() {
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

// Saves the current list of clients to a file.
void BankSystem::SaveClients() {
	// Create a vector to hold string representations of each client's data
	vector<string> vRecords;

	// Convert each ClientInfo object into a string record and store it in the vector
	for (ClientInfo& ClientInfo : Clients)
	{
		// Use a static method to convert the client info to a savable string format
		vRecords.push_back(ClientInfo::ConvertClientInfoToRecord(ClientInfo));
	}

	// Save all the client records to the file designated for client data
	FileOperations::SaveRecordsInFile(vRecords, FilePathes::Clients);
}
// Restores the list of clients from the saved file.
void BankSystem::RestoreUsersFromFile() {
	// Read all the client records from the file as strings
	vector<string> Records = FileOperations::RestoreDataFromFile(FilePathes::Clients);

	// Convert each string record back into a ClientInfo object and add it to the Clients vector
	for (string Record : Records)
	{
		Clients.push_back(ClientInfo::ConvertRecordToClientInfo(Record));
	}
}
// Returns the index (position) of the client with the given account number.
// If the account number is not found, returns -1.
short BankSystem::GetPositionClientByAccountNumber(const string& AccountNumber) {
	short pos = -1;

	// Loop through the list of clients to find a match
	for (short i = 0; i < Clients.size(); i++)
	{
		// Check if the current client's account number matches the given one
		if (Clients[i].getAccountNumber() == AccountNumber)
		{
			pos = i; // Save the position
			break;   // Exit the loop once found
		}
	}

	return pos; // Return the position, or -1 if not found
}

// Reads and validates an account number from user input.
// The account number must be exactly 10 digits and consist of numbers only.
string BankSystem::ReadAccountNumber()
{
	string accountNumber = "";

	do {
		// Prompt the user to enter an account number
		cout << "Please enter Account Number (10 digits): ";
		getline(cin >> ws, accountNumber); // Read the input, ignoring leading whitespace

		// Validate the input: check if it's 10 digits and all numeric
		if (accountNumber.size() != 10 || !(StringOperations::IsWordAllDigits(accountNumber))) {
			cout << "\n[Error] Account number must contain exactly 10 digits and numbers only.\n";
		}

	} while (accountNumber.size() != 10 || !(StringOperations::IsWordAllDigits(accountNumber))); // Repeat until valid input

	return accountNumber; // Return the validated account number
}

// Add a new client with an auto-generate unique account number 
void BankSystem::AddNewClient() {
	// Generate next available account number
	string accountNumber = GenerateNextAccountNumber();

	// Create a new client and read their data using the genereated account number
	ClientInfo client;
	client.ReadClientInfo(accountNumber);

	// Add the new client to the list of existing clients
	Clients.push_back(client);
}


// This function allows adding multiple new clients to the bank system.
// It keeps prompting the user to add more clients until they choose not to.
void BankSystem::AddNewClients() {
	char AddMore = 'Y'; // User input to decide whether to continue adding clients

	do {
		cout << "Adding New Clients:\n\n";

		AddNewClient(); // Add a single client using helper function

		// Ask user if they want to add another client
		cout << "\nClient Added Successfully, do you want to add more client Y/N? ";
		cin >> AddMore;

	} while (toupper(AddMore) == 'Y'); // Continue if user enters 'Y' or 'y'
}

// Prints the list of all clients in a formatted table view
void BankSystem::PrintClients() {
	// Add some vertical spacing before the table
	cout << "\n\n\n";

	// Print the title of the client list with the total number of clients
	cout << "\t\t\t\t\tClient List ( " << Clients.size() << " ) Client(s)" << endl;

	// Print the table header
	PrintHeaderTable();

	// Loop through the vector of clients and print each one
	for (ClientInfo client : Clients)
	{
		ClientInfo::PrintClientInfo(client); // Print client details
	}

	// Print a footer line at the end of the table
	cout << "\n-------------------------------------------------------------------------------------------------------------------" << endl;
}
void BankSystem::PrintHeaderTable() {
	std::cout << "-------------------------------------------------------------------------------------------------------------------" << endl;
	std::cout << " | " << "Account Number" << "   " << " | " << "Pin Code  " << " | Client Name                             " << " | " << "Phone Number           " << "  | Balance" << endl;
	std::cout << "-------------------------------------------------------------------------------------------------------------------" << endl;
}
// Prints the result of searching for a client by account number.
// If the client is found (pos != -1), their full information card is displayed.
// Otherwise, an error message is shown.
void BankSystem::PrintResultFind(short pos, string AccountNumber) {
	if (pos != -1)
		ClientInfo::PrintClientCard(Clients[pos]); // Display client information card
	else
		std::cout << "Client With Account Number (" << AccountNumber << ") Not Found!" << endl;
}
short BankSystem::FindClientByAccountNumber() {
	// Prompt the user to enter an account number
	string AccountNumber = ReadAccountNumber();

	// Find the position (index) of the client with that account number
	short PosIndex = GetPositionClientByAccountNumber(AccountNumber);

	// Display the result of the search to the user
	PrintResultFind(PosIndex, AccountNumber);

	// Return the position of the client (or -1 if not found)
	return PosIndex;
}
// Deletes a client from the system using their account number.
// Asks for confirmation before deletion and handles cases where the client is not found.
void BankSystem::DeleteClientByAccountNumber() {

	// Prompt user to enter a valid account number
	string AccountNumber = ReadAccountNumber();

	// Get the position of the client in the Clients vector
	short PosIndex = GetPositionClientByAccountNumber(AccountNumber);

	// If the account number is not found, inform the user
	if (PosIndex == -1)
	{
		cout << "Client With Account Number (" << AccountNumber << ") Not Found!" << endl;
	}
	else {
		// Display the client's details before deletion
		cout << "The Following are the client details: \n\n";
		ClientInfo::PrintClientCard(Clients[PosIndex]);

		// Confirm the deletion with the user
		if (ConsoleHelper::AreYouSure("\n\nAre you sure you want delete this client? Y/N ? "))
		{
			// Delete the client from the list
			Clients.erase(Clients.begin() + PosIndex);

			// Notify the user of successful deletion
			cout << "\n\n\n";
			cout << "Client Deleted Successfully\n";
		}
		else
		{
			// Notify that the operation was cancelled
			cout << "\nOperation cancelled. No changes were made.\n";
		}
	}
}

// Updates a client's information by searching with their account number.
// Asks for confirmation before making changes.
void BankSystem::UpdateClientByAccountNumber() {
	// Attempt to find the client and get their index
	short PosIndex = FindClientByAccountNumber();

	// If not found, exit the function
	if (PosIndex == -1) return;

	// Ask the user for confirmation before updating
	char UpdateClient = 'Y';
	cout << "\n\nAre you sure you want update this client? Y/N ? ";
	cin >> UpdateClient;
	cout << "\n\n";

	// If user confirms update
	if (toupper(UpdateClient) == 'Y')
	{
		// Call method to update the client's information
		Clients[PosIndex].UpdateClientInfo();

		// Notify the user of success and show updated client info
		cout << "\n\n";
		cout << "Client Updated Successfully\n";
		cout << "\n";
		cout << "Client info after update\n";
		ClientInfo::PrintClientCard(Clients[PosIndex]);
	}
	else
	{
		// User cancelled the update operation
		cout << "Update cancelled. No changes were made.\n";
	}
}
void BankSystem::ShowEndScreen() {
	ConsoleHelper::ShowScreenHeader("Program End");
}
void BankSystem::SaveClientsChanges() {
	ConsoleHelper::ShowScreenHeader("Save Clienst Changes Screen");

	cout << "Saving..." << endl;
	SaveClients();
	cout << "All changes have been saved successfully.\n";
}

short BankSystem::ReadMainMenuOption() {
	cout << "Choose an option [1-9]: ";
	return DataReader::ReadNumber();
}
void BankSystem::GoBackToMainMenu() {
	cout << "\n\n";
	cout << "\nPress any key to return to main menu...";
	system("pause>nul");
}
void BankSystem::ShowAllClientsScreen() {
	// Display the screen header with the title "Show All Clients Screen"
	ConsoleHelper::ShowScreenHeader("Show All Clients Screen");

	// Call the function to print the list of all clients
	PrintClients();
}
void BankSystem::ShowAddNewClientsScreen() {
	ConsoleHelper::ShowScreenHeader("Show Add New Clients Screen");
	AddNewClients();
}
void BankSystem::ShowDeleteClientScreen() {
	ConsoleHelper::ShowScreenHeader("Show Delete Client");
	DeleteClientByAccountNumber();
}
void BankSystem::ShowUpdateClientScreen() {
	ConsoleHelper::ShowScreenHeader("Show Update Client Screen");
	UpdateClientByAccountNumber();
}
void BankSystem::ShowFindClientScreen() {
	ConsoleHelper::ShowScreenHeader("Show Find Client Screen");
	FindClientByAccountNumber();
}
void BankSystem::ShowTransactionMenu() {
	cout << "\t[1] Desposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balances.\n";
	cout << "\t[4] Main Menu.\n";
}
short BankSystem::ReadTransactionMenuOptions() {
	cout << "Choose what do you want to do? [1 to 4]? ";
	return DataReader::ReadNumber();
}
short BankSystem::getValidClientPosition() {
	short PosIndexClient = 0;

	do {
		// Prompt the user to enter a valid account number
		string AccountNumber = ReadAccountNumber();

		// Get the index (position) of the client with the entered account number
		PosIndexClient = GetPositionClientByAccountNumber(AccountNumber);

		// If no client is found with the entered account number, show an error message
		if (PosIndexClient == -1) {
			cout << "Client With [" << AccountNumber << "] does not exist.\n";
		}

	} while (PosIndexClient == -1); // Repeat until a valid client is found

	return PosIndexClient; // Return the valid client's index
}

string BankSystem::GenerateNextAccountNumber() {
	// If there are no clients in the system, start from the first account number
	if (Clients.empty()) {
		return "0000000001";
	}

	// Get the last client's account number (assuming the list is ordered by creation)
	string lastAccountNumber = Clients.back().getAccountNumber();

	// Increment the account number by 1 while preserving formatting (e.g., leading zeros)
	return BigNumberUtils::IncrementOneNumber(lastAccountNumber);
}
bool BankSystem::ClientExistsByAccountNumber(const string& AccountNumber) {
	if (GetPositionClientByAccountNumber(AccountNumber) != -1)
		return true;
	else
		return false;
}

short BankSystem::ReadDepositAmount() {
	cout << "\n\n";
	cout << "Please Enter deposit amount? ";
	return DataReader::ReadNumber();
}
// Reads a valid withdrawal amount from the user, ensuring it's within allowed limits.
// Returns the remaining balance after withdrawal (balance - amount).
short BankSystem::GetWithdrawAmount(int balance) {
	cout << "\n\n";
	cout << "Please Enter Withdraw amount? ";

	// Read the initial amount to withdraw
	int amount = DataReader::ReadNumber();

	// Loop until a valid amount is entered
	while (amount < 50 || amount > balance)
	{
		if (amount < 0) {
			// Negative amount is invalid
			cout << "Please Enter positive number : ";
			cout << "Enter Another amount? ";
			amount = DataReader::ReadNumber();
		}
		else if (amount < 50)
		{
			// Minimum withdrawal limit is 50 EG
			cout << "Minimum withdrawal amount 50 EG : ";
			cout << "Enter Another amount? ";
			amount = DataReader::ReadNumber();
		}
		else
		{
			// Withdrawal amount cannot exceed current balance
			cout << "Amount Exceeds Withdraw amount, you can withdraw up to: " << balance << "\n";
			cout << "Enter Another amount? ";
			amount = DataReader::ReadNumber();
		}
	}

	// Return the balance after deducting the withdrawal amount
	return balance - amount;
}
// Displays the deposit screen and processes a deposit transaction for a client.
void BankSystem::ShowDepositScreen() {
	// Show a header for the deposit screen
	ConsoleHelper::ShowScreenHeader("Deposit Screen");
	cout << "\n";

	// Get the valid position (index) of the client to deposit to
	short PosIndexClient = getValidClientPosition();

	// Display the client's information card before the transaction
	ClientInfo::PrintClientCard(Clients[PosIndexClient]);

	// Read the amount the user wants to deposit
	short depositAmount = ReadDepositAmount();

	// Confirm the transaction with the user
	if (ConsoleHelper::AreYouSure("Are you sure want perform this transaction? Y/N ? "))
	{
		// Perform the deposit by adding to the client's balance
		Clients[PosIndexClient].setAccountBalance(Clients[PosIndexClient].getAccountBalance() + depositAmount);

		// Inform the user of success and show the new balance
		cout << "\nDeposit successful.\n";
		cout << "New Balance: " << Clients[PosIndexClient].getAccountBalance() << " EG\n";
	}
	else
	{
		// User cancelled the transaction
		cout << "Transaction cancelled. No changes were made.\n";
	}
}
void BankSystem::ShowWithdrawScreen() {
	// Display the header for the Withdraw Screen
	ConsoleHelper::ShowScreenHeader("Withdraw Screen");
	cout << "\n";

	// Get the valid index of the client who wants to withdraw
	short PosIndexClient = getValidClientPosition();

	// Print the client's information card
	ClientInfo::PrintClientCard(Clients[PosIndexClient]);

	// Ask the user for the withdrawal amount and calculate the new balance
	short balanceAfterWithdraw = GetWithdrawAmount(Clients[PosIndexClient].getAccountBalance());

	// Confirm the transaction with the user
	if (ConsoleHelper::AreYouSure("Are you sure want perform this transaction? Y/N ? ")) {
		// If confirmed, update the client's account balance
		Clients[PosIndexClient].setAccountBalance(balanceAfterWithdraw);
		cout << "\nDone Successfully. Now Balance is : " << Clients[PosIndexClient].getAccountBalance() << endl;
	}
	else {
		// If not confirmed, cancel the transaction
		cout << "Transaction cancelled. No changes were made.\n";
	}
}
void BankSystem::ShowTotalBalancesScreenHeader() {
	cout << "\t\tBalances List (" << Clients.size() << " Client (s)" << endl;
	cout << "==================================================================================" << endl;
	cout << " | " << left << setw(16) << "Account Number" << " | " << left << setw(40) << "Client Name" << " | " << "Balance" << endl;
	cout << "==================================================================================" << endl;
}

void BankSystem::ShowTotalBalancesScreen() {
	ShowTotalBalancesScreenHeader();
	int TotalSumBalance = 0;
	for (const ClientInfo& ClientInfo : Clients)
	{
		cout << " | " << left << setw(16) << ClientInfo.getAccountNumber() << " | " << left << setw(40) << ClientInfo.getName() << " | " << ClientInfo.getAccountBalance() << endl;
		TotalSumBalance += ClientInfo.getAccountBalance();
	}
	cout << "==================================================================================\n\n";
	cout << "\t\tTotal Balances : " << TotalSumBalance << endl;
}
// Executes the selected transaction menu option.
void BankSystem::PerformTransactionMenuOption(enTransactionMenuOptions TransactionMenuOption) {
	switch (TransactionMenuOption)
	{
	case eDeposit:
		// Clear screen and show deposit screen
		ConsoleHelper::ClearScreen();
		ShowDepositScreen();
		break;

	case eWithdraw:
		// Clear screen and show withdraw screen
		ConsoleHelper::ClearScreen();
		ShowWithdrawScreen();
		break;

	case eTotalBalances:
		// Clear screen, show total balances, and wait for user input before returning
		ConsoleHelper::ClearScreen();
		ShowTotalBalancesScreen();
		cout << "\nPress any key to return to Transaction menu...";
		system("pause>nul");  // Pause without showing message
		break;

	case MainMenu:
		// Clear screen and return to main menu (exit this function)
		ConsoleHelper::ClearScreen();
		return;

	default:
		// Handle invalid menu options gracefully
		cout << "Invalid Choice! Please choose [1-4]\n";
		cout << "Press any key to return to Transaction menu...";
		system("pause>nul");
		break;
	}
}
// Displays the transactions menu and processes user choices until they choose to exit.
void BankSystem::ShowTransactionScreen() {
	short Choice = 0;

	do
	{
		// Display a header for the transaction menu screen
		ConsoleHelper::ShowScreenHeader("Transactions Menu Screen");

		// Show the list of transaction options
		ShowTransactionMenu();

		// Separator for better readability
		cout << "\n==================================================\n\n";

		// Read the user's choice from the transaction menu
		Choice = ReadTransactionMenuOptions();

		// Perform the selected transaction operation
		PerformTransactionMenuOption((enTransactionMenuOptions)Choice);

		// Clear the screen before showing the menu again (except on exit)
		ConsoleHelper::ClearScreen();

	} while (Choice != 4); // Exit when user selects option 4
}

void BankSystem::ShowAccessDeniedMessage() {
	std::cout << "\n\n---------------------------------------------\n";
	std::cout << "Access Denied,\n";
	std::cout << "You Don't Have Permission To Do This,\n";
	std::cout << "Please Contact Your Admin\n";
	std::cout << "---------------------------------------------\n";
	cout << "Press any key to return to the Main menu...";
	system("pause>nul");
}

void BankSystem::PerformMainMenuOption(enMainMenuOptions MainMenuOptions) {
	// Get the singleton instance of ManageUsers
	ManageUsers& manageUsers = ManageUsers::getInstance();

	// Get the singleton instance of AuthManager
	AuthManager& authManager = AuthManager::getInstance();

	// Clear the console screen before continuing
	ConsoleHelper::ClearScreen();

	// Check if the currently logged-in user has permission to access the requested menu option
	// Also allow access if the option is Logout (everyone can logout)
	if (!UserInfo::HasPermission(authManager.getUserLogged(), MainMenuOptions) && MainMenuOptions != enMainMenuOptions::eLogout) {
		// If permission is denied, show an access denied message and exit the function
		ShowAccessDeniedMessage();
		return;
	}

	switch (MainMenuOptions)
	{
	case eListClients:
		ConsoleHelper::ClearScreen();
		ShowAllClientsScreen();
		GoBackToMainMenu();
		break;
	case eAddNewClients:
		ConsoleHelper::ClearScreen();
		ShowAddNewClientsScreen();
		GoBackToMainMenu();
		break;
	case eDeleteClients:
		ConsoleHelper::ClearScreen();
		ShowDeleteClientScreen();
		GoBackToMainMenu();
		break;
	case eUpdateClient:
		ConsoleHelper::ClearScreen();
		ShowUpdateClientScreen();
		GoBackToMainMenu();
		break;
	case eFindClient:
		ConsoleHelper::ClearScreen();
		ShowFindClientScreen();
		GoBackToMainMenu();
		break;
	case eTransaction:
		ConsoleHelper::ClearScreen();
		ShowTransactionScreen();
		ConsoleHelper::ClearScreen();
		break;
	case eSaveChanges:
		ConsoleHelper::ClearScreen();
		SaveClientsChanges();
		GoBackToMainMenu();
		break;
	case eManageUsers:
		ConsoleHelper::ClearScreen();
		manageUsers.ShowManageUsersScreen();
		//GoBackToMainMenu();
		break;
	case eLogout:
		ConsoleHelper::ClearScreen();
		return;
	default:
		ConsoleHelper::ClearScreen();
		cout << "Invalid Choice! Please choose [1-9]\n\n";
		cout << "Press any key to return to main menu...";
		system("pause>nul");
		break;
	}
}
// Displays the main menu and handles navigation based on user input.
void BankSystem::ShowMainMenu() {
	short MainMenuOption = 0;

	do
	{
		// Clear the console screen for a clean menu display
		ConsoleHelper::ClearScreen();

		// Display the main menu options
		cout << "\n=============================================================\n";
		cout << "\t\t\tBank Management System\n";
		cout << "=============================================================\n";
		cout << " [1] Show All Clients\n";
		cout << " [2] Add New Clients\n";
		cout << " [3] Update Clients\n";
		cout << " [4] Delete Clients\n";
		cout << " [5] Find Client\n";
		cout << " [6] Transactions\n";
		cout << " [7] Save Users Changes\n";
		cout << " [8] Manage Users\n";
		cout << " [9] Logout\n";
		cout << "=============================================================\n";

		// Read the user's choice from the menu
		MainMenuOption = ReadMainMenuOption();

		// If user chose to logout, exit the menu loop
		if (MainMenuOption == 9) return;

		// Perform the operation based on the selected menu option
		PerformMainMenuOption((enMainMenuOptions)MainMenuOption);

	} while (true); // Keep showing the menu until user chooses to logout
}



