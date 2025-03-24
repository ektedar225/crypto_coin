#ifndef MERKLETREE_H
#define MERKLETREE_H

#include <iostream>
#include <vector>
#include <openssl/sha.h>
#include "Transaction.h"
#include "TreeNode.h"

class MerkleTree {
public:
    TreeNode* rootnode;
    int numdocs;

    // Constructor
    MerkleTree() : rootnode(nullptr), numdocs(0) {}

    // Helper function to initialize a TreeNode
    void nodeinit(TreeNode* node, TreeNode* l, TreeNode* r, TreeNode* p, const std::string& val) {
        node->left = l;
        node->right = r;
        node->parent = p;
        node->val = val;
    }

    // Hashing function (SHA-256)
    std::string sha256(const std::string& data) {
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, data.c_str(), data.size());
        SHA256_Final(hash, &sha256);

        std::stringstream ss;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
        }
        return ss.str();
    }

    // Converts a transaction into a string representation
    std::string get_str(Transaction* tr) {
        std::string val = tr->coinID;
        if (tr->Source == nullptr)
            val += "#Genesis";
        else
            val += "#" + tr->Source->UID;

        val += "#" + tr->Destination->UID;

        if (tr->coinsrc_block == nullptr)
            val += "#Genesis";
        else
            val += "#" + tr->coinsrc_block->dgst;

        return sha256(val);
    }

    // Builds the Merkle tree and returns the root hash
    std::string Build(std::vector<Transaction*>& tr) {
        numdocs = tr.size();
        std::vector<TreeNode*> q;

        // Create leaf nodes
        for (auto* transaction : tr) {
            TreeNode* nd = new TreeNode();
            std::string val = get_str(transaction);
            nodeinit(nd, nullptr, nullptr, nullptr, val);
            q.push_back(nd);
        }

        // Build tree bottom-up
        while (q.size() > 1) {
            TreeNode* l = q[0]; q.erase(q.begin());
            TreeNode* r = q[0]; q.erase(q.begin());

            TreeNode* nd = new TreeNode();
            std::string l_val = l->val;
            std::string r_val = r->val;
            std::string data = sha256(l_val + "#" + r_val);

            nodeinit(nd, l, r, nullptr, data);
            l->parent = nd;
            r->parent = nd;
            q.push_back(nd);
        }

        rootnode = q[0];
        return rootnode->val;
    }
};

#endif // MERKLETREE_H
