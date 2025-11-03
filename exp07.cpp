#include <bits/stdc++.h>
using namespace std;

long long mul_mod(long long a, long long b, long long mod) {
    a %= mod;
    b %= mod;
    long long res = 0;
    while (b > 0) {
        if (b & 1) {
            if (res >= mod - a) res = res - (mod - a);
            else res = res + a;
        }
        if (a >= mod - a) a = a - (mod - a);
        else a = a + a;
        b >>= 1;
    }
    return res;
}

long long modexp(long long base, long long exp, long long mod) {
    base %= mod;
    long long result = 1 % mod;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

int main() {
    long long p, g;
    cout << "Enter prime p: ";
    cin >> p;
    cout << "Enter generator g: ";
    cin >> g;

    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<long long> dist(2, p - 2);

    long long a = dist(gen);
    long long b = dist(gen);

    long long A = modexp(g, a, p);
    long long B = modexp(g, b, p);

    long long s1 = modexp(B, a, p);
    long long s2 = modexp(A, b, p);

    cout << "\nPrivate a: " << a << "\nPrivate b: " << b << "\n\n";
    cout << "Public A = g^a mod p: " << A << "\n";
    cout << "Public B = g^b mod p: " << B << "\n\n";
    cout << "Shared secret (Alice): " << s1 << "\n";
    cout << "Shared secret (Bob):   " << s2 << "\n";

    if (s1 == s2) cout << "\nSuccess: shared secrets match.\n";
    else cout << "\nError: shared secrets differ.\n";
}
