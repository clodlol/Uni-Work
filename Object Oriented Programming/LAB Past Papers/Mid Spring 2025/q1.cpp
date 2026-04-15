#include <iostream>
using namespace std;

class TicTacToe
{
private:
    const int M = 3;
    const int N = 3;
    char **board{};

    bool checkRow(int rowNum, char playerChar)
    {
        for (int j = 0; j < N; ++j)
        {
            if (board[rowNum][j] != playerChar)
                return false;
        }

        return true;
    }
    bool checkCol(int colNum, char playerChar)
    {
        for (int i = 0; i < M; ++i)
        {
            if (board[i][colNum] != playerChar)
                return false;
        }

        return true;
    }
    bool checkDiagonals(char playerChar)
    {
        // main diagonal
        for (int i = 0, j = 0; i < M && j < N; ++i, ++j)
        {
            if (board[i][j] != playerChar)
                return false;
        }

        // anti diagonal
        for (int i = 0, j = N - 1; i < M; ++i, j = N - 1 - i)
        {
            if (board[i][j] != playerChar)
                return false;
        }

        return true;
    }

public:
    TicTacToe()
    {
        board = new char *[M];
        for (int i = 0; i < M; ++i)
        {
            board[i] = new char[N];
            for (int j = 0; j < N; ++j)
            {
                board[i][j] = ' ';
            }
        }
    }
    ~TicTacToe()
    {
        for (int i = 0; i < M; ++i)
            delete[] board[i];

        delete[] board;
    }

    void showBoard() const
    {
        for (int i = 0; i < M; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                cout << board[i][j] << " ";
            }
            cout << "\n";
        }
    }

    void updateBoard(char playerChar, int posI, int posJ)
    {
        if (posI >= M || posI < 0 || posJ >= N || posJ < 0)
        {
            cout << "Error while updating state.\n";
            return;
        }

        if (board[posI][posJ] != ' ')
        {
            cout << "Can't update a filled square.\n";
            return;
        }

        board[posI][posJ] = playerChar;
    }

    bool checkWin(char playerChar)
    {
        for (int i = 0; i < M; ++i)
        {
            if (checkRow(i, playerChar))
                return true;
        }

        for (int j = 0; j < N; ++j)
        {
            if (checkCol(j, playerChar))
                return true;
        }

        if (checkDiagonals(playerChar))
            return true;

        return false;
    }

    bool checkDraw()
    {
        for (int i = 0; i < M; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                if (board[i][j] == ' ')
                    return false;
            }
        }

        return true;
    }
};

int main()
{
    cout << "Welcome to TIC-TAC-TOE! Play the game by entering the corresponsding indices to fill squares! Enter -1 to quit.\n\n";

    TicTacToe game{};

    while (true)
    {
        int choiceX = 0, choiceY = 0;
        cout << "Player 1's turn: ";
        cin >> choiceX >> choiceY;
        if (choiceX == -1 || choiceY == -1)
            break;

        game.updateBoard('O', choiceY, choiceX);
        game.showBoard();
        if (game.checkWin('O'))
        {
            cout << "Player A wins!\n";
            break;
        }
        else if (game.checkDraw())
        {
            cout << "Draw!\n";
            break;
        }

        cout << "Player 2's turn: ";
        cin >> choiceX >> choiceY;
        if (choiceX == -1 || choiceY == -1)
            break;

        game.updateBoard('X', choiceY, choiceX);
        game.showBoard();
        if (game.checkWin('X'))
        {
            cout << "Player B wins!\n";
            break;
        }
        else if (game.checkDraw())
        {
            cout << "Draw!\n";
            break;
        }
    }

    return 0;
}