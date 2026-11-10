#include <iostream>
using namespace std;

struct TreeNode
{
    int data;
    int height;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int p_data) : data(p_data), height(0), left(NULL), right(NULL) {}
};

class AVLTree
{
    TreeNode *root;

    void clear(TreeNode *node)
    {
        if (!node)
            return;
        delete node;
        clear(node->left);
        clear(node->right);
    }

    TreeNode *LL(TreeNode *p)
    {
        auto A = p;
        auto B = p->left;
        // auto C = B->left;  unused, its children remain intact
        A->left = B->right;
        B->right = A;
        return B;
    }

    TreeNode *RR(TreeNode *p)
    {
        auto A = p;
        auto B = p->right;
        // auto C = B->right;  unused, its children remain intact
        A->right = B->left;
        B->left = A;
        return B;
    }

    TreeNode *LR(TreeNode *p)
    {
        auto A = p;
        auto B = p->left;
        auto C = B->right;
        B->right = C->left;
        A->left = C->right;
        C->left = B;
        C->right = A;
        return C;
    }

    TreeNode *RL(TreeNode *p)
    {
        auto A = p;
        auto B = p->right;
        auto C = B->left;
        A->right = C->left;
        B->left = C->right;
        C->left = A;
        C->right = B;
        return C;
    }

    int getBF(TreeNode *p)
    {
        int l = p->left ? p->left->height : 0;
        int r = p->right ? p->right->height : 0;
        return l - r;
    }

    int getH(TreeNode *p)
    {
        return 1 + max((p->left ? p->left->height : 0), (p->right ? p->right->height : 0));
    }

    TreeNode *insertHelper(TreeNode *root, int d)
    {

        if (!root)
            return new TreeNode(d);
        if (d < root->data)
        {
            root->left = insertHelper(root->left, d);
        }
        else if (d > root->data)
        {
            root->right = insertHelper(root->right, d);
        }
        // Equal cases don't happen

        root->height = max(getH(root->left), getH(root->right)) + 1;

        int bf = getBF(root);
        if (bf > 1) // Node is left heavy, fixed by either LL or LR
        {
            if (getBF(root->left) > 0) // Node fixed by LL
                return LL(root);
            else
                return LR(root);
        }
        else if (bf < -1) // Node is right heavy, fixed by either RR or RL
        {
            if (getBF(root->right) > 0) // Node fixed by RL
                return RL(root);
            else
                return RR(root);
        }

        return root;
    }

    TreeNode *findMin(TreeNode *root)
    {
        if (!root)
            return NULL;
        if (!root->left)
            return root;
        return findMin(root->left);
    }

    TreeNode *deleteHelper(TreeNode *root, int d)
    {
        if (!root)
            return NULL;
        if (root->data == d)
        {
            if (!root->left && !root->right)
            {
                delete root;
                return NULL;
            }

            if (!root->left)
            {
                auto temp = root->right;
                delete root;
                return temp;
            }

            if (!root->right)
            {
                auto temp = root->left;
                delete root;
                return temp;
            }

            auto temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteHelper(root->right, temp->data);
        }

        if (d < root->data)
            root->left = deleteHelper(root->left, d);
        else if (d > root->data)
            root->right = deleteHelper(root->right, d);

        root->height = max(getH(root->left), getH(root->right)) + 1;

        int bf = getBF(root);
        if (bf > 1) // Node is left heavy, fixed by either LL or LR
        {
            if (getBF(root->left) > 0) // Node fixed by LL
                return LL(root);
            else
                return LR(root);
        }
        else if (bf < -1) // Node is right heavy, fixed by either RR or RL
        {
            if (getBF(root->right) > 0) // Node fixed by RL
                return RL(root);
            else
                return RR(root);
        }

        return root;
    }

public:
    AVLTree() : root(NULL) {}
    ~AVLTree()
    {
        clear(root);
        root = NULL;
    }
    AVLTree(const AVLTree &other) = delete;
    AVLTree &operator=(const AVLTree &other) = delete;
};