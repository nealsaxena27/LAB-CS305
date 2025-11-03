#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

char matrix[5][5];

void generateKeyMatrix(string key) {
    bool used[26] = {false};
    key.erase(remove(key.begin(), key.end(), ' '), key.end());
    transform(key.begin(), key.end(), key.begin(), ::toupper);
    for (char &c : key) if (c == 'J') c = 'I';
    string newKey = "";
    for (char c : key) {
        if (!used[c - 'A']) {
            used[c - 'A'] = true;
            newKey += c;
        }
    }
    for (char c = 'A'; c <= 'Z'; c++) {
        if (c == 'J') continue;
        if (!used[c - 'A']) {
            used[c - 'A'] = true;
            newKey += c;
        }
    }
    int idx = 0;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            matrix[i][j] = newKey[idx++];
}

void findPosition(char c, int &row, int &col) {
    if (c == 'J') c = 'I';
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == c) {
                row = i;
                col = j;
                return;
            }
        }
    }
}

string prepareText(string text, bool forEncryption) {
    text.erase(remove(text.begin(), text.end(), ' '), text.end());
    transform(text.begin(), text.end(), text.begin(), ::toupper);
    string result = "";
    for (size_t i = 0; i < text.length(); i++) {
        char a = text[i];
        char b = (i + 1 < text.length()) ? text[i + 1] : 'X';

        if (a == 'J') a = 'I';
        if (b == 'J') b = 'I';

        if (a == b) {
            result += a;
            result += 'X';
        } else {
            result += a;
            result += b;
            i++;
        }
    }

    if (result.length() % 2 != 0)
        result += 'X';

    return result;
}

string encrypt(string plaintext) {
    string pt = prepareText(plaintext, true);
    string ct = "";

    for (size_t i = 0; i < pt.length(); i += 2) {
        int r1, c1, r2, c2;
        findPosition(pt[i], r1, c1);
        findPosition(pt[i + 1], r2, c2);

        if(r1 == r2){
            ct += matrix[r1][(c1 + 1) % 5];
            ct += matrix[r2][(c2 + 1) % 5];
        }
        else if(c1 == c2){
            ct += matrix[(r1 + 1) % 5][c1];
            ct += matrix[(r2 + 1) % 5][c2];
        }
        else{
            ct += matrix[r1][c2];
            ct += matrix[r2][c1];
        }
    }
    return ct;
}

string decrypt(string ciphertext) {
    string pt = "";
    for (size_t i = 0; i < ciphertext.length(); i += 2) {
        int r1, c1, r2, c2;
        findPosition(ciphertext[i], r1, c1);
        findPosition(ciphertext[i + 1], r2, c2);

        if(r1 == r2){
            pt += matrix[r1][(c1 + 4) % 5];
            pt += matrix[r2][(c2 + 4) % 5];
        }
        else if(c1 == c2){
            pt += matrix[(r1 + 4) % 5][c1];
            pt += matrix[(r2 + 4) % 5][c2];
        } 
        else{
            pt += matrix[r1][c2];
            pt += matrix[r2][c1];
        }
    }
    return pt;
}

int main() {
    string key, message;
    cout << "Enter key: ";
    getline(cin, key);
    generateKeyMatrix(key);
    cout << "Key Matrix:\n";
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }
    cout << "\nEnter message: ";
    getline(cin, message);
    string encrypted = encrypt(message);
    string decrypted = decrypt(encrypted);
    cout << "\nEncrypted: " << encrypted;
    cout << "\nDecrypted: " << decrypted << endl;
    return 0;
}