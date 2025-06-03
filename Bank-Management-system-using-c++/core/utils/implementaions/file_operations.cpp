#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "../headers/file_operations.h"
using namespace std;
// Saves a single record (string) into a file specified by FileName.
// Opens the file in output mode (overwrites existing content).
// If unable to open the file, prints a warning message.
void FileOperations::SaveRecordInFile(string Record, string FileName) {
	fstream file;
	file.open(FileName, ios::out);
	if (file.is_open())
	{
		file << Record << "\n";  // Write the record followed by a newline
		file.close();             // Close the file to save changes
	}
	else
	{
		cout << "Warning: Unable to open file: " << FileName << endl;
	}
}

// Saves multiple records (vector of strings) into the specified file.
// Each record is written on a new line.
// The file is opened in output mode, overwriting any existing content.
// If the file can't be opened, a warning is shown.
void FileOperations::SaveRecordsInFile(vector<string> vRecords, string FileName) {
	fstream file;
	file.open(FileName, ios::out);
	if (file.is_open())
	{
		for (string Record : vRecords)
		{
			file << Record << "\n";  // Write each record on a separate line
		}
		file.close();  // Close the file after writing all records
	}
	else
	{
		cout << "Warning: Unable to open file: " << FileName << endl;
	}
}

// Reads all lines (records) from the specified file and returns them as a vector of strings.
// Opens the file in input mode. If the file can't be opened, prints a warning and returns empty vector.
vector<string> FileOperations::RestoreDataFromFile(string FileName) {
	fstream file;
	vector<string> vContentFile;
	file.open(FileName, ios::in);
	if (file.is_open())
	{
		string Record = "";
		while (getline(file, Record)) {
			vContentFile.push_back(Record);  // Add each line read to the vector
		}
		file.close();
	}
	else
	{
		cout << "Warning: Unable to open file: " << FileName << endl;
	}
	return vContentFile;  // Return the vector of file lines (records)
}