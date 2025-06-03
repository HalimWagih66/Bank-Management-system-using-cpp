#pragma once
#include <string>
#include <vector>
using namespace std;

class FileOperations
{
public:

	static void SaveRecordInFile(string Record, string FileName);

	static void SaveRecordsInFile(vector<string> vRecords, string FileName);

	static vector<string> RestoreDataFromFile(string FileName);

	FileOperations() = default;
};

