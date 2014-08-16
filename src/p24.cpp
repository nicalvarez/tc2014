#include <bits/stdc++.h>
using namespace std;

#define forn(i,n) for (int i = 0; i < int(n); i++)
#define si(c) ((int)(c).size())

const int   
    INF = 1e9,
    MAXN = 110;

int m,n;
string a,b,v;

int trans[MAXN][30];

int pick[MAXN][MAXN][MAXN];
int memo[MAXN][MAXN][MAXN];
int go(int i, int j, int k) {
    if (k == si(v)) return -INF;
    if (i == m || j == n) return 0;
    int &res = memo[i][j][k];
    if (res != -1) return res;

    if (a[i] != b[j]) {
        int cand1 = go(i+1,j,k), cand2 = go(i,j+1,k);
        if (cand1 > cand2) { res = cand1; pick[i][j][k] = 0; }
        else { res = cand2; pick[i][j][k] = 1; }
    }
    else {
        int cand1 = 1 + go(i+1,j+1, trans[k][a[i]-'A']);
        int cand2 = go(i+1, j+1, k);
        if (cand1 > cand2) { res = cand1; pick[i][j][k] = 2; }
        else { res = cand2; pick[i][j][k] = 3; }
    }
    return res;
}

string build() {
    int i = 0, j = 0, k = 0;
    string res;
    while (i < m && j < n) {
        int p = pick[i][j][k];
        if (p == 0) i++;
        else if (p == 1) j++;
        else if (p == 2) {
            res += a[i];
            k = trans[k][a[i]-'A'];
            i++; j++;
        }
        else {
            i++; j++;
        }
    }
    if (res == "") return "0";
    return res;
}

int kmp(const string &a, const string &b) {
    int n = si(b);

    for (int res = n; res > 0; res--) {
        bool bad = false;
        for (int i = n-res; i < n; i++) if (b[i] != a[i-n+res]) {
            bad = true;
            break;
        }
        if (!bad) return res;
    }
    return 0;
}

int main(int argc, const char *argv[])
{
    cin >> a >> b >> v;
    m = si(a); n = si(b);

    string pref;
    forn(i,si(v)) {
        forn(c,26) trans[i][c] = kmp(v,pref + char('A' + c));
        pref += v[i];
    }

    fill(memo[0][0], memo[m+2][0], -1);
    go(0,0,0);
    cout << build() << endl;
    
    return 0;
}
