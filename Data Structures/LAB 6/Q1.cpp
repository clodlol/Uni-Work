#include <iostream>
using namespace std;

template <typename T>
struct Node
{
    T val;
    Node<T> *next;
    Node(const T &p_val) : val{p_val}, next{NULL} {}
    Node(const T &p_val, Node<T> *p_next) : val{p_val}, next{p_next} {}
};

template <typename T>
class Stack
{
    int count;
    Node<T> *sp;

    void reverseStack()
    {
        Node<T> *prev = NULL;
        auto ptr = sp;
        while (sp != NULL)
        {
            auto temp = sp->next;
            sp->next = prev;
            prev = sp;
            sp = temp;
        }
        sp = prev;
    }

public:
    Stack() : count{0}, sp{NULL} {}
    ~Stack()
    {
        clear();
    }

    Stack(const Stack &other) : count{0}, sp{NULL}
    {
        auto otherSp = other.sp;
        while (otherSp != NULL)
        {
            this->push(otherSp->val);
            otherSp = otherSp->next;
        }
        reverseStack();
        count = other.count;
    }

    Stack &operator=(const Stack &other)
    {
        if (this == &other)
            return *this;

        Stack temp = other;
        swap(count, temp.count);
        swap(sp, temp.sp);
        return *this;
    }

    bool isEmpty() const { return count == 0; }

    T pop()
    {
        if (isEmpty())
            return T{};
        auto data = sp->val;
        auto temp = sp;
        sp = sp->next;
        count--;
        delete temp;
        return data;
    }

    void push(const T &data)
    {
        auto newNode = new Node<T>(data);
        newNode->next = sp;
        sp = newNode;
        count++;
    }

    T top() const
    {
        if (isEmpty())
            return T{};
        return sp->val;
    }

    void clear()
    {
        while (sp != NULL)
        {
            auto temp = sp;
            sp = sp->next;
            delete temp;
        }
        count = 0;
    }
};

class WebPage
{
private:
    string url;
    string title;

public:
    WebPage() : url{}, title{} {}
    WebPage(string p_url, string p_title) : url{p_url}, title{p_title} {}

    const string &getTitle() const { return title; }
    const string &getUrl() const { return url; }

    void display() const { cout << title << " (" << url << ") "; }
};

class Browser
{
private:
    Stack<WebPage> backStack;
    Stack<WebPage> forwardStack;
    WebPage currentPage;

public:
    Browser() : backStack{}, forwardStack{}, currentPage{} {}

    void visitPage(string url, string title)
    {
        if (!currentPage.getUrl().empty())
        {
            backStack.push(currentPage);
        }

        currentPage = WebPage(url, title);
        forwardStack.clear();
    }
    void goBack()
    {
        if (!canGoBack())
            return;
        forwardStack.push(currentPage);
        currentPage = backStack.pop();
    }

    void goForward()
    {
        if (!canGoForward())
            return;
        backStack.push(currentPage);
        currentPage = forwardStack.pop();
    }

    void showCurrentPage() const
    {
        if (currentPage.getUrl().empty())
            return;
        cout << "Current Page: ";
        currentPage.display();
        cout << "\n";
    }

    void showBackHistory() const
    {
        auto copy = backStack;
        cout << "BACK HISTORY\n";
        while (!copy.isEmpty())
        {
            copy.pop().display();
            cout << "\n";
        }
    }

    void showForwardHistory() const
    {
        auto copy = forwardStack;
        cout << "FORWARD HISTORY\n";
        while (!copy.isEmpty())
        {
            copy.pop().display();
            cout << "\n";
        }
    }
    bool canGoBack() const
    {
        return !backStack.isEmpty();
    }
    bool canGoForward() const
    {
        return !forwardStack.isEmpty();
    }

    void clearHistory()
    {
        backStack.clear();
        forwardStack.clear();
    }

    bool isHistoryEmpty() const
    {
        return forwardStack.isEmpty() && backStack.isEmpty();
    }
};

static int failures = 0;

void check(bool cond, const string &what)
{
    cout << (cond ? "[PASS] " : "[FAIL] ") << what << "\n";
    if (!cond)
        failures++;
}

void section(const string &name)
{
    cout << "\n=== " << name << " ===\n";
}

int main()
{
    Browser b;

    section("Fresh browser");
    check(b.isHistoryEmpty(), "history is empty");
    check(!b.canGoBack() && !b.canGoForward(), "cannot go back or forward");
    b.goBack();
    b.goForward();
    b.showCurrentPage();

    section("First visit does not pollute history");
    b.visitPage("google.com", "Google");
    check(!b.canGoBack(), "no back history after first visit");
    b.showCurrentPage();

    section("Visit several pages");
    b.visitPage("wikipedia.org", "Wikipedia");
    b.visitPage("github.com", "GitHub");
    b.visitPage("stackoverflow.com", "Stack Overflow");
    b.showCurrentPage();
    b.showBackHistory();
    b.showForwardHistory();
    check(b.canGoBack(), "can go back");
    check(!b.canGoForward(), "cannot go forward");

    section("Go back twice");
    b.goBack();
    b.goBack();
    b.showCurrentPage();
    b.showBackHistory();
    b.showForwardHistory();
    check(b.canGoBack() && b.canGoForward(), "can go both ways");

    section("Go forward once");
    b.goForward();
    b.showCurrentPage();

    section("New visit clears forward history");
    b.visitPage("reddit.com", "Reddit");
    b.showCurrentPage();
    b.showBackHistory();
    b.showForwardHistory();
    check(!b.canGoForward(), "forward history cleared");
    b.goForward();
    b.showCurrentPage();

    section("Go back to the very start, then past it");
    while (b.canGoBack())
        b.goBack();
    b.showCurrentPage();
    b.goBack();
    b.showCurrentPage();
    b.showForwardHistory();

    section("Copying a Browser");
    Browser copy = b;
    Browser assigned;
    assigned = b;
    copy.visitPage("example.com", "Example");
    check(b.canGoForward(), "original unaffected by copy's navigation");
    check(assigned.canGoForward(), "assigned copy has same history");

    section("Clear history");
    b.clearHistory();
    check(b.isHistoryEmpty(), "history empty after clearHistory");
    check(!b.canGoBack() && !b.canGoForward(), "cannot navigate after clear");
    b.showCurrentPage();

    cout << "\n"
         << (failures == 0 ? "All checks passed." : "Some checks FAILED.") << "\n";
    return failures;
}