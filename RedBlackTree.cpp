struct RBTree {
	struct node {
		int key;
		bool c;//false black, true red
		node* l, *r, *p;
		node(int key1 = 0, bool c1 = false) :key(key1), c(c1), l(nullptr), r(nullptr), p(nullptr) {}
	};
	node* root, *ret, *tail;
	int size = 0;

	void init() {
		root = nullptr;
		ret = nullptr;
		tail = new node(-1);
		size = 0;
	}

	node* search(int key) {
		node *x = root;
		while (x != tail && x->key != key) {
			if (x->key > key)x = x->l;
			else x = x->r;
		}
		ret = x;
		return x;
	}

	node* succesor(node *x) {
		x = x->r;
		while (x->l != tail) {
			x = x->l;
		}
		return x;
		node *y = x->p;
		while (y&&x == y->r) {
			x = y;
			y = y->p;
		}
		return y;
	}

	node* predeccesor(node *x) {
		x = x->l;
		while (x->r != tail)x = x->r;
		return x;
		node *y = x->p;
		while (y&&x == y->l) {
			x = y;
			y = y->p;
		}
		return y;
	}

	void leftRotate(node* x) {
		node *y = x->r;
		x->r = y->l;
		if (y->l != tail)y->l->p = x;
		y->p = x->p;
		if (x->p == nullptr)root = y;
		else if (x == x->p->l)x->p->l = y;
		else x->p->r = y;
		y->l = x;
		x->p = y;
	}

	void rightRotate(node *x) {
		node *y = x->l;
		x->l = y->r;
		if (y->r != tail)y->r->p = x;
		y->p = x->p;
		if (x->p == nullptr)root = y;
		else if (x == x->p->r)x->p->r = y;
		else x->p->l = y;
		y->r = x;
		x->p = y;
	}

	node* insertNode(node *now, int key) {
		while (1) {
			if (now->key > key) {
				if (now->l != tail)now = now->l;
				else {
					now->l = new node(key, true);
					now->l->l = now->l->r = tail;
					now->l->p = now;
					return now->l;
				}
			}
			else {
				if (now->r != tail)now = now->r;
				else {
					now->r = new node(key, true);
					now->r->l = now->r->r = tail;
					now->r->p = now;
					return now->r;
				}
			}
		}
	}

	void insertRB(int key) {
		++size;
		if (size == 1) {
			root = new node(key, false);
			root->l = root->r = tail;
			return;
		}
		node* x = insertNode(root, key);
		if (x->p->p == nullptr)return;
		while (x->p->c) {//부모의 색상이 RED이면 문제가 생김 그래서 회전
			if (x->p == x->p->p->l) {//부모가 왼쪽자식이면
				node *y = x->p->p->r;
				if (y->c) {//부모의 형제가 RED
					y->c = false;
					x->p->c = false;
					x->p->p->c = true;
					x = x->p->p;
				}
				else {//부모의 형제가 BLACK
					if (x == x->p->r) {
						x = x->p;
						leftRotate(x);
					}
					x->p->c = false;
					x->p->p->c = true;
					rightRotate(x->p->p);
				}
			}
			else {
				node*y = x->p->p->l;
				if (y->c) {
					x->p->c = false;
					y->c = false;
					x->p->p->c = true;
					x = x->p->p;
				}
				else {
					if (x == x->p->l) {
						x = x->p;
						rightRotate(x);
					}
					x->p->c = false;
					x->p->p->c = true;
					leftRotate(x->p->p);
				}
			}
			if (x == root)break;
		}
		root->c = false;
		root->p = nullptr;
	}

	void delRBFixup(node *x) {
		node* w;
		while (x != root && !x->c) {
			if (x == x->p->l) {
				w = x->p->r;
				if (w->c) {
					w->c = false;
					x->p->c = true;
					leftRotate(x->p);
					w = x->p->r;
				}
				if (!w->l->c && !w->r->c) {
					w->c = true;
					x = x->p;
				}
				else {
					if (!w->r->c) {
						w->l->c = false;
						w->c = true;
						rightRotate(w);
						w = x->p->r;
					}
					w->c = x->p->c;
					x->p->c = false;
					w->r->c = false;
					leftRotate(x->p);
					x = root;
				}
			}
			else {
				w = x->p->l;
				if (w->c) {
					w->c = false;
					x->p->c = true;
					rightRotate(x->p);
					w = x->p->l;
				}
				if (!w->r->c && !w->l->c) {
					w->c = true;
					x = x->p;
				}
				else {
					if (!w->l->c) {
						w->r->c = false;
						w->c = true;
						leftRotate(w);
						w = x->p->l;
					}
					w->c = x->p->c;
					x->p->c = false;
					w->l->c = false;
					rightRotate(x->p);
					x = root;
				}
			}
		}
		x->c = false;
	}

	void RBTransplant(node* u, node *v) {
		if (u->p == nullptr)root = v;
		else if (u == u->p->l)u->p->l = v;
		else u->p->r = v;
		v->p = u->p;
	}

	node* delRB(int key) {
		--size;
		node *z, *y, *x, *p;
		z = search(key);
		y = z;
		bool yc = y->c;
		if (z->l == tail) {
			x = z->r;
			RBTransplant(z, z->r);
		}
		else if (z->r == tail) {
			x = z->l;
			RBTransplant(z, z->l);
		}
		else {
			y = succesor(z);
			yc = y->c;
			x = y->r;
			if (y->p == z)x->p = y;
			else {
				RBTransplant(y, y->r);
				y->r = z->r;
				y->r->p = y;
			}
			RBTransplant(z, y);
			y->l = z->l;
			y->l->p = y;
			y->c = z->c;
		}
		if (!yc)delRBFixup(x);
		return y;
	}
};
