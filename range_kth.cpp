#include <bits/stdc++.h>

using std::complex_literals::operator""i;
using std::string_literals::operator""s;

using lf = double;
using ll = std::ptrdiff_t;
using ull = std::size_t;
using us = unsigned;

constexpr ll k_inf = 0x3f3f3f3f3f3f3f3fl;
constexpr ll k_mod = 0x3b800001l;

auto	nxt(void) {
	ll x;
	std::cin >> x;
	return x;
}

/*
prob link:	https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P3834
		https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-T741150
start think:	
term think:	
start code:	
term code:	
*/

class	tree {
	std::shared_ptr<tree> ld_, rd_;
	ll f_, g_, tot_;

public:
	tree(ll, ll);
	void update(std::shared_ptr<tree>&, ll, ll);
	auto kth(std::shared_ptr<tree>&, ll) const;
};

tree::tree(ll p, ll q)
	: f_(p), g_(q), tot_(0) {}

void	tree::update(std::shared_ptr<tree> &y, ll p, ll k) {
	if (y) {
		ld_ = y->ld_;
		rd_ = y->rd_;
		tot_ = y->tot_ + k;
	} else
		tot_ = k;

	if (f_ == g_)
		return;

	if (p <= f_ + g_ >> 1) {
		ld_ = std::make_shared<tree>(f_, f_ + g_ >> 1);
		ld_->update(y ? y->ld_ : y, p, k);
	} else {
		rd_ = std::make_shared<tree>((f_ + g_ >> 1) + 1, g_);
		rd_->update(y ? y->rd_ : y, p, k);
	}
}

auto	tree::kth(std::shared_ptr<tree> &y, ll k) const {
	if (f_ == g_)
		return f_;

	ll ld_t = (ld_ ? ld_->tot_ : 0) - (y && y->ld_ ? y->ld_->tot_ : 0);

	if (k <= ld_t)
		return ld_->kth(y ? y->ld_ : y, k);
	else
		return rd_->kth(y ? y->rd_ : y, k - ld_t);
}

void	solve(void) {
	ll len = nxt(), queries = nxt(), range = (1l << 30) - 1;
	auto rt = std::make_unique<std::shared_ptr<tree>[]>(len + 1);
	rt[0] = std::make_shared<tree>(0, range);

	for (ll x = 1; x <= len; ++x){
		rt[x] = std::make_shared<tree>(0, range);
		rt[x]->update(rt[x - 1], nxt(), 1);
	}

	while (queries--) {
		ll x = nxt(), y = nxt(), k = nxt();
		std::cout << rt[y]->kth(rt[x - 1], k) << "\n"s;
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
