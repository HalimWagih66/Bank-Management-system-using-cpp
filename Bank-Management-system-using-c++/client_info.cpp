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
// Converts a ClientInfo object into a string record with fields separated by 'seperate' string
string ClientInfo::ConvertClientInfoToRecord(const ClientInfo& ClientInfo, string seperate) {
    string stClientRecord = "";
    stClientRecord += ClientInfo.AccountNumber + seperate;
    stClientRecord += ClientInfo.PinCode + seperate;
    stClientRecord += ClientInfo.name + seperate;
    stClientRecord += ClientInfo.PhoneNumber + seperate;
    stClientRecord += to_string(ClientInfo.AccountBalance);
    return stClientRecord;
}

// Prints client information in a formatted single line
void ClientInfo::PrintClientInfo(const ClientInfo& ClientInfo) {
    cout << left
        << " |  " << setw(16) << ClientInfo.AccountNumber
        << " | " << setw(10) << ClientInfo.PinCode
        << " | " << setw(40) << ClientInfo.name
        << " | " << setw(24) << ClientInfo.PhoneNumber
        << " | " << ClientInfo.AccountBalance << endl;
}

// Converts a string record back into a ClientInfo object by splitting the record using "#//#" delimiter
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
        // If conversion fails, default account balance to 0
        client.AccountBalance = 0;
    }
    return client;
}

// Prints detailed client info card to console
void ClientInfo::PrintClientCard(const ClientInfo& Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "\nAccount Number: " << Client.AccountNumber;
    cout << "\nPin Code: " << Client.PinCode;
    cout << "\nName: " << Client.name;
    cout << "\nPhone: " << Client.PhoneNumber;
    cout << "\nAccount Balance: " << Client.AccountBalance;
}

// Reads all client info fields from user input
void ClientInfo::ReadClientInfo(const string& AccountNum) {
    AccountNumber = AccountNum;           // Assign account number (usually fixed or passed)

    name = ReadValidName();               // Read and validate client name
    cout << "\n";

    PhoneNumber = ReadValidPhoneNumber(); // Read and validate phone number
    cout << "\n";

    PinCode = ReadValidPinCode();         // Read and validate pin code
    cout << "\n";

    AccountBalance = ReadValidAccountBalance(); // Read and validate account balance
    cout << "\n";
}

// Updates certain fields of the client info with user input
void ClientInfo::UpdateClientInfo() {
    name = ReadValidName();
    cout << "\n";
    PinCode = ReadValidPinCode();
    cout << "\n";
    PhoneNumber = ReadValidPhoneNumber();
}

// Prompt repeatedly for a valid name until input passes validation, then return it
string ClientInfo::ReadValidName()
{
    string name = "";

    cout << "Please enter a name: ";
    getline(cin >> ws, name);

    // Loop until name is valid according to InputValidatorUtils
    while (!InputValidatorUtils::IsValidName(name)) {
        cout << "Invalid Name, Please enter a valid Name: ";
        getline(cin >> ws, name);
    }
    return name;
}

// Prompt repeatedly for a valid PIN code (must be exactly 4 or 6 digits), then return it
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

    return pinCode;
}

// Prompt repeatedly for a valid phone number until it passes validation, then return it
string ClientInfo::ReadValidPhoneNumber() {
    string phoneNumber = "";

    cout << "Please enter a Phone Number: ";
    getline(cin >> ws, phoneNumber);

    while (!InputValidatorUtils::IsValidPhoneNumber(phoneNumber)) {
        cout << "Invalid Phone Number, Please enter a valid phone number: ";
        getline(cin >> ws, phoneNumber);
    }
    return phoneNumber;
}

// Prompt user for an account balance >= 100, repeat until valid, then return it
int ClientInfo::ReadValidAccountBalance() {
    int balance = 0;

    cout << "Please Enter an account balance: ";
    cin >> balance;

    while (balance < 100) {
        cout << "Minimum balance you can add is 100 EG\n";
        cout << "Please enter a number of more than 100 EG: ";
        cin >> balance;
    }
    return balance;
}