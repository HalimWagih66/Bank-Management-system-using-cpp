#pragma once
#include <string>
using namespace std;
class DataReader
{
public:
	static int ReadNumber();

	static string PromptAndReadLine(const string message);

	static int PromptAndReadNumber(const string message);
};