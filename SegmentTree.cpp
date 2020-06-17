struct segmentTree {
	ll seg[1 << 21];
	int base;

	void init(int n) {
		base = pow(2, (int)log2(n) + 1);
		for (int i = base; i < base + n; i++) cin >> seg[i];
		for (int i = base - 1; i > 0; i--)seg[i] = seg[i << 1] + seg[i << 1 | 1];
	}

	void update(int a, int b) { // Change (a) -> b
		int idx = base + a - 1;
		seg[idx] = b;
		for (int i = idx / 2; i > 0; i /= 2) seg[i] = seg[i << 1] + seg[i << 1 | 1];
	}

	ll query(int a, int b) { // query (a) ~ (b)
		ll ret = 0;
		int l = base + a - 1, r = base + b - 1;
		while (l <= r) {
			if (l & 1) ret += seg[l++];
			if (~r & 1)ret += seg[r--];
			l >>= 1;
			r >>= 1;
		}
		return ret;
	}
};
