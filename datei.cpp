//
// Created by Florian Schneck on 09.08.2025.
//

#include "datei.h"

/***************** Print the ERROR - return - codes to the console *****************/

void Print_Return(const int ReturnValue) {
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
    } else {
        std::cout << "File NOT found!" << std::endl;
        file.close();
        return false;
    }
}

/**************** Set nullptr to Value - Var *****************/

void datei::set_null_ptr() {
    std::cout << "Set NullPtr" << std::endl;
    iValue_1 = nullptr;
    iValue_2 = nullptr;
    iValue_4 = nullptr;
    iValue_8 = nullptr;
}

/*********************** check Settings ************************/

bool datei::check_settings() {
    int buffer = 0;
    int max_index_digits = 0;
    int max_column_digits = 0;

    /***************/
    buffer = (bytesPerCycle / blockSize) / columns; // Get max. Index - Digits
    while (buffer > 0) {
        buffer /= 10;
        max_index_digits++;
    }
    this->index_digits = max_index_digits; // safe the calculated max. Index digits to the class
    /***************/

    if (blockSize != 1 && blockSize != 2 && blockSize != 4 && blockSize != 8) return false; // Check blocksize

    if (bytesPerCycle < blockSize) return false; // Check bytesPerCycle

    if (columns < 1) return false; // Check Columns

    buffer = columns; // Get max. column lettering Digits
    while (buffer > 0) {
        buffer /= 10;
        max_column_digits++;
    }
    if (max_column_digits > digits) return false; // Check max. column lettering Digits

    return true;
}

/************************* Settings **************************/

/*********************************** Set ***********************************/

/************ set Path *************/

bool datei::setPath(const std::string &path) {
    this->path = path;
    return this->file_status();
}

/********** set BlockSize **********/

int datei::setBlockSize(const int &blockSize) {
    std::cout << "1" << std::endl;

    switch (this->blockSize) {
        // delete old Array
        default: // when not 1, 2, 4, 8
            return ERROR_WORKING_BYTES;
        case 1:
            delete[] iValue_1;
            iValue_1 = nullptr;
            break;
        case 2:
            delete[] iValue_2;
            iValue_2 = nullptr;
            break;
        case 4:
            delete[] iValue_4;
            iValue_4 = nullptr;
            break;
        case 8:
            delete[] iValue_8;
            iValue_8 = nullptr;
            break;
    }

    std::cout << "2" << std::endl;

    this->blockSize = blockSize; // write new BlockSize to the Class

    std::cout << "3" << std::endl;

    apply_Byte_Settings(); // resize Array

    std::cout << "4" << std::endl;

    return OK;
}

/********** set BytesPerCycle **********/

int datei::setBytesPerCycle(const int &bytesPerCycle) {
    if (bytesPerCycle < blockSize) return ERROR_WORKING_BYTES; // Check bytesPerCycle

    this->bytesPerCycle = bytesPerCycle;
    apply_Byte_Settings();

    return OK;
}

/********** set Columns **********/

int datei::setColumns(const int &columns) {
    int buffer = 0;

    if (columns < 1) return ERROR_DISPLAY_SETTINGS; // Check Columns

    buffer = (bytesPerCycle / blockSize) / columns; // Get max. Index - Digits
    while (buffer > 0) {
        buffer /= 10;
        index_digits++;
    }
    this->index_digits = index_digits; // safe the calculated max. Index digits to the class

    this->columns = columns;
    return OK;
}

/********** set Digits **********/

int datei::setDigits(const int &digits) {
    if (digits == -1) {     // when Digits = -1 -> Digits are calculated in read()
        this->digits = -1;
        std::cout << "Auto set Digits - enabled" << std::endl;
        return OK;
    }

    if (calc_digits(columns) > digits) return ERROR_DISPLAY_SETTINGS; // Check max. column lettering Digits

    this->index_digits = calc_digits((bytesPerCycle / blockSize) / columns);
    // safe the calculated max. Index digits to the class
    this->digits = digits;

    return OK;
}

