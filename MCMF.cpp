struct MCMF {
	struct edge {
		int to, c, f, w;
		edge *d;
		edge(int to1 = -1, int c1 = 0, int w1 = 0) :to(to1), c(c1), f(0), w(w1), d(nullptr) {}
		int spare() { return c - f; }
		void addFlow(int f1) {
			f += f1;
			d->f -= f1;
		}
	};

	int S = 0, E = ms - 1, mf = 0, mc = 0;
	vector<edge*>adj[ms];

	void init() {
		for (int i = 0; i < ms; i++)adj[i].clear();
		mf = mc = 0;
	}

	void addEdge(int u, int v, int c, int w) {
		edge *e1 = new edge(v, c, w), *e2 = new edge(u, 0, -w);
		e1->d = e2;
		e2->d = e1;
		adj[u].push_back(e1);
		adj[v].push_back(e2);
	}

	int solve() {
		while (1) {
			int pre[ms];
			edge* path[ms] = { 0 };
			bool InQ[ms] = { 0 };
			int dist[ms] = { 0 };
			for (int i = 0; i < ms; i++) {
				pre[i] = -1;
				dist[i] = 1e9;
			}
			queue<int> q;
			q.push(S);
			dist[S] = 0;
			while (!q.empty()) {
				int now = q.front();
				q.pop();
				InQ[now] = false;
				for (edge *e : adj[now]) {
					int next = e->to;
					if (e->spare() > 0 && dist[next] > dist[now] + e->w) {
						pre[next] = now;
						path[next] = e;
						dist[next] = dist[now] + e->w;
						if (!InQ[next]) {
							q.push(next);
							InQ[next] = true;
						}
					}
				}
			}
			if (pre[E] == -1)break;
			int flow = 1e9;
			for (int i = E; i != S; i = pre[i])flow = min(flow, path[i]->spare());
			for (int i = E; i != S; i = pre[i]) {
				path[i]->addFlow(flow);
				mc += path[i]->w * flow;
			}
			mf += flow;
		}
		return mc;
	}
};
