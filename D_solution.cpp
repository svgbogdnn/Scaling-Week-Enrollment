#include <bits/stdc++.h>
using namespace std;

struct P { double x, y; };

int n;
vector<vector<int>> g;
vector<int> sz, assign_idx;
vector<P> pts;

void dfs_size(int u, int p){
    sz[u] = 1;
    for(int v: g[u]) if(v!=p){ dfs_size(v,u); sz[u]+=sz[v]; }
}

double ang(const P& a, const P& o){
    return atan2(a.y - o.y, a.x - o.x);
}

void solve(int u, int p, vector<int> vec){
    int best = 0;
    for(int i=1;i<(int)vec.size();++i){
        int a = vec[i], b = vec[best];
        if (pts[a].x < pts[b].x || (pts[a].x == pts[b].x && pts[a].y < pts[b].y)) best = i;
    }
    swap(vec[0], vec[best]);
    int pu = vec[0];
    assign_idx[u] = pu;

    vector<int> rest(vec.begin()+1, vec.end());
    sort(rest.begin(), rest.end(), [&](int i, int j){
        double ai = ang(pts[i], pts[pu]), aj = ang(pts[j], pts[pu]);
        return ai < aj;
    });

    int off = 0;
    for(int v: g[u]) if(v!=p){
        vector<int> block(rest.begin()+off, rest.begin()+off+sz[v]);
        off += sz[v];
        solve(v, u, block);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; 
    if(!(cin>>t)) return 0;
    while(t--){
        cin>>n;
        g.assign(n, {});
        for(int i=0;i<n-1;++i){
            int u,v; cin>>u>>v; --u;--v;
            g[u].push_back(v); g[v].push_back(u);
        }
        pts.resize(n);
        for(int i=0;i<n;++i) cin>>pts[i].x>>pts[i].y;

        sz.assign(n,0);
        dfs_size(0,-1);

        vector<int> all(n);
        iota(all.begin(), all.end(), 0);

        assign_idx.assign(n,-1);
        solve(0,-1,all);

        for(int i=0;i<n;++i){
            if(i) cout<<' ';
            cout<<assign_idx[i]+1;
        }
        cout<<"\n";
    }
    return 0;
}
