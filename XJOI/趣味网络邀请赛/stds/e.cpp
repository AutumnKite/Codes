#include<bits/stdc++.h>
using namespace std;
 
#define ll long long
#define ldb long double
const int N=2.3e5+10;
const ldb eps=1e-9;
 
int n;
 
struct L{
    ll k, b;
    ldb f(ldb x){ return k*x+b; }
    ll f(ll x){ return k*x+b; }
}a[N]; vector<L>tb[N*4];
 
inline ldb cros(const L &a,const L &b){
    return (ldb)(a.b-b.b)/(b.k-a.k);
}
 
struct P{
    ldb x, y;
}; vector<P>tp[N*4];
 
struct node{
    int ty, id; ll tim;
}; vector<node>nd[N*4];
 
void calc(vector<L>&tb,vector<P>&tp,ll &anl,ll &anr,L t,int deb){
    int res, p=lower_bound(tb.begin(),tb.end(),t,[](L a,L b){return a.k<b.k;})-tb.begin()-1;
    if (t.f(tp[p].x)+eps>=tp[p].y){
        res=lower_bound(tp.begin(),tp.begin()+p+1,t,[](P a,L t){return !(t.f(a.x)+eps>=a.y);})-tp.begin();
        anl=cros(tb[res],t)-1;
        for (int sb=3;sb--;) if (t.f(anl)<tb[res].f(anl)) ++anl;
        res=lower_bound(tp.begin()+p,tp.end(),t,[](P a,L t){return t.f(a.x)+eps>=a.y;})-tp.begin();
        anr=cros(tb[res],t)+1;
        for (int sb=3;sb--;) if (t.f(anr)<tb[res].f(anr)) --anr;
    }else{
        anl=1; anr=0;
    }
}
void goup(int x,int id,ll st,ll en){
    nd[x].push_back({1,id,st});
    nd[x].push_back({-1,id,en});
    if (x==1) return;
    if (x%2==1){
        int fa=x/2, y=fa*2; ll anl, anr;
        calc(tb[y],tp[y],anl,anr,a[id],0);
        st=max(st,anl); en=min(en,anr);
    }
    if (st>en) return;
    goup(x/2,id,st,en);
}
 
void build(int x,int l,int r){
    if (x%2==0){
        static vector<L>tmp; tmp.clear(); for (int i=l;i<=r;++i) tmp.push_back(a[i]);
        sort(tmp.begin(),tmp.end(),[](L a,L b){ return a.k==b.k? a.b>b.b: a.k<b.k; });
        tmp.insert(tmp.begin(),(L){(ll)-2e6,(ll)-2.1e12}); tmp.push_back((L){(ll)-0,(ll)-2.1e12});
        tb[x].resize(r-l+3); tp[x].resize(r-l+3); tb[x].clear(); tp[x].clear(); vector<L>&st=tb[x];
        for (auto l:tmp){
            if (st.size()&&st.back().k==l.k) continue;
            while (st.size()>=2&&cros(st[st.size()-2],st[st.size()-1])>=cros(st[st.size()-2],l)) st.pop_back();
            st.push_back(l);
        }
        for (int i=1;i<st.size();++i){
            ldb w=cros(st[i-1],st[i]);
            tp[x].push_back({w,st[i].f(w)});
        }
    }
    nd[x].clear();
    if (l==r) goup(x,l,1,1e6);
    if (l==r) return;
    int mid=l+r>>1;
    build(x<<1,l,mid);
    build(x<<1|1,mid+1,r);
}
 
int m; ll ans[N], mx[N];
struct OPT{
    ll t, l, r;
}opt[N];
 
void add0(int x,int l,int r,int st,int en,int id){
    st=max(st,l); en=min(en,r);
    if (st>en) return;
    if (st==l&&en==r){
        nd[x].push_back({0,id,opt[id].t});
        return;
    }
    int mid=l+r>>1;
    add0(x<<1,l,mid,st,en,id);
    add0(x<<1|1,mid+1,r,st,en,id);
}
 
