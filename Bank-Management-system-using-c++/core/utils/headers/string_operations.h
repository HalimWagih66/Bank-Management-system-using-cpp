#pragma once
#include <vector>
#include <string>
using namespace std;
enum enWhatToCount
{
	SmallLatters = 0,
	CapitalLatters = 1,
	AllLatters = 2
};
class StringOperations
{
public:
	static vector<string> SplitString(string line, string delim);

	static string ReverceString(string line);

	static string TrimRight(string line);

	static string TrimLeft(string line);

	static string TrimString(string line);

	static bool IsVowel(char ch);

	static void PrintVowels(string line);

	static short CountLowerCaseInString(string line);

	static short CountUpperCaseInString(string line);

	static short CountLatters(string line, enWhatToCount WhatToCount = enWhatToCount::AllLatters);

	static string UpperCaseAllString(string Sentance);

	static void LowerCaseAllString(string& Sentance);

	static char InveringLatter(char latter);

	static void InveringString(string& text);

	static string RemovePauncuations(string text);

	static string ReadString();

	static string ReplaceWordInString(string line, string find, string replace, bool IsMatchCase = true);

	static short CountEachWordInTheString(string line);

	static bool HasUpperCase(const string& word);

	static bool HasLowerCase(const string& word);

	static bool HasSpecialCharacter(const string& word);

	static bool HasNumber(const string& word);

	static bool HasSpace(const string& word);

	static bool IsAlphaNameWithOneDotOrUnderscore(const string& Username);

	static short countNumberInWord(const string& word);

	static bool IsWordAllDigits(const string& word);

	static bool ContainsOnlyLettersAndSpaces(const string& string);


};

