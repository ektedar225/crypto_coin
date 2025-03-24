#ifndef CONVERSION_H
#define CONVERSION_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <openssl/bn.h>
#include <openssl/pem.h>
#include <openssl/evp.h>
#include <openssl/x509.h>

class Conversion {
public:
    // Convert byte array to hex string
    static std::string byteToHex(const std::vector<unsigned char>& data) {
        std::stringstream ss;
        for (unsigned char c : data) {
            ss << std::hex << std::setw(2) << std::setfill('0') << (int)c;
        }
        return ss.str();
    }

    // Convert hex string to byte array
    static std::vector<unsigned char> hexToByte(const std::string& hex) {
        std::vector<unsigned char> bytes;
        for (size_t i = 0; i < hex.length(); i += 2) {
            std::string byteString = hex.substr(i, 2);
            unsigned char byte = (unsigned char) strtol(byteString.c_str(), nullptr, 16);
            bytes.push_back(byte);
        }
        return bytes;
    }

    // Convert byte array to DSA Public Key
    static EVP_PKEY* getPublicKey(const std::vector<unsigned char>& encodedKey) {
        const unsigned char* p = encodedKey.data();
        return d2i_PUBKEY(nullptr, &p, encodedKey.size());
    }

    // Convert byte array to DSA Private Key
    static EVP_PKEY* getPrivateKey(const std::vector<unsigned char>& encodedKey) {
        const unsigned char* p = encodedKey.data();
        return d2i_PrivateKey(EVP_PKEY_DSA, nullptr, &p, encodedKey.size());
    }
};

#endif // CONVERSION_H
