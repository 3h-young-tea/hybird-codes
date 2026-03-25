#include <bits/stdc++.h>

using std::complex_literals::operator""i;
using std::string_literals::operator""s;

constexpr long k_inf = 0x3f3f3f3f3f3f3f3fl;
constexpr long k_mod = 0x3b800001l;

auto	nxt(void) {
	long x;
	std::cin >> x;
	return x;
}

/*
prob link:	https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P3834
start think:	
term think:	
start code:	
term code:	
*/

class	tree {
	std::shared_ptr<tree> ld_, rd_;
	long f_, g_, tot_;

public:
	tree(long, long);
	tree(const std::shared_ptr<tree>&, long, long);
	long kth(const std::shared_ptr<tree>&, long) const;
};

tree::tree(long f, long g)
	: f_(f), g_(g), tot_(0) {
	if (f_ == g_)
		return;

	ld_ = std::make_shared<tree>(f_, f_ + g_ >> 1);
	rd_ = std::make_shared<tree>((f_ + g_ >> 1) + 1, g_);
}

tree::tree(const std::shared_ptr<tree> &y, long p, long k)
	: ld_(y->ld_), rd_(y->rd_),
	f_(y->f_), g_(y->g_), tot_(y->tot_ + k) {
	if (f_ == g_)
		return;

	if (p <= f_ + g_ >> 1)
		ld_ = std::make_shared<tree>(y->ld_, p, k);
	else
		rd_ = std::make_shared<tree>(y->rd_, p, k);
}

long	tree::kth(const std::shared_ptr<tree> &y, long k) const {
	if (f_ == g_)
		return f_;

	long ld_tot = ld_->tot_ - y->ld_->tot_;

	if (k <= ld_tot)
		return ld_->kth(y->ld_, k);
	else
		return rd_->kth(y->rd_, k - ld_tot);
}

long	val_to_rank(std::vector<long> &a, std::vector<long> &b) {
	std::copy(a.begin(), a.end(), b.begin());
	std::sort(b.begin(), b.end());
	b.erase(std::unique(b.begin(), b.end()), b.end());

	for (long &x : a)
		x = std::lower_bound(b.begin(), b.end(), x) - b.begin() + 1;

	return b.size();
}

void	solve(void) {
	long len = nxt(), queries = nxt();
	std::vector<long> a(len), b(len);
	std::generate(a.begin(), a.end(), nxt);
	long v = val_to_rank(a, b);

	std::vector<std::shared_ptr<tree>> rt;
	rt.emplace_back(std::make_shared<tree>(1, v));

	for (long x : a)
		rt.emplace_back(std::make_shared<tree>(rt[rt.size() - 1], x, 1));

	while (queries--) {
		long x = nxt(), y = nxt(), k = nxt();
		std::cout << b[rt[y]->kth(rt[x - 1], k) - 1] << "\n"s;
	}

	std::exit(0);
}

signed	main(void) {
//	std::freopen(".in", "r", stdin);
//	std::freopen(".out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	long _ = 1;

//	_ = nxt();

	while (_--)
		solve();

	std::cout.flush();
	return EXIT_SUCCESS;
}
