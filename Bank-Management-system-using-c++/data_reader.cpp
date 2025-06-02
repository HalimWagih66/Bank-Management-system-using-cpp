#include "data_reader.h"
#include <iostream>
using namespace std;

int DataReader::ReadNumber() {
	short number = 0;
	cin >> number;
	while (cin.fail()) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid Number , Enter a Valid Number : ";
		cin >> number;
	}
	return number;
}