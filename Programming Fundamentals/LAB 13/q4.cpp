#include <iostream>
#include <fstream>

using namespace std;

string tweetyPath = "Record1.txt";
string porkyPath = "Record2.txt";
string outputPath = "Output.txt";

int main()
{
    char tweety[6][6];
    char porky[6][6];

    ifstream tweetyFile(tweetyPath, ios::in);
    if (!tweetyFile.is_open())
    {
        cout << "Error while opening tweety record file." << endl;
        system("pause");
        return -1;
    }

    int tweetyLineCounter = 0;
    string tweetyLine;
    while (getline(tweetyFile, tweetyLine))
    {
        if (tweetyLine.size() > 6)
        {
            cout << "Tweety file contains more than 6 chars in a row." << endl;
            system("pause");
            return -1;
        }

        for (int i = 0; i < 6; i++)
        {
            tweety[tweetyLineCounter][i] = tweetyLine[i];
        }

        tweetyLineCounter++;
    }

    tweetyFile.close();

    ifstream porkyFile(porkyPath, ios::in);
    if (!porkyFile.is_open())
    {
        cout << "Error while opening porky record file." << endl;
        system("pause");
        return -1;
    }

    int porkyLineCounter = 0;
    string porkyLine;
    while (getline(porkyFile, porkyLine))
    {
        if (porkyLine.size() > 6)
        {
            cout << "Porky file contains more than 6 chars in a row." << endl;
            system("pause");
            return -1;
        }

        for (int i = 0; i < 6; i++)
        {
            porky[porkyLineCounter][i] = porkyLine[i];
        }

        porkyLineCounter++;
    }

    porkyFile.close();

    int uniqueCounter = 0;
    char uniques[72];

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if (porky[i][j] != tweety[i][j])
            {
                uniques[uniqueCounter] = porky[i][j];
                uniqueCounter++;
                uniques[uniqueCounter] = tweety[i][j];
                uniqueCounter++;
            }
        }
    }

    ofstream outputFile(outputPath, ios::app);
    if (!outputFile.is_open())
    {
        cout << "Error occured while opening output file." << endl;
        system("pause");
        return -1;
    }

    cout << "Unique elements: ";
    for (int i = 0; i < uniqueCounter; i++)
    {
        outputFile << uniques[i];
        cout << uniques[i];
    }
    cout << endl;

    outputFile.close();

    cout << endl;
    system("pause");
    return 0;
}