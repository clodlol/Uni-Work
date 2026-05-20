class Image
{
    int rows, cols;
    int **img;

    int calcDivisor(int **filter, int m, int n)
    {
        int div = 0;
        for (int i = 0; i < m * n; ++i)
            div += filter[i / n][i % n];
        return div;
    }

    int calcCenter(int **img, int i, int j, int **filter, int m, int n, int div)
    {
        int val = 0;
        const int startI = i, startJ = j;
        while (i < i + m)
        {
            while (j < j + n)
            {
                val += img[i][j] * filter[i - startI][j - startJ];
                j++;
            }
            i++;
        }

        return (val / div);
    }

public:
    void filtering(int **filter, int m, int n, int stride)
    {
        int divisor = calcDivisor(filter, m, n);
        for (int i = 0; i < rows - m; i += stride)
        {
            for (int j = 0; j < cols - n; j += stride)
            {
                int r = i + (m / 2);
                int c = j + (n / 2);

                img[r][c] = calcCenter(img, i, j, filter, m, n, divisor);
            }
        }
    }
};