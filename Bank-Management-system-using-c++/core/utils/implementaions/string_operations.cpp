#include <string>
#include <vector>
#include <array>
#include <cctype>
#include <iostream>
#include <unordered_set>
#include "../headers/string_operations.h"

using namespace std;

// Splits a string by a given delimiter and returns a vector of words
vector<string> StringOperations::SplitString(string line, string delim) {
    short pos = 0;
    string sWord;
    vector<string> vString;

    // Keep splitting while the delimiter is found
    while ((pos = line.find(delim)) != std::string::npos) {
        sWord = line.substr(0, pos);
        if (sWord != "") {
            vString.push_back(sWord);
        }
        line.erase(0, pos + delim.length());
    }

    // Add the remaining part of the string if it's not empty
    if (line != "") {
        vString.push_back(line);
    }

    return vString;
}

// Reverses the order of words in a string
string StringOperations::ReverceString(string line) {
    vector<string> seperate = SplitString(line, " ");
    string RevString = "";
    for (short i = seperate.size() - 1; i != -1; i--) {
        RevString += seperate[i] + " ";
    }
    return RevString;
}

// Removes trailing spaces from the right side of a string
string StringOperations::TrimRight(string line) {
    for (short i = line.length() - 1; i != -1; i--) {
        if (line[i] != ' ')
            return line.substr(0, i + 1);  // include the last non-space character
    }
    return "";
}

// Removes leading spaces from the left side of a string
string StringOperations::TrimLeft(string line) {
    for (short i = 0; i < line.size(); i++) {
        if (line[i] != ' ')
            return line.substr(i);  // return from first non-space
    }
    return "";
}

// Removes both leading and trailing spaces
string StringOperations::TrimString(string line) {
    line = TrimLeft(line);
    line = TrimRight(line);
    return line;
}

// Checks if a character is a vowel (A, E, I, O, U)
bool StringOperations::IsVowel(char ch) {
    const std::array<char, 5> VowelsChars = { 'A','E' , 'I', 'O','U' };
    ch = toupper(ch);
    for (char letter : VowelsChars) {
        if (ch == letter) {
            return true;
        }
    }
    return false;
}

// Prints all vowels found in the input string
void StringOperations::PrintVowels(string line) {
    cout << "Vowels in String are : ";
    for (size_t i = 0; i < line.size(); i++) {
        if (IsVowel(line[i])) {
            cout << line[i] << "  ";
        }
    }
}

// Counts lowercase characters in the string
short StringOperations::CountLowerCaseInString(string line) {
    short CountLowerCase = 0;
    for (size_t i = 0; i < line.size(); i++) {
        if (islower(line[i])) {
            CountLowerCase++;
        }
    }
    return CountLowerCase;
}

// Counts uppercase characters in the string
short StringOperations::CountUpperCaseInString(string line) {
    short CountUpperCase = 0;
    for (size_t i = 0; i < line.size(); i++) {
        if (isupper(line[i])) {
            CountUpperCase++;
        }
    }
    return CountUpperCase;
}

// Counts letters based on the enum value (all, uppercase, lowercase)
short StringOperations::CountLatters(string line, enWhatToCount WhatToCount) {
    if (WhatToCount == enWhatToCount::AllLatters) {
        return line.length();
    }

    short count = 0;
    for (size_t i = 0; i < line.length(); i++) {
        if (WhatToCount == enWhatToCount::SmallLatters && islower(line[i])) {
            count++;
        }
        if (WhatToCount == enWhatToCount::CapitalLatters && isupper(line[i])) {
            count++;
        }
    }
    return count;
}

// Converts the whole string to uppercase
string StringOperations::UpperCaseAllString(string Sentance) {
    for (size_t i = 0; i < Sentance.size(); i++) {
        Sentance[i] = toupper(Sentance[i]);
    }
    return Sentance;
}

// Converts the whole string to lowercase (by reference)
void StringOperations::LowerCaseAllString(string& Sentance) {
    for (size_t i = 0; i < Sentance.size(); i++) {
        Sentance[i] = tolower(Sentance[i]);
    }
}

