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

typedef struct node *pnode;
typedef pair<pnode,pnode> pnn;

struct node {
    int key, prior, size;
    pnode l,r;

    tint sum;

    node() {} 
    node(int key, int prior): key(key), prior(prior), sum(key), size(1), l(0), r(0) {}
};

ostream &operator<<(ostream &out, pnode t) {
    if (!t) return out;
    out << (t->l);
    out << t->key << ' ';
    out << (t->r);
    return out;
}


struct treap {
    pnode root;

    treap(): root(0) {}

    int size(pnode p) { return p ? p->size : 0; }
    int size() { return size(root); }
    tint sum(pnode p) { return p ? p->sum : 0; }

    // Propagate delta to children
    void push(pnode p) {
        if (!p) return;
        
        // push delta
    }

    // Update function and size from children's values
    void pull(pnode p) {
        if (!p) return;

        p->size = 1 + size(p->l) + size(p->r);
        p->sum = p->key + sum(p->l) + sum(p->r);
        // update function and delta
    }  

    void splitKey(pnode t, int key, pnode &l, pnode &r) {
        if (!t) return void(l = r = 0);
        push(t);
        if (key <= t->key) splitKey(t->l, key, l, t->l), r = t;
        else splitKey(t->r, key, t->r, r), l = t;
        pull(t);
    }
    
    pnn splitKey(int key) {
        pnn res;
        splitKey(root,key,res.first, res.second);
        return res;
    }

    void splitSize(pnode t, int sz, pnode &l, pnode &r) {
        if (!t) return void(l = r = 0);
        push(t);
        if (sz <= size(t->l)) splitSize(t->l, sz, l, t->l), r = t; 
        else splitSize(t->r, sz - 1 - size(t->l), t->r, r), l = t; 
        pull(t);
    }

    pnn splitSize(int sz) {
        pnn res;
        splitSize(root, sz, res.first, res.second);
        return res;
    }

    tint sum(int k) {
        pnn sp = splitSize(k);
        tint res = sum(sp.first);
        //D(sp.first);
        //cerr << sp.first << endl; 
        merge(root, sp.first, sp.second);
        return res;
    }

    void merge(pnode &t, pnode l, pnode r) {
        if (!l || !r) return void(t = l ? l : r);
        push(l); push(r);
        if (l->prior < r->prior) merge(l->r, l->r, r), t = l;
        else merge(r->l, l, r->l), t = r; 
        pull(t);
    }

    pnode merge(pnode l, pnode r) {
        pnode res; merge(res, l,r);
        return res;
    }

    pnode merge(pnode o) { root = merge(root, o); }

    //void insertKey(pnode &t, pnode elem) {
        //pnn sp = splitKey(elem->key);
        
        //if (!t) return void(t = elem);
        //push(t);
        //if (elem->key < t->key) return insertKey(t->l, elem);
        //insertKey(t->r, elem);
        //pull(t);
    //}

    void insertKey(int key) {
        pnode elem = new node(key, rand());
        pnode t1, t2; splitKey(root, key, t1, t2);
        merge(t1,t1,elem);
        merge(root,t1,t2);
        //insertKey(root, elem);
    } 

    void insertPos(int pos, int key) {
        pnode elem = new node(key, rand());
        pnode t1,t2; splitSize(root, pos, t1, t2);
        merge(t1,t1,elem);
        merge(root,t1,t2);
    }

    void split3Key(pnode t, int key1, int key2, pnode &t1, pnode &t2, pnode &t3) {
        splitKey(t,key1,t1,t2);
        splitKey(t2,key2, t2, t3);
    }

    void split3Pos(pnode t, int pos1, int pos2, pnode &t1, pnode &t2, pnode &t3) {
        splitSize(t,pos1,t1,t2);
        splitSize(t2,pos2-pos1,t2,t3);
    }

    void eraseKey(int key1, int key2) {
        pnode t1,t2,t3; split3Key(root,key1,key2, t1, t2, t3);
        merge(root,t1,t3);
    }

    void erasePos(int pos1, int pos2) {
        pnode t1,t2,t3; split3Pos(root, pos1, pos2, t1, t2, t3);
        merge(root, t1, t2);
    }

    void erasePos(int pos) {
        erasePos(pos,pos+1);
    }

    void eraseKey(pnode &t, int key) {
        if (!t) return;
        push(t);
        if (key == t->key) merge(t,t->l, t->r);
        else if (key < t->key) eraseKey(t->l, key);
        else eraseKey(t->r, key);
        pull(t);
    }

    void eraseKey(int key) {
        eraseKey(root, key);
    }

    pnode findKey(pnode t, int key) {
        if (!t) return 0;
        if (key == t->key) return t;
        if (key < t->key) return findKey(t->l, key);
        return findKey(t->r, key);
    }

    pnode findKey(int key) { findKey(root, key); }

    pnode findPos(pnode t, int pos) {
        if (!t) return 0;
        if (pos <= size(t->l)) return findPos(t->l, pos);
        return findPos(t->r, pos - 1 - size(t->l));
    }
};


ostream& operator<<(ostream &out, const treap &t) {
    return (out << t.root);
}


const int MAXN = 3e5 + 100;

struct level {
    int a,b,id;
    bool operator<(const level &o) const { return b < o.b; }
    friend istream& operator>>(istream &in, level &l) {
        in >> l.a >> l.b;
        return in;
    }
};

int n,w;
level l[MAXN];
//int a[MAXN], b[MAXN];


int main() {
    ios_base::sync_with_stdio(false);
    cin >> n >> w;
    forn(i,n) cin >> l[i], l[i].id = i; 
    sort(l, l+n);

    int bestK;
    tint res = 1LL<<60, cum = 0;
    treap t;
    forn(i,n) t.insertKey(l[i].a);
    for (int k = 0; k <= n; k++) {
        if (k + n >= w) {
            tint cand = cum + t.sum(w-k);
            if (cand < res) {
                bestK = k;
                res = cand;
            }
        }
        if (k < n) {
            t.eraseKey(l[k].a);
            t.insertKey(l[k].b - l[k].a);
            cum += l[k].a;
        }
    }
    cout << res << endl;

    vi pass(n);
    vector<pii> cand;
    forn(i,n) {
        if (i < bestK) { pass[l[i].id] = 1; cand.pb({l[i].b - l[i].a, l[i].id}); }
        else { pass[l[i].id] = 0; cand.pb({l[i].a, l[i].id}); }
    }
    sort(all(cand));
    forn(i,w-bestK) pass[cand[i].second]++;
    forn(i,n) cout << pass[i]; cout << endl;

	return 0;
}
