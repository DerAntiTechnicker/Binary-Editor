//
// Created by Florian Schneck on 09.08.2025.
//

#include "datei.h"

/***************** Print the ERROR - return - codes to the console *****************/

void PrintError(int ReturnValue) {
    switch (ReturnValue) {
        default: std::cout << "No such Error Code..." << std::endl;
            break;
        case OK: std::cout << "OK" << std::endl;
            break;
        case ERROR: std::cout << "ERROR" << std::endl;
            break;
        case ERROR_WORKING_BYTES: std::cout << "ERROR - Working Bytes" << std::endl;
            break;
        case ERROR_OPEN_FILE: std::cout << "ERROR - Open File" << std::endl;
            break;
        case ERROR_DISPLAY_SETTINGS: std::cout << "ERROR - Display Settings" << std::endl;
            break;
    }
}

/*********************************************************************/
/**************** Check if File can be opened ****************/

bool datei::file_status() {
    file.open(path, std::ios::in | std::ios::binary);

    if (file.is_open()) {
        std::cout << "File found!" << std::endl;
        file.close();
        return true;
    }
    else {
        std::cout << "File NOT found!" << std::endl;
        file.close();
        return false;
    }
}

/**************** Set nullptr to Value - Var *****************/

void datei::set_null_ptr() {
    std::cout << "Set NullPtr" << std::endl;
    iValue_8 = nullptr;
    iValue_16 = nullptr;
    iValue_32 = nullptr;
    iValue_64 = nullptr;
}

/******************* Set a new File - Path *******************/

bool datei::setPath(const std::string &path) {
    this->path = path;
    return this->file_status();
}

/****************** get the new File - Path ******************/

std::string datei::getPath() const {
    return path;
}

/*********************** check Settings ************************/

bool datei::check_settings() {
    int buffer = 0;
    int max_index_digits = 0;
    int max_column_digits = 0;

    /***************/
    buffer = (bytesPerCycle / blockSize) / columns;      // Get max. Index - Digits
    while (buffer > 0) {
        buffer /= 10;
        max_index_digits++;
    }
    this->max_index_digits = max_index_digits;      // safe the calculated max. Index digits to the class
    /***************/

    if (blockSize != 1 && blockSize != 2 && blockSize != 4 && blockSize != 8) return false;     // Check blocksize

    if (bytesPerCycle < blockSize) return false;        // Check bytesPerCycle

    if (columns < 1) return false;      // Check Columns

    buffer = columns;        // Get max. column lettering Digits
    while (buffer > 0) {
        buffer /= 10;
        max_column_digits++;
    }
    if (max_column_digits > digits) return false;      // Check max. column lettering Digits

    return true;
}

/************************* Settings **************************/

/*int datei::setBytes(const int &blockSize, const int &bytesPerCycle) {
    this->blockSize = blockSize;
    this->bytesPerCycle = bytesPerCycle;
    if (blockSize > bytesPerCycle || blockSize != 1 && blockSize != 2 && blockSize != 4 && blockSize != 8) return ERROR_WORKING_BYTES;
    switch (blockSize) {
        // default: break;
        case 1: iValue_8 = new __int8[bytesPerCycle];
            break;

        case 2: iValue_16 = new __int16[bytesPerCycle / 2];
            break;

        case 4: iValue_32 = new __int32[bytesPerCycle / 4];
            break;

        case 8: iValue_64 = new __int64[bytesPerCycle / 8];
            break;
    }

    return OK;
}*/

int datei::setBlockSize(const int &blockSize) {
    std::cout << "BlockSize - ";

    if (blockSize != 1 && blockSize != 2 && blockSize != 4 && blockSize != 8) return ERROR_WORKING_BYTES;     // Check blocksize

    this->blockSize = blockSize;
    apply_Byte_Settings();

    return OK;
}

int datei::setBytesPerCycle(const int &bytesPerCycle) {
    std::cout << "BytesPerCycle - ";

    if (bytesPerCycle < blockSize) return ERROR_WORKING_BYTES;        // Check bytesPerCycle

    this->bytesPerCycle = bytesPerCycle;
    apply_Byte_Settings();

    return OK;
}

int datei::setColumns(const int &columns) {
    int buffer = 0;

    std::cout << "Columns - ";

    if (columns < 1) return ERROR_DISPLAY_SETTINGS;      // Check Columns

    buffer = (bytesPerCycle / blockSize) / columns;      // Get max. Index - Digits
    while (buffer > 0) {
        buffer /= 10;
        max_index_digits++;
    }
    this->max_index_digits = max_index_digits;      // safe the calculated max. Index digits to the class

    this->columns = columns;
    return OK;
}

int datei::setDigits(const int &digits) {
    std::cout << "Digits - ";

    int buffer = 0;
    int max_digits = 0;

    buffer = columns;        // Get max. column lettering Digits
    while (buffer > 0) {
        buffer /= 10;
        max_digits++;
    }
    if (max_digits > digits) return ERROR_DISPLAY_SETTINGS;      // Check max. column lettering Digits

    max_digits = 0;     // reset digit count -> 0

    buffer = (bytesPerCycle / blockSize) / columns;      // Get max. Index - Digits
    while (buffer > 0) {
        buffer /= 10;
        max_digits++;
    }
    this->max_index_digits = max_digits;      // safe the calculated max. Index digits to the class

    this->digits = digits;
    return OK;
}


