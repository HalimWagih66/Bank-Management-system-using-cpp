#pragma once
#include <vector>
#include "models/client_info.h"

using namespace std;
enum enMainMenuOptions
{
	eListClients = 1, eAddNewClients = 2, eUpdateClient = 3, eDeleteClients = 4, eFindClient = 5, eTransaction = 6, eSaveChanges = 7, eManageUsers = 8, eLogout = 9
};
enum enTransactionMenuOptions
{
	eDeposit = 1, eWithdraw, eTotalBalances, MainMenu
};

class BankSystem
{
private:
	vector<ClientInfo> Clients;

	static BankSystem* instance;

	void SaveClients();

	void RestoreClientsFromFile();

	void PrintHeaderTable();

	void PrintResultFind(short pos, string AccountNumber);

	short GetPositionClientByAccountNumber(const string& AccountNumber);
	
	string ReadAccountNumber();

	bool ClientExistsByAccountNumber(const string& AccountNumber);

	BankSystem();

public:
	~BankSystem();

	static BankSystem& getInstance();

	void AddNewClient();

	void AddNewClients();

	void PrintClients();

	short FindClientByAccountNumber();

	void DeleteClientByAccountNumber();

	void UpdateClientByAccountNumber();

	void ShowEndScreen();

	void SaveClientsChanges();

	short ReadMainMenuOption();

	void GoBackToMainMenu();

	void ShowAllClientsScreen();

	void ShowAddNewClientsScreen();

	void ShowDeleteClientScreen();

	void ShowUpdateClientScreen();

	void ShowFindClientScreen();

	void ShowTransactionMenu();

	short ReadTransactionMenuOptions();

	short getValidClientPosition();

	short ReadDepositAmount();

	short GetWithdrawAmount(int balance);

	void ShowDepositScreen();

	void ShowWithdrawScreen();

	void ShowTotalBalancesScreenHeader();

	void ShowTotalBalancesScreen();

	void PerformTransactionMenuOption(enTransactionMenuOptions TransactionMenuOption);

	void ShowTransactionScreen();

	void PerformMainMenuOption(enMainMenuOptions MainMenuOptions);

	void ShowMainMenu();

	void ShowAccessDeniedMessage();

	void destroyInstance();

	string GenerateNextAccountNumber();
};

