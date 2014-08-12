#include <bits/stdc++.h>
using namespace std;

typedef long long tint;

const int
    MAXN = 1100,
    MOD = 1e9 + 7;

tint fact[MAXN], inv[MAXN], ifact[MAXN];

tint comb(int m, int n) {
    if (n < 0 || n > m) return 0;
    return fact[m] * ifact[n] % MOD * ifact[m-n] % MOD;
}

int main(int argc, const char *argv[])
{
    ios_base::sync_with_stdio(false);

    inv[1] = 1;
    for (int n = 2; n < MAXN; n++)
        inv[n] = (MOD - MOD/n) * inv[MOD%n] % MOD;

    fact[0] = ifact[0] = 1;
    for (int n = 1; n < MAXN; n++) {
        fact[n] = n * fact[n-1] % MOD;
        ifact[n] = inv[n] * ifact[n-1] % MOD;
    }

    int n,m,k; cin >> n >> m >> k;
    cout << comb(n-1,2*k) * comb(m-1,2*k) % MOD << endl;
    return 0;
}
