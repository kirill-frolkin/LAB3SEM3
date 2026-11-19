#pragma once

#include <iostream>

class CompleteBinaryTree {
private:
    struct TreeNode {
        int data;
        TreeNode* left;
        TreeNode* right;
        explicit TreeNode(int v) : data(v), left(nullptr), right(nullptr) {}
    };

    TreeNode* root_;
    int count_;

    void deleteSubtree(TreeNode* node);

public:
    CompleteBinaryTree();
    ~CompleteBinaryTree();

    CompleteBinaryTree(const CompleteBinaryTree&) = delete;
    CompleteBinaryTree& operator=(const CompleteBinaryTree&) = delete;

    void insert(int value);
    bool find(int value) const;
    bool isComplete() const;
    void clear();

    int size() const;
    bool isEmpty() const;
};
