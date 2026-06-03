class ratings
{
    int **users;
    char **movies;
    int total_users;
    int total_movies;
    int get_user_index(char id);

    int cntMovs(int *movies)
    {
        int i = 0;
        while (movies[i] != -1)
            i++;
        return i;
    }

    int cntUsers(char *users)
    {
        int i = 0;
        while (users[i] != '!')
            i++;
        return i;
    }

    bool exists(int el, int *arr)
    {
        int i = 0;
        while (arr[i] != -1)
        {
            if (arr[i] == el)
                return true;
            i++;
        }

        return false;
    }

public:
    void Add_rating(char u, int m)
    {
        int uIdx = get_user_index(u), mIdx = m - 1;
        int oldMovCnt = cntMovs(users[uIdx]), oldUserCnt = cntUsers(movies[mIdx]);

        int *tempMovs = new int[oldMovCnt + 2];
        for (int i = 0; i < oldMovCnt; ++i)
            tempMovs[i] = users[uIdx][i];
        tempMovs[oldMovCnt] = m;
        tempMovs[oldMovCnt + 1] = -1;

        delete[] users[uIdx];
        users[uIdx] = tempMovs;

        char *tempUsers = new char[oldUserCnt + 2];
        for (int i = 0; i < oldUserCnt; ++i)
            tempUsers[i] = movies[mIdx][i];
        tempUsers[oldUserCnt] = u;
        tempUsers[oldUserCnt + 1] = '!';

        delete[] movies[mIdx];
        movies[mIdx] = tempUsers;
    }

    int *recommend(char u)
    {
        int uIdx = get_user_index(u);
        int recsCount = 0;
        int mCnt = cntMovs(users[uIdx]);
        bool *counted = new bool[total_movies]();
        for (int i = 0; i < mCnt; ++i)
        {
            char *commonCands = movies[users[uIdx][i] - 1];
            int j = 0;
            while (commonCands[j] != '!')
            {
                int commonCandIdx = get_user_index(commonCands[j]);
                int k = 0;
                while (users[commonCandIdx][k] != -1)
                {
                    int currMovIdx = users[commonCandIdx][k];
                    if (!exists(currMovIdx, users[uIdx]) && !counted[currMovIdx - 1])
                    {
                        recsCount++;
                        counted[currMovIdx - 1] = true;
                    }
                    k++;
                }
                j++;
            }
        }

        int *recs = new int[recsCount + 1];
        int recsCounter = 0;

        for (int i = 0; i < total_movies; ++i)
        {
            if (counted[i])
            {
                recs[recsCounter++] = i + 1;
            }
        }

        recs[recsCounter] = -1;
        delete[] counted;

        return recs;
    }
};