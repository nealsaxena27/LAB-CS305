#include <iostream>
using namespace std;

string encrypt(string plainText, int shift){
    string cipherText = "";
    for(int i = 0; i < plainText.size(); i++){
        if(isupper(plainText[i])){
            cipherText.push_back((plainText[i] - 'A' + shift) % 26 + 'A');
        }
        else{
            cipherText.push_back((plainText[i] - 'a' + shift) % 26 + 'a');
        }
    }
    return cipherText;
}

string decrypt(string cipherText, int shift){
    return encrypt(cipherText, 26 - shift);
}

int main(){
    string plainText;
    cout<<"Enter plaintext: "; cin>>plainText;
    int shift;
    cout<<"Enter shift (key): "; cin>>shift;
    string cipherText = encrypt(plainText, shift);
    cout<<"Encrypted ciphertext using Caeser Cipher: "<<cipherText<<endl;
    string decryptedPlainText = decrypt(cipherText, shift);
    cout<<"Decrypted plaintext: "<<decryptedPlainText<<endl;
}