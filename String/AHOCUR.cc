const int NODE = 40 * 20 + 1;
const int NC = 62;

int nextNode[NODE][NC];
int chr[NODE];
int parent[NODE];
int prefix[NODE];
int numNodes;
int match[NODE];

inline int toInt(char c) {
    if (c >= 'a' && c <= 'z') return c - 'a';
    if (c >= 'A' && c <= 'Z') return c - 'A' + 26;
    if (c >= '0' && c <= '9') return c - '0' + 52;
    assert(false && "Invalid char");
    return -1;
}

inline int getPrefix(int);

inline int go(int u, int c) {
    if (nextNode[u][c] != -1) return nextNode[u][c];
    if (u == 0) return 0;
    return nextNode[u][c] = go(getPrefix(u), c);
}

inline int getPrefix(int u) {
    if (prefix[u] != -1) return prefix[u];
    if (u == 0 || parent[u] == 0) return prefix[u] = 0;
    return prefix[u] = go(getPrefix(parent[u]), chr[u]);
}

void add(const string &s) {
    int u = 0;
    for (int i = 0; i < (int) s.size(); ++i) {
        int c = toInt(s[i]);
        if (nextNode[u][c] == -1) {
            nextNode[u][c] = numNodes;
            fill(nextNode[numNodes], nextNode[numNodes] + NC, -1);
            chr[numNodes] = c;
            parent[numNodes] = u;
            prefix[numNodes] = -1;
            match[numNodes] = -1;
            ++numNodes;
        }
        u = nextNode[u][c];
    }
    match[u] = 1;
}

inline bool getMatch(int u) {
    return match[u] == -1 ? (match[u] = getMatch(getPrefix(u))) : match[u];
}

void init() {
    fill(nextNode[0], nextNode[0] + NC, -1);
    numNodes = 1;
}

const int L = 100;
int mark[L + 1][NODE], c[NC], n, test;
double f[L + 1][NODE], p[NC];

double F(int len, int u) {
    if (getMatch(u)) return 0;
    if (len == 0) return 1;
    if (mark[len][u] == test) return f[len][u];
    mark[len][u] = test;
    f[len][u] = 0;
    for (int i = 0; i < n; ++i) f[len][u] += p[i] * F(len - 1, go(u, c[i]));
    return f[len][u];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.precision(12);
    int numTests; cin >> numTests;
    for (test = 1; test <= numTests; ++test) {
        init();
        int k; cin >> k;
        for (int i = 0; i < k; ++i) {
            string s; cin >> s;
            add(s);
        }
        cin >> n;
        for (int i = 0; i < n; ++i) {
            char x; cin >> x >> p[i];
            c[i] = toInt(x);
        }
        int len; cin >> len;
        cout << "Case #" << test << ": " << F(len, 0) << '\n';
    }
    return 0;
}
