struct MFDinic {
	struct edge {
		int to, c, f;
		edge* d;
		edge(int to1 = -1, int c1 = 0) :to(to1), c(c1), f(0), d(nullptr) {}
		int spare() { return c - f; }
		void addFlow(int f1) {
			f += f1;
			d->f -= f1;
		}
	};
	int S = 0, E = ms - 1, mf = 0, level[ms], work[ms];
	vector<edge*>adj[ms];

	void init() {
		for (int i = 0; i < ms; i++)adj[i].clear();
		for (int i = 0; i < 51; i++)s[i] = f[i] = 0;
		mf = 0;
	}

	void addEdge(int u, int v, int c) {
		edge* e1 = new edge(v, c), *e2 = new edge(u, 0);
		e1->d = e2;
		e2->d = e1;
		adj[u].push_back(e1);
		adj[v].push_back(e2);
	}

	bool init_level() {
		for (int i = 0; i < ms; i++)level[i] = -1;
		level[S] = 0;
		queue<int>q;
		q.push(S);
		while (!q.empty()) {
			int now = q.front();
			q.pop();
			for (edge* next : adj[now]) {
				int to = next->to;
				if (level[to] == -1 && next->spare() > 0) {
					level[to] = level[now] + 1;
					q.push(to);
				}
			}
		}
		return level[E] != -1;
	}

	int dfs(int curr, int dest, int flow) {
		if (curr == dest)return flow;
		for (int& i = work[curr]; i < adj[curr].size(); i++) {
			edge* next = adj[curr][i];
			int to = next->to;
			if (level[to] == level[curr] + 1 && next->spare() > 0) {
				int df = dfs(to, dest, min(next->spare(), flow));
				if (df > 0) {
					next->addFlow(df);
					return df;
				}
			}
		}
		return 0;
	}

	int solve() {
		while (init_level()) {
			for (int i = 0; i < ms; i++)work[i] = 0;
			while (1) {
				int flow = dfs(S, E, 1e9);
				if (flow == 0)break;
				mf += flow;
			}
		}
		return mf;
	}
};
