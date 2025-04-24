/*huffman gives you prefix free code so that there is no ambiguity in decoding the string from a bitvector*/

#include <iostream>
#include <unordered_map>
#include <queue>
#include <string>
#include <memory>

using namespace std;

struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
    Node(Node* l, Node* r) : ch('\0'), freq(l->freq + r->freq), left(l), right(r) {}
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

void buildCodeMap(Node* root, const string& path, unordered_map<char, string>& codeMap) {
    if (!root) return;
    if (!root->left && !root->right) {
        codeMap[root->ch] = path;
    }
    buildCodeMap(root->left, path + "0", codeMap);
    buildCodeMap(root->right, path + "1", codeMap);
}

string huffmanEncode(const string& text, Node*& rootOut, unordered_map<char, string>& codeMapOut) {
    unordered_map<char, int> freqMap;
    for (char c : text) freqMap[c]++;

    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (auto& pair : freqMap)
        pq.push(new Node(pair.first, pair.second));

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        pq.push(new Node(left, right));
    }

    Node* root = pq.top();
    unordered_map<char, string> codeMap;
    buildCodeMap(root, "", codeMap);

    for (auto &p:codeMap) cout<<"char: "<<p.first<<", code: "<<p.second<<endl;
    string encoded;
    for (char c : text) encoded += codeMap[c];

    rootOut = root;
    codeMapOut = codeMap;
    return encoded;
}

string huffmanDecode(const string& encoded, Node* root) {
    string decoded;
    Node* curr = root;
    for (char bit : encoded) {
        if (bit == '0') curr = curr->left;
        else curr = curr->right;

        if (!curr->left && !curr->right) {
            decoded += curr->ch;
            curr = root;
        }
    }
    return decoded;
}

void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

// Example usage
int main() {
    string text = "mississippi";

    Node* root = nullptr;
    unordered_map<char, string> codeMap;

    string encoded = huffmanEncode(text, root, codeMap);
    cout << "Encoded: " << encoded << endl;

    string decoded = huffmanDecode(encoded, root);
    cout << "Decoded: " << decoded << endl;

    freeTree(root); // Clean up memory
    return 0;
}