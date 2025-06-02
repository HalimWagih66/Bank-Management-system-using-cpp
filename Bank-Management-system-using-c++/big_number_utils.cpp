#include "big_number_utils.h"

string BigNumberUtils::IncrementOneNumber(string number)
{
	int sizeString = number.size();
	for (int i = sizeString - 1; i >= 0; i--)
	{
		if (number[i] <= '8') {
			number[i] += 1;
			return number;
		}
		else
			number[i] = '0';
	}
	return "1" + number;
}
