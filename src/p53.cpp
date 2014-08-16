#include <bits/stdc++.h>
using namespace std;

typedef long long tint;
#define forn(i,n) for (int i = 0; i < int(n); i++)

const int 
    MOD = 1e9 + 7,
    MAXN = 1100;

int n, x[MAXN];

int phi(int i) {
    int n = x[i], res = n;

    forn(j,i) if (j && n % x[j] == 0) {
        do { n /= x[j]; } while (n % x[j] == 0);
        res -= res/x[j];
    }
    if (n > 1) res -= res/n;
    return res;
}

int main(int argc, const char *argv[])
{
    while (cin >> n) {
        forn(i,n) cin >> x[i];
        sort(x,x+n);

        tint res = 1;
        forn(i,n) if (i) res = res*phi(i)%MOD;
        cout << res << endl;
    }
    return 0;
}
