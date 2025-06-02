#include "string_operations.h"
#include <string>
#include <vector>
#include <array>
#include <cctype>
#include <iostream>
#include <unordered_set>

vector<string> StringOperations::SplitString(string line, string delim) {
	short pos = 0;
	string sWord;
	vector<string> vString;
	while ((pos = line.find(delim)) != std::string::npos) {
		sWord = line.substr(0, pos);
		if (sWord != "")
		{
			vString.push_back(sWord);
		}
		line.erase(0, pos + delim.length());
	}
	if (line != "")
	{
		vString.push_back(line);
	}
	return vString;
}
string StringOperations::ReverceString(string line) {
	vector<string> seperate = SplitString(line, " ");
	string RevString = "";
	for (short i = seperate.size() - 1; i != -1; i--)
	{
		RevString += seperate[i] + " ";
	}
	return RevString;
}
string StringOperations::TrimRight(string line) {
	for (short i = line.length() - 1; i != -1; i--)
	{
		if (line[i] != ' ')return line.substr(0, i);
	}
}
string StringOperations::TrimLeft(string line) {
	for (short i = 0; i < line.size(); i++)
	{
		if (line[i] != ' ')return line.substr(i, line.length() - 1);
	}
	return line;
}
string StringOperations::TrimString(string line) {
	line = TrimLeft(line);
	line = TrimRight(line);
	return line;
}
bool StringOperations::IsVowel(char ch) {
	const std::array<char, 5> VowelsChars = { 'A','E' , 'I', 'O','U' };
	ch = toupper(ch);
	for (char letter : VowelsChars)
	{
		if (ch == letter)
		{
			return true;
		}
	}
	return false;
}
void StringOperations::PrintVowels(string line) {
	cout << "Vowels in String are : ";
	for (size_t i = 0; i < line.size(); i++)
	{
		if (IsVowel(line[i]))
		{
			cout << line[i] << "  ";
		}
	}
}
short StringOperations::CountLowerCaseInString(string line) {
	short CountLowerCase = 0;
	for (size_t i = 0; i < line.size(); i++)
	{
		if (islower(line[i]))
		{
			CountLowerCase++;
		}
	}
	return CountLowerCase;
}
short StringOperations::CountUpperCaseInString(string line) {
	short CountUpperCase = 0;
	for (size_t i = 0; i < line.size(); i++)
	{
		if (isupper(line[i]))
		{
			CountUpperCase++;
		}
	}
	return CountUpperCase;
}

short StringOperations::CountLatters(string line, enWhatToCount WhatToCount) {
	if (WhatToCount == enWhatToCount::AllLatters)
	{
		return line.length();
	}
	short count = 0;
	for (size_t i = 0; i < line.length(); i++)
	{
		if (WhatToCount == enWhatToCount::SmallLatters && islower(line[i]))
		{
			count++;
		}
		if (WhatToCount == enWhatToCount::CapitalLatters && isupper(line[i]))
		{
			count++;
		}
	}
	return count;
}
string StringOperations::UpperCaseAllString(string Sentance) {
	for (size_t i = 0; i < Sentance.size(); i++)
	{
		Sentance[i] = toupper(Sentance[i]);
	}
	return Sentance;
}
void StringOperations::LowerCaseAllString(string& Sentance) {
	for (size_t i = 0; i < Sentance.size(); i++)
	{
		Sentance[i] = tolower(Sentance[i]);
	}
}
char StringOperations::InveringLatter(char latter) {
	return isupper(latter) ? tolower(latter) : toupper(latter);
}
void StringOperations::InveringString(string& text) {
	for (size_t i = 0; i < text.size(); i++)
	{
		text[i] = InveringLatter(text[i]);
	}
}
string StringOperations::RemovePauncuations(string text) {
	string S2 = "";
	for (size_t i = 0; i < text.size(); i++)
	{
		if (!ispunct(text[i]))
		{
			S2.push_back(text[i]);
		}
	}
	return S2;
}
string StringOperations::ReadString() {
	string line;
	cout << "Please Enter Your String : ";
	getline(cin, line);
	return line;
}
string StringOperations::ReplaceWordInString(string line, string find, string replace, bool IsMatchCase) {
	vector<string> separate = SplitString(line, " ");
	string lineAfterReplace = "";
	string temp = "";
	for (string& word : separate)
	{
		if (IsMatchCase)
		{
			if (word == find)
				lineAfterReplace += replace + " ";
			else
				lineAfterReplace += word + " ";
		}
		else {
			if (UpperCaseAllString(word) == UpperCaseAllString(find))
				lineAfterReplace += replace + " ";
			else
				lineAfterReplace += word + " ";
		}

	}
	return lineAfterReplace.substr(0);
}
short StringOperations::CountEachWordInTheString(string line) {
	string delim = " ";
	short pos = 0;
	short count = 0;
	string sWord;
	while ((pos = line.find(delim)) != std::string::npos) {
		sWord = line.substr(0, pos);
		if (sWord != "")
		{
			count++;
		}
		line.erase(0, pos + delim.length());
	}
	if (line != "")
	{
		count++;
	}
	return count;
}

bool StringOperations::HasUpperCase(const string& word)
{
	for (const char& Char : word)
	{
		if (isupper(Char))
			return true;
	}
	return false;
}

bool StringOperations::HasLowerCase(const string& word)
{
	for (const char& Char : word)
	{
		if (islower(Char))
			return true;
	}
	return false;
}

bool StringOperations::HasSpecialCharacter(const string& word)
{
	for (const char& Char : word)
	{
		if (ispunct(Char))
			return true;
	}
	return false;
}

bool StringOperations::HasNumber(const string& word)
{
	for (const char& Char : word)
	{
		if (isdigit(Char))
			return true;
	}
	return false;
}

bool StringOperations::HasSpace(const string& word)
{
	for (char Char : word)
	{
		if (isspace(Char))
			return true;
	}
	return false;
}
// This function checks if the given word contains only alphabetic characters,
// and allows at most one separator character (either '.' or '_').
// Returns true if the condition is met, otherwise false.
bool StringOperations::IsAlphaNameWithOneDotOrUnderscore(const string& word)
{
	short sepCount = 0; // Counter for separator characters ('.' or '_')
	for (char c : word)
	{
		if (isalpha(c))
			continue; // Accept alphabetic characters

		if (c == '.' || c == '_') {
			if (++sepCount > 1)
				return false; // Reject if more than one separator found
		}
		else
		{
			return false;  // Reject any character that is not a letter or allowed separator
		}
	}
	return true;  // Word is valid if it passes all checks
}

short StringOperations::countNumberInWord(const string& AccountNumber)
{
	short count = 0;
	for (char ch : AccountNumber)
	{
		if (isdigit(ch))
		{
			count++;
		}
	}
	return count;
}
bool StringOperations::IsWordAllDigits(const string& AccountNumber) {
	for (char ch : AccountNumber) {
		if (!isdigit(ch)) {
			return false; 
		}
	}
	return !AccountNumber.empty();
}

bool StringOperations::ContainsOnlyLettersAndSpaces(const string& string)
{
	for (char c : string) {
		if (!isalpha(c) && !isspace(c)) {
			return false;
		}
	}
	return true;
}
