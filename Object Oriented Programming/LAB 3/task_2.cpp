#include <iostream>
#include <iomanip>
using namespace std;

void voteCasting(const char *const *const &candidates, const int &candidateCount, int *const *const &regions, int *const &total)
{
    // regions has 4 cols(fixed), candidateCount rows
    // total has length candidateCount

    for (int i = 0; i < candidateCount; i++)
    {
        int currentTotal = 0;
        for (int j = 0; j < 4; j++)
        {
            cout << "Enter the vote for candidate [" << candidates[i] << "] in region [" << (j + 1) << "]: ";
            cin >> regions[i][j];
            currentTotal += regions[i][j];
        }
        total[i] = currentTotal;
    }
}

void showRecord(const char *const *const &candidates, const int &candidateCount, const int *const *const &regions, const int *const &total)
{
    // regions has 4 cols(fixed), candidateCount rows
    // total has length candidateCount

    cout << "--------------------ELECTION RESULTS--------------------" << endl;
    cout << left << setw(10) << "Name" << setw(10) << "Region 1 " << setw(10) << "Region 2 " << setw(10) << "Region 3 " << setw(10) << "Region 4 " << setw(10) << "Total" << endl;
    cout << "--------------------------------------------------------" << endl;

    int winnerIndex = 0;
    int mostVotes = total[0];
    for (int i = 0; i < candidateCount; i++)
    {

        cout << left << setw(10) << candidates[i] << setw(10) << regions[i][0] << setw(10) << regions[i][1] << setw(10) << regions[i][2] << setw(10) << regions[i][3] << setw(10) << total[i] << endl;

        if (total[i] > mostVotes)
        {
            mostVotes = total[i];
            winnerIndex = i;
        }
    }

    cout << "Election Winner: " << candidates[winnerIndex] << " with " << mostVotes << " votes." << endl;
}

int main()
{
    int candidateCount = 3;
    char **candidates = new char *[candidateCount]{"Ashley", "Danny", "Donald"};
    int **regions = new int *[candidateCount];
    for (int i = 0; i < candidateCount; i++)
        regions[i] = new int[4]; // 4 regions(fixed)

    int *total = new int[candidateCount];

    voteCasting(candidates, candidateCount, regions, total);
    showRecord(candidates, candidateCount, regions, total);
    return 0;
}