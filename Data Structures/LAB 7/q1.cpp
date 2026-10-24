#include <iostream>
using namespace std;

struct TreeNode
{
    int data;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BinaryTree
{
private:
    TreeNode *root;

    void inOrderHelper(TreeNode *node) const
    {
        if (!node)
            return;
        inOrderHelper(node->left);
        cout << node->data << " ";
        inOrderHelper(node->right);
    }
    void preOrderHelper(TreeNode *node) const
    {
        if (!node)
            return;
        cout << node->data << " ";
        preOrderHelper(node->left);
        preOrderHelper(node->right);
    }
    void postOrderHelper(TreeNode *node) const
    {
        if (!node)
            return;
        postOrderHelper(node->left);
        postOrderHelper(node->right);
        cout << node->data << " ";
    }

    int countNodesHelper(TreeNode *node) const
    {
        if (!node)
            return 0;
        return 1 + countNodesHelper(node->left) + countNodesHelper(node->right);
    }
    int calculateHeightHelper(TreeNode *node) const
    {
        if (!node)
            return 0;

        return 1 + max(calculateHeightHelper(node->left), calculateHeightHelper(node->right));
    }
    int countLeavesHelper(TreeNode *node) const
    {
        if (!node)
            return 0;
        if (!node->left && !node->right)
            return 1;
        return countLeavesHelper(node->left) + countLeavesHelper(node->right);
    }

    bool isFullHelper(TreeNode *node) const
    {
        if (!node)
            return true;
        if (!node->left || !node->right)
            return false;
        return isFullHelper(node->left) && isFullHelper(node->right);
    }
    bool isBalancedHelper(TreeNode *node) const
    {
        if (!node)
            return true;

        if (abs(calculateHeightHelper(node->left) - calculateHeightHelper(node->right)) > 1)
            return false;

        return isBalancedHelper(node->left) && isBalancedHelper(node->right);
    }

    void printCurrentLevel(TreeNode *node, int level, int currLevel = 0) const
    {
        if (!node)
            return;

        if (currLevel == level)
        {
            cout << node->data << " ";
            return;
        }

        printCurrentLevel(node->left, level, currLevel + 1);
        printCurrentLevel(node->right, level, currLevel + 1);
    }

public:
    BinaryTree() : root(nullptr) {}
    void setRoot(TreeNode *r)
    {
        root = r;
    }

    void inOrder() const
    {
        inOrderHelper(root);
    }
    void preOrder() const
    {
        preOrderHelper(root);
    }
    void postOrder() const
    {
        postOrderHelper(root);
    }

    int countNodes() const
    {
        return countNodesHelper(root);
    }
    int calculateHeight() const
    {
        return calculateHeightHelper(root);
    }
    int countLeaves() const
    {
        return countLeavesHelper(root);
    }

    bool isFull() const
    {
        return isFullHelper(root);
    }
    bool isBalanced() const
    {
        return isBalancedHelper(root);
    }

    void levelOrderBFS() const
    {
        int H = calculateHeightHelper(root);
        for (int i = 0; i < H; ++i)
            printCurrentLevel(root, i);
    }
};
