#ifndef TREENODE_H
#define TREENODE_H

#include <string>

class TreeNode {
public:
    TreeNode* parent;
    TreeNode* left;
    TreeNode* right;
    std::string val;

    // Constructor
    TreeNode(std::string value = "") : parent(nullptr), left(nullptr), right(nullptr), val(value) {}
};

#endif // TREENODE_H
