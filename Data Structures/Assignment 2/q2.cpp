#include <iostream>
using namespace std;

struct TournamentEntry
{
    int entryId;
    string teamName;
    int teamRating;
    string winnerName;
    int winnerRating;

    TournamentEntry(int p_entryId) : entryId{p_entryId}, teamName{""}, teamRating{-1}, winnerName{""}, winnerRating{-1} {}

    bool isMatch() const { return winnerName.size() > 0; }
    bool isTeam() const { return teamName.size() > 0; }
};
struct TournamentEntryNode
{
    TournamentEntry data;
    TournamentEntryNode *left;
    TournamentEntryNode *right;

    TournamentEntryNode(const TournamentEntry &p_data) : data{p_data}, left{nullptr}, right{nullptr} {}
};

class Tournament
{
private:
    TournamentEntryNode *finalNode;

    void clear(TournamentEntryNode *&root)
    {
        if (!root)
            return;

        clear(root->left);
        clear(root->right);

        delete root;
        root = nullptr;
    }

    TournamentEntryNode *findNode(TournamentEntryNode *root, int nodeId) const
    {
        if (!root)
            return nullptr;
        if (root->data.entryId == nodeId)
            return root;

        auto left = findNode(root->left, nodeId);
        if (left)
            return left;

        auto right = findNode(root->right, nodeId);
        if (right)
            return right;

        return nullptr;
    }

    TournamentEntryNode *findNodeByName(TournamentEntryNode *root, const string &teamName) const
    {
        if (!root)
            return nullptr;
        if (root->data.teamName == teamName)
            return root;

        auto left = findNodeByName(root->left, teamName);
        if (left)
            return left;

        auto right = findNodeByName(root->right, teamName);
        if (right)
            return right;

        return nullptr;
    }

    void countEmptySlots(TournamentEntryNode *root, int &count) const
    {
        if (!root)
            return;
        if (!root->left && !root->right && !root->data.isTeam())
            count++;
        countEmptySlots(root->left, count);
        countEmptySlots(root->right, count);
    }

    void findMaxDepth(TournamentEntryNode *root, int currDepth, int &maxDepth) const
    {
        if (!root)
            return;
        currDepth++;
        maxDepth = max(maxDepth, currDepth);
        findMaxDepth(root->left, currDepth, maxDepth);
        findMaxDepth(root->right, currDepth, maxDepth);
    }

    void printBracketHelper(TournamentEntryNode *root, int currDepth, int maxDepth) const
    {
        if (!root)
            return;

        currDepth++;
        for (int i = 0; i < currDepth; ++i)
            cout << "----";

        if (root->data.isMatch())
        {
            cout << "Round of " << pow(2, currDepth) << " (Entry " << root->data.entryId << ")\n";
        }

        if (root->data.isTeam())
        {
            cout << root->data.teamName << " (" << root->data.teamRating << ") [Entry " << root->data.entryId << "]";
            if (!root->left && !root->right && currDepth != maxDepth)
                cout << " (bye)";

            cout << "\n";
        }

        printBracketHelper(root->left, currDepth, maxDepth);
        printBracketHelper(root->right, currDepth, maxDepth);
    }

    void printFixturesHelper(TournamentEntryNode *root) const
    {
        if (!root)
            return;

        printFixturesHelper(root->left);
        printFixturesHelper(root->right);

        if (root->data.isMatch())
        {
            cout << "Match " << root->data.entryId << " -> ";
        }
    }

    int countTeams(TournamentEntryNode *root) const
    {
        if (!root)
            return 0;

        return (root->data.isTeam() ? 1 : 0) + countTeams(root->left) + countTeams(root->right);
    }

    int countMatches(TournamentEntryNode *root) const
    {
        if (!root)
            return 0;

        return (root->data.isMatch() ? 1 : 0) + countMatches(root->left) + countMatches(root->right);
    }

    int countByes(TournamentEntryNode *root, int currDepth, int maxDepth) const
    {
        if (!root)
            return 0;

        currDepth++;
        if (!root->left && !root->right && currDepth < maxDepth && root->data.isTeam())
            return 1;

        return countByes(root->left, currDepth, maxDepth) + countByes(root->right, currDepth, maxDepth);
    }

