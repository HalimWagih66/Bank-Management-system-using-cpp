#pragma once
#include <string>
using namespace std;
class ClientInfo {
public:

	string AccountNumber;
	string PinCode;
	string name;
	string PhoneNumber;
	int AccountBalance;

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



