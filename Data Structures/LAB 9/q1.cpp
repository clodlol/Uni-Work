#include <iostream>
using namespace std;

struct AVLNode
{
    int data;
    int height;
    AVLNode *left;
    AVLNode *right;

    AVLNode(int val) : data(val), height(1), left(nullptr), right(nullptr) {}
};

class AVLOperations
{
private:
    AVLNode *root;

    int getHeight(AVLNode *node)
    {
        return node ? node->height : 0;
    }

    void updateHeight(AVLNode *node)
    {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }

    int getBalanceFactor(AVLNode *node)
    {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    AVLNode *rotateLeft(AVLNode *y)
    {
        auto x = y->right;
        y->right = x->left;
        x->left = y;
        updateHeight(y);
        updateHeight(x);
        return x;
    }
    AVLNode *rotateRight(AVLNode *y)
    {
        auto x = y->left;
        y->left = x->right;
        x->right = y;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    AVLNode *insertHelper(AVLNode *node, int key)
    {
        if (!node)
            return new AVLNode(key);
        if (key > node->data)
            node->right = insertHelper(node->right, key);
        else if (key < node->data)
            node->left = insertHelper(node->left, key);

        updateHeight(node);

        if (getBalanceFactor(node) > 1 && node->left->data < key) // LR
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        else if (getBalanceFactor(node) > 1 && node->left->data > key) // LL
        {
            return rotateRight(node);
        }
        else if (getBalanceFactor(node) < -1 && node->right->data > key) // RL
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        else if (getBalanceFactor(node) < -1 && node->right->data < key) // RR
        {
            return rotateLeft(node);
        }

        return node;
    }
    int isAVLHelper(AVLNode *node, long long minVal, long long maxVal) const
    {
        if (!node)
            return 0;
        if (!(minVal < node->data && node->data < maxVal))
            return -2;

        int lH = isAVLHelper(node->left, minVal, node->data);
        if (lH == -2)
            return -2;
        int rH = isAVLHelper(node->right, node->data, maxVal);
        if (rH == -2)
            return -2;

        if (abs(lH - rH) > 1)
            return -2;
        return 1 + max(lH, rH);
    }

    int getFloorHelper(AVLNode *node, int key, int ans = -1) const
    {
        if (!node)
            return ans;
        if (node->data == key)
            return node->data;
        if (node->data > key)
            return getFloorHelper(node->left, key, ans);

        ans = max(ans, node->data);
        return getFloorHelper(node->right, key, ans);
    }
    int getCeilHelper(AVLNode *node, int key, int ans = INT_MAX) const
    {
        if (!node)
            return ans;
        if (node->data == key)
            return node->data;
        if (node->data < key)
            return getCeilHelper(node->right, key, ans);

        ans = min(ans, node->data);
        return getCeilHelper(node->left, key, ans);
    }

public:
    AVLOperations() = default;
    AVLOperations(const AVLOperations &other) = delete;
    AVLOperations &operator=(const AVLOperations &other) = delete;

    void insert(int key)
    {
        root = insertHelper(root, key);
    }
    bool isAVL() const { return isAVLHelper(root, LLONG_MIN, LLONG_MAX) != -2; }
    int getFloor(int key) const
    {
        return getFloorHelper(root, key);
    }
    int getCeil(int key) const
    {
        int ceil = getCeilHelper(root, key);
        return ceil == INT_MAX ? -1 : ceil;
    }
    AVLNode *getRoot() const { return root; }
};