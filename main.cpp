#include "datei.h"
#include "CommandLine.h"


class chines {
    int index;
    std::string text;

public:
    chines() {
        index = 2;
        text = "Chines";
    }
};



int main() {
    datei test;
    CommandLine CLI;

    CLI.addCommand("settings",[&CLI, &test] {
        if (CLI.getArg(1) == "show") {
            std::cout << "Path: \"" << test.getPath() << "\"" << std::endl;
            std::cout << "BlockSize: " << test.getBlockSize() << std::endl;
            std::cout << "BytesPerCycle: " << test.getBytesPerCycle() << std::endl;
            std::cout << "Columns: " << test.getColumns() << std::endl;
            std::cout << "Digits: " << test.getDigits() << std::endl;
            std::cout << "Placeholder: \"" << test.getPlaceholder() << "\"" << std::endl;
            std::cout << "readPos: " << test.getReadPos() << std::endl;
        }
        else if (CLI.getArg(1) == "set") {
            int ArgValue = 0;
            if (CLI.getArg(2) == "Path") {
                const std::string buffer = CLI.getArg(3);
                Print_Return(test.setPath(buffer));
            }
            else if (CLI.getArg(2) == "BlockSize") {
                ArgValue = CLI.getArgValue(3);
                Print_Return(test.setBlockSize(ArgValue));
            }
            else if (CLI.getArg(2) == "BytesPerCycle") {
                ArgValue = CLI.getArgValue(3);
                Print_Return(test.setBytesPerCycle(ArgValue));
            }
            else if (CLI.getArg(2) == "Columns") {
                ArgValue = CLI.getArgValue(3);
                Print_Return(test.setColumns(ArgValue));
            }
            else if (CLI.getArg(2) == "Digits") {
                ArgValue = CLI.getArgValue(3);
                Print_Return(test.setDigits(ArgValue));
            }
            else if (CLI.getArg(2) == "Ph") {
                const std::string a = CLI.getArg(3);
                Print_Return(test.setPlaceholder(a[0]));
            }
            else if (CLI.getArg(2) == "readPos") {
                ArgValue = CLI.getArgValue(3);
                Print_Return(test.setReadPos(ArgValue));
            }
            else std::cout << "Argument does not exits!" << std::endl;
        }
        else std::cout << "Argument does not exits!" << std::endl;
    });

    CLI.addCommand("read",[&test] {
        test.read();
    });

    CLI.addCommand("print",[&test] {
        test.print();
    });

    CLI.addCommand("write",[&test] {
        Print_Return(test.write("Servus"));
    });

    CLI.addCommand("print_ASCII", [&test] {
        Print_Return(test.Print_ASCII());
    });

    test.setPath("C:/Users/Florian Schneck/CLionProjects/Binary-Editor/TEST.bin");
    test.setDigits(-1);
    test.setColumns(8);
    test.setBytesPerCycle(32);
    test.setBlockSize(1);
    test.setPlaceholder(' ');


    CLI.init();

    return 0;
}