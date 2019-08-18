#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <bitset>
#include <vector>
#define LL long long
#define For(i,a,b) for(register int i=(int)(a),i_E=(int)(b);i<=i_E;++i)
#define Fod(i,a,b) for(register int i=(int)(a),i_E=(int)(b);i>=i_E;--i)
#define cross(i,a) for(register int i=hd[(a)];i;i=pr[i])
using namespace std;
inline LL Max(LL a,LL b){return a>b?a:b;}
inline LL Min(LL a,LL b){return a<b?a:b;}
#define CH ch=getchar()
inline LL read(){
    LL x=0;int f=1,ch;
    for(CH;!isdigit(ch)&&ch!='-'&&ch!=EOF;CH);
    if(ch=='-') CH,f=-1;
    for(;isdigit(ch);CH) x=(x<<1)+(x<<3)+ch-'0';
    return x*f;
}
inline void write(LL x){
    if(x<0) x=-x,putchar('-');
    if(x<10) putchar(x+48);
    else write(x/10),putchar(x%10+48);
}
struct Treap{
    Treap *ls,*rs;
    int data,key,size;
    Treap(int v=0){ls=NULL,rs=NULL,data=v,key=rand(),size=1;}
}*T;
typedef pair<Treap*,Treap*> D;
#define fr first
#define sc second
inline int sz(Treap* u){return u?u->size:0;}
inline void up(Treap* u){u->size=(u->ls?u->ls->size:0)+(u->rs?u->rs->size:0)+1;}
inline D split(Treap* u,int k){
    if(!u) return D(NULL,NULL);
    if(sz(u->ls)>=k){D t=split(u->ls,k);u->ls=t.sc,up(u),t.sc=u;return t;}
    else{D t=split(u->rs,k-sz(u->ls)-1);u->rs=t.fr,up(u),t.fr=u;return t;}
}
inline Treap* merge(Treap* u,Treap* v){
    if(!u) return v;if(!v) return u;
    if(u->key<v->key){u->rs=merge(u->rs,v),up(u);return u;}
    else{v->ls=merge(u,v->ls),up(v);return v;}
}
inline int Rank(Treap* u,int x){
    return !u?0:(x<=u->data?Rank(u->ls,x):Rank(u->rs,x)+sz(u->ls)+1);
}
inline int Kth(int k){
    D x=split(T,k-1),y=split(x.sc,1);
    Treap* ans=y.fr;
    T=merge(merge(x.fr,ans),y.sc);
    return ans?ans->data:0;
}
inline void Insert(int v){
    int k=Rank(T,v);D x=split(T,k);Treap *u=new Treap(v);T=merge(merge(x.fr,u),x.sc);
}
inline void Delete(int v){
    int k=Rank(T,v);D x=split(T,k),y=split(x.sc,1);T=merge(x.fr,y.sc);
}
int main(){
    Fod(m,read(),1){
        int opt=read(),x=read();
        if(opt==1) Insert(x);
        if(opt==2) Delete(x);
        if(opt==3) write(Rank(T,x)+1),putchar('\n');
        if(opt==4) write(Kth(x)),putchar('\n');
        if(opt==5) write(Kth(Rank(T,x))),putchar('\n');
        if(opt==6) write(Kth(Rank(T,x+1)+1)),putchar('\n');
    }
}
