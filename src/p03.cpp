#include <iostream>
#include <vector>
using namespace std;

typedef long long tint;

const int MAXN = 110;

tint comb[MAXN][MAXN];

int main() {
	ios_base::sync_with_stdio(false);

	for (int m = 0; m < MAXN; m++) {
		comb[m][0] = comb[m][m] = 1;
		for (int n = 1; n < m; n++) comb[m][n] = comb[m-1][n-1] + comb[m-1][n];
	}

	int n;
	while (cin >> n) {
		vector<int> a;
		int tot = 0;
		for (int d = 2; d*d <= n; d++) if (n % d == 0) {
			int e = 0;
			do { e++; n /= d; } while (n % d == 0);
			a.push_back(e);
			tot += e;
		}
		if (n > 1) a.push_back(1), tot++;

		tint res = comb[2*tot-2][tot-1] / tot;
		for (int ai : a) {
			res *= comb[tot][ai];
			tot -= ai;
		}
		cout << res << endl;

	}
	return 0;
}
