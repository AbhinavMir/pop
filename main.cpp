#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>
#include <filesystem>
#include <regex>
#include <curl/curl.h>
using namespace std;

int initialize_pop_repository(const string &path = filesystem::current_path().string())
{
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

string sha1(const string &input)
{
	unsigned char hash[SHA_DIGEST_LENGTH];
	SHA1((unsigned char *)input.c_str(), input.length(), hash);

	stringstream ss;
	for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
	{
		ss << hex << setw(2) << setfill('0') << (int)hash[i];
	}

	return ss.str();
}

string sha1_first_two(const string &input)
{
	unsigned char hash[SHA_DIGEST_LENGTH];
	SHA1((unsigned char *)input.c_str(), input.length(), hash);

	stringstream ss;
	for (int i = 0; i < 2; i++)
	{
		ss << hex << setw(2) << setfill('0') << (int)hash[i];
	}

	return ss.str();
}
string cat_file(string sha)
{
	const string &path = filesystem::current_path().string();
	string file_path = path + "/.pop/objects/" + sha1_first_two(sha) + "/" + sha.substr(2);
	if (!filesystem::exists(file_path))
	{
		cout << "File does not exist" << endl;
		return "";
	}

	ifstream file(file_path);
	string content((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
	return content;
}

int clone(string url, string directory)
{
	if (filesystem::exists(directory))
	{
		cout << "Directory already exists" << endl;
		return 1;
	}

	if (initialize_pop_repository(directory) != 0)
	{
		cout << "Failed to initialize pop repository" << endl;
		return 1;
	}

	ofstream config_file(directory + "/.pop/config", ios::app);

	if (!config_file)
	{
		cout << "Failed to open config file" << endl;
		return 1;
	}

	config_file << "[remote \"origin\"]\n\turl = " << url << "\n";

	config_file.close();

	return 0;
}

int fetchRefs(string url)
{
	return 0;
}

bool check_url_validity(const string &url)
{

	regex url_regex(
		R"(^
        (http|https):
        ([\w-]+\.)+[\w-]+(\/[\w- ;,./?%&=]*)?   # domain & optional path
        $)",
		regex::extended);

	return regex_match(url, url_regex);
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		cout << "No command provided" << endl;
		return 1;
	}

	string sha = sha1("Hello World");
	cout << sha << endl;
	cout << sha1_first_two("Hello World") << endl;

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

			clone(url, directory);
		}
		else if (argc > 2 && argv[2] != NULL)
		{
			string url = argv[2];
			string directory = url.substr(url.find_last_of("/") + 1);

			clone(url, directory);
		}
		else
		{
			cout << "Invalid arguments" << endl;
		}
	}
	else
	{
		cout << "Invalid command or arguments" << endl;
		cout << "Usage: pop <command> [<args>]" << endl;
	}

	return 0;
}
