// fp_overflow_checker.cpp
// CS3339 Spring 2026 - Homework 2
// Name : Sarbocha Pandey

#include <iostream>
#include <bitset>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <iomanip>

// Reinterpret float bytes as an unsigned int (no value conversion)
unsigned int floatToBits(float f) {
    unsigned int bits;
    std::memcpy(&bits, &f, sizeof(float));
    return bits;
}

// Reinterpret unsigned int bytes as a float (no value conversion)
float bitsToFloat(unsigned int bits) {
    float f;
    std::memcpy(&f, &bits, sizeof(float));
    return f;
}

// Print the IEEE 754 bits of a float as: sign(1) exponent(8) mantissa(23)
void printIEEE(float f) {
    unsigned int bits = floatToBits(f);

    // Isolate each field via bit shifting and masking
    unsigned int sign     = (bits >> 31) & 0x1;
    unsigned int exponent = (bits >> 23) & 0xFF;
    unsigned int mantissa = bits & 0x7FFFFF;

    // Use bitset to print each field in binary
    std::cout << std::bitset<1>(sign)  << " "
              << std::bitset<8>(exponent) << " "
              << std::bitset<23>(mantissa);
}

int main(int argc, char* argv[]) {
    // Require exactly 2 arguments after the executable name
    if (argc != 3) {
        std::cout << "usage:" << std::endl;
        std::cout << "\t./fp_overflow_checker loop_bound loop_counter" << std::endl;
        std::cout << std::endl;
        std::cout << "\tloop_bound is a positive floating-point value" << std::endl;
        std::cout << "\tloop_counter is a positive floating-point value" << std::endl;
        return 1;
    }

    float loopBound   = std::atof(argv[1]);
    float loopCounter = std::atof(argv[2]);

    // Print the IEEE bit representation of both inputs
    std::cout << "Loop bound:   ";
    printIEEE(loopBound);
    std::cout << std::endl;

    std::cout << "Loop counter: ";
    printIEEE(loopCounter);
    std::cout << std::endl;
    std::cout << std::endl;

    // Extract the 8-bit biased exponents from each value
    int boundExp   = (int)((floatToBits(loopBound)   >> 23) & 0xFF);
    int counterExp = (int)((floatToBits(loopCounter) >> 23) & 0xFF);

    // Overflow happens when the exponent gap >= 24 (23 mantissa bits + 1 implicit bit)
    // meaning the counter is too small to change the bound
    int expDiff = boundExp - counterExp;

    if (expDiff < 24) {
        std::cout << "There is no overflow!" << std::endl;
    } else {
        // Build threshold float: sign=0, exponent = counterExp+24, mantissa=0
        // This is the smallest value where adding the counter has no effect
        unsigned int thresholdBits = (unsigned int)(counterExp + 24) << 23;
        float threshold = bitsToFloat(thresholdBits);

        std::cout << "Warning: Possible overflow!" << std::endl;
        std::cout << "Overflow threshold:" << std::endl;

        // Print threshold in base-10 scientific notation, then in bits
        std::cout << "\t" << std::scientific << std::setprecision(5) << threshold << std::endl;
        std::cout << "\t";
        printIEEE(threshold);
        std::cout << std::endl;
    }

    return 0;
}
