struct Bipartite_matching {
	int A[ms], B[ms], ret, n;
	bool used[ms];
	vector<int>adj[ms];

	void init() {
		for (int i = 0; i < ms; i++) {
			adj[i].clear();
			A[i] = B[i] = -1;
		}
		ret = 0;
	}

	void addEdge(int u, int v) {
		adj[u].push_back(v);
		//adj[v].push_back(u);
	}

	bool dfs(int a) {
		used[a] = true;
		for (int b : adj[a]) {
			int w = B[b];
			if (w == -1 || !used[w] && dfs(w)) {
				B[b] = a;
				A[a] = b;
				return true;
			}
		}
		return false;
	}

	int solve() {
		for (int i = 0; i < n; i++) {
			if (A[i] == -1) {
				for (int j = 0; j < ms; j++)used[j] = false;
				if (dfs(i))ret++;
			}
		}
		return ret;
	}
};
