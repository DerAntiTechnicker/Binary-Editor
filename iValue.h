//
// Created by Florian Schneck on 29.08.2025.
//

#ifndef IVALUE_H
#define IVALUE_H
#include <iostream>


class iValue {
    int index_1;
    __int8 *iValue_1;

    int index_2;
    __int16 *iValue_2;

    int index_4;
    __int32 *iValue_4;

    int index_8;
    __int64 *iValue_8;

public:
    iValue();
    ~iValue();

    template<class Typ>
    void add(const Typ &Value, const int &number_of_values) {
        switch (sizeof(Typ)) {
            default:
                std::cout << "This type is not supported!" << std::endl;
                break;
            case 1:
                __int8 buffer[index_1];
                for (int i = 0; i < index_1; i++) buffer[i] = iValue_1[i];
                delete[] iValue_1;
                iValue_1 = new __int8[number_of_values];
                index_1 = number_of_values;
                for (int i = 0; i < index_1; i++) iValue_1[i] = buffer[i];
        }
    }
};



#endif //IVALUE_H
