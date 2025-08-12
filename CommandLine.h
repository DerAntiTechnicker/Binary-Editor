//
// Created by Florian Schneck on 12.08.2025.
//

#ifndef COMMANDLINE_H
#define COMMANDLINE_H
#include <iostream>
#include <utility>


class CommandLine {
    bool running;
    int commandANZ;
    int i;

public:
    std::string *commands;
    std::string input;

public:
    CommandLine() {
        running = true;     // set infinity loop
        commandANZ = 0;
        i = 0;

        commands = new std::string[1];

        std::string input;
    }


    void CommandActions();


    void init() {
        clrscr();

        while (running) {
            std::cout << "> ";
            std::getline(std::cin, input);
            for (i = 0; i < commandANZ; i++) {
                if (input == "") {}
                else if (input == "help") {
                    std::cout << "Commands:" << std::endl;
                    for ()
                }
                else if (input != commands[i] && i == commandANZ - 1) std::cout << "ERROR - Command not recognized!\n";
                CommandActions();
            }
        }
    }

    void addCommand(std::string newCommand) {
        std::string buffer[commandANZ];
        for (int i = 0; i < commandANZ; i++) {
            buffer[i] = commands[i];
        }
        delete[] commands;
        commandANZ++;
        commands = new std::string[commandANZ];
        for (int i = 0; i < commandANZ; i++) {
            commands[i] = buffer[i];
        }
        commands[commandANZ - 1] = newCommand;
    }





    static void clrscr();
};



#endif //COMMANDLINE_H