int datei::setByteSettings(const int &blockSize, const int &bytesPerCycle) {
    if (blockSize != 1 && blockSize != 2 && blockSize != 4 && blockSize != 8) return ERROR_WORKING_BYTES;     // Check blocksize
    if (bytesPerCycle < blockSize) return ERROR_WORKING_BYTES;        // Check bytesPerCycle

    this->blockSize = blockSize;
    this->bytesPerCycle = bytesPerCycle;

    apply_Byte_Settings();
    return OK;
}
// When setting blockSize ad bytesPerCycle -> apply_Byte_Settings() is only once called...

int datei::setTableSettings(const int &columns, const int &digits) {
    if (setColumns(columns) != OK) return ERROR_DISPLAY_SETTINGS;
    if (setDigits(digits) != OK) return ERROR_DISPLAY_SETTINGS;
    return OK;
}
// Just do both within 1 funcion


void datei::apply_Byte_Settings() {
    switch (blockSize) {
        default: break;
        case 1:
            delete[] iValue_8;
            iValue_8 = new __int8[bytesPerCycle];
            break;

        case 2:
            delete[] iValue_8;
            iValue_16 = new __int16[bytesPerCycle / 2];
            break;

        case 4:
            delete[] iValue_8;
            iValue_32 = new __int32[bytesPerCycle / 4];
            break;

        case 8:
            delete[] iValue_8;
            iValue_64 = new __int64[bytesPerCycle / 8];
            break;
    }
}

/************************ GetDigits **************************/

int datei::getDigits(int Value) {
    int digit_buffer = 0;

    if (Value == 0) return 1;

    if (Value < 0) {
        Value *= -1;    // make positive
        digit_buffer = 1;   // digit_buffer +1, because of '-'
        while (Value > 0) {
            Value /= 10;
            digit_buffer++;
        }
        return digit_buffer;
    }

    while (Value > 0) {
        Value /= 10;
        digit_buffer++;
    }
    return digit_buffer;
}

void datei::apply_max_index_digits() {
    this->max_index_digits = getDigits((1 + (bytesPerCycle / blockSize)) / columns);
}


/*************************** Read ****************************/

int datei::read() {
    init_Table();

    file.open(path, std::ios::in | std::ios::binary);
    if (file.is_open()) {
        switch (blockSize) {
            default:
                return ERROR;
                // break;
            case 1:
                for (int i = 0; i < bytesPerCycle / blockSize; i++) {
                    file.read(&iValue_8[i], blockSize);     // no reinterpret_cast needed, because iValue_8 -> 1Byte like char
                }
                if (Print_Values(iValue_8) == ERROR_DISPLAY_SETTINGS) return ERROR_DISPLAY_SETTINGS;
                break;
            case 2:
                for (int i = 0; i < bytesPerCycle / blockSize; i++) {
                    file.read(reinterpret_cast<char*>(&iValue_16[i]), blockSize);
                }
                if (Print_Values(iValue_16) == ERROR_DISPLAY_SETTINGS) return ERROR_DISPLAY_SETTINGS;
                break;
            case 4:
                for (int i = 0; i < bytesPerCycle / blockSize; i++) {
                    file.read(reinterpret_cast<char*>(&iValue_32[i]), blockSize);
                }
                if (Print_Values(iValue_32) == ERROR_DISPLAY_SETTINGS) return ERROR_DISPLAY_SETTINGS;
                break;
            case 8:
                for (int i = 0; i < bytesPerCycle / blockSize; i++) {
                    file.read(reinterpret_cast<char*>(&iValue_64[i]), blockSize);
                }
                if (Print_Values(iValue_64) == ERROR_DISPLAY_SETTINGS) return ERROR_DISPLAY_SETTINGS;
                break;
        }
        std::cout << std::endl;
        return OK;
    }
    return ERROR_OPEN_FILE;     // Happens only, when the File can't be opened...
}                               // If it can be opened, it Returns "OK" and end the function

/**************************** Init Table *****************************/

void datei::init_Table() {
    apply_max_index_digits();

    for (int i = 0; i < max_index_digits; i++) printf(" ");     // Empty Space in Row 0 line 0
    printf(" %c ", 186);       // start of the index - column

    for (int i = 0; i < columns; i++) {     // Do once for every column

        int digits = getDigits(i);

        for (int j = 0; j < this->digits - digits; j++) printf("0");    // fill empty space with 0
        printf("%d", i);    // print column lettering
        printf(" | ");      // print spacer between columns
    }

    printf("\n");       // New line for dividing line

    for (int i = 0; i < max_index_digits + 1; i++) printf("%c", 205);     // line Space in Row 0; line 1
    printf("%c", 206);      // character to connect vertical and horizontal line
    for (int i = 0; i < (digits + 3) * columns; i++) printf("%c", 205);     // horizontal dividing line
}

/*************************** Print Values ****************************/

template<class Typ>
int datei::Print_Values(Typ *Value) {
    for (int a = 0; a < bytesPerCycle / blockSize; a++) {       // amount of Values
        if (a % columns == 0) {     // do NEW LINE and a new index number every "columns" lines
            printf("\n");
            for (int b = 0; b < max_index_digits - getDigits(a / columns); b++) {       // print 0 for every "not used" character, that is needed
                printf("0");
            }
            printf("%d %c", a / columns, 186);      // print index and vertical dividing line
        }

        printf(" ");
        for (int b = 0; b < digits - getDigits(Value[a]); b++) printf("0");
        std::cout << static_cast<int>(Value[a]) << " |";
    }
    return OK;
}