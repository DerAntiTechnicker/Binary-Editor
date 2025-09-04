//
// Created by Florian Schneck on 09.08.2025.
//

#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>

/************ Constructor Default Settings ************/

#define DEFAULT_BLOCK_SIZE 1
#define DEFAULT_BYTES_PER_CYCLE 1
#define DEFAULT_COLUMNS 1
#define DEFAULT_DIGITS 1

/******************************************************/

enum Return_Value {      // Return Codes...
    OK,
    ERROR,
    ERROR_WORKING_BYTES,
    ERROR_OPEN_FILE,
    ERROR_DISPLAY_SETTINGS
};

enum mode {
    MANUAL,
    AUTO
};

void Print_Return(int ReturnValue);       // Print Error Information from recieved return code to console

template<class Typ>
std::string ValuetoString(const Typ &Value);

/************************************/

class datei {
public:     // file - related variables
    std::string path;
    std::fstream file;

// private:    // Internal Variables
    __int8 *iValue_1;       // Variable to store 1 Byte Values
    __int16 *iValue_2;     // Variable to store 2 Byte Values
    __int32 *iValue_4;     // Variable to store 4 Byte Values
    __int64 *iValue_8;     // Variable to store 8 Byte Values

    std::string *Value;

    int blockSize;      // Size of a read Value [Bytes]
    int bytesPerCycle;      // How many Bytes are extracted [Bytes]

    int index_digits;

    int digits;    // The digits per Value to be displayed -> digitsPerNumber = 3 -> "2" is displayed as "002"
    mode digit_mode;
    int columns;         // The number of columns to be displayed when reading from a file
    char placeholder;       // placeholder for not used characters (f.ex.: 001)

    int ReadPos;        // pos to start reading from

public:
    datei() {       // default Konstruktor
        set_null_ptr();
        path = "";
        placeholder = '0';
        blockSize = DEFAULT_BLOCK_SIZE;     // Default Values
        bytesPerCycle = DEFAULT_BYTES_PER_CYCLE;
        columns = DEFAULT_COLUMNS;
        digits = DEFAULT_DIGITS;
        digit_mode = AUTO;
        ReadPos = 0;
        check_settings();   // called, because it also calculates the max. Index digits...
    }

    ~datei() {      // Destructor
        delete[] iValue_1;
        delete[] iValue_2;
        delete[] iValue_4;
        delete[] iValue_8;
        delete[] Value;
        file.close();       // Close File in case it is still open
    }

    Return_Value read();     // Read from a File
    Return_Value print();    // prints the Values to the Console
    Return_Value write(const std::string &text);
    Return_Value Print_ASCII() const;

    Return_Value getCSV();

    bool setPath(std::string path);      // update the Path
    Return_Value setBlockSize(const int &blockSize);
    Return_Value setBytesPerCycle(const int &bytesPerCycle);
    Return_Value setColumns(const int &columns);
    Return_Value setDigits(const int &digits);
    Return_Value setPlaceholder(const char &placeholder);
    Return_Value setReadPos(const int &ReadPos);

    std::string getPath() const;        // return the current
    int getBlockSize() const;
    int getBytesPerCycle() const;
    int getColumns() const;
    int getDigits() const;
    std::string getDigitMode() const;
    char getPlaceholder() const;
    int getReadPos() const;


    bool check_settings();

// private:    // Internal Functions
private:
    Return_Value file_status();    // returns TRUE if a file can be opened, if not: FALSE
    void set_null_ptr();    // sets every pointer (iValue_8, ...) to nullptr
    void apply_Byte_Settings();     // resize the Arrays where to store the Values

    template<class Typ>
    static int calc_digits(Typ Value);    // get the number of digits of the give Value

    void apply_max_index_digits();

    void init_Table();

    Return_Value Print_Values();
};

#endif //FILE_H