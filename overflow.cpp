#include <iostream>
#include <bitset>
#include <iomanip>
using namespace std;

int main(int argc, char* argv[]) {

    // 1️⃣ Check correct number of arguments
    if (argc != 3) {
        cout << "Error: Two floating-point arguments required." << endl;
        return 1;
    }

    // 2️⃣ Convert inputs to float
    float bound = stof(argv[1]);
    float increment = stof(argv[2]);

    // 3️⃣ Get IEEE 754 bit representations
    unsigned int bound_bits_int = *reinterpret_cast<unsigned int*>(&bound);
    unsigned int increment_bits_int = *reinterpret_cast<unsigned int*>(&increment);

    bitset<32> bound_bits(bound_bits_int);
    bitset<32> increment_bits(increment_bits_int);

    // 4️⃣ Print IEEE representations
    cout << bound_bits << endl;
    cout << increment_bits << endl;

    // 5️⃣ Extract exponent fields (bits 30–23)
    int exp_bound = (bound_bits_int >> 23) & 0xFF;
    int exp_increment = (increment_bits_int >> 23) & 0xFF;

    // 6️⃣ Compute exponent difference
    int diff = exp_bound - exp_increment;

    // 7️⃣ Detect overflow condition
    if (diff > 23) {

        cout << "Warning: Possible overflow!" << endl;
        cout << "Overflow threshold:" << endl;

        // Threshold exponent = increment exponent + 23
        int threshold_exp = exp_increment + 23;

        // Build new float:
        // sign = 0
        // exponent = threshold_exp
        // fraction = 0
        unsigned int threshold_bits_int = (threshold_exp << 23);

        bitset<32> threshold_bits(threshold_bits_int);

        float threshold = *reinterpret_cast<float*>(&threshold_bits_int);

        // Print decimal threshold
        cout << threshold << endl;

        // Print bit representation
        cout << threshold_bits << endl;
    }
    else {
        cout << "No overflow!" << endl;
    }

    return 0;
}
