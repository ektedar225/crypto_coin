#include <iostream>
#include <vector>
#include <string>
#include "DSCoin_Honest.h"
#include "DSCoin_Malicious.h"
#include "Transaction.h"
#include "TransactionBlock.h"
#include "Members.h"
#include "EmptyQueueException.h"

using namespace std;

class Moderator {
public:
    // Honest Initialization
    void initializeDSCoin(DSCoin_Honest& DSObj, int coinCount) {
        int k = 100000;

        // Setting the source for the coins
        Members obj;
        obj.UID = "Moderator";

        // Initializing the coins and distributing in Round Robin fashion
        for (int i = 0; i < coinCount; i++) {
            Transaction temp;
            temp.coinID = to_string(k++);
            temp.Source = &obj;
            temp.Destination = &DSObj.memberlist[i % DSObj.memberlist.size()];
            temp.coinsrc_block = nullptr;
            DSObj.pendingTransactions.AddTransactions(temp);
        }

        // k-1 because in the last iteration k was incremented
        DSObj.latestCoinID = to_string(k - 1);
        int j = 0;

        // Forming TransactionBlocks
        while (true) {
            vector<Transaction> arr(DSObj.bChain.tr_count);
            for (int q = 0; q < DSObj.bChain.tr_count; q++) {
                try {
                    arr[q] = DSObj.pendingTransactions.RemoveTransaction();
                } catch (EmptyQueueException& e) {
                    cerr << e.what() << endl;
                }
            }

            TransactionBlock* temp = new TransactionBlock(arr);

            // Adding the coins in mycoins of the destination of transaction
            for (auto& txn : arr) {
                txn.Destination->mycoins.push_back({txn.coinID, temp});
            }
            j += DSObj.bChain.tr_count;

            DSObj.bChain.InsertBlock_Honest(temp);

            // Condition to check if all the coins have been distributed
            if (j == coinCount)
                break;
        }
    }

    // Malicious Initialization
    void initializeDSCoin(DSCoin_Malicious& DSObj, int coinCount) {
        int k = 100000;

        // Setting the source for the coins
        Members obj;
        obj.UID = "Moderator";

        // Initializing the coins and distributing in Round Robin fashion
        for (int i = 0; i < coinCount; i++) {
            Transaction temp;
            temp.coinID = to_string(k++);
            temp.Source = &obj;
            temp.Destination = &DSObj.memberlist[i % DSObj.memberlist.size()];
            temp.coinsrc_block = nullptr;
            DSObj.pendingTransactions.AddTransactions(temp);
        }

        // k-1 because in the last iteration k was incremented
        DSObj.latestCoinID = to_string(k - 1);
        int j = 0;

        // Forming TransactionBlocks
        while (true) {
            vector<Transaction> arr(DSObj.bChain.tr_count);
            for (int q = 0; q < DSObj.bChain.tr_count; q++) {
                try {
                    arr[q] = DSObj.pendingTransactions.RemoveTransaction();
                } catch (EmptyQueueException& e) {
                    cerr << e.what() << endl;
                }
            }

            TransactionBlock* temp = new TransactionBlock(arr);

            // Adding the coins in mycoins of the destination of transaction
            for (auto& txn : arr) {
                txn.Destination->mycoins.push_back({txn.coinID, temp});
            }
            j += DSObj.bChain.tr_count;

            DSObj.bChain.InsertBlock_Malicious(temp);

            // Condition to check if all the coins have been distributed
            if (j == coinCount)
                break;
        }
    }
};