/******* set Placeholder ********/

int datei::setPlaceholder(const char &placeholder) {
    this->placeholder = placeholder;
    return OK;
}

/********* set ReadPos **********/

int datei::setReadPos(const int &ReadPos) {
    if (ReadPos < 0) return ERROR;
    this->ReadPos = ReadPos;
    return OK;
}

/***************************************************************************/

/*********************************** Get ***********************************/

/*********** get Path ***********/

std::string datei::getPath() const {
    return path;
}

/******** get BlockSize *********/

int datei::getBlockSize() const {
    return blockSize;
}

/******* get bytePerCycle *******/

int datei::getBytesPerCycle() const {
    return bytesPerCycle;
}

/********* get Columns **********/

int datei::getColumns() const {
    return columns;
}

/********** get Digits **********/

int datei::getDigits() const {
    return digits;
}

/******* get Placeholder ********/

char datei::getPlaceholder() const {
    return placeholder;
}

/********* get ReadPos **********/

int datei::getReadPos() const {
    return ReadPos;
}



/***************************************************************************/

/********** apply Byte Settings to Value var **********/
// is called every time, the BlockSize or the bytesPerCycle changed, to resize the specific Value Array

void datei::apply_Byte_Settings() {
    switch (blockSize) {        // no default case -> blockSize already verified in setBlockSize()
        case 1:
            iValue_1 = new __int8[bytesPerCycle];
            break;

        case 2:
            iValue_2 = new __int16[bytesPerCycle / 2];
            break;

        case 4:
            iValue_4 = new __int32[bytesPerCycle / 4];
            break;

        case 8:
            iValue_8 = new __int64[bytesPerCycle / 8];
            break;
    }
}

/********************* Calculate Digits **********************/

