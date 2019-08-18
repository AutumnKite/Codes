#include <cstdio>
#include <algorithm>
int n;
struct cpu{
    int id, s, t, p;
    bool operator < (const cpu &res) const {
        return p < res.p || p == res.p && s > res.s;
    }
}a[1000005];
struct Heap{
    cpu h[100005];
    int sz;
    Heap(){ sz = 0; }
    void push(cpu x){ h[++sz] = x, std :: push_heap(h + 1, h + 1 + sz); }
    cpu pop(){ return std :: pop_heap(h + 1, h + 1 + sz), h[sz--]; }
}H;
int main(){
    while (++n, ~scanf("%d%d%d%d", &a[n].id, &a[n].s, &a[n].t, &a[n].p)) ;
    a[n--].s = 1000000000;
    for (register int i = 1, T = 0, cnt = 0; cnt < n; ){
        if (!H.sz) H.push(a[i]), T = a[i].s, ++i;
        cpu tmp = H.pop();
        if (T + tmp.t <= a[i].s) T += tmp.t, printf("%d %d\n", tmp.id, T), ++cnt;
        else tmp.t -= a[i].s - T, H.push(tmp), T = a[i].s;
        if (T == a[i].s) H.push(a[i]), ++i;
    }
}