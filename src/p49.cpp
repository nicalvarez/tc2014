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

const int 
    MAXK = 20,
    MAXN = 1e5 + 100;

int n;
vi adj[MAXN];

int h[2*MAXN], lvl[MAXN];
int res[MAXN];


int t = 0, d[MAXN];
void dfs(int u, int p, int l) {
    d[u] = t; h[t++] = l;
    res[u] = lvl[u] = l;
    for (int v : adj[u]) if (v != p) {
        dfs(v,u,l+1);
        h[t++] = l;
    }
}

int LIM;

vi upd;
void update(int u) {
    upd.pb(u);
    if (si(upd) >= LIM) {
        queue<int> q;
        for (int v: upd) q.push(v), res[v] = 0;
        while (!q.empty()) {
            int t = q.front(); q.pop();
            for (int v : adj[t]) if (res[v] > res[t] + 1) {
                res[v] = res[t]+1;
                q.push(v);
            }
        }
        upd.clear();
    }
}

int st[MAXK][2*MAXN];

void initRMQ() {
    forn(i,2*n) st[0][i] = h[i];
    for (int k = 1; (1<<k) <= 2*n; k++) {
        forn(i,2*n) st[k][i] = min(st[k-1][i], st[k-1][i+(1<<(k-1))]);
    }
}

int rmq(int i, int j) {
    int len = j-i+1;
    int pot = 31 - __builtin_clz(len);
    return min(st[pot][i], st[pot][j-(1<<pot)+1]);
}

int lcaDist(int u, int v) {
    return lvl[u] + lvl[v] - 2*rmq(min(d[u],d[v]), max(d[u],d[v]));
}

int query(int u) {
    int ans = res[u];
    for (int v : upd) {
        ans = min(ans, lcaDist(u,v));
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    int m; cin >> n >> m; 
    forn(_,n-1) {
        int u,v; cin >> u >> v;
        u--; v--;
        adj[u].pb(v); adj[v].pb(u);
    }

    dfs(0,-1, 0);
    initRMQ();

    LIM = int(sqrt(m));
    while (m--) {
        int t,v; cin >> t >> v; v--;
        if (t == 1) update(v);
        else cout << query(v) << endl;
    }

	return 0;
}
