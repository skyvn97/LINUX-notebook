const int N = 50000, INF = 1e9;
int mx[N], my[N], d[N], nx, ny;
vector<int> g[N];

bool dfs(int u, int mind) {
    for (int v : g[u]) if(my[v] == -1 ? d[u] == mind : d[my[v]] == d[u]+1 && dfs(my[v], mind)) return mx[u] = v, my[v] = u, true;
    d[u] = INF;
    return false;
}

int maxMatch() {
    int matching = 0;
    fill(mx, mx + nx, -1); fill(my, my + ny, -1);
    while(true) {
        fill(d, d + nx, INF); queue<int> q;
        for(int u = 0; u < nx; ++u) if(mx[u] == -1) d[u] = 0, q.push(u);
        int mind = INF;
        while(!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : g[u]) if(my[v] == -1) mind = min(mind, d[u]);
            else if(d[my[v]] == INF) d[my[v]] = d[u]+1, q.push(my[v]);
        }
        if(mind == INF) break;
        for(int u = 0; u < nx; ++u) if(d[u] > mind) d[u] = INF;
        for(int u = 0; u < nx; ++u)
            if(mx[u] == -1 && dfs(u, mind)) ++matching;
    }
    return matching;
}
