#include <iostream>
#include <string>
#include "CRF.h" // Assuming CRF is a custom class for hashing

using namespace std;

class TransactionBlock {
public:
    string dgst;
    string trsummary;
    string nonce;
    TransactionBlock* previous;
    int trarray_size; // Equivalent to length in Java
};

class BlockChain_Honest {
public:
    int tr_count;
    static const string start_string;
    TransactionBlock* lastBlock;

    BlockChain_Honest() : lastBlock(nullptr), tr_count(0) {}

    void InsertBlock_Honest(TransactionBlock* newBlock) {
        CRF obj(64);
        string st;

        // Simultaneous nonce and dgst calculation
        for (long i = 1000000001L; i <= 9999999999L; i++) {
            st = to_string(i);
            string temp;

            // Empty BlockChain case
            if (lastBlock == nullptr) {
                temp = obj.Fn(start_string + "#" + newBlock->trsummary + "#" + st);
            }
            // General Case
            else {
                temp = obj.Fn(lastBlock->dgst + "#" + newBlock->trsummary + "#" + st);
            }

            // Check if the first four letters are "0000"
            if (temp.substr(0, 4) == "0000") {
                newBlock->previous = lastBlock;
                newBlock->dgst = temp;
                newBlock->nonce = st;
                tr_count = newBlock->trarray_size;
                lastBlock = newBlock;
                return;
            }
        }
    }
};

const string BlockChain_Honest::start_string = "DSCoin";
