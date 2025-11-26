#include <iostream>
#include <fstream>
using namespace std;

string inputPath = "Input.txt";
string encryptedPath = "Encrypted.txt";
string decryptedPath = "Decrypted.txt";

const int MAX_INPUT_LEN = 100;
const int encryptionConstant = 4;

int main()
{
    int choice = 0;
    cout << "Enter 1 to encrypt from input file. Enter 2 to decrypt from encrypt file." << endl;
    cin >> choice;

    if (choice != 1 && choice != 2)
    {
        cout << "Invalid choice." << endl;
        system("pause");
        return -1;
    }

    if (choice == 1)
    {
        ifstream inputFile(inputPath, ios::in);
        if (!inputFile.is_open())
        {
            cout << "An error occured while trying to open input file." << endl;
            system("pause");
            return -1;
        }

        int inputCharCounter = 0;
        char inputChars[MAX_INPUT_LEN];
        string inputLine;
        while (getline(inputFile, inputLine))
        {
            for (int i = 0; i < inputLine.size(); i++)
            {
                if (inputCharCounter < MAX_INPUT_LEN)
                {
                    inputChars[inputCharCounter] = inputLine[i];
                    inputCharCounter++;
                }
            }
        }

        inputFile.close();

        for (int i = 0; i < inputCharCounter; i++)
        {
            inputChars[i] += encryptionConstant;
        }

        ofstream encryptFile(encryptedPath, ios::out);
        if (!encryptFile.is_open())
        {
            cout << "An error occured while trying to open encrypt file." << endl;
            system("pause");
            return -1;
        }

        cout << "Encrypted message: ";
        for (int i = 0; i < inputCharCounter; i++)
        {
            encryptFile << inputChars[i];
            cout << inputChars[i];
        }
        cout << endl;

        encryptFile.close();
    }
    else
    {
        ifstream encryptFileRead(encryptedPath, ios::in);
        if (!encryptFileRead.is_open())
        {
            cout << "An error occured while trying to open encrypt file." << endl;
            system("pause");
            return -1;
        }

        int encryptCharCounter = 0;
        char encryptChars[MAX_INPUT_LEN];
        string encryptLine;
        while (getline(encryptFileRead, encryptLine))
        {
            if (encryptLine.size() > 100)
            {
                cout << "Encrypt file contains more than 100 chars!" << endl;
                system("pause");
                return -1;
            }

            for (int i = 0; i < encryptLine.size(); i++)
            {
                if (encryptCharCounter < MAX_INPUT_LEN)
                {
                    encryptChars[encryptCharCounter] = encryptLine[i];
                    encryptCharCounter++;
                }
            }
        }

        encryptFileRead.close();

        char decryptChars[MAX_INPUT_LEN];
        int decryptCharCounter = 0;

        cout << "Decrypted message: ";
        for (int i = 0; i < encryptCharCounter; i++)
        {
            decryptChars[decryptCharCounter] = (encryptChars[i] - encryptionConstant);
            cout << decryptChars[decryptCharCounter];
            decryptCharCounter++;
        }
        cout << endl;

        ofstream decryptFile(decryptedPath, ios::app);
        if (!decryptFile.is_open())
        {
            cout << "An error occured while trying to open decrypt file." << endl;
            system("pause");
            return -1;
        }

        for (int i = 0; i < decryptCharCounter; i++)
        {
            decryptFile << decryptChars[i];
        }

        decryptFile.close();
    }

    cout << endl;
    system("pause");
    return 0;
}