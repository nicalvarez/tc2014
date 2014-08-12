#include <bits/stdc++.h>
using namespace std;

#define forn(i,n) for (int i = 0; i < int(n); i++)

const int MAXN = 510;

int n, a[MAXN], b[MAXN][MAXN];

bool check(int mask) {
    static int c[MAXN][MAXN];
    forn(i,n) forn(j,n) {
        if (i == j) c[i][j] = 0;
        else if ((i&1) && (j&1)) c[i][j] = a[i] | a[j];
        else if (!(i&1) && !(j&1)) c[i][j] = a[i] & a[j];
        else c[i][j] = a[i] ^ a[j];
        if ((b[i][j] & mask) != (c[i][j] & mask)) return false;
    }
    return true;
}

int main(int argc, const char *argv[])
{
    ios_base::sync_with_stdio(false);
    while (cin >> n) {
        forn(i,n) forn(j,n) cin >> b[i][j];
        if (n == 1) {
            cout << (b[0][0] == 0 ? "YES" : "NO") << endl;
            continue;
        }
        for (int i = 0; i < n; i += 2) a[i] = b[1][i] ^ b[1][0];
        for (int i = 1; i < n; i += 2) a[i] = b[0][i];
        forn(b,31) if (!check(1<<b))
            forn(i,n) a[i] ^= (1<<b);

        int ALL = (1LL<<31)-1;
        cout << (check(ALL) ? "YES" : "NO") << endl;
    }
    return 0;
}
