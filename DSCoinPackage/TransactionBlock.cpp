#ifndef TRANSACTIONBLOCK_H
#define TRANSACTIONBLOCK_H

#include <vector>
#include <string>
#include "Transaction.h"
#include "MerkleTree.h"
#include "CRF.h"

class TransactionBlock {
public:
    std::vector<Transaction*> trarray; // Array of transactions
    TransactionBlock* previous;        // Pointer to previous block
    MerkleTree Tree;                   // Merkle tree instance
    std::string trsummary;              // Summary of transactions (Merkle root)
    std::string nonce;                  // Nonce for Proof of Work
    std::string dgst;                   // Digital signature (hash)

    // Constructor to initialize the Transaction Block
    TransactionBlock(std::vector<Transaction*> t) {
        trarray = t;  // Store transactions
        previous = nullptr;
        trsummary = Tree.Build(trarray); // Compute Merkle root
        dgst = "";
    }

    // Checks if the transaction is valid or not
    bool checkTransaction(Transaction* t) {
        // Miner reward case where coinsrc_block is null
        if (t->coinsrc_block == nullptr) {
            return true;
        }

        // Check for double spending in blockchain history
        TransactionBlock* temp = this->previous;
        while (temp != t->coinsrc_block) {
            for (auto& transaction : temp->trarray) {
                if (transaction->coinID == t->coinID) {
                    return false; // Double spending detected
                }
            }
            temp = temp->previous;
        }

        // Check for double spending in the current block
        int count = 0;
        for (auto& transaction : t->coinsrc_block->trarray) {
            if (transaction->coinID == t->coinID &&
                transaction->Destination->UID == t->Source->UID) {
                count++;
            }
        }
        
        return (count == 1);
    }
};

#endif // TRANSACTIONBLOCK_H
