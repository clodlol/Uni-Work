#include <iostream>
using namespace std;

int main()
{
    string s = "abcabcbb";
    int longest = 0;
    for (int i = 0; i < s.size(); i++)
    {
        int count = 0;
        for(int j = i+1; j < s.size(); j++)
        {   
            if(s[i] == s[j])
            {
                break;
            } else {
                
                count++;
            }
        }
        
        
    }

    system("pause");
    return 0;
}