#include <bits/stdc++.h>
using namespace std;

long long modexp(long long base, long long exp, long long mod) {
    long long result = 1 % mod;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

long long egcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    long long x1, y1;
    long long g = egcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

long long modinv(long long a, long long m) {
    long long x, y;
    long long g = egcd(a, m, x, y);
    x %= m;
    if (x < 0) x += m;
    return (g == 1) ? x : -1;
}

int main() {
    long long p, q, e;
    cout << "Enter prime p: ";
    cin >> p;
    cout << "Enter prime q: ";
    cin >> q;
    cout << "Enter public exponent e: ";
    cin >> e;

    long long n = p * q;
    long long phi = (p - 1) * (q - 1);
    long long d = modinv(e, phi);

    cout << "\nPublic key (n, e): (" << n << ", " << e << ")\n";
    cout << "Private key (n, d): (" << n << ", " << d << ")\n\n";

    long long message;
    cout << "Enter message as integer (0 < m < n): ";
    cin >> message;

    long long cipher = modexp(message, e, n);
    long long decrypted = modexp(cipher, d, n);

    cout << "\nCiphertext: " << cipher << "\n";
    cout << "Decrypted message: " << decrypted << "\n";
}
