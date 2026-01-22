//usaco orz
#include<bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=1e5, mxM=2e5, B=100;

vector<int> adj[mxN], radj[mxN];
vector<pair<int, int>> dist[mxN];
int n, m, q;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m>>q;
    for(int i=0; i<m; i++) {
        int a, b;
        cin>>a>>b;
        --a, --b;
        adj[a].push_back(b);
		radj[b].push_back(a);
    }
	vector<int> dis(n, -1);
	for(int i=0; i<n; i++) {
		dist[i].push_back({0, i});
		vector<int> rec;
		for(int j : radj[i]) {
			for(auto [d, v] : dist[j]) {
				if(dis[v]==-1)
					dis[v]=d+1, rec.push_back(v);
				else
					dis[v]=max(dis[v], d+1);
			}
		}
		for(int j : rec)
			dist[i].push_back({dis[j], j});
		sort(dist[i].begin(), dist[i].end(), greater<pair<int, int>>());
		while(dist[i].size()>B)
			dist[i].pop_back();
		for(int j : rec) {
			dis[j]=-1;
		}
	}
    while(q--) {
        int st;
        cin>>st;
        --st;
        int c;
        cin>>c;
        set<int> s;
        for(int i=0; i<c; i++) {
            int x;
            cin>>x;
            --x;
            s.insert(x);
        }
        if(c<B) {
            int ans=-1;
            for(auto [dis, x] : dist[st]) {
                if(s.find(x)==s.end()) {
                    ans=dis;
                    break;
                }
            }
            cout<<ans<<"\n";
        } else {
            vector<int> dis(n);
            for(int x : s)
                dis[x]=-1;
            for(int i=0; i<n; i++) {
                if(dis[i]==-1)
                    continue;
                for(int j : adj[i]) 
                    dis[j]=max(dis[i]+1, dis[j]);
            }
            cout<<dis[st]<<"\n";
        }
    }
    return 0;
}

