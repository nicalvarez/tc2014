#include <bits/stdc++.h>
using namespace std;

#define forn(i,n) for (int i = 0; i < int(n); i++)
#define si(c) ((int)(c).size())
#define pb push_back
#define all(c) (c).begin(), (c).end()

typedef vector<int> vi;

const int 
    MAXN = 25,
    MAXM = MAXN*(MAXN-1)/2; 

int n,m,d[MAXM], cnt[500];

vi pos;

bool viable(int p) {
    for (int pi : pos) {
        int d = abs(pi-p);
        if (!cnt[d]) return false;
    }
    return true;
}

void put(int p) {
    for (int pi : pos) {
        int d = abs(pi-p);
        cnt[d]--;
    }
    pos.pb(p);
}

void take() {
    int p = pos.back(); pos.pop_back();
    for (int pi : pos) {
        int d = abs(pi-p);
        cnt[d]++;
    }
}

set<vi> res;
void go(int from) {
    //cerr << from << endl;
    if (from == m) {
        vi cand = pos;
        sort(all(cand));
        vi d; forn(i,n-1) d.pb(cand[i+1] - cand[i]);
        res.insert(d);

        reverse(all(cand));
        d.clear(); forn(i,n-1) d.pb(cand[i] - cand[i+1]);
        res.insert(d);
        return;
    }

    if(cnt[d[from]] == 0) go(from+1);

    int p = pos[0] + d[from];
    if (viable(p)) { put(p); go(from+1); take(); }
    if (si(pos) > 1) {
        p = pos[1] - d[from];
        if (viable(p)) { put(p); go(from+1); take(); }
    }
}

void init() {
    fill_n(cnt,500,0);
    res.clear();
    pos.clear();
}

int main(int argc, const char *argv[])
{
    ios_base::sync_with_stdio(false);
    while (cin >> n && n) {
        init();
        m = n*(n-1)/2;
        forn(i,m) {
            cin >> d[i];
            cnt[d[i]]++;
        }
        
        pos.pb(0);
        go(0);
        for (auto &row : res) {
            forn(i,si(row)) {
                if (i) cout << ' ';
                cout << row[i];
            }
            cout << endl;
        }
        cout << "-----" << endl;
    }
    return 0;
}
