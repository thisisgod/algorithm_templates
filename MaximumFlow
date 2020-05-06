struct MF {
	struct edge {
		int to, c, f;
		edge *d;
		edge(int to1 = -1, int c1 = 0) :to(to1), c(c1), f(0), d(nullptr) {}
		int spare() { return c - f; }
		void addFlow(int f1) {
			f += f1;
			d->f -= f1;
		}
	};

	int S = 0, E = ms - 1, mf = 0;
	vector<edge*>adj[ms];

	void init() {
		for (int i = 0; i < ms; i++)adj[i].clear();
		mf = 0;
	}

	void addEdge(int u, int v, int c) {
		edge *e1 = new edge(v, c), *e2 = new edge(u, 0);
		e1->d = e2;
		e2->d = e1;
		adj[u].push_back(e1);
		adj[v].push_back(e2);
	}

	int solve() {
		while (1) {
			int pre[ms];
			for (int i = 0; i < ms; i++)pre[i] = -1;
			edge* path[ms] = { 0 };
			queue<int> q;
			q.push(S);
			while (!q.empty()) {
				int now = q.front();
				q.pop();
				for (edge *e : adj[now]) {
					int next = e->to;
					if (pre[next] == -1 && e->spare() > 0) {
						pre[next] = now;
						path[next] = e;
						q.push(next);
						if (next == E)break;
					}
				}
			}
			if (pre[E] == -1)break;
			int flow = 1e9;
			for (int i = E; i != S; i = pre[i])flow = min(flow, path[i]->spare());
			for (int i = E; i != S; i = pre[i])path[i]->addFlow(flow);
			mf += flow;
		}
		return mf;
	}
};
