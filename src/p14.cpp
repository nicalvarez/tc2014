#include <bits/stdc++.h>
using namespace std;

#define forn(i,n) for (int i = 0; i < int(n); i++)
#define si(c) ((int)(c).size())
#define pb push_back

typedef vector<int> vi;

const int MAXN = 1e5 + 100;

int n, deg[MAXN], res[MAXN];
vi adj[MAXN];

stack<int> cand;
void remove(int u) {
    if (res[u] != -1) return;
    res[u] = 0;
    deg[u] = -1;
    int p = -1;
    forn(i,si(adj[u])) {
        int v = adj[u][i];
        if (res[v] == -1) {
            p = v;
            break;
        }
    }
    if (p == -1) return;
    res[p] = 1;
    deg[p] = -1;
    forn(i,si(adj[p])) {
        int v = adj[p][i];
        if (res[v] == -1) {
            deg[v]--;
            if (deg[v] == 1) cand.push(v);
        }
    }
}

#include <sys/resource.h>
void expandStack() {
    rlimit rl;
    getrlimit(RLIMIT_STACK, &rl);
    rl.rlim_cur = rl.rlim_max;
    setrlimit(RLIMIT_STACK, &rl);
}

bool vis[MAXN];
int dfs(int u) {
    if (vis[u]) return 0;
    vis[u] = true;
    int ans = 1;
    forn(i,si(adj[u])) {
        int v = adj[u][i];
        if (res[v] != -1) continue;
        ans += dfs(v);
    }
    return ans;
}

void init() {
    fill_n(deg,n,0);
    fill_n(res,n,-1);
    fill_n(vis,n,false);
    forn(u,n) adj[u].clear();
    while (!cand.empty()) cand.pop();
}

int main(int argc, const char *argv[])
{
    ios_base::sync_with_stdio(false);
    expandStack();
    int T; cin >> T;
    while (T--) {
        cin >> n;
        init();
        forn(u,n) {
            int v; cin >> v; v--;
            adj[u].pb(v);
            adj[v].pb(u);
            deg[u]++; deg[v]++;
        }

        forn(u,n) if (deg[u] == 1) cand.push(u);
        while (!cand.empty()) {
            int u = cand.top(); cand.pop();
            remove(u);
        }

        int ans = 0;
        forn(u,n) 
            if (res[u] != -1) ans += res[u];
            else if (!vis[u]) ans += (dfs(u)+1) / 2;

        cout << ans << endl;
    }
    return 0;
}
