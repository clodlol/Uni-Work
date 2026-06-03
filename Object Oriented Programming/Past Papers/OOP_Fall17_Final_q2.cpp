template <typename T>
void rotateOnce(T **mat, int size)
{
    T topRight = mat[0][size - 1];
    for (int i = 0, j = size - 1; j > 0; --j)
        mat[i][j] = mat[i][j - 1];
    for (int j = 0, i = 0; i < size - 1; ++i)
        mat[i][j] = mat[i + 1][j];
    for (int i = size - 1, j = 0; j < size - 1; ++j)
        mat[i][j] = mat[i][j + 1];
    for (int j = size - 1, i = size - 1; i > 1; --i)
        mat[i][j] = mat[i - 1][j];
    mat[1][size - 1] = topRight;
}

template <typename T>
void rotateSquare(T **mat, int size, int rotateVal)
{
    if (size <= 0)
    {
        throw "Matrix of size 0 passed\n";
    }

    if (rotateVal < 0)
    {
        throw "Rotate value cannot be less than 0\n";
    }

    if (!mat)
        throw "nullptr passed\n";

    for (int i = 0; i < size; ++i)
        if (!mat[i])
            throw "nullptr passed\n";

    for (int i = 0; i < rotateVal; ++i)
        rotateOnce(mat, size);
}