template<class Typ>
int datei::calc_digits(Typ Value) {
    int digit_buffer = 0;

    if (Value == 0) return 1;

    if (Value < 0) {
        Value *= -1; // make positive
        digit_buffer = 1; // digit_buffer +1, because of '-'
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
    this->index_digits = calc_digits((1 + (bytesPerCycle / blockSize)) / columns);
}


/*************************** Read ****************************/

int datei::read() {
    file.open(path, std::ios::in | std::ios::binary);
    file.seekg(ReadPos, std::ios::beg);        // read from Byte "fromByte"

    if (file.is_open()) {
        std::variant <__int8, __int16, __int32, __int64> max_value;
        switch (blockSize) {
            default:
                return ERROR;
            // break;
            case 1:
                for (int i = 0; i < bytesPerCycle / blockSize; i++) {
                    file.read(&iValue_1[i], blockSize);     // no reinterpret_cast needed, because iValue_8 -> 1Byte like char
                    if (digits == -1 && std::get<__int8>(max_value) < iValue_1[i]) max_value = iValue_1[i];       // max. read Value for auto Calc digits, only when digits == -1
                }
                if (digits == -1) {
                    digits = calc_digits(std::get<__int8>(max_value));
                    Print_Values(iValue_1);
                    digits = -1;
                }
                else Print_Values(iValue_1);
                break;
            case 2:
                for (int i = 0; i < bytesPerCycle / blockSize; i++) {
                    file.read(reinterpret_cast<char*>(&iValue_2[i]), blockSize);     // no reinterpret_cast needed, because iValue_8 -> 1Byte like char
                    if (digits == -1 && std::get<__int16>(max_value) < iValue_2[i]) max_value = iValue_2[i];       // max. read Value for auto Calc digits, only when digits == -1
                }
                if (digits == -1) {
                    digits = calc_digits(std::get<__int16>(max_value));
                    Print_Values(iValue_2);
                    digits = -1;
                }
                else Print_Values(iValue_2);
                break;
            case 4:
                for (int i = 0; i < bytesPerCycle / blockSize; i++) {
                    file.read(reinterpret_cast<char*>(&iValue_4[i]), blockSize);     // no reinterpret_cast needed, because iValue_8 -> 1Byte like char
                    if (digits == -1 && std::get<__int32>(max_value) < iValue_4[i]) max_value = iValue_4[i];       // max. read Value for auto Calc digits, only when digits == -1
                }
                if (digits == -1) {
                    digits = calc_digits(std::get<__int32>(max_value));
                    Print_Values(iValue_4);
                    digits = -1;
                }
                else Print_Values(iValue_4);
                break;
            case 8:
                for (int i = 0; i < bytesPerCycle / blockSize; i++) {
                    file.read(reinterpret_cast<char*>(&iValue_8[i]), blockSize);     // no reinterpret_cast needed, because iValue_8 -> 1Byte like char
                    if (digits == -1 && std::get<__int64>(max_value) < iValue_8[i]) max_value = iValue_8[i];       // max. read Value for auto Calc digits, only when digits == -1
                }
                if (digits == -1) {
                    digits = calc_digits(std::get<__int64>(max_value));
                    Print_Values(iValue_8);
                    digits = -1;
                }
                else Print_Values(iValue_8);
                break;
        }
        digits = -1;
        file.close();
        std::cout << std::endl;

        std::cout << "read" << std::endl;

        return OK;
    }
    file.close();
    return ERROR_OPEN_FILE; // Happens only, when the File can't be opened...
} // If it can be opened, it Returns "OK" and end the function

/**************************** Init Table *****************************/

void datei::init_Table() {
    apply_max_index_digits();

    for (int i = 0; i < index_digits; i++) printf(" "); // Empty Space in Row 0 line 0
    printf(" %c ", 186); // start of the index - column

    for (int i = 0; i < columns; i++) {
        // Do once for every column

        int digits = calc_digits(i);

        for (int j = 0; j < this->digits - digits; j++) printf("%c", placeholder); // fill empty space with 0
        printf("%d", i); // print column lettering
        printf(" | "); // print spacer between columns
    }

    printf("\n"); // New line for dividing line

    for (int i = 0; i < index_digits + 1; i++) printf("%c", 205); // line Space in Row 0; line 1
    printf("%c", 206); // character to connect vertical and horizontal line
    for (int i = 0; i < (digits + 3) * columns; i++) printf("%c", 205); // horizontal dividing line

    std::cout << "initTable" << std::endl;
}

/*************************** Print Values ****************************/

template<class Typ>
int datei::Print_Values(Typ &Value) {
    init_Table();
    for (int a = 0; a < bytesPerCycle / blockSize; a++) {
        // amount of Values
        if (a % columns == 0) {
            // do NEW LINE and a new index number every "columns" lines
            printf("\n");
            for (int b = 0; b < index_digits - calc_digits(a / columns); b++) {
                // print 0 for every "not used" character, that is needed
                printf("%c", placeholder);
            }
            printf("%d %c", a / columns, 186); // print index and vertical dividing line
        }

        printf(" ");


        switch (blockSize) {        // no default case -> blockSize already verified in setBlockSize()
            case 1:
                for (int b = 0; b < digits - calc_digits(iValue_1[a]); b++) printf("%c", placeholder);
                std::cout << static_cast<int>(iValue_1[a]) << " |";
                break;
            case 2:
                for (int b = 0; b < digits - calc_digits(iValue_2[a]); b++) printf("%c", placeholder);
                std::cout << static_cast<int>(iValue_2[a]) << " |";
                break;
            case 4:
                for (int b = 0; b < digits - calc_digits(iValue_4[a]); b++) printf("%c", placeholder);
                std::cout << iValue_4[a] << " |";
                break;
            case 8:
                for (int b = 0; b < digits - calc_digits(iValue_8[a]); b++) printf("%c", placeholder);
                std::cout << static_cast<int>(iValue_8[a]) << " |";
                break;
        }
    }
    std::cout << "Print_Values" << std::endl;
    return OK;
}
