struct _2SAT {
	int scc[ms], low[ms], order[ms], cnt, c, result[ms / 2];
	bool visit[ms];
	stack<int> s;
	vector<int>adj[ms];

	void dfs(int now) {
		visit[now] = true;
		s.push(now);
		order[now] = low[now] = ++c;
		for (int next : adj[now]) {
			if (visit[next]) {
				low[now] = min(low[now], order[next]);
				continue;
			}
			else if (!order[next]) {
				dfs(next);
				low[now] = min(low[now], low[next]);
			}
		}
		if (low[now] == order[now]) {
			++cnt;
			while (!s.empty()) {
				int tmp = s.top();
				s.pop();
				scc[tmp] = cnt;
				visit[tmp] = false;
				if (tmp == now)return;
			}
		}
	}

	void makeScc(int n) { for (int i = 0; i < n * 2; i++)if (!order[i])dfs(i); }

	int solve(int n) {// 가능성 판단
		for (int i = 0; i < n * 2; i += 2)if (scc[i] == scc[i + 1])return 0;
		return 1;
	}

	void solve1(int n) { // 어떤걸로 가능한지 탐색
		for (int i = 0; i < n; i++)result[i] = -1;

		P p[ms];
		for (int i = 0; i < n * 2; i++)p[i] = { scc[i],i };
		sort(p, p + n * 2);

		for (int i = n * 2 - 1; i >= 0; i--) {
			int var = p[i].second;
			if (result[var / 2] == -1)result[var / 2] = !(var % 2);
		}
		for (int i = 0; i < n; i++)cout << result[i] << ' ';
	}

	int rev(int a) { return a % 2 ? a - 1 : a + 1; }

	void inp(int n, int m) {
		int a, b;
		for (int i = 0; i < n; i++) {
			cin >> a >> b;
			a = a < 0 ? -(a + 1) * 2 : a * 2 - 1;
			b = b < 0 ? -(b + 1) * 2 : b * 2 - 1;
			adj[rev(a)].push_back(b);
			adj[rev(b)].push_back(a);
		}
	}
};
