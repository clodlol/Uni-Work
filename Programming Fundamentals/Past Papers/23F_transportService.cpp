const int CITY_MAX = 100;

int countPassengers(int cityMap[CITY_MAX][CITY_MAX], int size, int startRow, int startCol)
{
    // we will assume the starting position is based on 0 index, and is valid for given size
    int count = 0;
    int jStart = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = jStart; j < size; j++)
        {
            if ((cityMap[i][j] != -1) && (i >= startRow && j >= startCol))
                count += cityMap[i][j];

            if (cityMap[i][j] == -1)
            {
                jStart = j - 1;

                if (i + 1 < size && cityMap[i + 1][jStart] == -1)
                    return -1;

                break;
            }

            jStart = j;
        }
    }
}