#include "CompleteBinaryTree.h"
#include <queue>

CompleteBinaryTree::CompleteBinaryTree() : root_(nullptr), count_(0) {}

CompleteBinaryTree::~CompleteBinaryTree() {
    clear();
}

void CompleteBinaryTree::deleteSubtree(TreeNode* node) {
    if (node == nullptr) {
        return;
    }
    deleteSubtree(node->left);
    deleteSubtree(node->right);
    delete node;
}

void CompleteBinaryTree::clear() {
    deleteSubtree(root_);
    root_ = nullptr;
    count_ = 0;
}

void CompleteBinaryTree::insert(int value) {
    TreeNode* newNode = new TreeNode(value);
    if (root_ == nullptr) {
        root_ = newNode;
        ++count_;
        return;
    }

    std::queue<TreeNode*> q;
    q.push(root_);

    while (!q.empty()) {
        TreeNode* cur = q.front();
        q.pop();

        if (cur->left == nullptr) {
            cur->left = newNode;
            ++count_;
            return;
        }
        q.push(cur->left);

        if (cur->right == nullptr) {
            cur->right = newNode;
            ++count_;
            return;
        }
        q.push(cur->right);
    }
}

bool CompleteBinaryTree::find(int value) const {
    if (root_ == nullptr) {
        return false;
    }
    std::queue<const TreeNode*> q;
    q.push(root_);
    while (!q.empty()) {
        const TreeNode* cur = q.front();
        q.pop();
        if (cur->data == value) {
            return true;
        }
        if (cur->left != nullptr) {
            q.push(cur->left);
        }
        if (cur->right != nullptr) {
            q.push(cur->right);
        }
    }
    return false;
}

bool CompleteBinaryTree::isComplete() const {
    if (root_ == nullptr) {
        return true;
    }
    std::queue<const TreeNode*> q;
    q.push(root_);
    bool seenEmpty = false;

    while (!q.empty()) {
        const TreeNode* cur = q.front();
        q.pop();

        if (cur->left != nullptr) {
            if (seenEmpty) {
                return false;
            }
            q.push(cur->left);
        } else {
            seenEmpty = true;
        }

        if (cur->right != nullptr) {
            if (seenEmpty) {
                return false;
            }
            q.push(cur->right);
        } else {
            seenEmpty = true;
        }
    }
    return true;
}

int CompleteBinaryTree::size() const {
    return count_;
}

bool CompleteBinaryTree::isEmpty() const {
    return count_ == 0;
}
