#include <bits/stdc++.h>
using namespace std;

#define forn(i,n) for (int i = 0; i < int(n); i++)
#define pb push_back
#define all(c) (c).begin(), (c).end()
#define si(c) ((int)(c).size())

const int MAXN = 1100;

int n,h,d[MAXN];

int main(int argc, const char *argv[])
{
    ios_base::sync_with_stdio(false);
    while (cin >> n >> h && n != -1) {
        forn(i,n-1) {
            cin >> d[i+1];
            d[i+1] += d[i];
        }
        forn(i,n) d[i] -= h*i;

        vector<int> rem;
        forn(i,n) {
            if (d[i] > d[0] || d[i] < d[n-1]) continue;
            rem.pb(-d[i]);
        }

        vector<int> res;
        forn(i,si(rem)) {
            int d = rem[i];
            int pos = upper_bound(all(res), d) - res.begin();
            if (pos == si(res)) res.pb(d);
            else res[pos] = d;
        }

        if (si(res) < 2) cout << -1 << endl;
        else cout << n-si(res) << endl;
    }
    return 0;
}
