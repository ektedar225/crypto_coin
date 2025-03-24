#include <iostream>
#include <string>
#include <vector>
#include "TransactionQueue.h" // Assuming TransactionQueue is a custom class
#include "BlockChain_Honest.h" // Assuming BlockChain_Honest is a custom class
#include "Members.h" // Assuming Members is a custom class

using namespace std;

class DSCoin_Honest {
public:
    TransactionQueue* pendingTransactions;
    BlockChain_Honest* bChain;
    vector<Members*> memberlist;
    string latestCoinID;
};