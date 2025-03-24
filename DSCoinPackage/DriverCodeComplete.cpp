#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Transaction {
public:
    string sender, receiver;
    int amount;
    Transaction(string s, string r, int a) : sender(s), receiver(r), amount(a) {}
};

class Block {
public:
    vector<Transaction> transactions;
    string previousHash;
    string hash;
    
    Block(string prevHash) : previousHash(prevHash) {}
    void addTransaction(Transaction t) {
        transactions.push_back(t);
    }
};

class Blockchain {
public:
    vector<Block> chain;
    Blockchain() {
        chain.push_back(Block("GenesisBlock"));
    }
    void addBlock(Block newBlock) {
        chain.push_back(newBlock);
    }
};

class Member {
public:
    string name;
    int balance;
    Member(string n, int b) : name(n), balance(b) {}
    void sendMoney(Member &receiver, int amount, Blockchain &bc) {
        if (balance >= amount) {
            balance -= amount;
            receiver.balance += amount;
            Block newBlock(bc.chain.back().hash);
            newBlock.addTransaction(Transaction(name, receiver.name, amount));
            bc.addBlock(newBlock);
        } else {
            cout << "Insufficient balance!\n";
        }
    }
};

int main() {
    Blockchain DSCoin;
    Member alice("Alice", 1000);
    Member bob("Bob", 500);
    
    alice.sendMoney(bob, 200, DSCoin);
    cout << "Alice Balance: " << alice.balance << "\n";
    cout << "Bob Balance: " << bob.balance << "\n";
    return 0;
}
