//
// Created by Florian Schneck on 29.08.2025.
//


#include "iValue.h"

iValue::iValue() {
    iValue_1 = new __int8[1];
    iValue_2 = new __int16[1];
    iValue_4 = new __int32[1];
    iValue_8 = new __int64[1];
}

iValue::~iValue() {
    delete[] iValue_1;
    delete[] iValue_2;
    delete[] iValue_4;
    delete[] iValue_8;
}