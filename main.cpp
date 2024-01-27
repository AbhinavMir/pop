#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>
using namespace std;
int initialize_pop_repository()
{
    const string &path = filesystem::current_path().string();
    if (filesystem::exists(path + "/.pop"))
    {
        cout << "Already a pop repository" << endl;
        return 1;
    }

    cout << "Initializing pop repository in " << filesystem::current_path().string() << endl;
    filesystem::create_directories(path + "/.pop/objects");
    filesystem::create_directories(path + "/.pop/refs/heads");
    filesystem::create_directories(path + "/.pop/refs/tags");

    ofstream head_file(path + "/.pop/HEAD");
    head_file << "ref: refs/heads/master\n";
    head_file.close();

    ofstream config_file(path + "/.pop/config");
    config_file << "[core]\n\trepositoryformatversion = 0\n\tfilemode = true\n\tbare = false\n\tlogallrefupdates = true\n";
    config_file.close();

    ofstream description_file(path + "/.pop/description");
    description_file << "Unnamed repository; edit this file 'description' to name the repository.\n";
    description_file.close();

    return 0;
}

string sha1(const std::string& input) {
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1((unsigned char*)input.c_str(), input.length(), hash);

    std::stringstream ss;
    for(int i = 0; i < SHA_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    return ss.str();
}

int clone(string url, string directory)
{
    if (filesystem::exists(directory))
    {
        cout << "Directory already exists" << endl;
        return 1;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "No command provided" << endl;
        return 1;
    }

    string command = argv[1];

    if (command == "init")
    {
        initialize_pop_repository();
    }
    else if (command == "add" && argc == 3)
    {
        cout << "Add: " << argv[2] << endl;
    }
    else if (command == "commit" && argc == 4 && string(argv[2]) == "-m")
    {
        cout << "Commit: " << argv[3] << endl;
    }
    else if (command == "push")
    {
        if (argc == 2)
        {
            cout << "Push" << endl;
        }
        else if (argc == 3 && string(argv[2]) == "--force")
        {
            cout << "Push with force" << endl;
        }
    }
    else if (command == "clone")
    {
        if (argc > 3 && argv[2] != NULL && argv[3] != NULL)
        {
            string url = argv[2];
            string directory = argv[3];


        }
    }
    else
    {
        cout << "Invalid command or arguments" << endl;
        cout << "Usage: pop <command> [<args>]" << endl;
    }

    return 0;
}
