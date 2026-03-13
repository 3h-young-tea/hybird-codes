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
prob link:	https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-B3694
start think:	
term think:	
start code:	mar 13th 2026, 7:07
term code:	mar 13th 2026, 7:23
*/

void	merge_sort(std::vector<ll>&a, ll f, ll g) {
	if (g <= f)
		return;

	merge_sort(a, f, f + g >> 1);
	merge_sort(a, (f + g >> 1) + 1, g);

	std::vector<ll>t(g - f + 1);
	std::merge(a.begin() + f, a.begin() + (f + g >> 1) + 1,
		a.begin() + (f + g >> 1) + 1, a.begin() + g + 1,
		t.begin());
	std::copy(t.begin(), t.end(), a.begin() + f);
}

template<class func>
auto	b_query(ll f, ll g, func chk) {
	while (f < g)
		if (ll h = f + g >> 1; !chk(h))
			f = h + 1;
		else
			g = h;
	return f;
}

auto	range_to_rank(std::vector<ll>&a, std::vector<ll>&b, bool base) {
	b.resize(a.size());
	std::copy(a.begin(), a.end(), b.begin());
	merge_sort(b, 0, b.size() - 1);

	ll v = 0;

	for (ll x = 1; x < b.size(); ++x)
		if (b[x] != b[x - 1])
			b[++v] = b[x];

	b.resize(v + 1);

	for (ll x = 0; x < a.size(); ++x)
		a[x] = b_query(0, b.size() - 1, [&](ll y) {
			return a[x] <= b[y];
		}) + base;

	return v + base;
}

void	solve(void) {
	ll n = nxt();
	std::vector<ll>a(n), b;
	std::generate(a.begin(), a.end(), nxt);
	range_to_rank(a, b, 1);
	for (ll x = 0; x < n; ++x)
		std::cout << a[x] << " \n"s[x == n - 1];
}

auto	main(void)->signed {
//	std::freopen(".in", "r", stdin);
//	std::freopen(".out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	ll _ = 1;

	_ = nxt();

	while (_--)
		solve();

	std::cout.flush();
	return 0;
}
