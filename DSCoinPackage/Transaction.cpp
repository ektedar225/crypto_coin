#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Members;
class TransactionBlock;

class Transaction {
public:
    std::string coinID;
    Members* Source;               // Pointer to Source member
    Members* Destination;          // Pointer to Destination member
    TransactionBlock* coinsrc_block; // Pointer to the block containing this transaction
    Transaction* next;              // Pointer to the next transaction in the list
    Transaction* previous;          // Pointer to the previous transaction in the list

    // Constructor
    Transaction() : Source(nullptr), Destination(nullptr), coinsrc_block(nullptr), next(nullptr), previous(nullptr) {}
};

#endif // TRANSACTION_H
