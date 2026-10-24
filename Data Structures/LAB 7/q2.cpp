#include <iostream>
using namespace std;

struct BSTNode
{
    int data;
    BSTNode *left;
    BSTNode *right;

    BSTNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BinarySearchTree
{
private:
    BSTNode *root;

    BSTNode *insertHelper(BSTNode *node, int val)
    {
        if (!node)
            return new BSTNode(val);

        if (val < node->data)
            node->left = insertHelper(node->left, val);

        if (val > node->data)
            node->right = insertHelper(node->right, val);

        return node;
    }
    bool searchHelper(BSTNode *node, int val) const
    {
        if (!node)
            return false;

        if (node->data == val)
            return true;

        return (node->data < val) ? (searchHelper(node->right, val)) : (searchHelper(node->left, val));
    }

    void kthSmallestHelper(BSTNode *node, int k, int &count, int &result) const
    {
        if (!node)
            return;
        kthSmallestHelper(node->left, k, count, result);
        count++;
        if (count == k)
            result = node->data;

        kthSmallestHelper(node->right, k, count, result);
    }
    void kthLargestHelper(BSTNode *node, int k, int &count, int &result) const
    {
        if (!node)
            return;
        kthLargestHelper(node->right, k, count, result);
        count++;
        if (count == k)
            result = node->data;
        kthLargestHelper(node->left, k, count, result);
    }
    void convertToGreaterSumTreeHelper(BSTNode *node, int &runningSum)
    {
        if (!node)
            return;
        convertToGreaterSumTreeHelper(node->right, runningSum);
        node->data += runningSum;
        runningSum = node->data;
        convertToGreaterSumTreeHelper(node->left, runningSum);
    }

    void inOrderHelper(BSTNode *node) const
    {
        if (!node)
            return;
        inOrderHelper(node->left);
        cout << node->data << " ";
        inOrderHelper(node->right);
    }

public:
    BinarySearchTree() : root{nullptr} {}

    void insert(int val)
    {
        root = insertHelper(root, val);
    }
    bool search(int val) const
    {
        return searchHelper(root, val);
    }

    int findKthSmallest(int k) const
    {
        int count = 0;
        int result = 0;
        kthSmallestHelper(root, k, count, result);
        return result;
    }
    int findKthLargest(int k) const
    {
        int count = 0;
        int result = 0;
        kthLargestHelper(root, k, count, result);
        return result;
    }

    void convertToGreaterSumTree()
    {
        int sum = 0;
        convertToGreaterSumTreeHelper(root, sum);
    }
    void printInOrder() const
    {
        inOrderHelper(root);
    }
};
