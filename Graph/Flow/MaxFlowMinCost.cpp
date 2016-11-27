#define FORE(i,v) for (__typeof((v).begin()) i=(v).begin();i!=(v).end();i++)
    
class MaxFlowMinCost {
    private:
    static const int INF=(int)1e9+7;
    struct Edge {
        int from,to,capa,flow,cost;
        Edge() {
            from=to=capa=flow=cost=0;
        }
        Edge(int u,int v,int ca,int co) {
            from=u;to=v;capa=ca;flow=0;cost=co;
        }
        int residental(void) const {
            return (capa-flow);
        }
    };
    int n;
    vector<vector<int> > adj;
    vector<Edge> edge;
    vector<int> dist,trace;
    bool FordBellman(int s,int t) {
        fill(dist.begin(), dist.end(), INF);
        fill(trace.begin(), trace.end(), -1);
        vector<bool> inQueue(n+7,false);
        queue<int> q;
        dist[s]=0;q.push(s);inQueue[s]=true;
        while (!q.empty()) {
            int u=q.front();q.pop();inQueue[u]=false;
            FORE(it,adj[u]) if (edge[*it].residental()>0) {
                int v=edge[*it].to;
                if (dist[v]>dist[u]+edge[*it].cost) {
                    dist[v]=dist[u]+edge[*it].cost;
                    trace[v]=*it;
                    if (!inQueue[v]) {
                        q.push(v);inQueue[v]=true;
                    }
                }
            }
        }
        return (dist[t]<INF);
    }
    public:
    MaxFlowMinCost() {
        n=0;
    }
    MaxFlowMinCost(int n) {
        this->n=n;
        adj.assign(n+7,vector<int>());
        dist.assign(n+7,0);
        trace.assign(n+7,0);
    }
    void addEdge(int u,int v,int ca,int co) {
        adj[u].push_back(edge.size());
        edge.push_back(Edge(u,v,ca,co));
        adj[v].push_back(edge.size());
        edge.push_back(Edge(v,u,0,-co));
    }
    pair<int,int> getFlow(int s,int t) {
        int totFlow=0;
        int totCost=0;
        while (FordBellman(s,t)) {
            int delta=INF;
            for (int u=t;u!=s;u=edge[trace[u]].from)
                delta=min(delta,edge[trace[u]].residental());
            for (int u=t;u!=s;u=edge[trace[u]].from) {
                edge[trace[u]].flow+=delta;
                edge[trace[u]^1].flow-=delta;
            }
            totFlow+=delta;
            totCost+=delta*dist[t];
        }
        return (make_pair(totFlow,totCost));
    }
};
