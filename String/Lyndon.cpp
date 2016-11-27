// Decompose s = w1w2..wk : k max and w1 >= w2 >= ...

vector<string> lyndon(string s) {
    int n = (int) s.length();
    int i = 0;
    vector<string> result;
    while (i < n) {
        int j = i + 1, k = i;
        while (j < n && s[k] <= s[j]) {
            if (s[k] < s[j]) k = i;
            else ++k;
            ++j;
        }
        while (i <= k) {
            result.push_back(s.substr(i, j - k));
            i += j - k;
        }
    }
    return result;
}

int main() {
    auto f = [](vector<string>x){for(auto y:x)cout<<y<<' ';cout<<'\n';};
    f(lyndon("abcdef")); // abcdef
    f(lyndon("fedcba")); // f e d c b a
    f(lyndon("aaaaaa")); // a a a a a a
    f(lyndon("ababab")); // ab ab ab
    return 0;
}
