vector<int> manacher(const string &os) {
    int n = os.size();
    string s;
    for(int i = 0; i < n; ++i) {
        s += os[i];
        if(i != n - 1) s += '$';
    }
    int mx = 0, id = 0;
    n = s.size();
    vector<int> p (n);
    for(int i = 0; i < n; ++i) {
        p[i] = mx > i ? min(p[2 * id - i], mx - i) : 1;
        while(p[i] <= i && i + p[i] < n && s[i - p[i]] == s[i + p[i]]) ++p[i];
        if(i + p[i] > mx) {
            mx = i + p[i];
            id = i;
        }
    }
    return p;
}
