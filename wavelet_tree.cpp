#include <iostream>
#include <unordered_set>
#include <string>
#include <memory>
#include <vector>
using namespace std;


struct WaveletNode {
    WaveletNode* left;
    WaveletNode* right;
    vector<int> bitvector;
    char ch;                            // Only used in leaves

    WaveletNode() : left(nullptr), right(nullptr) {}
    WaveletNode(char c) : left(nullptr), right(nullptr), ch(c) {}
};

WaveletNode* BuildWavelet(const string& T, const vector<char>& alphabet) {
    if (alphabet.size() == 1) {
        return new WaveletNode(alphabet[0]);  // Leaf node
    }

    int mid = alphabet.size() / 2;
    unordered_set<char> leftalpha(alphabet.begin(), alphabet.begin() + mid);
    unordered_set<char> rightalpha(alphabet.begin() + mid, alphabet.end());

    string leftstring = "", rightstring = "";
    vector<int> bitvector;

    for (char c : T) {
        if (leftalpha.count(c)) {
            bitvector.push_back(0);
            leftstring += c;
        } else {
            bitvector.push_back(1);
            rightstring += c;
        }
    }

    WaveletNode* node = new WaveletNode();
    node->bitvector = bitvector;

    node->left = BuildWavelet(leftstring, vector<char>(alphabet.begin(), alphabet.begin() + mid));
    node->right = BuildWavelet(rightstring, vector<char>(alphabet.begin() + mid, alphabet.end()));

    return node;
}

char access(WaveletNode* root,int index)
{
    if(!root->left&&!root->right) return root->ch;
    else if (root->bitvector[index]==0) return access(root->left,index);
    else return access(root->right,index);
}

int rank(WaveletNode* root,int index , char ch)
{
    
}
int main()
{
    string T = "mississippi";
    unordered_set<char> uset;

    for(int i =0 ;i <T.size();++i)
    {
        if(uset.find(T[i])==uset.end())uset.insert(T[i]);
    }
    WaveletNode* root = BuildWavelet(T,vector<char>(uset.begin(),uset.end()));
    cout<<access(root, 5);
}