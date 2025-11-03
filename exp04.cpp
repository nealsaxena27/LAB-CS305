#include <bits/stdc++.h>
using namespace std;

char shift_char(char ch, char key_ch, bool encrypt = true) {
    int p = ch - 'A';
    int k = key_ch - 'A';
    int r = encrypt ? (p + k) % 26 : (p - k + 26) % 26;
    return char(r + 'A');
}

string vigenere_encrypt(string &plaintext, string &key) {
    string out;
    out.reserve(plaintext.size());
    int i = 0;
    for (char c : plaintext) {
        char key_ch = key[i % key.size()];
        out.push_back(shift_char(c, key_ch, true));
        ++i;
    }
    return out;
}

string vigenere_decrypt(string &ciphertext, string &key) {
    string out;
    out.reserve(ciphertext.size());
    int i = 0;
    for (char c : ciphertext) {
        char key_ch = key[i % key.size()];
        out.push_back(shift_char(c, key_ch, false));
        ++i;
    }
    return out;
}

string autokey_encrypt(string &plaintext, string &key) {
    string key_stream = key + plaintext;
    string out;
    out.reserve(plaintext.size());
    int i = 0;
    for (char c : plaintext) {
        char key_ch = key_stream[i];
        out.push_back(shift_char(c, key_ch, true));
        ++i;
    }
    return out;
}

string autokey_decrypt(string &ciphertext, string &key) {
    string key_stream = key;
    string out;
    out.reserve(ciphertext.size());
    int i = 0;
    for (char c : ciphertext) {
        char key_ch = key_stream[i];
        char plain_ch = shift_char(c, key_ch, false);
        out.push_back(plain_ch);
        key_stream.push_back(plain_ch);
        ++i;
    }
    return out;
}

int main() {
    cout<<"Enter plaintext: ";
    string plainText; cin>>plainText;
    
    cout<<"Enter key1: ";
    string key1; cin>>key1;
    string cipherText1 = autokey_encrypt(plainText, key1);
    cout<<"Encrypted ciphertext using AutoKey Cipher: "<<cipherText1<<endl;
    string decryptedCipherText1 = autokey_decrypt(cipherText1, key1);
    cout<<"Decrypted ciphertext using AutoKey Cipher: "<<decryptedCipherText1<<endl; 
    string cipherText2 = vigenere_encrypt(plainText, key1);
    cout<<"Encrypted ciphertext using Vignere Cipher: "<<cipherText2<<endl;
    string decryptedCipherText2 = vigenere_decrypt(cipherText2, key1);
    cout<<"Decrypted ciphertext using Vignere Cipher: "<<decryptedCipherText2<<endl; 
    
    cout<<"Enter key2: ";
    string key2; cin>>key2;
    cipherText1 = autokey_encrypt(plainText, key2);
    cout<<"Encrypted ciphertext using AutoKey Cipher: "<<cipherText1<<endl;
    decryptedCipherText1 = autokey_decrypt(cipherText1, key2);
    cout<<"Decrypted ciphertext using AutoKey Cipher: "<<decryptedCipherText1<<endl; 
    cipherText2 = vigenere_encrypt(plainText, key2);
    cout<<"Encrypted ciphertext using Vignere Cipher: "<<cipherText2<<endl;
    decryptedCipherText2 = vigenere_decrypt(cipherText2, key2);
    cout<<"Decrypted ciphertext using Vignere Cipher: "<<decryptedCipherText2<<endl; 
}
