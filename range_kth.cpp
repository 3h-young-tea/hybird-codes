#include<bits/stdc++.h>
using namespace std::string_literals;
#define try "i`ve aked wf!"s
using lf=double;
using ll=std::ptrdiff_t;
using ull=std::size_t;
using us=unsigned;
#define uoj unique_ptr
#define qoj shared_ptr
#define muoj make_unique
#define mqoj make_shared
constexpr ll inf=0x3f3f3f3f3f3f3f3fl;
constexpr ll mod=0x3b800001l;
auto nxt(void){ll x;std::cin>>x;return x;}
/*
prob link:	https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P3834
start think:	
term think:	
start code:	mar 6th 2026, 12:39
term code:	mar 6th 2026, 12:52
start dbg:	mar 6th 2026, 12:54
term dbg:	mar 6th 2026, 13:06
start dbg:	mar 6th 2026, 13:27
term dbg:	mar 6th 2026, 13:36
*/
class	tree{
	std::qoj<tree>ld,rd;
	ll f,g,tot;
public:
	tree(ll,ll);
	void build(ll,ll);
	void update(std::qoj<tree>&,ll,ll);
	auto kth(std::qoj<tree>&,ll);
};
tree::tree(ll p,ll q){
	f=p,g=q,tot=0;
}
void	tree::update(std::qoj<tree>&x,ll p,ll k){
	if(x){
		ld=x->ld,rd=x->rd;
		tot=x->tot+k;
	}else	tot=k;
	if(f==g)
		return;
	if(p<=f+g>>1)
		ld=std::mqoj<tree>(f,f+g>>1),
		ld->update(x?x->ld:x,p,k);
	else	rd=std::mqoj<tree>((f+g>>1)+1,g),
		rd->update(x?x->rd:x,p,k);
}
auto	tree::kth(std::qoj<tree>&x,ll k){
	if(f==g)
		return f;
	ll ldt=(ld?ld->tot:0)-(x&&x->ld?x->ld->tot:0);
	if(k<=ldt)
		return ld->kth(x?x->ld:x,k);
	else	return rd->kth(x?x->rd:x,k-ldt);
}
void	solve(void){
	ll n=nxt(),q=nxt(),v=(1l<<30)-1;
	auto rt=std::muoj<std::qoj<tree>[]>(n+1);
	rt[0]=std::mqoj<tree>(0,v);
	for(ll x=1;x<=n;x++)
		rt[x]=std::mqoj<tree>(0,v),
		rt[x]->update(rt[x-1],nxt(),1);
	while(q--){
		ll x=nxt(),y=nxt(),k=nxt();
		std::cout<<rt[y]->kth(rt[x-1],k)<<"\n"s;
	}
}
auto	main(void)->signed{
//	std::freopen(".in","r",stdin);
//	std::freopen(".out","w",stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	ll _=1;
//	_=nxt();
	while(_--)
		solve();
	std::cout.flush();
	return 0;
}
