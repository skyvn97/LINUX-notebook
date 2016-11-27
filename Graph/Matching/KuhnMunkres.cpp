const int INF = (int) 1e9;
const int M = 1000;
int c[M][M], fx[M], fy[M], my[M], m; // m = number of vertices
bool vx[M], vy[M];

int slack(int u, int v) {
    return c[u][v] - fx[u] - fy[v];
}

bool dfs(int u) {
    vx[u] = true;
    for(int v = 0; v < m; ++v)
        if(slack(u, v) == 0 && !vy[v]) {
            vy[v] = true;
            if(my[v] == -1 || dfs(my[v]))
                return my[v] = u, true;
        }
    return false;
}

void maxMatchMinCost() {
    memset(my, -1, sizeof my);
    for(int i = 0; i < m; ++i)
        fx[i] = *min_element(c[i], c[i] + m);
    for(int i = 0; i < m; ++i) {
        memset(vx, 0, sizeof vx);
        memset(my, 0, sizeof vy);
        while(!dfs(i)) {
            int delta = INF;
            for(int u = 0; u < m; ++u) if(vx[u])
                for(int v = 0; v < m; ++v) if(!vy[v])
                    delta = min(delta, slack(u, v));
            for(int u = 0; u < m; ++u) if(vx[u])
                fx[u] += delta, vx[u] = false;
            for(int u = 0; u < m; ++u) if(vy[u])
                fy[u] -= delta, vy[u] = false;
        }
    }
}
