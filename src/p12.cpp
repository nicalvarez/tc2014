#include <bits/stdc++.h>
using namespace std;

typedef long long tint;
#define forn(i,n) for (int i = 0; i < int(n); i++)

const int 
    MAXN = 2100,
    INF = 10000;

int n, k;
tint a[MAXN];

tint tol;
inline bool valid(int i, int j) {
    if (j == n) return true;
    return tol * (j-i) >= abs(a[i] - a[j]);
}

int memo[MAXN];
int go(int from) {
    if (from == n) return 0;

    int &res = memo[from];
    if (res != -1) return res;

    res = INF;
    for (int to = from+1; to <= n; to++) if (valid(from,to)) {
        res = min(res, to-from-1 + go(to));
    }
    return res;
}

int go() {
    int res = INF;
    for (int first = 0; first < n; first++) res = min(res, first + go(first));
    return res;
}

int main(int argc, const char *argv[])
{
    ios_base::sync_with_stdio(false);

    cin >> n >> k;
    forn(i,n) cin >> a[i];

    tint lo = -1, hi = tint(2e9) + 1;
    while (lo + 1 < hi) {
        tint mi = (lo + hi) / 2;
        fill_n(memo, n+2, -1);
        tol = mi;
        if (go() <= k) hi = mi;
        else lo = mi;
    }
    cout << hi << endl;
    
    return 0;
}
