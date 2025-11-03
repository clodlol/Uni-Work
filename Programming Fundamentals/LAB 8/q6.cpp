#include <iostream>

using namespace std;

void removeVowels(char input[], char output[], int size) {
    for(int i = 0; i < size; i++) {
        if(input[i] == 'a' || input[i] == 'e' || input[i] == 'i' || input[i] == 'o' || input[i] == 'u' || input[i] == 'A' || input[i] == 'E' || input[i] == 'I' || input[i] == 'O' || input[i] == 'U') {
            output[i] = '\0';
        } else {
            output[i] = input[i];
        }
    }
}

int main() {
    const int size = 50;
    char sentence[size];
    char cleanedSentence[size];
    
    for(int i = 0; i < size; i++)
        sentence[i] = '\0';
    
    cout << "Enter a sentence: ";
    cin.getline(sentence, size+1);
    
    removeVowels(sentence, cleanedSentence, size);
    cout << "Cleaned sentence: ";
    for(int i = 0; i < size; i++)
        cout << cleanedSentence[i];
}