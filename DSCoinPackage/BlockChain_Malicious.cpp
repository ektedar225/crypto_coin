#include <iostream>
#include <string>
#include <vector>
#include "CRF.h" // Assuming CRF is a custom class for hashing
#include "MerkleTree.h" // Assuming MerkleTree is a custom class

using namespace std;

class TransactionBlock {
public:
    string dgst;
    string trsummary;
    string nonce;
    TransactionBlock* previous;
    vector<string> trarray; // Equivalent to Java array

    bool checkTransaction(const string& transaction) {
        // Placeholder for actual transaction validation
        return true;
    }
};

class BlockChain_Malicious {
public:
    int tr_count;
    static const string start_string;
    vector<TransactionBlock*> lastBlocksList;

    static bool checkTransactionBlock(TransactionBlock* tB) {
        CRF obj(64);

        if (tB->dgst.substr(0, 4) != "0000")
            return false;

        if (tB->previous == nullptr) {
            if (tB->dgst != obj.Fn(start_string + "#" + tB->trsummary + "#" + tB->nonce))
                return false;
        } else {
            if (tB->dgst != obj.Fn(tB->previous->dgst + "#" + tB->trsummary + "#" + tB->nonce))
                return false;
        }

        MerkleTree Tree;
        if (tB->trsummary != Tree.Build(tB->trarray))
            return false;

        for (const auto& transaction : tB->trarray) {
            if (!tB->checkTransaction(transaction))
                return false;
        }

        return true;
    }

    TransactionBlock* FindLongestValidChain() {
        TransactionBlock* ret = lastBlocksList[0];
        int max = 0;

        for (auto* block : lastBlocksList) {
            TransactionBlock* temp = block;
            int indmax = 0;

            while (temp != nullptr) {
                if (checkTransactionBlock(temp))
                    indmax++;
                else
                    indmax = 0;
                temp = temp->previous;
            }

            if (indmax > max) {
                max = indmax;
                int compl = 0;
                TransactionBlock* flag = block;
                while (flag != nullptr) {
                    compl++;
                    flag = flag->previous;
                }
                flag = block;
                for (int j = 0; j < compl - max; j++) {
                    flag = flag->previous;
                }
                ret = flag;
            }
        }
        return ret;
    }

    void InsertBlock_Malicious(TransactionBlock* newBlock) {
        TransactionBlock* lastBlock = this->FindLongestValidChain();
        CRF obj(64);
        string st;

        for (long i = 1000000001L; i <= 9999999999L; i++) {
            st = to_string(i);
            string temp;

            if (lastBlock == nullptr) {
                temp = obj.Fn(start_string + "#" + newBlock->trsummary + "#" + st);
            } else {
                temp = obj.Fn(lastBlock->dgst + "#" + newBlock->trsummary + "#" + st);
            }

            if (temp.substr(0, 4) == "0000") {
                newBlock->nonce = st;
                newBlock->previous = lastBlock;
                newBlock->dgst = temp;
                int x = 0;

                for (size_t j = 0; j < lastBlocksList.size(); j++) {
                    if (lastBlocksList[j] == lastBlock) {
                        lastBlocksList[j] = newBlock;
                        x = 1;
                        break;
                    }
                }

                if (x == 0) {
                    for (size_t q = 0; q < lastBlocksList.size(); q++) {
                        if (lastBlocksList[q] == nullptr) {
                            lastBlocksList[q] = newBlock;
                            break;
                        }
                    }
                }
                return;
            }
        }
    }
};

const string BlockChain_Malicious::start_string = "DSCoin";