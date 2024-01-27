#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "No command provided" << std::endl;
        return 1;
    }

    std::string command = argv[1];

    if (command == "add" && argc == 3) {
        std::cout << "Add: " << argv[2] << std::endl;
    } else if (command == "commit" && argc == 4 && std::string(argv[2]) == "-m") {
        std::cout << "Commit: " << argv[3] << std::endl;
    } else if (command == "push") {
        if (argc == 2) {
            std::cout << "Push" << std::endl;
        } else if (argc == 3 && std::string(argv[2]) == "--force") {
            std::cout << "Push with force" << std::endl;
        }
    } else {
        std::cout << "Invalid command or arguments" << std::endl;
    }

    return 0;
}
