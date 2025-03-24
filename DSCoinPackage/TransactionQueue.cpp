#ifndef TRANSACTIONQUEUE_H
#define TRANSACTIONQUEUE_H

#include "Transaction.h"
#include <stdexcept> // For exception handling

class TransactionQueue {
public:
    Transaction* firstTransaction;
    Transaction* lastTransaction;
    int numTransactions;

    // Constructor
    TransactionQueue() {
        firstTransaction = nullptr;
        lastTransaction = nullptr;
        numTransactions = 0;
    }

    // ENQUEUE OPERATION
    void AddTransactions(Transaction* transaction) {
        // Case for empty queue
        if (firstTransaction == nullptr) {
            firstTransaction = transaction;
            firstTransaction->next = nullptr;
            firstTransaction->previous = nullptr;
            lastTransaction = firstTransaction;
            numTransactions = 1;
            return;
        }

        // General case for insertion
        transaction->next = nullptr;
        lastTransaction->next = transaction;
        transaction->previous = lastTransaction;
        lastTransaction = transaction;
        numTransactions++;
    }

    // DEQUEUE OPERATION
    Transaction* RemoveTransaction() {
        if (numTransactions == 0) {
            throw std::runtime_error("Queue is empty!"); // Equivalent to EmptyQueueException
        }

        // Single element case
        if (numTransactions == 1) {
            Transaction* temp = firstTransaction;
            firstTransaction = nullptr;
            lastTransaction = nullptr;
            numTransactions--;
            return temp;
        }

        // General deletion case
        Transaction* temp = firstTransaction;
        firstTransaction = firstTransaction->next;
        firstTransaction->previous = nullptr;
        numTransactions--;
        return temp;
    }

    // LENGTH OF QUEUE
    int size() {
        return numTransactions;
    }
};

#endif // TRANSACTIONQUEUE_H
