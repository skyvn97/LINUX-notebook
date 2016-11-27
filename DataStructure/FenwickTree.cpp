struct FenwickTree { // 1-based index
    vector<int> tmul, tadd;
    int n;

    FenwickTree(int _n): tmul (_n + 1), tadd (_n + 1), n (_n) {
    }

    void update_point(int x, int mul, int add) {
        while (1<=x && x<=n) {
            tmul[x]+=mul;
            tadd[x]+=add;
            x+=x&(-x);
        }
    }

    void update_range(int l, int r, int val) { // l to r (inclusive)
        update_point(l,val,-val*(l-1));
        update_point(r,-val,val*r);
    }

    int get(int x) {
        int mul = 0, add = 0, fst = x;
        while (1<=x && x<=n) {
            mul+=tmul[x];
            add+=tadd[x];
            x=x&(x-1);
        }
        return (mul*fst+add);
    }

    int value(int x) {
        return (get(x)-get(x-1));
    }
};

