#include "CommandLine.h"

#include <algorithm>
#include <cmath>
#include <string>


/******************* split String ********************/

void CommandLine::split_String() {
    std::string buffer;

    input.push_back(' ');       // to get the last argument working

    for (int i = 0; i < input.size(); i++) {
        if (input[i] == '\"') {     // exception, when somethins insind "" is, to be able to input strings with spacesddd
            i++;
            do {
                buffer += input[i];
                i++;
            } while (input[i] != '\"');
        }
        else if (input[i] != ' ') {
            buffer += input[i];     // write one more character of the argument to the buffer
        }
        else if (input[i] == ' ' && input[i - 1] != ' ') {      // add only to argument, when found an exception directly after a character
            argument.push_back(buffer);     // write the buffer to a new argument
            buffer.clear();
        }
    }
}

/******************* String to Int *******************/

int CommandLine::StrToInt(const int &arg_num) const {

    for (const int test : argument[arg_num]) {      // get the ASCII code of every character of Arg Nr. arg_num
        if (test >= 48 && test <= 57 || test == 45) {}        // if between "0" and "9"
        else {
            std::cout << "ERROR - \"" << static_cast<char>(test) << "\" is not Value!" << std::endl;        // static_cast to print the character and not the ASCII code    // static_cast -> type of original Value to cast immer int
            return 0;
        }
    }

    if (argument[arg_num] != " " && arg_num <= argument.size() - 1) return std::stoi(argument[arg_num]);
    else return 0;
}

/******************* add a Command *******************/

void CommandLine::addCommand(const std::string &name, const std::function <void()> &func) {
    if (!command.contains(name)) {     // if no command called like this is found
        // command.insert({name, {{func, {}}, ""}});
        command.insert({name, {{func, std::vector<std::string>{}}, ""}});
    }
    else std::cout << "WARNING - You are trying to add the command: \"" << name << "\", but it already exists\n" << "The existing Command is not affected..." << std::endl;
}

/****************** erase a Command ******************/

void CommandLine::eraseCommand(const std::string &name) {
    if (!command.contains(name)) std::cout << "WARNING - You are trying to erase the command: \"" << name << "\", but it does not exist!" << std::endl;
    else command.erase(name);       // erase the command
}

/*********** add explanation to a Command ************/

void CommandLine::add_explanation(const std::string &name, const std::string &explanations) {
    if (command.count(name) == 1) {     // only if the command exits
        command[name].second = explanations;       // add the explanation to the second element of the pair of the second element of the map
    }
    else std::cout << "WARNING - You are trying to add an explanation to the command: \"" << name << "\", but it does not exist\n" << "No explanation added..." << std::endl;
}

/*************** display explenations ***************/

void CommandLine::display_explanations() const {
    std::cout << "------------------------------------------------" << std::endl;       // first top spacer
    for (const auto& explanation : command) {
        printf("\033[1m\033[38;2;105;0;255m");       // set: bold, RGB - color
        std::cout << explanation.first << std::endl;        // print Command - Name
        printf("\033[0m");      // reset Graphics Mode / Color
        if (!explanation.second.second.empty()) {
            std::cout << explanation.second.second << std::endl;        // print the second of the pair in the Value of the map
        }
        else {
            printf("\033[31m");     // set text - color to RED
            std::cout << "No explanation..." << std::endl;
            printf("\033[0m");      // reset Graphics Mode / Color
        }
        std::cout << "------------------------------------------------" << std::endl;       // spacer
    }
}

/********** execute function for a command ***********/

void CommandLine::execute_Command(const std::string &name) {
    (command[name].first.first)();        // call the function to the name  //.first -> the std::function is the first element of the pair
}

/******************* if Argument ********************/

bool CommandLine::addArg(const std::string &command_name, const std::string &arg_name, const int &pos) {
    command.at(command_name).first.second.push_back(arg_name);      // add the argument name to the command

    if (argument.size() > 1) {
        int t = 0;
        for (int i = 1; i < argument.size(); i++) {
            if (argument[i] == arg_name) t++;
        }
        if (t > 0) return true;
        else {      // not needed, because if (t > 0) == true -> return true; -> it will never be executed
            std::cout << "ERROR - Argument does not exist!" << std::endl;
            return false;
        }
    }
    return false;
}

/******************* getArgValue ********************/

int CommandLine::getArgValue(const int &pos) const {
    if (argument.size() >= pos + 1) {
        return StrToInt(pos);
    }
    else return -1;
}

/********************** getArg **********************/

std::string CommandLine::getArg(const int &pos) const {
    if (pos < argument.size()) return argument[pos];
    else {
        std::cout << "WARNING - \"getArg\" pos = " << pos << "not valid, not such Position" << std::endl;
        return "";
    }
}

int CommandLine::GetArgCount() const {
    return static_cast<int>(argument.size());
}


/*********************** init ***********************/      // init and display the command line

void CommandLine::init() {
    while (running) {       // if running = false -> the Programm exits normally through main (it just breaks the while loop, and does not end the programm
        argument.clear();
        std::cout << "> ";       // marker for input line
        std::getline(std::cin, input);

        split_String();

        if (argument.at(0).empty()){}
        else {
            if (command.count(argument[0]) == 1) {        // get the number of commands with the name stored in input. If more than 0 commands are avaliable -> execute
                execute_Command(argument[0]);             // execute the Command for input
            }
            else std::cout << "ERROR - no such command..." << std::endl;
        }
    }
}