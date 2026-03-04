#include <iostream>
#include <iomanip>
using namespace std;

class Book
{
    int id;
    string title;
    string author;
    int quantityAvailable;

public:
    Book() {}
    Book(int id, string t, string a, int q) : id(id), title(t), author(a), quantityAvailable(q) {}

    void print() const
    {
        cout << left << setw(5) << id << setw(16) << title << setw(16) << author << setw(10) << quantityAvailable << "\n";
    }

    int getId() const { return id; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getQuantity() const { return quantityAvailable; }

    void setId(const int &id) { this->id = id; }
    void setTitle(const string &s) { title = s; }
    void setAuthor(const string &s) { author = s; }
    void setQuantity(const int &q) { quantityAvailable = q; }
};

void updateBookQuantity(Book *books, const int &numBooks, const int &identifier, const int &newQuantity)
{
    for (int i = 0; i < numBooks; i++)
    {
        if (books[i].getId() == identifier)
        {
            books[i].setQuantity(newQuantity);
        }
    }
}

void inputBooksArray(Book *books, const int &numBooks)
{
    cout << "\n";
    for (int i = 0; i < numBooks; i++)
    {
        string title, author;
        int id, q;
        cout << (i + 1) << "\n";
        cout << "ID: ";
        cin >> id;
        books[i].setId(id);
        cout << "Title: ";
        cin >> title;
        books[i].setTitle(title);
        cout << "Author: ";
        cin >> author;
        books[i].setAuthor(author);
        cout << "Quantity: ";
        cin >> q;
        books[i].setQuantity(q);
        cout << "\n";
    }
}

bool validateInput(Book *books, const int &numBooks, const int &searchId, const int &quantity)
{
    bool valid = false;
    if (quantity < 0)
        return false;

    for (int i = 0; i < numBooks; i++)
    {
        if (books[i].getId() == searchId)
        {
            valid = true;
            break;
        }
    }

    return valid;
}

void printBooksArray(Book *const books, const int &numBooks)
{
    cout << "\n";
    cout << left << setw(5) << "ID" << setw(16) << "Title" << setw(16) << "Author" << setw(10) << "Quantity" << "\n";
    cout << left << setw(5) << "--" << setw(16) << "-----" << setw(16) << "------" << setw(10) << "--------" << "\n";
    for (int i = 0; i < numBooks; i++)
    {
        books[i].print();
    }
    cout << "\n";
}

int main()
{
    const int NUM_BOOKS = 2;
    int searchId = 0, newQuantity = 0;
    Book *books = new Book[NUM_BOOKS];
    inputBooksArray(books, NUM_BOOKS);

    printBooksArray(books, NUM_BOOKS);

    bool valid = false;
    while (!valid)
    {
        cout << "Enter the book id that you want to change: ";
        cin >> searchId;
        cout << "Enter the new quantity of the book: ";
        cin >> newQuantity;
        valid = validateInput(books, NUM_BOOKS, searchId, newQuantity);
    }

    updateBookQuantity(books, NUM_BOOKS, searchId, newQuantity);
    printBooksArray(books, NUM_BOOKS);

    return 0;
}