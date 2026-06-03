class social_network
{
private:
    int num_users;
    int **friends;

    bool exists(int idx, int *frnd)
    {
        int c = 0;
        while (frnd[c] != -1)
        {
            if (frnd[c] == idx)
                return true;
            c++;
        }

        return false;
    }

    int cntFrnds(int *u)
    {
        int c = 0;
        while (u[c] != -1)
            c++;

        return c;
    }

    void copyWithCounter(int *tempRow, int *oldFrnd, int &c)
    {
        c = 0;
        while (oldFrnd[c] != -1)
        {
            tempRow[c] = oldFrnd[c];
            c++;
        }
    }

public:
    void add_user(int *frnd)
    {
        int **temp = new int *[num_users + 1];
        for (int i = 0; i < num_users; ++i)
        {
            bool currIsFrnd = exists(i, frnd);
            temp[i] = new int[cntFrnds(friends[i]) + exists(i, frnd) + 1];

            int c = 0;
            copyWithCounter(temp[i], friends[i], c);

            if (currIsFrnd)
            {
                temp[i][c] = num_users;
                c++;
            }

            temp[i][c] = -1;
        }

        int c = 0;
        copyWithCounter(temp[num_users], frnd, c);
        temp[num_users][c] = -1;

        for (int i = 0; i < num_users; ++i)
            delete[] friends[i];
        delete[] friends;

        friends = temp;
        num_users++;
    }

    double compute_CC(int uIdx)
    {
        int count = cntFrnds(friends[uIdx]);

        int kU = cntFrnds(friends[uIdx]);
        int eU = 0;

        for (int i = 0; i < count - 1; ++i)
        {
            for (int j = i + 1; j < count; ++j)
            {
                if (exists(friends[uIdx][j], friends[i]))
                    eU++;
            }
        }

        return (2 * eU / static_cast<double>(kU * (kU - 1)));
    }
};