    TournamentEntryNode *predictChampion(TournamentEntryNode *root) const
    {
        if (!root)
            return nullptr;

        if (!root->left && !root->right)
            return root;

        if (!root->left)
            return predictChampion(root->right);
        if (!root->right)
            return predictChampion(root->left);

        auto leftChamp = predictChampion(root->left);
        auto rightChamp = predictChampion(root->right);

        if (!leftChamp)
            return rightChamp;
        if (!rightChamp)
            return leftChamp;

        return (leftChamp->data.teamRating >= rightChamp->data.teamRating) ? leftChamp : rightChamp;
    }

    TournamentEntryNode *withdrawTeamHelper(TournamentEntryNode *root, const string &teamName)
    {
        if (!root)
            return nullptr;

        if (root->data.isTeam() && root->data.teamName == teamName)
        {
            delete root;
            return nullptr;
        }

        root->left = withdrawTeamHelper(root->left, teamName);
        root->right = withdrawTeamHelper(root->right, teamName);

        if (root->data.isMatch())
        {

            if (!root->left && !root->right)
            {
                delete root;
                return nullptr;
            }

            if (!root->left)
            {
                TournamentEntryNode *survivor = root->right;
                delete root;
                return survivor;
            }

            if (!root->right)
            {
                TournamentEntryNode *survivor = root->left;
                delete root;
                return survivor;
            }
        }

        return root;
    }

    void teamJourneyHelper(TournamentEntryNode *root, const string &teamName) const
    {
        if (!root)
            return;
        teamJourneyHelper(root->left, teamName);
        teamJourneyHelper(root->right, teamName);

        if (!root->data.isMatch())
            return;

        TournamentEntryNode *oppNode = nullptr;
        if (root->left && (root->left->data.teamName == teamName || root->left->data.winnerName == teamName))
            oppNode = root->right;

        if (root->right && (root->right->data.teamName == teamName || root->right->data.winnerName == teamName))
            oppNode = root->left;

        if (!oppNode)
            return;

        cout << "Match " << root->data.entryId << ": " << teamName << " vs " << (oppNode->data.isMatch() ? oppNode->data.winnerName : oppNode->data.teamName) << " -";
        if (root->data.winnerName == "NA")
            cout << " pending\n";
        else
        {
            cout << " " << (root->data.winnerName == teamName ? "won\n" : "lost\n");
        }

        if (root->data.winnerName != "NA" && root->data.winnerName != teamName)
        {
            cout << teamName << " lost against " << (oppNode->data.isMatch() ? oppNode->data.winnerName : oppNode->data.teamName) << " in Match " << root->data.entryId << ".\n";
        }
    }

    TournamentEntryNode *firstMeetingHelper(TournamentEntryNode *root, const string &teamA, const string &teamB)
    {
        if (!root)
            return nullptr;
        if (root->data.teamName == teamA)
            return root;
        if (root->data.teamName == teamB)
            return root;
        auto leftWinner = firstMeetingHelper(root->left, teamA, teamB);
        auto rightWinner = firstMeetingHelper(root->right, teamA, teamB);

        if (leftWinner && rightWinner)
            return root;

        return leftWinner ? leftWinner : rightWinner;
    }

    bool alreadyPlayed(TournamentEntryNode *root, const string &teamName) const
    {
        if (!root)
            return false;
        if (root->data.isMatch() && root->data.winnerName != "NA" && (root->left && root->left->data.teamName == teamName || root->right && root->right->data.teamName == teamName))
            return true;
        return alreadyPlayed(root->left, teamName) || alreadyPlayed(root->right, teamName);
    }

    void printLevelHelper(TournamentEntryNode *root, int level) const
    {
        if (!root)
            return;
        if (level == 0)
        {
            if (root->data.isMatch())
                cout << "Match " << root->data.entryId << " ";
            else if (root->data.isTeam())
                cout << root->data.teamName << " ";
            return;
        }
        printLevelHelper(root->left, level - 1);
        printLevelHelper(root->right, level - 1);
    }

public:
    Tournament() : finalNode{nullptr} {}
    ~Tournament()
    {
        clear(finalNode);
    }

    void createFinal(int nodeId)
    {
        clear(finalNode);
        finalNode = new TournamentEntryNode(TournamentEntry{nodeId});

        cout << "createFinal(" << nodeId << "): Final successfully created.\n";
    }

