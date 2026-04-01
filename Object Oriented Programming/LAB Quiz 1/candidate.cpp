#include <iostream>
using namespace std;

class Candidate
{
private:
    int m_id{};
    string m_name{};
    int *m_voteCount{};

public:
    Candidate(int id = 0, const string &name = "")
        : m_id{id}, m_name{name}, m_voteCount{new int(0)} {}
    ~Candidate() { delete m_voteCount; }

    void cast() { *m_voteCount++; }

    int getId() const { return m_id; }

    Candidate &operator++()
    {
        cast();
        return *this;
    }

    int operator+(const Candidate &candidate)
    {
        return *m_voteCount + *candidate.m_voteCount;
    }

    bool operator>(const Candidate &candidate)
    {
        return *m_voteCount > *candidate.m_voteCount;
    }

    friend ostream &operator<<(ostream &out, const Candidate &candidate);

    void display() const
    {
        cout << *this;
    }
};

ostream &operator<<(ostream &out, const Candidate &candidate)
{
    return out << "Candidate Details: "
               << candidate.m_name << ", " << *candidate.m_voteCount << " votes" << "\n";
}

class Election
{
private:
    int m_candidateCount{};
    Candidate *m_candidates{};

public:
    Election(int candidateCount)
        : m_candidateCount{candidateCount}, m_candidates{new Candidate[candidateCount]} {}
    ~Election() { delete[] m_candidates; }

    void display()
    {
        cout << "ELECTION DETAILS: " << "\n";
        for (int i = 0; i < m_candidateCount; ++i)
        {
            m_candidates[i].display();
        }
    }

    void cast(int id)
    {
        int foundIndex = -1;
        for (int i = 0; i < m_candidateCount; ++i)
        {
            if (m_candidates[i].getId() == id)
            {
                foundIndex = i;
                break;
            }
        }

        if (foundIndex != -1)
        {
            ++m_candidates[foundIndex];
        }
        else
        {
            cout << "Candidate not found." << "\n";
        }
    }

    Candidate &operator[](int i)
    {
        return m_candidates[i];
    }
};