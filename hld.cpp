#include <bits/stdc++.h>

using std::complex_literals::operator""i;
using std::string_literals::operator""s;

using lf = double;
using ll = std::ptrdiff_t;
using ull = std::size_t;
using us = unsigned;

constexpr ll k_inf = 0x3f3f3f3f3f3f3f3fl;
constexpr ll k_mod = 0x3b800001l;
constexpr ll k_max_ver = 1l << 17;

auto	nxt(void) {
	ll x;
	std::cin >> x;
	return x;
}

/*
prob link:	https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P3384
start think:	
term think:	
start code:	mar 12th 2026, 20:02
term code:	mar 12th 2026, 20:37
start dbg:	mar 12th 2026, 20:38
solve 里的 a 数组没有初始化为 tree_siz 长度
term dbg:	mar 12th 2026, 20:39
*/

class	tree {
	std::unique_ptr<tree> ld_, rd_;
	ll f_, g_;
	ll v_, t_;

	void push_up(void);
	void push_down(void);

public:
	tree(ll, ll, std::vector<ll>&);
	void update(ll, ll, ll);
	auto query(ll, ll, ll) const;
};

void	tree::push_up(void) {
	v_ = ld_->v_ + rd_->v_;
}

void	tree::push_down(void) {
	if (t_ == 0)
		return;

	ld_->t_ += t_;
	ld_->v_ += t_ * (ld_->g_ - ld_->f_ + 1);

	rd_->t_ += t_;
	rd_->v_ += t_ * (rd_->g_ - rd_->f_ + 1);

	t_ = 0;
}

tree::tree(ll p, ll q, std::vector<ll> &a)
	: f_(p), g_(q), v_(0), t_(0) {
	if (f_ == g_) {
		v_ = a[f_];
		return;
	}

	ld_ = std::make_unique<tree>(f_, f_ + g_ >> 1, a);
	rd_ = std::make_unique<tree>((f_ + g_ >> 1) + 1, g_, a);

	push_up();
}

void	tree::update(ll p, ll q, ll k) {
	if (p <= f_ && g_ <= q) {
		t_ += k;
		v_ += k * (g_ - f_ + 1);
		return;
	}

	push_down();

	if (p <= ld_->g_)
		ld_->update(p, q, k);

	if (rd_->f_ <= q)
		rd_->update(p, q, k);

	push_up();
}

auto	tree::query(ll p, ll q, ll yy) const {
	ll xt = 0;

	if (p <= f_ && g_ <= q) {
		return xt = v_ + yy * (g_ - f_ + 1);
	}

	if (p <= ld_->g_)
		xt += ld_->query(p, q, yy + t_);

	if (rd_->f_ <= q)
		xt += rd_->query(p, q, yy + t_);

	return xt;
}

class	vtx{
public:
	std::vector<vtx*> to_;
	vtx *t_, *u_, *d_;
	ll dep_, siz_;
	ll dfn_;
	ll val_;

	void add_edge(vtx*);
	void dfs1(vtx*);
	void dfs2(vtx*);
};

vtx v[k_max_ver];

void	vtx::add_edge(vtx *y) {
	to_.emplace_back(y);
}

void	vtx::dfs1(vtx *_) {
	if (u_ = _)
		dep_ = u_->dep_ + 1;

	d_ = v;
	siz_ = 1;

	for (vtx *y : to_) {
		if (y->d_)
			continue;

		y->dfs1(this);
		siz_ += y->siz_;

		if (d_->siz_ < y->siz_ || d_->siz_ == y->siz_ && y < d_)
			d_ = y;
	}
}

std::vector<vtx*> rev;

void	vtx::dfs2(vtx *_) {
	t_ = _;
	dfn_ = rev.size();
	rev.emplace_back(this);

	if (d_ == v)
		return;

	d_->dfs2(t_);

	for (vtx *y : to_) {
		if (y->t_)
			continue;

		y->dfs2(y);
	}
}

void	upd_way(std::unique_ptr<tree> &rt, vtx *x, vtx *y, ll z) {
	while (x->t_ != y->t_) {
		if (x->t_->dep_ < y->t_->dep_)
			std::swap(x, y);

		rt->update(x->t_->dfn_, x->dfn_, z);
		x = x->t_->u_;
	}

	if (y->dep_ < x->dep_)
		std::swap(x, y);

	rt->update(x->dfn_, y->dfn_, z);
}

auto	qry_way(const std::unique_ptr<tree> &rt, vtx *x, vtx *y) {
	ll yt = 0;

	while (x->t_ != y->t_) {
		if (x->t_->dep_ < y->t_->dep_)
			std::swap(x, y);

		yt += rt->query(x->t_->dfn_, x->dfn_, 0);
		x = x->t_->u_;
	}

	if (y->dep_ < x->dep_)
		std::swap(x, y);

	return yt += rt->query(x->dfn_, y->dfn_, 0);
}

void	upd_sub(std::unique_ptr<tree> &rt, vtx *x, ll z) {
	rt->update(x->dfn_, x->dfn_ + x->siz_ - 1, z);
}

auto	qry_sub(const std::unique_ptr<tree> &rt, vtx *x) {
	return rt->query(x->dfn_, x->dfn_ + x->siz_ - 1, 0);
}

void	solve(void) {
	ll tree_siz = nxt(), queries = nxt();
	vtx *s = v + nxt();
	ll mod = nxt();

	for (vtx *x = v + 1; x <= v + tree_siz; ++x)
		x->val_ = nxt();

	for (ll t = 1; t < tree_siz; ++t) {
		vtx *x = v + nxt();
		vtx *y = v + nxt();
		x->add_edge(y);
		y->add_edge(x);
	}

	s->dfs1(nullptr);
	s->dfs2(s);

	std::vector<ll>a(tree_siz);

	for (ll x = 0; x < tree_siz; ++x)
		a[x] = rev[x]->val_;

	auto rt = std::make_unique<tree>(0, tree_siz - 1, a);

	while (queries--) {
		ll op = nxt();

		if (op == 1) {
			vtx *x = v + nxt();
			vtx *y = v + nxt();
			ll z = nxt();
			upd_way(rt, x, y, z);
		} else if (op == 2) {
			vtx *x = v + nxt();
			vtx *y = v + nxt();
			std::cout << qry_way(rt, x, y) % mod << "\n"s;
		} else if (op == 3) {
			vtx *x = v + nxt();
			ll z = nxt();
			upd_sub(rt, x, z);
		} else if (op == 4) {
			vtx *x = v + nxt();
			std::cout << qry_sub(rt, x) % mod << "\n"s;
		} else
			std::cerr << "i`ve aked wf!\n"s;
	}
}

auto	main(void)->signed {
//	std::freopen(".in", "r", stdin);
//	std::freopen(".out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	ll _ = 1;

//	_ = nxt();

	while (_--)
		solve();

	std::cout.flush();
	return 0;
}