    void splitMatch(int nodeId, int leftId, int rightId)
    {
        auto node = findNode(finalNode, nodeId);
        if (!node)
        {
            cout << "splitMatch(" << nodeId << ", " << leftId << ", " << rightId << "): Node not found.\n";
            return;
        }
        if (node->data.isMatch())
        {
            cout << "splitMatch(" << nodeId << ", " << leftId << ", " << rightId << "): Node already a match.\n";
            return;
        }
        if (node->data.isTeam())
        {
            cout << "splitMatch(" << nodeId << ", " << leftId << ", " << rightId << "): Node already holds a team.\n";
            return;
        }

        if (leftId <= 0 || rightId <= 0)
        {
            cout << "splitMatch(" << nodeId << ", " << leftId << ", " << rightId << "): One or more of the feeders have invalid ID.\n";
            return;
        }

        if (leftId == rightId)
        {
            cout << "splitMatch(" << nodeId << ", " << leftId << ", " << rightId << "): Feeders have equal IDs.\n";
            return;
        }

        if (findNode(finalNode, leftId))
        {
            cout << "splitMatch(" << nodeId << ", " << leftId << ", " << rightId << "): Left feeder already in use.\n";
            return;
        }

        if (findNode(finalNode, rightId))
        {
            cout << "splitMatch(" << nodeId << ", " << leftId << ", " << rightId << "): Right feeder already in use.\n";
            return;
        }

        node->left = new TournamentEntryNode(TournamentEntry{leftId});
        node->right = new TournamentEntryNode(TournamentEntry{rightId});
        node->data.winnerName = "NA";

        cout << "splitMatch(" << nodeId << ", " << leftId << ", " << rightId << "): Match successfully created.\n";
    }

    void assignTeam(int nodeId, const string &teamName, int rating)
    {
        auto node = findNode(finalNode, nodeId);
        if (!node)
        {
            cout << "assignTeam(" << nodeId << ", " << teamName << ", " << rating << "): Node not found.\n";
            return;
        }
        if (node->data.isMatch())
        {
            cout << "assignTeam(" << nodeId << ", " << teamName << ", " << rating << "): Node already a match.\n";
            return;
        }
        if (node->data.isTeam())
        {
            cout << "assignTeam(" << nodeId << ", " << teamName << ", " << rating << "): Node already holds a team.\n";
            return;
        }

        if (teamName.size() <= 0 || rating <= 0)
        {
            cout << "assignTeam(" << nodeId << ", " << teamName << ", " << rating << "): Invalid parameters.\n";
            return;
        }

        if (findNodeByName(finalNode, teamName))
        {
            cout << "assignTeam(" << nodeId << ", " << teamName << ", " << rating << "): Team name already in use.\n";
            return;
        }

        node->data.teamName = teamName;
        node->data.teamRating = rating;

        cout << "assignTeam(" << nodeId << ", " << teamName << ", " << rating << "): Team successfully assigned.\n";
    }

    void checkReady() const
    {
        int count = 0;
        countEmptySlots(finalNode, count);
        if (count > 0)
        {
            cout << "checkReady(): Bracket not ready, " << count << " slots empty.\n";
            return;
        }

        cout << "checkReady(): Bracket ready.\n";
    }

    void printBracket() const
    {
        int depth = 0;
        findMaxDepth(finalNode, 0, depth);

        printBracketHelper(finalNode, 0, depth);
    }

    void printLevels() const
    {
        int maxDepth = 0;
        findMaxDepth(finalNode, 0, maxDepth);
        for (int i = 0; i < maxDepth; ++i)
        {
            cout << "Level " << i << ": ";
            printLevelHelper(finalNode, i);
            cout << "\n";
        }
    }

    void printFixtures() const
    {
        printFixturesHelper(finalNode);
        cout << "\n";
    }

    void printMeasures() const
    {
        int maxDepth = 0;
        findMaxDepth(finalNode, 0, maxDepth);

        cout << "Teams: " << countTeams(finalNode) << "\n";
        cout << "Matches: " << countMatches(finalNode) << "\n";
        cout << "Rounds: " << maxDepth - 1 << "\n";
        cout << "Byes: " << countByes(finalNode, 0, maxDepth) << "\n";
        auto champion = predictChampion(finalNode);
        if (champion)
            cout << "Predicted Champion: " << champion->data.teamName << "\n";
        cout << "\n";
    }

