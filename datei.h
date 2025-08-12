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

enum Error_Codes{      // Return Codes...
    OK,
    ERROR,
    ERROR_WORKING_BYTES,
    ERROR_OPEN_FILE,
    ERROR_DISPLAY_SETTINGS
};

void PrintError(int ReturnValue);       // Print Error Information from recieved return code to console

/************************************/

class datei {
public:     // file - related variables
    std::string path;
    std::fstream file;

private:    // Internal Variables
    __int8 *iValue_8;       // Variable to store 1 Byte Values
    __int16 *iValue_16;     // Variable to store 2 Byte Values
    __int32 *iValue_32;     // Variable to store 4 Byte Values
    __int64 *iValue_64;     // Variable to store 8 Byte Values

    int blockSize;      // Size of a read Value [Bytes]
    int bytesPerCycle;      // How many Bytes are extracted [Bytes]

    int max_index_digits;

    int digits;    // The digits per Value to be displayed -> digitsPerNumber = 3 -> "2" is displayed as "002"
    int columns;         // The number of columns to be displayed when reading from a file

public:
    datei() {       // default Konstruktor
        set_null_ptr();
        path = "";
        blockSize = DEFAULT_BLOCK_SIZE;     // Default Values
        bytesPerCycle = DEFAULT_BYTES_PER_CYCLE;
        columns = DEFAULT_COLUMNS;
        digits = DEFAULT_DIGITS;
        check_settings();   // called, because it also calculates the max. Index digits...
    }
    explicit datei (const std::string path) {     // überladener Konstruktor -> path
        this->set_null_ptr();
        this->path = path;
        this->file_status();        // Print to the console, if the File can be opened, or not
        blockSize = DEFAULT_BLOCK_SIZE;     // Default Values
        bytesPerCycle = DEFAULT_BYTES_PER_CYCLE;
        columns = DEFAULT_COLUMNS;
        digits = DEFAULT_DIGITS;

        check_settings();   // called, because it also calculates the max. Index digits...
    }

    ~datei() {      // Destructor
        delete[] iValue_8;
        delete[] iValue_16;
        delete[] iValue_32;
        delete[] iValue_64;
        file.close();       // Close File in case it is still open
    }

    int read();     // Read from a File
    std::string getPath() const;        // return the current Path
    bool setPath(const std::string &path);      // update the Path

    int setBlockSize(const int &blockSize);
    int setBytesPerCycle(const int &bytesPerCycle);
    int setColumns(const int &columns);
    int setDigits(const int &digits);

    int setByteSettings(const int &blocksize, const int &bytesPerCycle);
    int setTableSettings(const int &columns, const int &digits);

    bool check_settings();

private:    // Internal Functions
    bool file_status();    // returns TRUE if a file can be opened, if not: FALSE
    void set_null_ptr();    // sets every pointer (iValue_8, ...) to nullptr
    void apply_Byte_Settings();     // resize the Arrays where to store the Values
    static int getDigits(int Value);    // get the number of digits of the give Value

    void apply_max_index_digits();

    void init_Table();

    template<class Typ>
    int Print_Values(Typ *Value);
};



#endif //FILE_H