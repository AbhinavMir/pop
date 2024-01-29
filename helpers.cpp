#include <filesystem>
#include <fstream>
#include <string>
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>
#include <iostream>

#define GIT_PROTOCOL_POR 9418

class BlobManager
{
public:
	std::string sha1_first_two(const std::string &sha)
	{
		// Assuming this function returns the first two characters of the SHA1 hash
		return sha.substr(0, 2);
	}

	std::string cat_file(std::string sha)
	{
		const std::string &path = std::filesystem::current_path().string();
		std::string file_path = path + "/.pop/objects/" + sha1_first_two(sha) + "/" + sha.substr(2);

		if (!std::filesystem::exists(file_path))
		{
			std::cout << "File does not exist" << std::endl;
			return "";
		}

		std::ifstream file(file_path);
		std::string content((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
		return content;
	}
};

class Crypto
{
public:
	std::string sha1(const std::string &input)
	{
		unsigned char hash[SHA_DIGEST_LENGTH];
		SHA1(reinterpret_cast<const unsigned char *>(input.c_str()), input.length(), hash);

		std::stringstream ss;
		for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
		{
			ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
		}

		return ss.str();
	}

	std::string sha1_first_two(const std::string &input)
	{
		unsigned char hash[SHA_DIGEST_LENGTH];
		SHA1(reinterpret_cast<const unsigned char *>(input.c_str()), input.length(), hash);

		std::stringstream ss;
		for (int i = 0; i < 2; i++)
		{
			ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
		}

		return ss.str();
	}
}

class RepositoryManager
{
public:
	Repository(const std::string &path) : repoPath(path)
	{
		if (!std::filesystem::exists(repoPath + "/.pop"))
		{
			initialize();
		}
	}

	std::string getRepoPath() const
	{
		return repoPath;
	}

	std::int initializeRepository(const std::string &path = std::filesystem::current_path().string())
	{
		if (std::filesystem::exists(path + "/.pop"))
		{
			std::cout << "Already a pop repository" << std::endl;
			return 1;
		}

		std::cout << "Initializing pop repository in " << std::filesystem::current_path().string() << std::endl;
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

		return 0;
	}

private:
	std::string repoPath;
};

class GitNetworkProtocol
{
public:
	int getFromLocalRepository(const std::string &sha)
	{
		return 0;
	}

	int getFromSmartHTTP(const std::string &sha)
	{
		return 0;
	}

	int getFromDumbHTTP(const std::string &sha)
	{
		return 0;
	}

	int getFromGitProtocol(const std::string &sha)
	{
		return 0;
	}
}

class Authentication
{
public:
	int authenticate(const std::string &username, const std::string &password)
	{
		return 0;
	}
}