    void recordResult(int nodeId, const string &winnerName)
    {
        auto node = findNode(finalNode, nodeId);
        if (!node)
        {
            cout << "recordResult(" << nodeId << ", " << winnerName << "): Node not found.\n";
            return;
        }
        if (!node->left && !node->right)
        {
            cout << "recordResult(" << nodeId << ", " << winnerName << "): Node is a team slot.\n";
            return;
        }
        if (node->data.winnerName != "NA")
        {
            cout << "recordResult(" << nodeId << ", " << winnerName << "): Node already has a winner.\n";
            return;
        }

        auto leftNode = node->left;
        auto rightNode = node->right;

        bool leftDecided = leftNode->data.isMatch() ? leftNode->data.winnerName != "NA" : leftNode->data.isTeam();
        bool rightDecided = rightNode->data.isMatch() ? rightNode->data.winnerName != "NA" : rightNode->data.isTeam();

        if (!leftDecided)
        {
            cout << "recordResult(" << nodeId << ", " << winnerName << "): Left feeder (entry " << leftNode->data.entryId << ") is undecided.\n";
            return;
        }
        if (!rightDecided)
        {
            cout << "recordResult(" << nodeId << ", " << winnerName << "): Right feeder (entry " << rightNode->data.entryId << ") is undecided.\n";
            return;
        }

        string leftName = leftNode->data.isMatch() ? leftNode->data.winnerName : leftNode->data.teamName;
        string rightName = rightNode->data.isMatch() ? rightNode->data.winnerName : rightNode->data.teamName;
        int leftRating = leftNode->data.isMatch() ? leftNode->data.winnerRating : leftNode->data.teamRating;
        int rightRating = rightNode->data.isMatch() ? rightNode->data.winnerRating : rightNode->data.teamRating;

        if (winnerName != leftName && winnerName != rightName)
        {
            cout << "recordResult(" << nodeId << ", " << winnerName << "): Invalid winner name.\n";
            return;
        }

        bool leftWins = (winnerName == leftName);
        int winnerRating = leftWins ? leftRating : rightRating;
        string oppName = leftWins ? rightName : leftName;
        int oppRating = leftWins ? rightRating : leftRating;

        node->data.winnerName = winnerName;
        node->data.winnerRating = winnerRating;

        cout << "recordResult(" << nodeId << ", " << winnerName << "): Match " << nodeId << ": " << winnerName << " beat " << oppName << "\n";
        if (winnerRating < oppRating)
            cout << "recordResult(" << nodeId << ", " << winnerName << "): UPSET: " << winnerRating << " beat " << oppRating << "\n";
        if (node == finalNode)
            cout << "recordResult(" << nodeId << ", " << winnerName << "): CHAMPION: " << winnerName << "\n";
    }

    void withdrawTeam(const string &teamName)
    {
        if (!findNodeByName(finalNode, teamName))
        {
            cout << "withdrawTeam(" << teamName << "): Team not found.\n";
            return;
        }

        if (alreadyPlayed(finalNode, teamName))
        {
            cout << "withdrawTeam(" << teamName << "): Team has already played and cannot withdraw.\n";
            return;
        }

        finalNode = withdrawTeamHelper(finalNode, teamName);
        cout << "withdrawTeam(" << teamName << "): Team successfully withdrawn.\n";
    }

    void teamJourney(const string &teamName) const
    {
        cout << "teamJourney(" << teamName << "): \n";
        teamJourneyHelper(finalNode, teamName);
    }

    void firstMeeting(const string &teamA, const string &teamB)
    {
        if (teamA == teamB)
        {
            cout << "firstMeeting(" << teamA << ", " << teamB << "): Both teams are the same.\n";
            return;
        }

        if (!findNodeByName(finalNode, teamA))
        {
            cout << "firstMeeting(" << teamA << ", " << teamB << "): Team " << teamA << " not found.\n";
            return;
        }

        if (!findNodeByName(finalNode, teamB))
        {
            cout << "firstMeeting(" << teamA << ", " << teamB << "): Team " << teamB << " not found.\n";
            return;
        }

        auto meetingNode = firstMeetingHelper(finalNode, teamA, teamB);
        if (!meetingNode)
        {
            cout << "firstMeeting(" << teamA << ", " << teamB << "): Teams do not meet each other.\n";
            return;
        }
        cout << "firstMeeting(" << teamA << ", " << teamB << "): Teams meet on Match " << meetingNode->data.entryId << " if they keep winning.\n";
    }
};

