struct topological_sort {
	vector<int>adj[ms];
	queue<int> q;
	int indeg[ms] = { 0 }, ret[ms] = { 0 }, cnt = 0;

	void init() {
		for (int i = 0; i < ms; i++) {
			adj[i].clear();
			indeg[i] = ret[i] = 0;
		}
		while (!q.empty())q.pop();
		cnt = 0;
	}

	void solve() {
		for (int i = 0; i < ms; i++)if (!indeg[i])q.push(i);
		while (!q.empty()) {
			int now = q.front();
			q.pop();
			ret[cnt++] = now;
			for (int next : adj[now]) {
				indeg[next]--;
				if (!indeg[next])q.push(next);
			}
		}
	}
};
