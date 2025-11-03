#include <bits/stdc++.h>
using namespace std;

string permute(string &bits, vector<int> &perm){
    string out; out.reserve(perm.size());
    for(int p: perm) out.push_back(bits[p-1]);
    return out;
}
string lshift(string &s, int n){ 
    return s.substr(n) + s.substr(0,n);
}

pair<string,string> SDESSubKeyGenerate(string initialKey){
    vector<int> P10 = {3,5,2,7,4,10,1,9,8,6};
    vector<int> P8  = {6,3,7,4,8,5,10,9};
    string p10 = permute(initialKey, P10);
    string L = p10.substr(0,5), R = p10.substr(5,5);
    L = lshift(L,1); R = lshift(R,1);
    string s = L + R;
    string K1 = permute(s, P8);
    L = lshift(L,2); R = lshift(R,2);
    s = L + R;
    string K2 = permute(s, P8);
    return {K1,K2};
}

int main(){
    cout << "Enter 10-bit key (string like 1010000010): ";
    string initialKey; cin>>initialKey;
    pair<string, string> subKeys = SDESSubKeyGenerate(initialKey);
    string K1 = subKeys.first, K2 = subKeys.second;
    cout << "Initial Key: " << initialKey << "\nSubkey K1: " << K1 << "\nSubkey K2: " << K2 << '\n';
    return 0;
}
