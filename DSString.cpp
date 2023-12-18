#include "DSString.h"

DSString::DSString()
{
    data = new char[1];
    data[0] = '\0';
    len = 0;
}

DSString::DSString(const char *givenVariable)
{ // constructor that converts a cstring

    len = strlen(givenVariable);
    data = new char[len + 1];
    strcpy(data, givenVariable);
    data[len] = '\0';
}

DSString::DSString(const DSString &variableClass)
{ // rule of 3 - copy constructor

    len = variableClass.length();
    data = new char[len + 1];
    data[len] = '\0';
    strcpy(data, variableClass.data);
}

DSString::~DSString()
{ // rule of 3 - destructor

    delete[] data;
}

DSString &DSString::operator=(const DSString &variable)
{ // rule of 3 - copy assignment operator

    delete[] data;
    len = variable.length();
    data = new char[len + 1];
    strcpy(data, variable.data);
    return *this;
}

size_t DSString::length() const
{ // finds the length of data

    return len;
}

char &DSString::operator[](size_t index)
{ // returns reference at the given point

    return data[index];
}

DSString DSString::operator+(const DSString &newString) const
{ // combines data and newString

    int i = 0;
    int dataSize = length();
    int size = length() + newString.length();
    int startingPoint = dataSize + 1;
    char *combination = new char[size + 1];
    while (data[i] != '\0')
    {
        combination[i] = data[i];
    }
    for (int s = startingPoint; s < size; s++)
    {
        combination[s] = newString.data[s - startingPoint];
    }
    combination[size] = '\0';
    DSString temp = combination;
    delete[] combination;
    return temp;
}

bool DSString::operator==(const DSString &givenVariable) const
{ // compares data and givenVariable to see if they are the same

    if (data == nullptr)
    {
        return false;
    }
    int dataLength = length();
    int givenVariableLength = givenVariable.length();

    if (dataLength != givenVariableLength)
    {
        return false;
    }

    for (int i = 0; i < dataLength && i < givenVariableLength; i++)
    {
        if (data[i] != givenVariable.data[i])
        {
            return false;
        }
    }
    return true;
}

bool DSString::operator<(const DSString &givenVariable) const
{ // compares data and givenVariable to determine which one is smaller

    if (data == nullptr)
    {
        return false;
    }
    int dataLength = length();
    int givenVariableLength = givenVariable.length();

    for (int i = 0; i < dataLength; i++)
    {
        if (i == givenVariableLength)
        {
            return false;
        }
        else if (data[i] < givenVariable.data[i])
        {
            return true;
        }
        else if (data[i] > givenVariable.data[i])
        {
            return false;
        }
    }
    if (dataLength < givenVariableLength)
    {
        return true;
    }
    else
    {
        return false;
    }
}

DSString DSString::substring(size_t start, size_t numChars) const
{ // returns a specific combination given parameters

    DSString orderedCombination;
    orderedCombination.data = new char[numChars + 1];
    orderedCombination.len = numChars;

    for (size_t i = 0; i < numChars; i++)
    {
        orderedCombination.data[i] = data[start + i];
    }
    orderedCombination.data[numChars] = '\0';

    return orderedCombination;
}

DSString DSString::toLower() const
{ // turns letters lowercased

    int i = 0;
    char *toLowerdata = data;
    while (toLowerdata[i] != '\0')
    {
        if (toLowerdata[i] >= 'A' && toLowerdata[i] <= 'Z')
        {
            toLowerdata[i] += 32;
        }
        i++;
    }
    return toLowerdata;
}

char *DSString::c_str() const
{ // returns a pointer a null-terminated c-string holding the content of this object

    return data;
}

std::string DSString::string() const
{ // conversion to std::string EXTRA CREDIT

    std::string stringVersion = data;
    return stringVersion;
}

std::ostream &operator<<(std::ostream &output, const DSString &str)
{ // print the contents of this string to the output stream

    output << str.data;
    return output;
}

std::vector<DSString> DSString::tokenization()
{ // creates a vector to hold different tokenized strings

    size_t start = 0;
    std::vector<DSString> Storage;
    for (size_t i = 0; i <= len; i++)
    {
        if (!isalpha(data[i]))
        {
            if (i > start)
            {
                toLower();
                DSString newStorage = substring(start, i - start);
                Storage.push_back(newStorage);
            }
            start = i + 1;
        }
    }
    if (start < len)
    {
        toLower();
        DSString newStorage = substring(start, len - start);
        Storage.push_back(newStorage);
    }
    return Storage;
}
