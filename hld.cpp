#include<bits/stdc++.h>
using namespace std::string_literals;
using lf=double;
using ll=std::ptrdiff_t;
using ull=std::size_t;
using us=unsigned;
template<typename ty>
using ue5=std::unique_ptr<ty>;
constexpr ll inf=0x3f3f3f3f3f3f3f3fl;
constexpr ll ver=1l<<17;
constexpr ll mod=0x3b800001l;
auto nxt(void){ll x;std::cin>>x;return x;}
/*
prob link:	https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P3384
start think:	
term think:	
start code:	
term code:	
*/
class	tree{
	ue5<tree>ld,rd;
	ll f,g,v,t;
public:
	tree(ll,ll,std::vector<ll>&);
	void push_up(void);
	void push_down(void);
	void update(ll,ll,ll);
	auto query(ll,ll,ll);
};
tree::tree(ll p,ll q,std::vector<ll>&a){
	f=p,g=q,t=0;
	if(f==g){
		v=a[f];
		return;
	}	ld=std::make_unique<tree>(f,f+g>>1,a);
	rd=std::make_unique<tree>((f+g>>1)+1,g,a);
	push_up();
}
void	tree::push_up(void){
	v=ld->v+rd->v;
}
void	tree::push_down(void){
	if(t==0)
		return;
	ld->t+=t;
	rd->t+=t;
	ld->v+=t*(ld->g-ld->f+1);
	rd->v+=t*(rd->g-rd->f+1);
	t=0;
}
void	tree::update(ll p,ll q,ll k){
	if(p<=f&&g<=q){
		t+=k;
		v+=k*(g-f+1);
		return;
	}	push_down();
	if(p<=ld->g)
		ld->update(p,q,k);
	if(rd->f<=q)
		rd->update(p,q,k);
	push_up();
}
auto	tree::query(ll p,ll q,ll yy){
	if(p<=f&&g<=q)
		return v+yy*(g-f+1);
	push_down();
	ll ct=0;
	if(p<=ld->g)
		ct+=ld->query(p,q,yy+t);
	if(rd->f<=q)
		ct+=rd->query(p,q,yy+t);
	return ct;
}
class	vtx{
public:
	std::vector<vtx*>to;
	vtx *t,*u,*d;
	ll dep,siz,dfn,val;
	void add_edge(vtx*);
	void dfs1(vtx*);
	void dfs2(vtx*);
}	v[ver];
void	vtx::add_edge(vtx *y){
	to.emplace_back(y);
}
void	vtx::dfs1(vtx *_){
	if(u=_)
		dep=u->dep+1;
	else	u=(vtx*)'$';
	siz=1,d=v;
	for(vtx *y:to){
		if(y->u)
			continue;
		y->dfs1(this);
		siz+=y->siz;
		if(d->siz<y->siz)
			d=y;
	}
}
ll dfc;
vtx *rev[ver];
void	vtx::dfs2(vtx *_){
	t=_;
	rev[dfn=++dfc]=this;
	if(d==v)
		return;
	d->dfs2(t);
	for(vtx *y:to){
		if(y->t)
			continue;
		y->dfs2(y);
	}
}
void	upd_way(ue5<tree>&rt,vtx *x,vtx *y,ll k){
	while(x->t!=y->t){
		if(x->t->dep<y->t->dep)
			std::swap(x,y);
		rt->update(x->t->dfn,x->dfn,k);
		x=x->t->u;
	}	if(y->dep<x->dep)
		std::swap(x,y);
	rt->update(x->dfn,y->dfn,k);
}
auto	qry_way(ue5<tree>&rt,vtx *x,vtx *y){
	ll jv=0;
	while(x->t!=y->t){
		if(x->t->dep<y->t->dep)
			std::swap(x,y);
		jv+=rt->query(x->t->dfn,x->dfn,0);
		x=x->t->u;
	}	if(y->dep<x->dep)
		std::swap(x,y);
	return jv+=rt->query(x->dfn,y->dfn,0);
}
void	upd_sub(ue5<tree>&rt,vtx *x,ll k){
	rt->update(x->dfn,x->dfn+x->siz-1,k);
}
auto	qry_sub(ue5<tree>&rt,vtx *x){
	return rt->query(x->dfn,x->dfn+x->siz-1,0);
}
void	solve(void){
	ll n=nxt(),q=nxt();
	vtx *s=v+nxt();
	ll p=nxt();
	for(vtx *x=v+1;x<=v+n;x++)
		x->val=nxt();
	for(ll t=n-1;t;t--){
		vtx *x=v+nxt();
		vtx *y=v+nxt();
		x->add_edge(y);
		y->add_edge(x);
	}	s->dfs1(nullptr);
	s->dfs2(s);
	std::vector<ll>a(n+1);
	for(ll x=1;x<=n;x++)
		a[x]=rev[x]->val;
	auto rt=std::make_unique<tree>(1,n,a);
	while(q--){
		ll op=nxt();
		if(op==1){
			vtx *x=v+nxt();
			vtx *y=v+nxt();
			ll k=nxt();
			upd_way(rt,x,y,k);
		}else	if(op==2){
			vtx *x=v+nxt();
			vtx *y=v+nxt();
			std::cout<<qry_way(rt,x,y)%p<<"\n"s;
		}else	if(op==3){
			vtx *x=v+nxt();
			ll k=nxt();
			upd_sub(rt,x,k);
		}else	if(op==4){
			vtx *x=v+nxt();
			std::cout<<qry_sub(rt,x)%p<<"\n"s;
		}else	std::cerr<<"~\n"s;
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
	return 0;
}
