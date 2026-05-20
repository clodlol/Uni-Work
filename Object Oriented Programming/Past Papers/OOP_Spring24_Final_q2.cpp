int countLen(int *arr)
{
    int i = 0;
    while (arr[i] != -1)
        i++;

    return i;
}

bool exists(int tag, int *pref)
{
    int i = 0;
    while (pref[i] != -1)
    {
        if (pref[i] == tag)
            return true;
        i++;
    }

    return false;
}

bool matchTags(int *pref, int *tags)
{
    int tagsLen = countLen(tags);
    for (int i = 0; i < tagsLen - 1; ++i)
    {
        for (int j = i + 1; j < tagsLen; ++j)
        {
            if (exists(tags[i], pref) && exists(tags[j], pref))
                return true;
        }
    }

    return false;
}

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

int *VideoSystem::GetSuggestedVideoIdsByUserPref(int *userPref)
{
    int recsLen = 0;
    for (int i = 0; i < totalVideos; ++i)
    {
        Video currVid = allVideos[i];
        if (matchTags(userPref, currVid.GetTagsList()))
            recsLen++;
    }

    int recsCounter = 0;
    int *recs = new int[recsLen + 1];
    for (int i = 0; i < totalVideos; ++i)
    {
        Video currVid = allVideos[i];
        if (matchTags(userPref, currVid.GetTagsList()))
            recs[recsCounter++] = currVid.GetId();
    }

    recs[recsCounter] = -1;

    return recs;
}