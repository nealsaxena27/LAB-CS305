#include <bits/stdc++.h>
using namespace std;
const int MOD = 26;

int egcd(int a, int b, int &x, int &y){
    if (b == 0) { x = 1; y = 0; return a; }
    int x1, y1;
    int g = egcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

int modinv_int(int a, int mod){
    a %= mod; if (a < 0) a += mod;
    int x, y;
    int g = egcd(a, mod, x, y);
    int res = x % mod;
    if (res < 0) res += mod;
    return res;
}

vector<vector<int>> matrix_minor(vector<vector<int>>& M, int r, int c){
    int n = M.size();
    vector<vector<int>> minor;
    minor.reserve(n-1);
    for (int i = 0; i < n; ++i) {
        if (i == r) continue;
        vector<int> row;
        row.reserve(n-1);
        for (int j = 0; j < n; ++j) if (j != c) row.push_back(M[i][j]);
        minor.push_back(row);
    }
    return minor;
}

long long determinant(vector<vector<int>>& M){
    int n = M.size();
    if (n == 1) return (long long)M[0][0];
    if (n == 2) return (long long)M[0][0]*M[1][1] - (long long)M[0][1]*M[1][0];
    long long det = 0;
    for (int j = 0; j < n; ++j) {
        auto minor = matrix_minor(M, 0, j);
        long long cofactor = ((j % 2 == 0) ? 1 : -1) * (long long)M[0][j] * determinant(minor);
        det += cofactor;
    }
    return det;
}

vector<vector<int>> cofactor_matrix(vector<vector<int>>& M){
    int n = M.size();
    vector<vector<int>> C(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            auto minor = matrix_minor(M, i, j);
            long long det_minor = determinant(minor);
            int sign = ((i + j) % 2 == 0) ? 1 : -1;
            long long val = sign * det_minor;
            C[i][j] = (int)val;
        }
    }
    return C;
}

vector<vector<int>> transpose(const vector<vector<int>>& M){
    int n = M.size();
    vector<vector<int>> T(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            T[j][i] = M[i][j];
    return T;
}

vector<vector<int>> matrix_mod_inverse(vector<vector<int>>& M, int mod){
    int n = M.size();
    long long det = determinant(M);
    int det_mod = (int)((det % mod + mod) % mod);
    int det_inv = modinv_int(det_mod, mod);
    auto cof = cofactor_matrix(M);
    auto adj = transpose(cof);
    vector<vector<int>> inv(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            long long val = (long long)adj[i][j] * det_inv;
            int vmod = (int)((val % mod + mod) % mod);
            inv[i][j] = vmod;
        }
    }
    return inv;
}

vector<int> mat_vec_mul_mod(vector<vector<int>>& M, const vector<int>& v, int mod){
    int n = M.size();
    vector<int> res(n, 0);
    for (int i = 0; i < n; ++i) {
        long long sum = 0;
        for (int j = 0; j < n; ++j) sum += (long long)M[i][j] * v[j];
        res[i] = (int)((sum % mod + mod) % mod);
    }
    return res;
}

vector<int> text_to_numbers(const string& s){
    vector<int> out;
    for (char ch : s) {
        if (isalpha((unsigned char)ch)) {
            char up = toupper((unsigned char)ch);
            out.push_back(up - 'A');
        }
    }
    return out;
}

string numbers_to_text(const vector<int>& nums){
    string s;
    s.reserve(nums.size());
    for (int x : nums) s.push_back(char((x % MOD + MOD) % MOD + 'A'));
    return s;
}

vector<vector<int>> create_key_matrix(const string& key){
    string k;
    for (char c : key) if (isalpha((unsigned char)c)) k.push_back(toupper((unsigned char)c));
    int L = (int)k.size();
    int n = (int)round(sqrt(L));
    vector<int> nums = text_to_numbers(k);
    vector<vector<int>> M(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            M[i][j] = nums[i*n + j];
    return M;
}

vector<int> pad_plaintext(vector<int> nums, int n, int pad_val = 23){
    while ((int)nums.size() % n != 0) nums.push_back(pad_val);
    return nums;
}

string encrypt(string& plainText, vector<vector<int>>& K){
    int n = K.size();
    vector<int> nums = text_to_numbers(plainText);
    nums = pad_plaintext(nums, n);
    vector<int> out;
    for (int i = 0; i < nums.size(); i += n) {
        vector<int> block(nums.begin() + i, nums.begin() + i + n);
        auto enc = mat_vec_mul_mod(K, block, MOD);
        out.insert(out.end(), enc.begin(), enc.end());
    }
    return numbers_to_text(out);
}

string decrypt(string& cipherText, vector<vector<int>>& K){
    int n = K.size();
    auto invK = matrix_mod_inverse(K, MOD);
    vector<int> nums = text_to_numbers(cipherText);
    vector<int> out;
    for (int i = 0; i < nums.size(); i += n) {
        vector<int> block(nums.begin() + i, nums.begin() + i + n);
        auto dec = mat_vec_mul_mod(invK, block, MOD);
        out.insert(out.end(), dec.begin(), dec.end());
    }
    return numbers_to_text(out);
}

void print_matrix(const vector<vector<int>>& M){
    for (auto &r: M) {
        for (int x: r) cout<<setw(3)<<x;
        cout<<endl;
    }
}

int main(){
        cout<<"Enter key: ";
        string key; cin>>key;
        auto K = create_key_matrix(key);
        cout<<"Key matrix ("<<(int)K.size()<<"x"<<(int)K.size()<<"):\n";
        print_matrix(K);
        cout<<endl;

        cout<<"Enter plaintext: ";
        string plainText; cin>>plainText;
        string cipherText = encrypt(plainText, K);
        cout<<"Encrypted cipherText using Hill Cipher: "<<cipherText<<endl;
        string decryptedCipherText = decrypt(cipherText, K);
        cout<<"Decrypted ciphertext using Hill Cipher: "<<decryptedCipherText<<endl;
}
