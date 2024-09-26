#include<iostream>
#include"mylibrary.h"

using namespace std;
using namespace mylib;
//https://chatgpt.com/c/41e38095-c7ad-4934-9e6f-b8f9186abb0b
int main() {
    std::string input = "aman@0101";
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