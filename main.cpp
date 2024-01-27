#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

void initialize_git_repository() {
    const std::string& path = std::filesystem::current_path().string();
    std::filesystem::create_directories(path + "/.pop/objects");
    std::filesystem::create_directories(path + "/.pop/refs/heads");
    std::filesystem::create_directories(path + "/.pop/refs/tags");

    std::ofstream head_file(path + "/.pop/HEAD");
    head_file << "ref: refs/heads/master\n";
    head_file.close();

    std::ofstream config_file(path + "/.pop/config");
    config_file << "[core]\n\trepositoryformatversion = 0\n\tfilemode = true\n\tbare = false\n\tlogallrefupdates = true\n";
    config_file.close();

    std::ofstream description_file(path + "/.pop/description");
    description_file << "Unnamed repository; edit this file 'description' to name the repository.\n";
    description_file.close();
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "No command provided" << std::endl;
        return 1;
    }

    std::string command = argv[1];
    
    if (command == "init") {
        std::cout << "Initialize git repository in " << std::filesystem::current_path().string() << std::endl;
        initialize_git_repository();
    } else if (command == "add" && argc == 3) {
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
        std::cout << "Usage: pop <command> [<args>]" << std::endl;
    }

    return 0;
}
