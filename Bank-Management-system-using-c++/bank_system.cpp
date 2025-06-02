#include "bank_system.h"
#include <vector>
#include <string>
#include <iostream>
#include "manage_users.h"
#include "string_operations.h"
#include "data_reader.h"
#include <iomanip>
#include "console_helper.h"
#include "big_number_utils.h"
#include "client_info.h"
#include "file_names.h"
#include "file_operations.h"

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

void BankSystem::SaveClients() {
	vector<string> vRecords;
	for (ClientInfo& ClientInfo : Clients)
	{
		vRecords.push_back(ClientInfo::ConvertClientInfoToRecord(ClientInfo));
	}
	FileOperations::SaveRecordsInFile(vRecords, FileNames::Clients);
}
void BankSystem::RestoreUsersFromFile() {
	vector<string>Records = FileOperations::RestoreDataFromFile(FileNames::Clients);
	for (string Record : Records)
	{
		Clients.push_back(ClientInfo::ConvertRecordToClientInfo(Record));
	}
}
short BankSystem::GetPositionClientByAccountNumber(const string& AccountNumber) {
	short pos = -1;
	for (short i = 0; i < Clients.size(); i++)
	{
		if (Clients[i].AccountNumber == AccountNumber)
		{
			pos = i;
			break;
		}
	}
	return pos;
}

