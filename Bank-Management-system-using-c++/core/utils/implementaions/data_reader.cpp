#include <iostream>
#include "../headers/data_reader.h"
using namespace std;

int DataReader::ReadNumber() {
    int number = 0;               // Variable to store the user input

    cin >> number;                // Read an integer from standard input

    // Loop until a valid integer is entered
    while (cin.fail()) {
        cin.clear();             // Clear the error flag on cin (invalid input)
        // Ignore everything in the input buffer until a newline or max stream size
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid Number, Enter a Valid Number: ";
        cin >> number;           // Try reading input again
    }

    return number;               // Return the valid integer input
}