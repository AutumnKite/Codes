#include<bits/stdc++.h>
#include"airline.h"
using namespace std;

const int _ = 5e4 + 3;
struct Edge{int end , upEd , w;}Ed[_ * 4]; int head[_] , cntEd , n , q , x , y , L;
void addEd(int p , int q , int r){Ed[++cntEd] = (Edge){q , head[p] , r}; head[p] = cntEd;}
struct EDGE{int p , q , w;};

long long dst[_];
void run_dijk(vector < int > node , int fir){
	for(auto t : node) dst[t] = 1e18;
	priority_queue < pair < long long , int > > q; dst[fir] = 0; q.push(make_pair(0 , fir));
	while(!q.empty()){
		long long v = -q.top().first; int t = q.top().second; q.pop(); if(dst[t] != v) continue;
		for(int i = head[t] ; i ; i = Ed[i].upEd)
			if(dst[Ed[i].end] > v + Ed[i].w){dst[Ed[i].end] = v + Ed[i].w; q.push(make_pair(-dst[Ed[i].end] , Ed[i].end));}
	}
}

struct Data{
	int ch[2] , sp[2]; unordered_map < int , int > id;
	vector < int > bel; vector < long long > dst[2];
	void builddst(vector < int > node , vector < EDGE > edge){
		cntEd = 0; for(auto t : node) head[t] = 0;
		for(auto t : edge){addEd(t.p , t.q , t.w); addEd(t.q , t.p , t.w);}
		for(int i = 0 ; i < 2 ; ++i){run_dijk(node , sp[i]); for(auto t : node) dst[i].push_back(::dst[t]);}
	}
}dat[_ << 3]; int cntdat;

int divide(vector < int > node , vector < EDGE > pot){
	Data &t = dat[++cntdat]; for(int i = 0 ; i < node.size() ; ++i) t.id[node[i]] = i;
	int N = node.size() , mx = 0 , now = cntdat; EDGE mxed;
	for(auto x : pot){int p = t.id[x.p] , q = t.id[x.q] , v = min(abs(q - p) , N - abs(q - p)); if(v > mx){mx = v; mxed = x;}}
	
	t.sp[0] = mxed.p; t.sp[1] = mxed.q; vector < int > L , R; bool flg = 0; int pl = t.id[mxed.p] , pr = t.id[mxed.q];
	for(int i = 0 ; i < node.size() ; ++i){
		(flg ? R : L).push_back(node[i]); t.bel.push_back(flg);
		if(i == pl || i == pr){flg ^= 1; (flg ? R : L).push_back(node[i]); t.bel.back() = -1;}
	}
	vector < EDGE > PL , PR;
	for(auto x : pot){
		int mx = max(t.bel[t.id[x.p]] , t.bel[t.id[x.q]]);
		if(mx != 1){PL.push_back(x);} if(mx != 0){PR.push_back(x);}
	}
	if(node.size() > 3){t.ch[0] = divide(L , PL); t.ch[1] = divide(R , PR);}
	t.builddst(node , pot); return now;
}

long long solvedst(int id , int p , int q){
	Data &t = dat[id]; int x = t.id[p] , y = t.id[q];
	long long mn = min(t.dst[0][x] + t.dst[0][y] , t.dst[1][x] + t.dst[1][y]);
	if(t.id.size() != 3 && t.bel[x] == t.bel[y] && max(t.bel[x] , t.bel[y]) != -1)
		mn = min(mn , solvedst(t.ch[t.bel[x]] , p , q));
	return mn;
}

int cnttms = 0;
void myassert(bool flag , string error){if(!flag){cout << error << endl; exit(0);}}
long long distance(int p , int q){
	myassert(p >= 1 && p <= n && q >= 1 && q <= n , "Airport number out of range [1,n].");
	myassert(++cnttms <= L , "Query time exceeds L.");
	return p == q ? 0 : solvedst(1 , p , q);
}

signed main(){
	ios::sync_with_stdio(0); cin >> n >> q >> x >> y >> L; vector < EDGE > pot;
	for(int i = 1 ; i <= 2 * n - 3 ; ++i){int p , q , w; cin >> p >> q >> w; pot.push_back((EDGE){p , q , w});}
	vector < int > P(q); for(int i = 0 ; i < q ; ++i) cin >> P[i];
	vector < int > node; for(int i = 1 ; i <= n ; ++i) node.push_back(i);
	divide(node , pot);
	cout << solve(n , x , y , q , P , L) << endl;
	cerr << cnttms << endl; return 0;
}
