class Video
{
    int *tagsList;
    int id;

public:
    int *GetTagsList();
    int GetId();
};

class VideoSystem
{
    Video *allVideos;
    int totalVideos;

public:
    int *GetSuggestedVideoIdsByUserPref(int *);
};

int countUserPrefs(int *userPref)
{
    int i = 0;
    while (userPref[i] != -1)
    {
        i++;
    }

    return i;
}

int *VideoSystem::GetSuggestedVideoIdsByUserPref(int *userPref)
{
    // for each string in userPref, find that string in each video of allVideos, if found store allVideos[foundIndex].id
    // count first
    int vidCount = 0, userPrefsCnt = countUserPrefs(userPref);
    for (int i = 0; i < totalVideos; ++i)
    {
        int *tags = allVideos[i].GetTagsList();
        int j = 0, matchedCount = 0;
        bool alreadySuggested = false;
        while (tags[j] != -1)
        {
            for (int k = 0; k < userPrefsCnt; ++k)
            {
                if (tags[j] == userPref[k])
                {
                    matchedCount++;
                    if (matchedCount == 2)
                    {
                        vidCount++;
                        alreadySuggested = true;
                        break;
                    }
                }
            }

            if (alreadySuggested)
            {
                matchedCount = 0;
                break;
            }

            j++;
        }
    }

    int *res = new int[vidCount + 1];
    int resCounter = 0;
    res[vidCount] = -1;

    for (int i = 0; i < totalVideos; ++i)
    {
        int *tags = allVideos[i].GetTagsList();
        int j = 0, matchedCount = 0;
        bool alreadySuggested = false;
        while (tags[j] != -1)
        {
            for (int k = 0; k < userPrefsCnt; ++k)
            {
                if (tags[j] == userPref[k])
                {
                    matchedCount++;
                    if (matchedCount >= 2)
                    {
                        res[resCounter++] = allVideos[i].GetId();
                        alreadySuggested = true;
                        break;
                    }
                }
            }

            if (alreadySuggested)
            {
                matchedCount = 0;
                break;
            }

            j++;
        }
    }

    return res;
}