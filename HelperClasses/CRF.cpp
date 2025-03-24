#ifndef CRF_H
#define CRF_H

#include <iostream>
#include <openssl/sha.h>  // OpenSSL for SHA-256
#include <sstream>
#include <iomanip>

class CRF {
public:
    int outputsize;

    // Constructor
    CRF(int size) {
        outputsize = size;
        if (outputsize > 64) {
            throw std::invalid_argument("Output size cannot exceed 64 bytes (SHA-256 limit)");
        }
    }

    // Function to compute SHA-256 hash and return truncated output
    std::string Fn(const std::string& input) {
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, input.c_str(), input.length());
        SHA256_Final(hash, &sha256);

        std::stringstream ss;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
        }

        std::string full_hash = ss.str();
        return full_hash.substr(0, outputsize);
    }
};

#endif // CRF_H
