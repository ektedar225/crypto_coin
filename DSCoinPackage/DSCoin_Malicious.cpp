#include <iostream>
#include <string>
#include <vector>
#include "TransactionQueue.h" // Assuming TransactionQueue is a custom class
#include "BlockChain_Malicious.h" // Assuming BlockChain_Malicious is a custom class
#include "Members.h" // Assuming Members is a custom class

using namespace std;

class DSCoin_Malicious {
public:
    TransactionQueue* pendingTransactions;
    BlockChain_Malicious* bChain;
    vector<Members*> memberlist;
    string latestCoinID;
};