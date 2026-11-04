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

class AVLAdvanced
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

    AVLNode *findMin(AVLNode *node)
    {
        return (!node || !node->left) ? node : findMin(node->left);
    }
    AVLNode *rebalance(AVLNode *node)
    {
        if (!node)
            return node;

        updateHeight(node);

        int bf = getBalanceFactor(node);
        if (bf > 1 && getBalanceFactor(node->left) < 0) // LR
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        else if (bf > 1 && getBalanceFactor(node->left) >= 0) // LL
        {
            return rotateRight(node);
        }
        else if (bf < -1 && getBalanceFactor(node->right) > 0) // RL
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        else if (bf < -1 && getBalanceFactor(node->right) <= 0) // RR
        {
            return rotateLeft(node);
        }

        return node;
    }
    AVLNode *deleteNodeHelper(AVLNode *node, int key)
    {
        if (!node)
            return node;

        if (key < node->data)
        {
            node->left = deleteNodeHelper(node->left, key);
        }
        else if (key > node->data)
        {
            node->right = deleteNodeHelper(node->right, key);
        }
        else
        {
            if (!node->right && !node->left)
            {
                delete node;
                return NULL;
            }

            if (!node->right)
            {
                auto c = node->left;
                delete node;
                return c;
            }

            if (!node->left)
            {
                auto c = node->right;
                delete node;
                return c;
            }

            auto c = findMin(node->right);
            node->data = c->data;
            node->right = deleteNodeHelper(node->right, c->data);
        }

        node = rebalance(node);
        return node;
    }
    int getDiameterHelper(AVLNode *node, int &maxDiameter)
    {
        if (!node)
            return 0;
        int l = getDiameterHelper(node->left, maxDiameter);
        int r = getDiameterHelper(node->right, maxDiameter);
        maxDiameter = max(maxDiameter, l + r + 1);
        return 1 + max(l, r);
    }
    void convertToDLLHelper(AVLNode *node, AVLNode *&head, AVLNode *&prev)
    {
        if (!node)
            return;

        convertToDLLHelper(node->left, head, prev);

        if (!prev)
            head = node;
        else
        {
            prev->right = node;
            node->left = prev;
        }
        prev = node;

        convertToDLLHelper(node->right, head, prev);
    }

public:
    AVLAdvanced();
    void remove(int key)
    {
        root = deleteNodeHelper(root, key);
    }

    int getDiameter()
    {
        int maxDiameter = 0;
        getDiameterHelper(root, maxDiameter);
        return maxDiameter;
    }

    AVLNode *convertToDLL()
    {
        AVLNode *head = nullptr;
        AVLNode *prev = nullptr;
        convertToDLLHelper(root, head, prev);
        root = nullptr;
        return head;
    }

    AVLNode *getRoot()
    {
        return root;
    }
};