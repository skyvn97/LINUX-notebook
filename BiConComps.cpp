const int N = 1024;

int count, parent[N], low[N}, num[N], n; //n vertices 0..n-1
bool visited[N];
vector<int> G[N];
stack<pair<int, int> > s;

void OutputComp(int u, int v) {
	pair<int, int> edge;
	do {
		edge = s.top(); s.pop();
		printf("%d %d\n", edge.first, edge.second);
	} while (edge != make_pair(u, v));
	printf("\n");
}

void dfs(int u) {
	visited[u] = true;
	count++;
	low[u] = num[u] = count;
	for (int v : G[u]) {
		if (!visited[v]) {
			s.push({u, v});
			parent[v] = u;
			dfs(v);
			if (low[v] >= num[u]) OutputComp(u, v);
			low[u] = min(low[u], low[v]);
		} else if (parent[u] != v && num[v] < num[u]) {
			s.push({u, v});
			low[u] = min(low[u], num[v]);
		}
	}
}

void BiconnectedComponents {
	count = 0;
	memset(parent, -1, sizeof parent);
	for (int i = 0; i < n; i++)
		if (!visited[i]) dfs(i);
}
