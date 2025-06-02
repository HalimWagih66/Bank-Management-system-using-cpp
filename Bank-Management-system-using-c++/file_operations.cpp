#include "file_operations.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
void FileOperations::SaveRecordInFile(string Record, string FileName) {
	fstream file;
	file.open(FileName, ios::out);
	if (file.is_open())
	{
		file << Record << "\n";
		file.close();
	}
	else
	{
		cout << "Warning: Unable to open file: " << FileName << endl;
	}
}
void FileOperations::SaveRecordsInFile(vector<string> vRecords, string FileName) {
	fstream file;
	file.open(FileName, ios::out);
	if (file.is_open())
	{
		for (string Record : vRecords)
		{
			file << Record << "\n";
		}
		file.close();
	}
	else
	{
		cout << "Warning: Unable to open file: " << FileName << endl;
	}
}
vector<string> FileOperations::RestoreDataFromFile(string FileName) {
	fstream file;
	vector<string> vContentFile;
	file.open(FileName, ios::in);
	if (file.is_open())
	{
		string Record = "";
		while (getline(file, Record)) {
			vContentFile.push_back(Record);
		}
		file.close();
	}
	else
	{
		cout << "Warning: Unable to open file: " << FileName << endl;
	}
	return vContentFile;
}