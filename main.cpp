/***************************************************
* Author: Florian Schneck
 * created: 10.08.2025
 ***************************************************
 * Work to do:
 *              - redesign -> Print_column_index();
 *
 ***************************************************/

#include "datei.h"
#include "CommandLine.h"

#include <conio.h>

void CommandLine::CommandActions() {     // later it should be only a prototype!
        if (input == commands[i]) {     // exit
            running = false;
        }
}

int main() {
    CommandLine cmdLine;
    cmdLine.init();
    getch();
    return 0;
}







/*std::fstream file("C:/Users/Florian Schneck/ClionProjects/Binary-Editor/Test.bin", std::ios::out | std::ios::trunc | std::ios::binary);
    int text[1000];
    for (int i = 0; i < 50; i++) text[i] = 24;
    for (int i = 50; i < 100; i++) text[i] = 1024;
    file.write(reinterpret_cast<char*>(text), sizeof(int) * 100);*/