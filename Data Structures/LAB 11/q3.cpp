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

struct SymbolFreq
{
    char ch;
    int freq;
};

class NodeMinHeap
{
private:
    HuffmanNode **data;
    int capacity;
    int currentSize;

    void siftUp(int index)
    {
        int parent = (index - 1) / 2;
        int child = index;
        while (child > 0)
        {
            if (data[parent]->freq > data[child]->freq)
                swap(data[parent], data[child]);
            else
                break;

            child = parent;
            parent = (parent - 1) / 2;
        }
    }
    void siftDown(int index)
    {
        int parent = index;
        while (parent < currentSize)
        {
            int leftChild = 2 * parent + 1;
            int rightChild = 2 * parent + 2;

            if (leftChild >= currentSize)
                break;

            int minChild = -1;

            if (rightChild >= currentSize)
                minChild = leftChild;
            else
                minChild = min(data[leftChild]->freq, data[rightChild]->freq) == data[leftChild]->freq ? leftChild : rightChild;

            if (data[parent]->freq > data[minChild]->freq)
                swap(data[parent], data[minChild]);
            else
                break;

            parent = minChild;
        }
    }

public:
    NodeMinHeap(int cap = 256) : capacity(cap), currentSize(0), data(new HuffmanNode *[cap]) {}
    ~NodeMinHeap()
    {
        delete[] data;
    }

    void push(HuffmanNode *node)
    {
        if (currentSize >= capacity)
            return;

        data[currentSize] = node;
        siftUp(currentSize);
        currentSize++;
    }
    HuffmanNode *popMin()
    {
        if (currentSize == 0)
            return NULL;

        auto retVal = data[0];
        data[0] = data[currentSize - 1];
        currentSize--;

        siftDown(0);
        return retVal;
    }
    int size() const { return currentSize; }
};

class TreeComparator
{
private:
    void sortDescending(SymbolFreq *arr, int n)
    {
        bool sorted = false;
        while (!sorted)
        {
            sorted = true;
            for (int i = 0; i < n - 1; ++i)
            {
                if (arr[i].freq < arr[i + 1].freq)
                {
                    swap(arr[i], arr[i + 1]);
                    sorted = false;
                }
            }
        }
    }
    int findBestSplit(const SymbolFreq *arr, int start, int end)
    {
        int ans = INT_MAX;
        int ansIdx = -1;
        int rightSum = 0;
        for (int i = start; i <= end; ++i)
        {
            rightSum += arr[i].freq;
        }

        int leftSum = 0;
        for (int i = start + 1; i <= end; ++i)
        {
            leftSum += arr[i - 1].freq;
            rightSum -= arr[i - 1].freq;

            // rightSum is sum from [i ... end]
            if (abs(leftSum - rightSum) < ans)
            {
                ans = abs(leftSum - rightSum);
                ansIdx = i;
            }
        }

        return ansIdx;
    }
    HuffmanNode *buildTopDown(SymbolFreq *arr, int start, int end)
    {
        if (start == end)
            return new HuffmanNode(arr[start].ch, arr[start].freq);

        int bestSplit = findBestSplit(arr, start, end);
        auto newNode = new HuffmanNode(0, sumFreqs(arr, start, end));
        newNode->left = buildTopDown(arr, start, bestSplit - 1);
        newNode->right = buildTopDown(arr, bestSplit, end);

        return newNode;
    }

    int sumFreqs(SymbolFreq *arr, int start, int end)
    {
        int sum = 0;
        for (int i = start; i <= end; ++i)
        {
            sum += arr[i].freq;
        }

        return sum;
    }

    HuffmanNode *buildBottomUpHeap(const SymbolFreq *arr, int n)
    {
        NodeMinHeap heap(n);
        for (int i = 0; i < n; ++i)
        {
            heap.push(new HuffmanNode(arr[i].ch, arr[i].freq));
        }

        while (heap.size() > 1)
        {
            auto a = heap.popMin();
            auto b = heap.popMin();
            auto newNode = new HuffmanNode(0, a->freq + b->freq);
            newNode->left = min(a->freq, b->freq) == a->freq ? a : b;
            newNode->right = newNode->left == a ? b : a;
            heap.push(newNode);
        }

        return heap.popMin();
    }

    int computeTotalBits(HuffmanNode *root, const SymbolFreq *arr, int n)
    {
        string *codes = new string[256];

        generateCodes(root, "", codes);

        int total = 0;
        for (int i = 0; i < n; ++i)
        {
            total += arr[i].freq * codes[(unsigned char)arr[i].ch].size();
        }

        delete[] codes;
        return total;
    }

    void printCodes(HuffmanNode *node, string codes[256], bool &first)
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
        printCodes(node->left, codes, first);
        printCodes(node->right, codes, first);
    }

    void destroyTree(HuffmanNode *node)
    {
        if (!node)
            return;
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

public:
    void compareApproaches(SymbolFreq *arr, int n)
    {
        if (n <= 0)
            return;

        // bottom-up first, so the heap sees the leaves in the original order
        HuffmanNode *bottomUp = buildBottomUpHeap(arr, n);

        sortDescending(arr, n);
        HuffmanNode *topDown = buildTopDown(arr, 0, n - 1);

        string bottomCodes[256];
        string topCodes[256];
        generateCodes(bottomUp, "", bottomCodes);
        generateCodes(topDown, "", topCodes);

        bool first = true;
        cout << "[ Bottom-Up Min-Heap Codes ]" << endl;
        printCodes(bottomUp, bottomCodes, first);
        cout << endl;
        cout << "Bottom-Up Total Bits : " << computeTotalBits(bottomUp, arr, n) << " bits" << endl;

        first = true;
        cout << endl
             << "[ Top-Down Partition Codes ]" << endl;
        printCodes(topDown, topCodes, first);
        cout << endl;
        cout << "Top-Down Total Bits : " << computeTotalBits(topDown, arr, n) << " bits" << endl;

        destroyTree(bottomUp);
        destroyTree(topDown);
    }
};

int main()
{
    SymbolFreq arr[] = {{'A', 15}, {'B', 7}, {'C', 6}, {'D', 6}, {'E', 5}};
    TreeComparator comparator;
    comparator.compareApproaches(arr, 5);
    return 0;
}