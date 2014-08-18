
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

const int MAXC = 30;

const string
    YES = "Ordering is possible.",
    NO = "The door cannot be opened.";

bool present[MAXC];
bool adj[MAXC][MAXC];
int out[MAXC], in[MAXC];

bool vis[MAXC];
void dfs(int u) {
    if (vis[u]) return;
    vis[u] = true;
    forn(v,MAXC) if (adj[u][v])
        dfs(v);
}

bool connected() {
    int comp = 0;
    forn(c,MAXC) if (present[c] && !vis[c]) {
        dfs(c);
        comp++;
        if (comp > 1) return false;
    }
    return true;
}

bool euler() {
    vi bal;
    forn(u,MAXC) {
        if (in[u] == out[u]) continue;
        bal.pb(in[u] - out[u]);
    }
    if (bal.empty()) return true;
    if (si(bal) == 2 && max(bal[0], bal[1]) == 1) return true;
    return false; 
}

void init() {
    fill_n(out, MAXC, 0);
    fill_n(in, MAXC, 0);
    fill_n(vis, MAXC, false);
    fill_n(present, MAXC, false);
    fill(adj[0], adj[MAXC], false);
}

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) {
        init();
        int n; cin >> n;
        while (n--) {
            string s; cin >> s;
            int u = s[0] - 'a', v = s[si(s)-1] - 'a';
            out[u]++; in[v]++;
            adj[u][v] = adj[v][u] = true;
            present[u] = present[v] = true;
        }

        if (connected() && euler()) cout << YES << endl;
        else cout << NO << endl;
    }


	return 0;
}
