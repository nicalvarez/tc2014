#include <bits/stdc++.h>
using namespace std;

typedef long long tint;

tint eval(tint a, tint b, tint c, tint x) {
    return a*x*x + b*x + c;
}

void solve(tint a, tint b, tint c, tint &x, tint &t) {
    if (a == 0) {
    }
    tint cand = -b / (2*a);
    tint cand1 = cand - cand%4;
    tint cand2 = cand1 + 4;
    x = cand1; t = eval(a,b,c,cand1);
    tint t2 = eval(a,b,c,cand2);
    if (t2 < t) {
        t = t2;
        x = cand2;
    }
}

int main(int argc, const char *argv[])
{
    ios_base::sync_with_stdio(false);
    int n,m;
    tint a,bx,by,cx,cy;
    a = bx = by = cx = cy = 0;
    cin >> n >> m;
    for (int i = 2; i < 4*n; i += 4)
        for (int j = 2; j < 4*m; j += 4) {
            tint cij; cin >> cij;
            a += cij;
            bx -= 2 * cij * i;
            by -= 2 * cij * j;
            cx += cij * i*i;
            cy += cij * j*j;
        }

    if (a == 0) {
        cout << 0 << endl << "0 0" << endl;
        return 0;
    }

    tint x,y,tx,ty;
    solve(a, bx, cx, x, tx);
    solve(a, by, cy, y, ty);

    cout << tx+ty << endl; 
    cout << x/4 << ' ' << y/4 << endl;
    return 0;
}
