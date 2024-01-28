#include <filesystem>
#include <fstream>
#include <string>
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>

class Repository {
public:
    Repository(const std::string& path) : repoPath(path) {
        if (!std::filesystem::exists(repoPath + "/.pop")) {
            initialize();
        }
    }

	std::string getRepoPath() const {
		return repoPath;
	}


private:
    std::string repoPath;

    void initialize() {
        // Initialization logic...
    }
};

class SHA1Hasher {
public:
    static std::string hash(const std::string& input) {
        unsigned char hash[SHA_DIGEST_LENGTH];
        SHA1(reinterpret_cast<const unsigned char*>(input.c_str()), input.length(), hash);
        std::stringstream ss;
        for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
            ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
        }
        return ss.str();
    }
};

// Usage in main or other functions...
