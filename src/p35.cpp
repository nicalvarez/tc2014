#include <bits/stdc++.h>
using namespace std;

#define forn(i,n) for (int i = 0; i < int(n); i++)
#define si(c) ((int)(c).size())
#define pb push_back
#define mp make_pair
#define forsn(i,a,b) for (int i = int(a); i < int(b); i++)
#define dforsn(i,a,b) for (int i = int(b)-1; i >= int(a); i--)
#define all(c) (c).begin(), (c).end()
#define D(a) cerr << #a << " = " << a << endl;

typedef long long tint;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;

const int MAXM = 110;

int n,m;
pii e[MAXM]; 

int dist(int a, int b) {
    int res = b-a;
    if (res < 0) res += n;
    return res;
}

bool btw(int a, int m, int b) {
    if (m == a || m == b) return false;
    return dist(a,m) + dist(m,b) == dist(a,b);
}

bool inter(int a1, int b1, int a2, int b2) {
    bool cross1 = btw(a1,a2,b1) && btw(b1,b2,a1);
    bool cross2 = btw(a1,b2,b1) && btw(b1,a2,a1);
    return cross1 || cross2;
} 

bool inter(pii a, pii b) { return inter(a.first, a.second, b.first, b.second); };

int col[MAXM];
vi adj[MAXM];

bool dfs(int u, int c) {
    if (col[u] != -1) return c == col[u];
    col[u] = c;
    bool res = true;
    for (int v : adj[u]) res &= dfs(v,1-c);
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin >> n >> m;
    forn(i,m) {
        int u,v; cin >> u >> v;
        u--; v--;
        e[i] = {u,v};
    }
    forn(j,m) forn(i,j) if (inter(e[i], e[j])) {
        adj[i].pb(j);
        adj[j].pb(i);
    }

    fill_n(col,m,-1);
    bool good = true;
    forn(u,m) if (col[u] == -1) {
        good &= dfs(u,0);
    }

    if (!good) cout << "Impossible" << endl;
    else {
        forn(u,m) cout << (col[u] ? 'i' : 'o');
        cout << endl;
    }

	return 0;
}
