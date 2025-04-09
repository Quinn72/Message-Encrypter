#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <sstream>
#include <bitset>

// Simple Base64 encoding table
const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";

std::string base64_encode(const std::string& input) {
    std::string encoded;
    int val = 0;
    int valb = -6;

    for (unsigned char c : input) {
        val = (val << 8) + c;
        valb += 8;

        while (valb >= 0) {
            encoded.push_back(base64_chars[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }

    if (valb > -6) {
        encoded.push_back(base64_chars[((val << 8) >> (valb + 8)) & 0x3F]);
    }

    while (encoded.size() % 4) {
        encoded.push_back('=');
    }

    return encoded;
}

// Caesar Cipher
char caesar(char c, int shift) {
    if (std::isupper(c))
        return (c - 'A' + shift) % 26 + 'A';
    else if (std::islower(c))
        return (c - 'a' + shift) % 26 + 'a';
    else
        return c;
}

// Atbash Cipher
char atbash(char c) {
    if (std::isupper(c))
        return 'Z' - (c - 'A');
    else if (std::islower(c))
        return 'z' - (c - 'a');
    else
        return c;
}

// ROT13 Cipher
char rot13(char c) {
    return caesar(c, 13);
}

int main() {
    std::string input;
    std::cout << "Enter string to encrypt: ";
    std::getline(std::cin, input);

    while (input.empty() || input == " ") {
        system("cls");
        std::cout << "Enter string to encrypt: ";
        std::getline(std::cin, input);
    }

    int caesarShift;
    std::cout << "Enter Caesar cipher shift amount: ";
    std::cin >> caesarShift;

    while (caesarShift == 0) {
        system("cls");
        std::cout << "Enter Caesar cipher shift amount: ";
        std::cin >> caesarShift;
    }

    // Apply Caesar, then Atbash, then ROT13
    std::string encrypted;
    for (char c : input) {
        char step1 = caesar(c, caesarShift);
        char step2 = atbash(step1);
        char step3 = rot13(step2);
        encrypted.push_back(step3);
    }

    std::string base64Encoded = base64_encode(encrypted);

    system("cls");
    std::cout << "Encrypted (Caesar + Atbash + ROT13), then Base64 encoded:\n";
    std::cout << base64Encoded << std::endl;

    return 0;
}
