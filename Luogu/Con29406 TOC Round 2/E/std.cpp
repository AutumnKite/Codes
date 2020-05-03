#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<set>
using namespace std;
#define N 100010
int read()
{
    int x=0,f=1;char c=getchar();
    while (c<'0'||c>'9') {if (c=='-') f=-1;c=getchar();}
    while (c>='0'&&c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x*f;
}
int n,m,root[N],rev[N],cnt;
struct data{int l,r,x;
}tree[N<<6];
struct data2
{
    int l,r;
    bool operator <(const data2&a) const
    {
        return r<a.r;
    }
};
set<data2> q;
void ins(int &k,int x,int l,int r)
{
    if (!k) k=++cnt;tree[k].x++;
    if (l==r) return;
    int mid=l+r>>1;
    if (x<=mid) ins(tree[k].l,x,l,mid);
    else ins(tree[k].r,x,mid+1,r);
}
void split(int &x,int &y,int rk,int op)
{
    if (!x) return;
    tree[y=++cnt].x=tree[x].x-rk,tree[x].x=rk;
    if (op==0)
    {
        if (tree[tree[x].l].x==rk)
        {
            tree[y].r=tree[x].r,tree[x].r=0;
            return;
        }
        else if (tree[tree[x].l].x>rk)
        {
            tree[y].r=tree[x].r,tree[x].r=0;
            split(tree[x].l,tree[y].l,rk,op);
        }
        else split(tree[x].r,tree[y].r,rk-tree[tree[x].l].x,op);
    }
    else
    {
        if (tree[tree[x].r].x==rk)
        {
            tree[y].l=tree[x].l,tree[x].l=0;
            return;
        }
        else if (tree[tree[x].r].x>rk)
        {
            tree[y].l=tree[x].l,tree[x].l=0;
            split(tree[x].r,tree[y].r,rk,op);
        }
        else split(tree[x].l,tree[y].l,rk-tree[tree[x].r].x,op);
    }
}
void merge(int &x,int &y,int l,int r) 
{
    if (!x||!y) {x|=y;return;}
    tree[x].x+=tree[y].x;
    if (l<r)
    {
        int mid=l+r>>1;
        merge(tree[x].l,tree[y].l,l,mid);
        merge(tree[x].r,tree[y].r,mid+1,r);
    }
}
int query(int k,int l,int r,int x,int op)
{
    if (l==r) return l;
    int mid=l+r>>1;
    if (op==0)
    {
        if (tree[tree[k].l].x>=x) return query(tree[k].l,l,mid,x,op);
        else return query(tree[k].r,mid+1,r,x-tree[tree[k].l].x,op);
    }
    else
    {
        if (tree[tree[k].r].x>=x) return query(tree[k].r,mid+1,r,x,op);
        else return query(tree[k].l,l,mid,x-tree[tree[k].r].x,op);
    }
}
int main()
{
    n=read(),m=read();
    for (int i=1;i<=n;i++) ins(root[i],read(),1,n),q.insert((data2){i,i});
    while (m--)
    {
        int opt=read();
		if (opt==0)
		{
			int l=read(),r=read(),op=read();
			set<data2>::iterator it=q.lower_bound((data2){l,l});
			if ((*it).l<l)
			{
				split(root[(*it).l],root[l],l-(*it).l,rev[(*it).l]);
				int L=(*it).l,R=(*it).r;
				q.erase(it);
				q.insert((data2){L,l-1});
				q.insert((data2){l,R});
				rev[l]=rev[L];
			}
			it=q.lower_bound((data2){r+1,r+1});
			if (it!=q.end()&&(*it).l<=r)
			{
				split(root[(*it).l],root[r+1],r-(*it).l+1,rev[(*it).l]);
				int L=(*it).l,R=(*it).r;
				q.erase(it);
				q.insert((data2){L,r});
				q.insert((data2){r+1,R});
				rev[r+1]=rev[L];
			}
			it=q.lower_bound((data2){l,l});it++;
			while (it!=q.end()&&(*it).r<=r) merge(root[l],root[(*it).l],1,n),it++;
			it=q.lower_bound((data2){l,l});
			while (it!=q.end()&&(*it).r<=r) q.erase(it),it=q.lower_bound((data2){l,l});
			q.insert((data2){l,r});
			rev[l]=op;
		}
		else
		{
			int x=read();
			set<data2>::iterator it=q.lower_bound((data2){x,x});
			cout<<query(root[(*it).l],1,n,x-(*it).l+1,rev[(*it).l])<<endl;
		}
    }
}
