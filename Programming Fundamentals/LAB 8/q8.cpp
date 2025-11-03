#include <iostream>

using namespace std;

void charFrequency(char arr[], int size) {
    int freq[size];
    for(int i = 0; i < size; i++)
        freq[i] = 0;
        
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(arr[j] == arr[i] && i != j)
                freq[i]++;
        }
        freq[i]++;
    }
    
    for(int i = 0; i < size; i++)
        cout << freq[i] << " ";
}

int main() {
    const int size = 5;
    char sentence[size];
    
    cout << "Enter a sentence: ";
    cin.getline(sentence, size+1);
    
    charFrequency(sentence, size);
}