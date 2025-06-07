#include "../headers/data_reader.h"
#include <iostream>

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

string DataReader::PromptAndReadLine(const string message)
{
    string input;
    cout << message;
    getline(cin >> ws, input);
    return input;
}
int DataReader::PromptAndReadNumber(const string message)
{
    int number = 0;
    cout << message;
    number = ReadNumber();  // Call ReadNumber to get a valid integer input
    return number;          // Return the valid integer input
}