#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<stack>
#include<map>
#include<set>
#include<math.h>
#define ms 50
using namespace std;
typedef long long int ll;

struct Catalan { // 소인수들을 관리할 BIT
	struct Prime {
		int mod, prime[ms * 2 + 1], primes[ms * 2 + 1], factor[ms * 2 + 1], pc;

		void getPrime(int n) {
			int len = n * 2;
			for (int i = 2; i <= len; i++) {
				prime[i] = 1;
				factor[i] = i;
			}
			for (int i = 2; i*i <= len; i++) {
				if (!prime[i])continue;
				int j = i * i;
				while (j <= len) {
					prime[j] = 0;//소수판별
					factor[j] = i;//소인수저장
					j += i;
				}
			}
			pc = 0;
			for (int i = 2; i <= len; i++) {
				if (prime[i]) {
					prime[i] = ++pc;
					primes[pc] = i;//소수 기록
				}
			}
		}

		int expmod(int a, int n) {// (a^n)%M을 O(log n)에 계산하는 함수
			if (!n) return 1;
			int d = expmod(a, n / 2);
			ll dd = ((ll)d*d) % mod;
			if (n % 2)return (dd*a) % mod;
			return (int)dd;
		}
	};

	Prime c;
	int data[ms + 1], tree[2 * ms + 1], leaf[2 * ms + 1], size;// segment Tree 구성

	void init(int n, int m) {
		data[0] = 1;
		c.mod = m;
		c.getPrime(n);
		size = 1;
		while (size <= c.pc)size <<= 1;
		for (int i = 1; i < 2 * size; i++) tree[i] = 1;
	}

	void multiply(int x, int diff) {
		// 곱하는 수가 들어오면 소인수 분해한 뒤 각 소인수를 인덱스트리에 삽입.
		while (x > 1) {
			int v = c.factor[x];
			insert(c.prime[v], diff);//v가 몇번째 소수인지와 승수를 인자로 넘겨줌
			x /= v;
		}
	}

	void insert(int x, int diff) {
		int v = size + x;
		leaf[v] += diff;// leaf에는 몇승인지 쌓임
		tree[v] = c.expmod(c.primes[x], leaf[v]);//tree에는 tree^leaf의 값이 쌓임 이걸 모드 빠르게 해주기 위해서 logN 모드 사용
		while (v != 1) {
			v /= 2;
			tree[v] = (int)(((ll)tree[v * 2] * tree[v * 2 + 1]) % (ll)c.mod);
		}
	}

	int getTop() { return tree[1]; }

	void getCatalanNumber(int n) {
		for (int i = 1; i <= n; i++) {
			int N = i - 1;

			// 관계식 Cn+1 = 2(2*n+1)/(n+2) * Cn 을 이용해서 계산하는 부분
			multiply(2, 1);
			multiply(2 * N + 1, 1);
			multiply(N + 2, -1);
			data[i] = getTop();
		}
	}

	int getCatalan(int n) { return data[n]; }
};
