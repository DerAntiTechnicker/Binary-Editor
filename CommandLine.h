#ifndef COMMANDLINE_H
#define COMMANDLINE_H
#include <iostream>
#include <map>
#include <functional>
#include <vector>


class CommandLine {
    bool running;       // bool variable for the "while" loop to get a never ending loop until running -> false

    std::string input;
    std::vector<std::string> argument;

    std::map <std::string, std::pair<std::pair<std::function<void()>, std::vector<std::string>>, std::string>> command;

    void execute_Command(const std::string &name);      // execute the given lambda to the given command - name (calls execute_func)
    void split_String();

public:
    CommandLine() {
        running = true;

        // command.insert({"exit", {[this](){running = false;}, "Exit the Programm"}});
        addCommand("exit",[this](){running = false;});

        addCommand("help",[this](){display_explanations();});

        addCommand("clear",[](){
        printf("\033[2J");      // erase console
        system("cls");      // erase console - erases and removes the previous lines
        printf("\033[H");
        });
        add_explanation("clear", "clear the screen...");

        // command.insert({"help", {[this](){display_explanations();}, "Display a list of all Commands"}});        // for some reason the function "display_explanations" can't be called directly, that's because it is called through a lambda function

        argument.emplace_back(" ");
    }

    void addCommand(const std::string &name, const std::function <void()> &func);        // add a command to "commands"
    void eraseCommand(const std::string &name);                                          // erase a Command
    void add_explanation(const std::string &name, const std::string &explanation);       // add an explanation to an existing Command "name"
    void display_explanations() const;                                                         // displays a list of all Commands and, if avaliable, the explanations

    bool addArg(const std::string &command_name, const std::string &arg_name, const int &pos);
    int getArgValue(const int &pos) const;      // Get the input Value as an int ("1" -> 1)
    std::string getArg(const int &pos) const;       // get the Arg Nr. pos as the input string
    int GetArgCount() const;

    int StrToInt(const int &arg_num) const;     /* Get the Int of the given String (at argument)
    Returns 0 if the argument is not a number ("0", "1", "2", ...)*/

    void init();        // Init and start the CLI
};


#endif //COMMANDLINE_H