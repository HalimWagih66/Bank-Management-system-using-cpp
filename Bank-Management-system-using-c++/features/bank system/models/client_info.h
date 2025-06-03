#pragma once
#include <string>
using namespace std;
class ClientInfo {

private:
	string AccountNumber;
	string PinCode;
	string name;
	string PhoneNumber;
	int AccountBalance;
public:

	void setAccountNumber(const string& accountNumber) { AccountNumber = accountNumber; }

	void setPinCode(const string& pinCode) { PinCode = pinCode; }

	void setName(const string& name) { this->name = name; }

	void setPhoneNumber(const string& phoneNumber) { PhoneNumber = phoneNumber; }

	void setAccountBalance(int accountBalance) { AccountBalance = accountBalance; }

	string getAccountNumber() const { return AccountNumber; }

	string getPinCode() const { return PinCode; }

	string getName() const { return name; }

	string getPhoneNumber() const { return PhoneNumber; }

	int getAccountBalance() const { return AccountBalance; }

	ClientInfo();

	static string ConvertClientInfoToRecord(const ClientInfo& ClientInfo, string seperate = "#//#");

	static void PrintClientInfo(const ClientInfo& ClientInfo);

	static ClientInfo ConvertRecordToClientInfo(string ClientRecord);

	static void PrintClientCard(const ClientInfo& Client);

	void ReadClientInfo(const string& AccountNum);

	void UpdateClientInfo();

	string ReadValidName();

	string ReadValidPinCode();

	string ReadValidPhoneNumber();

	int ReadValidAccountBalance();
};



