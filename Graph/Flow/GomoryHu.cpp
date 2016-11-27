vector<vector<int> > gomoryHu(DinicFlow &network) {
    int n = network.n;
    vector<vector<int> > d (n, vector<int>(n, network.INF));
    vector<int> p (n, 0);
	for(int i = 1; i < n; ++i) {
		network.resetFlow();
		int flow = network.maxFlow(i, p[i]);
		for(int j = i + 1; j < n; ++j)
			if(network.dist[j] >= 0 && p[j] == p[i])
				p[j] = i;
		d[i][p[i]] = d[p[i]][i] = flow;
		for(int j = 0; j < i; ++j) d[i][j] = d[j][i] = min(flow, d[p[i]][j]);
	}
    return d;
}
