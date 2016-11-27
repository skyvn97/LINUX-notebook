vector<int> calcZ(const string &s) {
    int n = s.size();
    vector<int> z (n);
    for (int i = 1, j = 0; i < n; ++i) {
        if (j + z[j] > i) z[i] = min(j + z[j] - i, z[i - j]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if (j + z[j] <= i || i + z[i] > j + z[j]) j = i;
    }
    return z;
}
