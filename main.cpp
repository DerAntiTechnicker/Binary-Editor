/***************************************************
* Author: Florian Schneck
 * created: 10.08.2025
 ***************************************************
 * Work to do:
 *              - redesign -> Print_column_index();
 *
 ***************************************************/

#include "datei.h"


int main() {
    // datei test ("C:/Users/Florian Schneck/ClionProjects/Binary_Editor/Test.bin");
    datei test;

    test.setPath("C:/Users/Florian Schneck/ClionProjects/Binary_Editor/Test.bin");
    PrintError(test.setBlockSize(4));
    PrintError(test.setBytesPerCycle(420));
    PrintError(test.setColumns(8));
    PrintError(test.setDigits(4));
    PrintError(test.read());


    /*std::fstream file("C:/Users/Florian Schneck/ClionProjects/Binary_Editor/Test.bin", std::ios::out | std::ios::trunc | std::ios::binary);
    int text[1000];
    for (int i = 0; i < 50; i++) text[i] = 24;
    for (int i = 50; i < 100; i++) text[i] = 1024;
    file.write(reinterpret_cast<char*>(text), sizeof(int) * 100);*/
    return 0;
}