string BankSystem::ReadAccountNumber()
{
	string accountNumber = "";
	do {
		cout << "Please enter Account Number (10 digits): ";
		getline(cin >> ws, accountNumber);

		if (accountNumber.size() != 10 || !(StringOperations::IsWordAllDigits(accountNumber))) {
			cout << "\n[Error] Account number must contain exactly 10 digits and numbers only.\n";
		}

	} while (accountNumber.size() != 10 || !(StringOperations::IsWordAllDigits(accountNumber)));

	return accountNumber;
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

void BankSystem::PrintClients() {
	cout << "\n\n\n";
	cout << "\t\t\t\t\tClient List ( " << Clients.size() << " ) Client(s)" << endl;
	PrintHeaderTable();
	for (ClientInfo client : Clients)
	{
		ClientInfo::PrintClientInfo(client);
	}
	cout << "\n-------------------------------------------------------------------------------------------------------------------" << endl;
}
void BankSystem::PrintHeaderTable() {
	std::cout << "-------------------------------------------------------------------------------------------------------------------" << endl;
	std::cout << " | " << "Account Number" << "   " << " | " << "Pin Code  " << " | Client Name                             " << " | " << "Phone Number           " << "  | Balance" << endl;
	std::cout << "-------------------------------------------------------------------------------------------------------------------" << endl;
}
void BankSystem::PrintResultFind(short pos, string AccountNumber) {
	if (pos != -1)
		ClientInfo::PrintClientCard(Clients[pos]);
	else
		std::cout << "Client With Account Number (" << AccountNumber << ") Not Found!" << endl;
}
short BankSystem::FindClientByAccountNumber() {
	string AccountNumber = ReadAccountNumber();
	short PosIndex = GetPositionClientByAccountNumber(AccountNumber);
	PrintResultFind(PosIndex, AccountNumber);
	return PosIndex;
}
void BankSystem::DeleteClientByAccountNumber() {

	string AccountNumber = ReadAccountNumber();
	short PosIndex = GetPositionClientByAccountNumber(AccountNumber);
	if (PosIndex == -1)
	{
		cout << "Client With Account Number (" << AccountNumber << ") Not Found!" << endl;
	}
	else {
		cout << "The Following are the client details: \n\n";
		ClientInfo::PrintClientCard(Clients[PosIndex]);
		if (ConsoleHelper::AreYouSure("\n\nAre you sure you want delete this client? Y/N ? "))
		{
			Clients.erase(Clients.begin() + PosIndex);
			cout << "\n\n\n";
			cout << "Client Deleted Successfully\n";
		}
		else
		{
			cout << "\nOperation cancelled. No changes were made.\n";
		}
	}
}
void BankSystem::UpdateClientByAccountNumber() {
	short PosIndex = FindClientByAccountNumber();
	if (PosIndex == -1)return;
	char UpdateClient = 'Y';
	cout << "\n\nAre you sure you want update this client? Y/N ? ";
	cin >> UpdateClient;
	cout << "\n\n";
	if (toupper(UpdateClient) == 'Y')
	{
		Clients[PosIndex].UpdateClientInfo();
		cout << "\n\n";
		cout << "Client Updated Successfully\n";
		cout << "\n";
		cout << "Client info after update\n";
		ClientInfo::PrintClientCard(Clients[PosIndex]);
	}
	else
	{
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
	do
	{
		string AccountNumber = ReadAccountNumber();
		PosIndexClient = GetPositionClientByAccountNumber(AccountNumber);
		if (PosIndexClient == -1)
		{
			cout << "Client With [" << AccountNumber << "] does not exist.\n";
		}
	} while (PosIndexClient == -1);
	return PosIndexClient;
}

string BankSystem::GenerateNextAccountNumber() {
	if (Clients.empty()) {
		return "0000000001";  
	}
	string lastAccountNumber = Clients.back().AccountNumber;
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
short BankSystem::GetWithdrawAmount(int balance) {
	cout << "\n\n";
	cout << "Please Enter Withdraw amount? ";
	int amount = DataReader::ReadNumber();
	while (amount < 50 || amount > balance)
	{
		if (amount < 0) {
			cout << "Please Enter positive number : ";
			cout << "Enter Another another amount? ";
			amount = DataReader::ReadNumber();
		}
		else if (amount < 50)
		{
			cout << "Minimum withdrawal amount 50 EG : ";
			cout << "Enter Another another amount? ";
			amount = DataReader::ReadNumber();
		}
		else
		{
			cout << "Amount Exceeds Withdraw amount , you can withdraw up to : " << balance;
			cout << "Enter Another another amount? ";
			amount = DataReader::ReadNumber();
		}
	}
	return balance - amount;
}
void BankSystem::ShowDepositScreen() {
	ConsoleHelper::ShowScreenHeader("Deposit Screen");
	cout << "\n";
	short PosIndexClient = getValidClientPosition();
	ClientInfo::PrintClientCard(Clients[PosIndexClient]);
	short depositAmount = ReadDepositAmount();
	if (ConsoleHelper::AreYouSure("Are you sure want perform this transaction? Y/N ? "))
	{
		Clients[PosIndexClient].AccountBalance += depositAmount;
		cout << "\nDeposit successful.\n";
		cout << "New Balance: " << Clients[PosIndexClient].AccountBalance << " EG\n";
	}
	else
	{
		cout << "Transaction cancelled. No changes were made.\n";
	}
}
void BankSystem::ShowWithdrawScreen() {
	ConsoleHelper::ShowScreenHeader("Withdraw Screen");
	cout << "\n";
	short PosIndexClient = getValidClientPosition();
	ClientInfo::PrintClientCard(Clients[PosIndexClient]);
	short balanceAfterWithdraw = GetWithdrawAmount(Clients[PosIndexClient].AccountBalance);
	if (ConsoleHelper::AreYouSure("Are you sure want perform this transaction? Y/N ? "))
	{
		Clients[PosIndexClient].AccountBalance = balanceAfterWithdraw;
		cout << "\nDone Successfully. Now Balance is : " << Clients[PosIndexClient].AccountBalance << endl;
	}
	else
	{
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
		cout << " | " << left << setw(16) << ClientInfo.AccountNumber << " | " << left << setw(40) << ClientInfo.name << " | " << ClientInfo.AccountBalance << endl;
		TotalSumBalance += ClientInfo.AccountBalance;
	}
	cout << "==================================================================================\n\n";
	cout << "\t\tTotal Balances : " << TotalSumBalance << endl;
}
void BankSystem::PerformTransactionMenuOption(enTransactionMenuOptions TransactionMenuOption) {
	switch (TransactionMenuOption)
	{
	case eDeposit:
		ConsoleHelper::ClearScreen();
		ShowDepositScreen();
		break;
	case eWithdraw:
		ConsoleHelper::ClearScreen();
		ShowWithdrawScreen();
		break;
	case eTotalBalances:
		ConsoleHelper::ClearScreen();
		ShowTotalBalancesScreen();
		cout << "\nPress any key to return to Transaction menu...";
		system("pause>nul");
		break;
	case MainMenu:
		ConsoleHelper::ClearScreen();
		return;
	default:
		cout << "Invalid Choice! Please choose [1-4]\n";
		cout << "Press any key to return to main menu...";
		system("pause>nul");
		break;
	}
}
void BankSystem::ShowTransactionScreen() {
	short Choice = 0;
	do
	{
		ConsoleHelper::ShowScreenHeader("Transactions Menu Screen");
		ShowTransactionMenu();
		cout << "\n==================================================\n\n";
		Choice = ReadTransactionMenuOptions();
		PerformTransactionMenuOption((enTransactionMenuOptions)Choice);
		ConsoleHelper::ClearScreen();
	} while (Choice != 4);
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
void BankSystem::ShowMainMenu() {
	short MainMenuOption = 0;
	do
	{
		ConsoleHelper::ClearScreen();
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

		MainMenuOption = ReadMainMenuOption();
		if (MainMenuOption == 9)return;
		PerformMainMenuOption((enMainMenuOptions)MainMenuOption);
	} while (true);
}



