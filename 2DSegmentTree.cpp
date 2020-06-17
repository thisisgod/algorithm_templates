struct _2DsegmentTree {
	int seg[1 << 12][1 << 12], base;

	void init(int n) {
		base = pow(2, (int)log2(n) + 1);
		for (int i = base; i < base + n; i++)for (int j = base; j < base + n; j++) cin >> seg[i][j];
		for (int i = base; i < base + n; i++)for (int j = base - 1; j > 0; j--)seg[i][j] = seg[i][j << 1] + seg[i][j << 1 | 1];
		for (int i = base - 1; i > 0; i--)for (int j = 0; j < base + n; j++)seg[i][j] = seg[i << 1][j] + seg[i << 1 | 1][j];
	}

	void update(int a, int b, int c) { // Change (a,c) -> c
		int idx = base + b - 1, itr = base + a - 1;
		seg[itr][idx] = c;
		for (int i = itr / 2; i > 0; i /= 2)seg[i][idx] = seg[i << 1][idx] + seg[i << 1 | 1][idx];
		for (int i = idx / 2; i > 0; i /= 2) {
			seg[itr][i] = seg[itr][i << 1] + seg[itr][i << 1 | 1];
			for (int j = itr / 2; j > 0; j /= 2)seg[j][i] = seg[j << 1][i] + seg[j << 1 | 1][i];
		}
	}

	ll query(int a, int b, int c, int d) { // query (a,c) ~ (b,d)
		ll ret = 0;
		int yl = base + a - 1, yr = base + c - 1;
		while (yl <= yr) {
			if (yl & 1) {
				int l = base + b - 1, r = base + d - 1;
				while (l <= r) {
					if (l & 1) ret += seg[yl][l++];
					if (~r & 1)ret += seg[yl][r--];
					l >>= 1;
					r >>= 1;
				}
				yl++;
			}
			if (~yr & 1) {
				int l = base + b - 1, r = base + d - 1;
				while (l <= r) {
					if (l & 1) ret += seg[yr][l++];
					if (~r & 1)ret += seg[yr][r--];
					l >>= 1;
					r >>= 1;
				}
				yr--;
			}
			yl >>= 1;
			yr >>= 1;
		}
		return ret;
	}
};
