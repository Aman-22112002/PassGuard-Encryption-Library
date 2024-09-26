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
/*
    // test function - 1
    //adding two integer values
    void add(int a,int b)
    {
        int c = a+b;
        cout<<"The value of c is "<<c<<endl;
    }

    // test function - 2
    // returns the logarithmic values
    double precise_logarithm(double base, double x, int precision) 
    {
        return round(log(x) / log(base) * pow(10, precision)) / pow(10, precision);
    }

    void logarithm(double base,double x)
    {
        
        int precision = 4;

        double result = precise_logarithm(base, x, precision);

        std::cout << std::fixed << std::setprecision(precision)
              << "The precise logarithm of " << x << " with base " << base
              << " is: " << result << std::endl;
    }

    // test function - 3
    // for Trignometric values
    double deg_to_rad(double degrees) 
    {
        return degrees * M_PI / 180.0;
    }

    double sin(double x) 
    {
        double term = x;
        double result = x;
        int i = 1;

        while (fabs(term) >= 1e-8) 
        {
            term *= (-x * x) / ((2 * i) * (2 * i + 1));
            result += term;
            i++;
        }

        return result;
    }

    double cos(double x) 
    {
        double term = 1;
        double result = 1;
        int i = 1;

        while (fabs(term) >= 1e-8) 
        {
            term *= (-x * x) / ((2 * i - 1) * (2 * i));
            result += term;
            i++;
        }

        return result;
    }

    double tan(double x) 
    {
        return sin(x) / cos(x);
    }

    void trigonometric_functions(double degrees) 
    {
        double radians = deg_to_rad(degrees);
        double sine_value = sin(radians);
        double cosine_value = cos(radians);
        double tangent_value = tan(radians);

        std::cout << "For " << degrees << " degrees:" << std::endl;
        std::cout << "Sine: " << sine_value << std::endl;
        std::cout << "Cosine: " << cosine_value << std::endl;
        std::cout << "Tangent: " << tangent_value << std::endl;
    }

    // test function - 4
    // for inverse trignometric values
    double rad_to_deg(double radians) 
    {
        return radians * 180.0 / M_PI;
    }

    double asin_deg(double x) 
    {
        if (x < -1 || x > 1) 
        {
            std::cerr << "Error: Input value out of range for arcsine function." << std::endl;
            return NAN;
        }
        return rad_to_deg(asin(x));
    }

    double acos_deg(double x) 
    {
        if (x < -1 || x > 1) 
        {
            std::cerr << "Error: Input value out of range for arccosine function." << std::endl;
            return NAN;
        }
        return rad_to_deg(acos(x));
    }

    double atan_deg(double x) 
    {
        return rad_to_deg(atan(x));
    }
    
    void inverse_trigo(double value) 
    {

        double asin_result = asin_deg(value);
        if (!std::isnan(asin_result))
        {
            std::cout << "Arcsine of " << value << " is: " << asin_result << " degrees" << std::endl;
        }

        double acos_result = acos_deg(value);
        if (!std::isnan(acos_result))
        {
            std::cout << "Arccosine of " << value << " is: " << acos_result << " degrees" << std::endl;
        }

        double atan_result = atan_deg(value);
        std::cout << "Arctangent of " << value << " is: " << atan_result << " degrees" << std::endl;

    }

    // test function - 5
    // square of a number 
    void square(unsigned long long int num) 
    {
        cout << num * num;
    }
    
    // test function - 6
    // square root of any number 
    void square_root(double num, double precision = 1e-6) 
    {
        if (num < 0) 
        {
            std::cerr << "Error: Cannot calculate square root of a negative number." << std::endl;
             // Return a negative value to indicate an error
        }

        double x0 = num; // Initial guess, can be any positive number
        double x1 = 0;

        while (true) 
        {
            x1 = 0.5 * (x0 + num / x0); // Newton-Raphson formula
            if (fabs(x1 - x0) < precision) // Check for convergence
            {
                break;
            }
            x0 = x1; // Update the guess for the next iteration
        }

        cout<<x1;
    }
*/
}
#endif