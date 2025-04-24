#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<map>

using namespace std;

string BWT(string T)
{
    T =  T+"$"; 
    int n = T.size();
    vector<string> BWM;

    for(int i = 0; i < n; ++i)
    {
        string rotation = T.substr(i) + T.substr(0, i);
        BWM.push_back(rotation);
    }

    sort(BWM.begin(), BWM.end()); 

    string BWT = "";
    for(int i = 0; i < n; ++i)
    {
        BWT += BWM[i][n - 1];      
    }

    return BWT;
}

string LF_Map(string BWT)
{
    int n = BWT.size();
    map<char, int> freq;        
    vector<int> occ(n);         
    int start_index = -1;
    for (int i = 0; i < n; ++i)
    {
        if (BWT[i] == '$') start_index = i;
        occ[i] = freq[BWT[i]];
        freq[BWT[i]]++;
    }
    string T = "";
    while (T.size() < n)
    {
        T = BWT[start_index] + T;
        int jump = 0;
        for (auto& p : freq)
        {
            if (p.first == BWT[start_index]) break;
            jump += p.second;
        }

        start_index = jump + occ[start_index];
    }

    return T;
}


int main()
{
    string T;
    cout<<"Enter Input String: ";
    cin>>T;
    string bw=BWT(T);
    cout<<"BWT: "<<bw<<endl;
    cout<<"OG String: "<< LF_Map(bw);
}