const int V = 1000, INF = 1e9;
int g[V][V], mx[V], my[V], fx[V], fy[V], d[V], ar[V], tr[V], p;

int slack(int u, int v) {
    return g[u][v] - fx[u] - fy[v];
}

int augment(int s) {
    queue<int> q; q.push(s);
    fill_n(tr, p, -1);
    for(int i = 0; i < p; ++i)
        d[i] = slack(s, i), ar[i] = s;
    while(true) {
        while(!q.empty()) {
            int u = q.front(); q.pop();
            for(int v = 0; v < p; ++v) if(tr[v] == -1) {
                int w = slack(u, v);
                if(w == 0) {
                    tr[v] = u;
                    if(my[v] == -1) return v;
                    q.push(my[v]);
                }
                if(d[v] > w) d[v] = w, ar[v] = u;
            }
        }
        int delta = INF;
        for(int v = 0; v < p; ++v) if(tr[v] == -1) delta = min(delta, d[v]);
        fx[s] += delta;
        for(int v = 0; v < p; ++v)
            if(tr[v] == -1) d[v] -= delta;
            else fx[my[v]] += delta, fy[v] -= delta;
        for(int v = 0; v < p; ++v) if(tr[v] == -1 && d[v] == 0) {
            tr[v] = ar[v];
            if(my[v] == -1) return v;
            q.push(my[v]);
        }
    }
}

void maxMatchMinCost() {
    fill_n(mx, p, -1); fill_n(my, p, -1);
    for(int i = 0; i < p; ++i) fx[i] = *min_element(g[i], g[i]+p); 
    for(int s = 0; s < p; ++s) {
        int f = augment(s);
        while(f != -1) {
            int x = tr[f], nx = mx[x];
            mx[x] = f; my[f] = x; f = nx;
        }
    }
}
