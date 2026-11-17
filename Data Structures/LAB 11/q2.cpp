#include <iostream>
#include <string>
using namespace std;

struct HuffmanNode
{
    char ch;
    int freq;
    HuffmanNode *left;
    HuffmanNode *right;

    HuffmanNode(char c, int f)
        : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

void generateCodes(HuffmanNode *node, string currentCode, string codes[256])
{
    if (!node)
        return;
    if (!node->left && !node->right)
    {
        codes[(unsigned char)node->ch] = (currentCode == "") ? "0" : currentCode;
        return;
    }
    generateCodes(node->left, currentCode + "0", codes);
    generateCodes(node->right, currentCode + "1", codes);
}

string encodeText(const string &text, string codes[256])
{
    string encoded = "";
    for (size_t i = 0; i < text.length(); i++)
        encoded += codes[(unsigned char)text[i]];
    return encoded;
}

string decodeText(HuffmanNode *root, const string &bits)
{
    string decoded = "";
    HuffmanNode *curr = root;
    for (size_t i = 0; i < bits.length(); i++)
    {
        curr = (bits[i] == '0') ? curr->left : curr->right;
        if (!curr->left && !curr->right)
        {
            decoded += curr->ch;
            curr = root;
        }
    }
    return decoded;
}

struct DLLNode
{
    HuffmanNode *treeNode;
    DLLNode *prev;
    DLLNode *next;

    DLLNode(HuffmanNode *node)
        : treeNode(node), prev(nullptr), next(nullptr) {}
};

class SortedDLL
{
private:
    DLLNode *head;
    DLLNode *tail;
    int count;

public:
    SortedDLL() : head(NULL), tail(NULL), count(0) {}
    ~SortedDLL()
    {
        auto ptr = head;
        while (ptr)
        {
            auto temp = ptr;
            ptr = ptr->next;
            delete temp;
        }
    }

    void insertSorted(HuffmanNode *node)
    {
        if (!head)
        {
            head = tail = new DLLNode(node);

            ++count;
            return;
        }

        if (head->treeNode->freq > node->freq)
        {
            auto temp = new DLLNode(node);
            temp->next = head;
            head->prev = temp;
            head = temp;

            ++count;
            return;
        }

        if (tail->treeNode->freq <= node->freq)
        {
            auto temp = new DLLNode(node);
            temp->prev = tail;
            tail->next = temp;
            tail = temp;

            ++count;
            return;
        }

        auto ptr = head;
        DLLNode *prev = NULL;
        while (ptr && ptr->treeNode->freq <= node->freq)
        {
            prev = ptr;
            ptr = ptr->next;
        }

        prev->next = new DLLNode(node);
        prev->next->prev = prev;
        prev->next->next = ptr;

        ptr->prev = prev->next;

        ++count;
    }
    HuffmanNode *extractMin()
    {
        if (!head)
            return NULL;

        auto temp = head;
        auto retVal = temp->treeNode;
        head = head->next;

        if (!head)
            tail = head;
        else
            head->prev = NULL;

        delete temp;
        --count;
        return retVal;
    }
    int size() const
    {
        return count;
    }
};

class HuffmanDLL
{
private:
    HuffmanNode *root;
    string codes[256];
    void destroyTree(HuffmanNode *node)
    {
        if (!node)
            return;
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

public:
    HuffmanDLL() : root(NULL) {}
    ~HuffmanDLL()
    {
        destroyTree(root);
    }

    void buildTree(const string &text)
    {
        int freq[256] = {0}; // total 256 ascii codes
        for (char c : text)
        {
            freq[(unsigned char)c]++;
        }

        SortedDLL list;

        for (int i = 0; i < 256; ++i)
        {
            if (freq[i] == 0)
                continue;

            list.insertSorted(new HuffmanNode(i, freq[i]));
        }

        while (list.size() > 1)
        {
            auto a = list.extractMin();
            auto b = list.extractMin();
            auto newNode = new HuffmanNode(0, a->freq + b->freq);
            newNode->left = min(a->freq, b->freq) == a->freq ? a : b;
            newNode->right = newNode->left == a ? b : a;
            list.insertSorted(newNode);
        }

        root = list.extractMin();
    }
    void printCodes(HuffmanNode *node, bool &first)
    {
        if (!node)
            return;
        if (!node->left && !node->right)
        {
            if (!first)
                cout << " | ";
            cout << node->ch << " : " << codes[(unsigned char)node->ch];
            first = false;
            return;
        }
        printCodes(node->left, first);
        printCodes(node->right, first);
    }

    void runDemo(const string &text)
    {
        buildTree(text);
        generateCodes(root, "", codes);

        cout << "[SLL Huffman]" << endl;
        bool first = true;
        printCodes(root, first);
        cout << endl;

        string encoded = encodeText(text, codes);
        cout << "Encoded : " << encoded << " (" << encoded.length() << " bits)" << endl;
        cout << "Decoded : " << decodeText(root, encoded) << endl;
    }
};

int main()
{
    HuffmanDLL demo;
    demo.runDemo("ILOVEDSA");
    return 0;
}