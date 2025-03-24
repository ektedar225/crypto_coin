#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <ctime>
#include <cstdlib>

using namespace std;

class Transaction {
public:
    string sender;
    string receiver;
    int amount;
    string transactionID;

    Transaction(string s, string r, int a, string id) {
        sender = s;
        receiver = r;
        amount = a;
        transactionID = id;
    }
};

class Block {
public:
    string previousHash;
    vector<Transaction> transactions;
    string currentHash;

    Block(string prevHash) {
        previousHash = prevHash;
        currentHash = generateHash();
    }

    void addTransaction(Transaction t) {
        transactions.push_back(t);
    }

    string generateHash() {
        return to_string(rand() % 1000000); // Simple hash for demonstration
    }
};

class DSCoin {
private:
    vector<Block> blockchain;
    vector<Transaction> pendingTransactions;
    unordered_map<string, int> balances;

public:
    DSCoin() {
        blockchain.push_back(Block("GenesisBlock"));
    }

    void addTransaction(string sender, string receiver, int amount) {
        if (balances[sender] < amount) {
            cout << "Transaction failed: Insufficient balance.\n";
            return;
        }
        string transactionID = to_string(rand() % 1000000);
        pendingTransactions.push_back(Transaction(sender, receiver, amount, transactionID));
        balances[sender] -= amount;
        balances[receiver] += amount;
        cout << "Transaction added successfully!\n";
    }

    void mineBlock() {
        if (pendingTransactions.empty()) {
            cout << "No transactions to mine.\n";
            return;
        }
        Block newBlock(blockchain.back().currentHash);
        for (Transaction t : pendingTransactions) {
            newBlock.addTransaction(t);
        }
        blockchain.push_back(newBlock);
        pendingTransactions.clear();
        cout << "Block mined successfully with hash: " << newBlock.currentHash << "\n";
    }

    void printBlockchain() {
        for (int i = 0; i < blockchain.size(); i++) {
            cout << "Block " << i << " - Hash: " << blockchain[i].currentHash << "\n";
        }
    }
};

int main() {
    srand(time(0));
    DSCoin dsc;
    dsc.addTransaction("Alice", "Bob", 10);
    dsc.addTransaction("Bob", "Charlie", 5);
    dsc.mineBlock();
    dsc.printBlockchain();
    return 0;
}
