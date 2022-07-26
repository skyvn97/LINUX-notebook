class MaxFlowMinCost {
    static const int INF = (int)1e9 + 7;
    static const long long LL_INF = (long long)1e18 + 7LL;
 
    struct Edge {
        int from, to, flow, capa;
        long long cost;
 
        Edge(int _from = 0, int _to = 0, int _capa = 0, long long _cost = 0) {
            from = _from; to = _to; flow = 0; capa = _capa; cost = _cost;
        }
 
        int residual(void) const {
            return capa - flow;
        }
    };
 
    int numNode;
    vector<vector<int>> adj;
    vector<Edge> edges;
    vector<long long> dist;
    vector<int> trc;
    vector<bool> inQueue;
 
public:
    MaxFlowMinCost(int _numNode = 0) {
        numNode = _numNode;
        adj.assign(numNode + 7, vector<int>());
        dist.assign(numNode + 7, 0);
        trc.assign(numNode + 7, -1);
        inQueue.assign(numNode + 7, false);
    }
 
    int addEdge(int from, int to, int capa, long long cost) {
        adj[from].push_back(edges.size());
        edges.push_back(Edge(from, to, capa, cost));
        adj[to].push_back(edges.size());
        edges.push_back(Edge(to, from, 0, -cost));
        return edges.size() - 2;
    }
 
private:
    bool fordBellman(int s, int t) {
        FOR(i, 1, numNode) {
            dist[i] = LL_INF;
            trc[i] = -1;
            inQueue[i] = false;
        }
 
        queue<int> q;
        dist[s] = 0; q.push(s); inQueue[s] = true;
 
        while (!q.empty()) {
            int u = q.front(); q.pop(); inQueue[u] = false;
            for (int id : adj[u]) if (edges[id].residual() > 0) {
                int v = edges[id].to;
                if (minimize(dist[v], dist[u] + edges[id].cost)) {
                    trc[v] = id;
                    if (!inQueue[v]) {
                        q.push(v); inQueue[v] = true;
                    }
                }
            }
        }
 
        return dist[t] < LL_INF;
    }
 
public:
    pair<int, long long> getFlow(int src, int snk) {
        int totFlow = 0;
        long long totCost = 0;
 
        while (fordBellman(src, snk)) {
            int delta = INF;
            for (int u = snk; u != src; u = edges[trc[u]].from) minimize(delta, edges[trc[u]].residual());
            for (int u = snk; u != src; u = edges[trc[u]].from) {
                edges[trc[u]].flow += delta;
                edges[trc[u] ^ 1].flow -= delta;
            }
            totFlow += delta;
            totCost += delta * dist[snk];
        }
 
        return make_pair(totFlow, totCost);
    }
 
    int traceFlow(int id) const {
        return edges[id].flow;
    }
};