// Inverts the case of a character (uppercase to lowercase or vice versa)
char StringOperations::InveringLatter(char latter) {
    return isupper(latter) ? tolower(latter) : toupper(latter);
}

// Inverts the case of all characters in a string (by reference)
void StringOperations::InveringString(string& text) {
    for (size_t i = 0; i < text.size(); i++) {
        text[i] = InveringLatter(text[i]);
    }
}

// Removes punctuation characters from a string
string StringOperations::RemovePauncuations(string text) {
    string S2 = "";
    for (size_t i = 0; i < text.size(); i++) {
        if (!ispunct(text[i])) {
            S2.push_back(text[i]);
        }
    }
    return S2;
}

// Replaces all matching words in a string with another word (case sensitive or insensitive)
string StringOperations::ReplaceWordInString(string line, string find, string replace, bool IsMatchCase) {
    vector<string> separate = SplitString(line, " ");
    string lineAfterReplace = "";

    for (string& word : separate) {
        if (IsMatchCase) {
            lineAfterReplace += (word == find ? replace : word) + " ";
        }
        else {
            lineAfterReplace += (UpperCaseAllString(word) == UpperCaseAllString(find) ? replace : word) + " ";
        }
    }

    return lineAfterReplace;
}

// Counts the number of words in a string
short StringOperations::CountEachWordInTheString(string line) {
    string delim = " ";
    short pos = 0;
    short count = 0;
    string sWord;

    while ((pos = line.find(delim)) != std::string::npos) {
        sWord = line.substr(0, pos);
        if (sWord != "") {
            count++;
        }
        line.erase(0, pos + delim.length());
    }

    if (line != "") {
        count++;
    }

    return count;
}

// Checks if the string contains at least one uppercase letter
bool StringOperations::HasUpperCase(const string& word) {
    for (const char& Char : word) {
        if (isupper(Char))
            return true;
    }
    return false;
}

// Checks if the string contains at least one lowercase letter
bool StringOperations::HasLowerCase(const string& word) {
    for (const char& Char : word) {
        if (islower(Char))
            return true;
    }
    return false;
}

// Checks if the string contains at least one special (punctuation) character
bool StringOperations::HasSpecialCharacter(const string& word) {
    for (const char& Char : word) {
        if (ispunct(Char))
            return true;
    }
    return false;
}

// Checks if the string contains at least one numeric digit
bool StringOperations::HasNumber(const string& word) {
    for (const char& Char : word) {
        if (isdigit(Char))
            return true;
    }
    return false;
}

// Checks if the string contains at least one space character
bool StringOperations::HasSpace(const string& word) {
    for (char Char : word) {
        if (isspace(Char))
            return true;
    }
    return false;
}

// Checks if a word contains only letters and at most one dot or underscore
bool StringOperations::IsAlphaNameWithOneDotOrUnderscore(const string& word) {
    short sepCount = 0;

    for (char c : word) {
        if (isalpha(c))
            continue;

        if (c == '.' || c == '_') {
            if (++sepCount > 1)
                return false;
        }
        else {
            return false;
        }
    }

    return true;
}

// Counts how many digits are in a given string
short StringOperations::countNumberInWord(const string& AccountNumber) {
    short count = 0;
    for (char ch : AccountNumber) {
        if (isdigit(ch)) {
            count++;
        }
    }
    return count;
}

// Checks if the entire string consists of digits only
bool StringOperations::IsWordAllDigits(const string& AccountNumber) {
    for (char ch : AccountNumber) {
        if (!isdigit(ch)) {
            return false;
        }
    }
    return !AccountNumber.empty();
}

// Checks if a string contains only alphabetic letters and spaces
bool StringOperations::ContainsOnlyLettersAndSpaces(const string& str) {
    for (char c : str) {
        if (!isalpha(c) && !isspace(c)) {
            return false;
        }
    }
    return true;
}
