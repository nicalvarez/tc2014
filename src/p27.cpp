#include <bits/stdc++.h>
using namespace std;

typedef long long tint;

int n,x,y,c;

tint count(int t) {
    tint res = 0;
    int r1 = max(1,x-t), r2 = min(n,x+t);
    for (int r = r1; r <= r2; r++) {
        int d = t-abs(x-r);
        int c1 = max(1,y-d), c2 = min(n,y+d);
        res += c2-c1+1;
    }
    return res;
}

int main(int argc, const char *argv[])
{
    ios_base::sync_with_stdio(false);
    cin >> n >> x >> y >> c;
    if (c == 1) cout << 0 << endl;
    else {
        tint lo = 0, hi = 1;
        while (count(hi) < c) lo = hi, hi *= 2;
        while (lo + 1 < hi) {
            int mi = (lo+hi)/2;
            if (count(mi) >= c) hi = mi;
            else lo = mi;
        }
        cout << hi << endl;
    }

    return 0;
}