void buildMainBracket(Tournament &t)
{
    t.createFinal(1);
    t.splitMatch(1, 2, 3);
    t.splitMatch(2, 4, 5);
    t.splitMatch(3, 6, 7);
    t.splitMatch(4, 8, 9);
    t.splitMatch(7, 10, 11);
    t.assignTeam(8, "Lahore", 88);
    t.assignTeam(9, "Karachi", 80);
    t.assignTeam(5, "Peshawar", 79);
    t.assignTeam(6, "Quetta", 85);
    t.assignTeam(10, "Multan", 90);
    t.assignTeam(11, "Islamabad", 72);
}

void section(const string &title)
{
    cout << "\n===== " << title << " =====\n";
}

int main()
{
    section("Part A: build + validation");
    {
        Tournament t;
        t.createFinal(1);
        t.splitMatch(1, 2, 3);
        t.splitMatch(2, 4, 5);
        t.splitMatch(3, 6, 7);
        t.splitMatch(4, 8, 9);
        t.splitMatch(7, 10, 11);
        t.assignTeam(8, "Lahore", 88);
        t.assignTeam(9, "Karachi", 80);
        t.assignTeam(5, "Peshawar", 79);
        t.assignTeam(6, "Quetta", 85);
        t.assignTeam(10, "Multan", 90);
        t.checkReady();
        t.assignTeam(11, "Lahore", 70);
        t.assignTeam(11, "Islamabad", 0);
        t.assignTeam(11, "Islamabad", 72);
        t.checkReady();

        cout << "-- rejected calls --\n";
        t.splitMatch(99, 12, 13);
        t.splitMatch(1, 12, 13);
        t.splitMatch(8, 12, 13);
        t.assignTeam(2, "Hyderabad", 70);
        t.assignTeam(8, "Hyderabad", 70);
    }

    section("Part B: reports");
    {
        Tournament t;
        buildMainBracket(t);
        cout << "\n-- printBracket --\n";
        t.printBracket();
        cout << "\n-- printLevels --\n";
        t.printLevels();
        cout << "\n-- printFixtures --\n";
        t.printFixtures();
    }

    section("Part C: measures");
    {
        Tournament t;
        buildMainBracket(t);
        t.printMeasures();
    }

    section("Part D: results");
    {
        Tournament t;
        buildMainBracket(t);
        t.recordResult(2, "Lahore");
        t.recordResult(4, "Peshawar");
        t.recordResult(4, "Lahore");
        t.recordResult(4, "Karachi");
        t.recordResult(7, "Islamabad");
        cout << "\n-- bracket after two results --\n";
        t.printBracket();

        t.recordResult(2, "Peshawar");
        t.recordResult(3, "Quetta");
        t.recordResult(1, "Quetta");
        t.recordResult(8, "Lahore");
        t.recordResult(50, "Lahore");

        cout << "\n-- journeys after all results --\n";
        t.teamJourney("Lahore");
        t.teamJourney("Quetta");
    }

    section("Part E: withdrawals");
    {
        Tournament t;
        buildMainBracket(t);
        t.withdrawTeam("Karachi");
        t.printBracket();
        t.printMeasures();
        t.withdrawTeam("Multan");
        t.printMeasures();
    }

    cout << "\n-- root withdrawal --\n";
    {
        Tournament t;
        t.createFinal(1);
        t.splitMatch(1, 2, 3);
        t.assignTeam(2, "A", 50);
        t.assignTeam(3, "B", 60);
        t.withdrawTeam("A");
        t.printMeasures();
    }

    cout << "\n-- refused withdrawals --\n";
    {
        Tournament t;
        buildMainBracket(t);
        t.recordResult(4, "Lahore");
        t.withdrawTeam("Karachi");
        t.withdrawTeam("Zaman");
    }

    section("Part F: journeys + meetings");
    {
        Tournament t;
        buildMainBracket(t);
        t.teamJourney("Lahore");
        t.firstMeeting("Lahore", "Karachi");
        t.firstMeeting("Lahore", "Peshawar");
        t.firstMeeting("Lahore", "Multan");
        t.firstMeeting("Quetta", "Islamabad");
        t.firstMeeting("Lahore", "Lahore");
        t.firstMeeting("Lahore", "Nobody");
    }

    return 0;
}