#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class Superhero
{
private:
    string name;
    int power_level;
    vector<string> special_ability;

public:
    Superhero(string n, int pl, const vector<string> &sa)
    {
        if (pl < 1 || pl > 100)
        {
            throw invalid_argument("Power level must be between 1 and 100.");
        }
        for (const string &ability : sa)
        {
            if (ability.empty())
            {
                throw invalid_argument("Special abilities cannot be empty strings.");
            }
        }
        name = n;
        power_level = pl;
        special_ability = sa;
    }

    void display() const
    {
        cout << "Name: " << name << " | Power Level: " << power_level << "\nAbilities: ";
        for (const string &ability : special_ability)
        {
            cout << "[" << ability << "] ";
        }
        cout << "\n-------------------\n";
    }
};

void addSuperhero(vector<Superhero> &team)
{
    string name;
    int power_level;
    int ability_count;
    vector<string> abilities;

    cout << "Enter Superhero Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);

    while (true)
    {
        try
        {
            cout << "Enter Power Level (1-100): ";
            if (!(cin >> power_level))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw invalid_argument("Invalid input: Power level must be an integer.");
            }
            if (power_level < 1 || power_level > 100)
            {
                throw invalid_argument("Error: Power level out of bounds (1-100).");
            }
            break;
        }
        catch (const invalid_argument &e)
        {
            cout << e.what() << " Try again.\n";
        }
    }

    cout << "How many special abilities? ";
    cin >> ability_count;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < ability_count; ++i)
    {
        while (true)
        {
            try
            {
                string ability;
                cout << "Enter ability " << i + 1 << ": ";
                getline(cin, ability);
                if (ability.empty())
                {
                    throw invalid_argument("Error: Ability string cannot be empty.");
                }
                abilities.push_back(ability);
                break;
            }
            catch (const invalid_argument &e)
            {
                cout << e.what() << " Try again.\n";
            }
        }
    }

    team.emplace_back(name, power_level, abilities);
    cout << "Superhero added successfully!\n";
}

void displayTeam(const vector<Superhero> &team)
{
    if (team.empty())
    {
        cout << "The superhero team is currently empty.\n";
        return;
    }
    cout << "\n--- Superhero Team ---\n";
    for (const Superhero &hero : team)
    {
        hero.display();
    }
}