namespace tree2{
    struct TR{
        int ty, pre; ll rk, rb, sk, sb;
    }tr[N*4];
    inline TR operator + (const TR &a,const TR &b){
        return {(a.ty|b.ty),(a.ty? a.pre: a.pre+b.pre),(b.ty? b.rk: a.rk),(b.ty? b.rb: a.rb),a.sk+b.sk+a.rk*b.pre,a.sb+b.sb+a.rb*b.pre};
    }
    void build(int x,int l,int r){
        tr[x]={0,r-l+1,0,0,0,0};
        if (l==r) return;
        int mid=l+r>>1;
        build(x<<1,l,mid);
        build(x<<1|1,mid+1,r);
    }
    void cg(int x,int l,int r,int p){
        if (l==r){
            if (tr[x].ty) tr[x]={0,1,0,0,0,0};
            else tr[x]={1,0,a[l].k,a[l].b,a[l].k,a[l].b};
            return;
        }
        int mid=l+r>>1;
        if (p<=mid) cg(x<<1,l,mid,p);
        else cg(x<<1|1,mid+1,r,p);
        tr[x]=tr[x<<1]+tr[x<<1|1];
    }
    int fin(int x,int l,int r,ll nowx,ll nowy){
        if (l==r) return l;
        int mid=l+r>>1; TR &lt=tr[x<<1];
        if (lt.ty&&lt.rk*nowx+lt.rb>nowy) return fin(x<<1,l,mid,nowx,nowy);
        else return fin(x<<1|1,mid+1,r,nowx,nowy);
    }
    TR que(int x,int l,int r,int p){
        if (l>=p) return tr[x];
        int mid=l+r>>1;
        if (p<=mid) return que(x<<1,l,mid,p)+que(x<<1|1,mid+1,r,p);
        else return que(x<<1|1,mid+1,r,p);
    }
}
 
void dfs(int x,int l,int r){
    sort(nd[x].begin(),nd[x].end(),[](node a,node b){return a.tim==b.tim? a.ty>b.ty: a.tim<b.tim;});
    tree2::build(1,l,r);
    for (auto o:nd[x]){
        if (o.ty){
            tree2::cg(1,l,r,o.id);
        }else{
            ll rk=tree2::tr[1].rk, rb=tree2::tr[1].rb;
            ll nowx=opt[o.id].t;
            if (rk*nowx+rb<=mx[o.id]){
                ans[o.id]+=mx[o.id]*(r-l+1);
            }else{
                int p=tree2::fin(1,l,r,nowx,mx[o.id]);
                tree2::TR res=tree2::que(1,l,r,p);
                ans[o.id]+=mx[o.id]*(p-l)+res.sk*nowx+res.sb;
                mx[o.id]=rk*nowx+rb;
            }
        }
    }
    if (l==r) return;
    int mid=l+r>>1;
    dfs(x<<1,l,mid);
    dfs(x<<1|1,mid+1,r);
}
 
void gaoit(){
    build(1,1,n);
    for (int i=1;i<=m;++i){
        add0(1,1,n,opt[i].l,opt[i].r,i);
        mx[i]=-2.1e12;
    }
    dfs(1,1,n);
    {
        reverse(a+1,a+n+1);
        for (int i=1;i<=m;++i){
            opt[i]={opt[i].t,n+1-opt[i].r,n+1-opt[i].l};
        }
    }
}
 
int main(){
    cin>>n>>m;
    for (int i=1;i<=n;++i) scanf("%lld",&a[i].b);
    for (int i=1;i<=n;++i) scanf("%lld",&a[i].k), a[i].k*=-1;
    for (int i=1;i<=m;++i) scanf("%lld%lld%lld",&opt[i].t,&opt[i].l,&opt[i].r);
    gaoit();
    gaoit();
    static ll sk[N], sb[N];
    for (int i=1;i<=n;++i) sk[i]=sk[i-1]+a[i].k, sb[i]=sb[i-1]+a[i].b;
    for (int i=1;i<=m;++i){
        ll x=opt[i].t, l=opt[i].l, r=opt[i].r;
        ans[i]=ans[i]-mx[i]*(r-l+1)-((sk[r]-sk[l-1])*x+(sb[r]-sb[l-1]));
        printf("%lld\n",ans[i]);
    }
}