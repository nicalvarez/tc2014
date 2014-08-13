#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

typedef unsigned int ui;

#define forn(i,n) for (int i = 0; i < int(n); i++)
#define pb push_back
#define si(c) ((int)(c).size())
typedef vector<ui> vi;

const int MAXN = 700;

int m,n,d;
vector<ui> row[MAXN*MAXN];

int id(int i, int j) { return i*m + j; }

void mark(int i, int j) {
	row[i][j>>5] |= ui(1)<<(j&31);
}

bool check(int i, int j) { return row[i][j>>5] & (1<<(j&31)); }

void operator^=(vi &a, const vi &b) {
        int n =si(a);
        assert(n = si(b));
        forn(i,n) a[i] ^= b[i];
}

void init(int N) {
	int sz = N/32 + 1;
	forn(i,N) row[i].clear(), row[i].resize(sz,0);
}

int main(int argc, char *argv[])
{
    ios_base::sync_with_stdio(false);
	while (cin >> m >> n >> d && n) {
		int target = m*n;
		init(target);
		forn(i,n) forn(j,m) {
			vi cols;
			int x; cin >> x;
			if (x) cols.pb(target);
            cols.pb(id(i,j));
			for (int ii = max(0,i-d); ii <= min(n-1,i+d); ii++) {
				int di = abs(i-ii), dj = d - di;
				int jj = j - dj;
				if (jj >= 0) cols.pb(id(ii,jj));

				if (dj == 0) continue;
				jj = j + dj;
				if (jj < m) cols.pb(id(ii,jj));
			}
			int ID = id(i,j);
			for (int c : cols) mark(ID,c);
		}

        vector<bool> vis(target,false);
        forn(j,target) {
                forn(i,target) if (!vis[i] && check(i,j)) {
                        vis[i] = true;
                        forn(i2,target) if (!vis[i2] && check(i2,j)) row[i2] ^= row[i];
                        break;
                }
        }
        vi bad(si(row[0]),0);
        bad[target>>5] |= 1<<(target&31);
        
        bool res = true;
        forn(i,target) if (row[i] == bad) { res = false; break; }

        cout << res << endl;
	}

	return 0;
}
