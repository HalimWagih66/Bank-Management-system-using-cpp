#include "client_info.h"
#include <string>
#include <iostream>
#include <iomanip>
#include "string_operations.h"
#include "input_validator_utils.h"
#include <vector>

ClientInfo::ClientInfo() {
	AccountNumber = "";
	PinCode = "";
	name = "";
	PhoneNumber = "";
	AccountBalance = 0;
}
string ClientInfo::ConvertClientInfoToRecord(const ClientInfo& ClientInfo, string seperate) {
	string stClientRecord = "";
	stClientRecord += ClientInfo.AccountNumber + seperate;
	stClientRecord += ClientInfo.PinCode + seperate;
	stClientRecord += ClientInfo.name + seperate;
	stClientRecord += ClientInfo.PhoneNumber + seperate;
	stClientRecord += to_string(ClientInfo.AccountBalance);
	return stClientRecord;
}
void ClientInfo::PrintClientInfo(const ClientInfo& ClientInfo) {
	cout << left
		<< " |  " << setw(16) << ClientInfo.AccountNumber
		<< " | " << setw(10) << ClientInfo.PinCode
		<< " | " << setw(40) << ClientInfo.name
		<< " | " << setw(24) << ClientInfo.PhoneNumber
		<< " | " << ClientInfo.AccountBalance << endl;
}
ClientInfo ClientInfo::ConvertRecordToClientInfo(string ClientRecord) {
	StringOperations stringOperations;
	vector<string> ClientInfoFromFile = stringOperations.SplitString(ClientRecord, "#//#");
	ClientInfo client;
	client.AccountNumber = ClientInfoFromFile[0];
	client.PinCode = ClientInfoFromFile[1];
	client.name = ClientInfoFromFile[2];
	client.PhoneNumber = ClientInfoFromFile[3];
	try {
		client.AccountBalance = stoi(ClientInfoFromFile[4]);
	}
	catch (...) {
		client.AccountBalance = 0;
	}
	return client;
}
void ClientInfo::PrintClientCard(const ClientInfo& Client)
{
	cout << "\nThe following are the client details:\n";
	cout << "\nAccout Number: " << Client.AccountNumber;
	cout << "\nPin Code : " << Client.PinCode;
	cout << "\nName : " << Client.name;
	cout << "\nPhone : " << Client.PhoneNumber;
	cout << "\nAccount Balance: " << Client.AccountBalance;
}
void ClientInfo::ReadClientInfo(const string& AccountNum) {
	AccountNumber = AccountNum;

	name = ReadValidName();
	cout << "\n";
	PhoneNumber = ReadValidPhoneNumber();
	cout << "\n";

	PinCode = ReadValidPinCode();
	cout << "\n";
	AccountBalance = ReadValidAccountBalance();
	cout << "\n";
}
void ClientInfo::UpdateClientInfo() {
	name = ReadValidName();
	cout << "\n";
	PinCode = ReadValidPinCode();
	cout << "\n";
	PhoneNumber = ReadValidPhoneNumber();
}

// Repeatedly prompts the user to enter a valid name
// until the input passes validation via IsValidName.
// Returns the validated name as a string.
string ClientInfo::ReadValidName()
{
	string name = "";

	cout << "Please enter a name : ";

	getline(cin >> ws, name);

	// Keep asking until a valid name is entered
	while (!InputValidatorUtils::IsValidName(name)) {

		cout << "Invalid Name , Please Enter a valid Name : ";

		getline(cin >> ws, name);
	}
	return name;  // Return the validated name
}

// Repeatedly prompts the user to enter a valid PIN code
// until it matches the expected format (4 or 6 digits).
// Returns the validated PIN code.
string ClientInfo::ReadValidPinCode() {
	string pinCode;

	cout << "Please enter a pin code: ";
	getline(cin >> ws, pinCode);

	while (!InputValidatorUtils::IsValidPinCode(pinCode)) {
		cout << "\nInvalid PIN code.\n";
		cout << "A PIN code must be exactly 4 or 6 digits.\n";
		cout << "Please enter a pin code: ";
		getline(cin >> ws, pinCode);
	}

	return pinCode; // Return the valid PIN code
}

string ClientInfo::ReadValidPhoneNumber() {
	string phoneNumber = "";

	cout << "Please enter a Phone Number: ";
	getline(cin >> ws, phoneNumber);

	while (!InputValidatorUtils::IsValidPhoneNumber(phoneNumber)) {
		cout << "Invalid a Phone Number , Please enter a valid phone number : ";
		getline(cin>>ws,phoneNumber);
	}
	return phoneNumber;
}

int ClientInfo::ReadValidAccountBalance() {
	int balance = 0;

	cout << "Please Enter an account balance : ";
	cin >> balance;
	while (balance < 100) {
		cout <<"minimum balance can you add is 100 EG\n",
		cout<<"Please enter a number of more than 100 EG : ";
		cin >> balance;
	}
	return balance;
}