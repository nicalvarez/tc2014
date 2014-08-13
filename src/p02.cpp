#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define forn(i,n) for (int i = 0; i < int(n); i++)
#define pb push_back

const int MAXN = 1010;

vector<int> adj[MAXN];
int n, deg[MAXN];
bool change[MAXN];

void init() {
	fill_n(deg,2*n,0);
	fill_n(change, 2*n, false);
	forn(u,2*n) adj[u].clear();
}

int main() {
	ios_base::sync_with_stdio(false);
	int T; cin >> T;
	while (T--) {
		cin >> n;
		init();
		forn(i,n) forn(j,n) {
			char c; cin >> c;
			if (c == 'O') { adj[i+n].pb(j); deg[j]++; }
			else { adj[j].pb(i+n); deg[i+n]++; }
		}
		vector<int> res;
		int took = 0;
		for (;;) {
			int U = -1;
			forn(u,2*n) if (deg[u] == 0) { U = u; break; }
			if (U == -1) break;
			took++;
			deg[U]--;
			if (change[U]) res.pb(U);
			for (int v : adj[U]) {
				deg[v]--;
				change[v] = true;
			}
		}
		if (took == 2*n) {
			bool first= true;
			for (int x : res) {
				if (!first) cout << ' ';
				if (x < n) cout << 'C'; else cout << 'R';
				cout << x%n + 1;
				first = false;
			}
			cout << endl;
		}
		else cout << "No solution" << endl;
	}
	return 0;
}
