struct ConvexHull {
	struct point {
		int x, y;
		int p, q;
		point(int x1 = 0, int y1 = 0) :x(x1), y(y1) {}
		point operator-(point a) {
			return point(x - a.x, y - a.y);
		}
		bool operator==(point a) {
			return x == a.x&&y == a.y;
		}
		bool operator <(const point& O) {
			if (1LL * q*O.p != 1LL * p*O.q) return 1LL * q*O.p < 1LL * p*O.q;
			if (y != O.y) return y < O.y;
			return x < O.x;
		}
	};

	int n, t, chk[20];
	point arr[100000], pnt;
	vector<point> ret;

	int ccw(point u, point v) {
		return u.x*v.y - u.y*v.x;
	}

	int direction(point a, point b, point c) {
		if (ccw(b - a, c - a) > 0)return 1;
		if (ccw(b - a, c - a) < 0)return -1;
		else return 0;
	}

	bool between(point a, point b, point c) {
		if (direction(a, b, c))return false;
		if (a.x != b.x) return a.x <= c.x&&c.x <= b.x || b.x <= c.x&&c.x <= a.x;
		else return a.y <= c.y&&c.y <= b.y || b.y <= c.y&&c.y <= a.y;
	}

	double area(point a, point b, point c) {
		double ret = (double)(a.x*b.y + b.x*c.y + c.x*a.y - a.y*b.x - c.y*a.x - b.y*c.x) / 2;
		return ret < 0 ? -ret : ret;
	}

	bool insidePolygon(int idx) {
		int chk = 0, n = ret.size();
		for (int i = 0; i < n; i++) {
			int nxt = (i + 1) % n;
			if (between(ret[i], ret[nxt], pnt)) return true;
			if (ret[i].y < pnt.y&&ret[nxt].y >= pnt.y && direction(ret[i], ret[nxt], pnt)>0 ||
				ret[nxt].y < pnt.y&&ret[i].y >= pnt.y&&direction(ret[nxt], ret[i], pnt)>0)chk++;
		}
		if (chk % 2)return true;
		return false;
	}

	void makeConvexHull() {
		sort(arr, arr + n);
		for (int i = 1; i < n; i++) {
			arr[i].p = arr[i].x - arr[0].x;
			arr[i].q = arr[i].y - arr[0].y;
		}
		sort(arr + 1, arr + n);
		ret.push_back(arr[0]);
		ret.push_back(arr[1]);
		for (int i = 2; i < n; i++) {
			while (ret.size() >= 2) {
				point first = ret[ret.size() - 1], second = ret[ret.size() - 2];
				ret.pop_back();
				if (direction(second, first, arr[i]) > 0) {
					ret.push_back(first);
					break;
				}
			}
			ret.push_back(arr[i]);
		}
		if (ret[0] == ret[ret.size() - 1])ret.pop_back();
	}
};
