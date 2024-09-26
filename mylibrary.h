#ifndef MYLIBRARY_H_
#define MYLIBRARY_H_
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

namespace mylib{

// Function to generate random salt of specified length
std::string generateSalt(int length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::string salt;
    salt.reserve(length);
    srand(time(NULL)); // Seed for randomness
    for (int i = 0; i < length; ++i) {
        salt += charset[rand() % (sizeof(charset) - 1)];
    }
    return salt;
}

// Function to hash (encrypt) a string with salt using a simple hash function
std::string hashWithSalt(const std::string& input, const std::string& salt) {
    std::string saltedInput = salt + input;
    unsigned int hash = 0;

    for (char ch : saltedInput) {
        hash += ch;
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    std::stringstream ss;
    ss << std::hex << std::setw(8) << std::setfill('0') << hash;
    return ss.str();
}

// Function to verify a string against a hashed (encrypted) string with salt
bool verifyHashedWithSalt(const std::string& input, const std::string& hashed, const std::string& salt) {
    std::string expectedHash = hashWithSalt(input, salt);
    return (hashed == expectedHash);
}


int main() {
    std::string input = "Hello, world!";
    std::string salt = generateSalt(8); // Generate a salt of length 8
    
    // Encrypt (Hash with salt)
    std::string hashed = hashWithSalt(input, salt);
    std::cout << "Hashed (Encrypted) string: " << hashed << std::endl;

    // Verify
    bool isValid = verifyHashedWithSalt(input, hashed, salt);
    if (isValid) {
        std::cout << "Verification: Passed" << std::endl;
    } else {
        std::cout << "Verification: Failed" << std::endl;
    }

    return 0;
}

}
#endif
