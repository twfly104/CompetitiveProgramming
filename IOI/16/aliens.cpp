// It took me 5 day to complete this code and with AI debugging. So annoyed!
#include "aliens.h"
#include<bits/stdc++.h>
using namespace std;

#define ll int32_t
#define F first
#define S second 

#define sz(x) (int)x.size()
#define int long long

const int mxM=1e5+5;

struct line{
	int a,b,cnt;
};

int m;
vector<pair<int,int>> v(mxM);

bool slope(auto fi, auto se, auto x){
	//fix
	return (se.b-fi.b)*(se.a-x.a)>=(fi.a-se.a)*(x.b-se.b);
}

int go(int penalty, int ty){
	//becaido orz
	//https://hackmd.io/@erichung0906/ryat4wycc
	deque<line> stk;
	vector<pair<int,int>> dp(m+1);
	stk.push_back({-2*(v[1].F-1),(v[1].F-1)*(v[1].F-1),0});
	for(int i=1;i<=m;i++){
		//fix make_pair
		while(stk.size()>1&&make_pair(stk[1].a*v[i].S+stk[1].b,stk[1].cnt)<=make_pair(stk[0].a*v[i].S+stk[0].b,stk[0].cnt)){
			stk.pop_front();
		}
		//do stuff
		auto best=stk.front();
		dp[i].F=best.a*v[i].S+best.b+v[i].S*v[i].S+penalty;
		dp[i].S=best.cnt+1;
		if(i!=m){
			line li={-2*(v[i+1].F-1),dp[i-1+1].F+(v[i+1].F-1)*(v[i+1].F-1)-max(0ll,(v[i].S-v[i+1].F+1))*max(0ll,(v[i].S-v[i+1].F+1)),dp[i].S};
			while(stk.size()>1&&slope(stk[sz(stk)-2],stk[sz(stk)-1],li)){
				stk.pop_back();	
			}
			stk.push_back(li);
		}
	}
	if(ty==1)
		return dp[m].F;
	else
		return dp[m].S;
}

//dp_i=min({dpj-1 + (ri-lj+1)^2-max(0,rj-1 - lj + 1)^2})
//dpi=-2(lj - 1)ri+(dpj-1 + (lj - 1)^2 - max^2) + ri^2		
//i>=j

int take_photos(ll m, ll n, ll k, vector<ll> r, vector<ll> c){
	for(int i=1;i<=m;i++){
    	v[i]={min(r[i-1],c[i-1]),max(r[i-1],c[i-1])};
	}
	sort(v.begin()+1,v.begin()+m+1,[&](auto x, auto y){
    	if(x.F!=y.F){
    		return x.F<y.F;
		} else{
			return x.S>y.S;
		}
	});
	int sz=0;
	for(int i=1;i<=m;i++){
		//fix
		if(sz==0||v[i].S>v[sz].S)
			v[++sz]=v[i];
	}
	m=sz;
	::m=m;
    int le=0,ri=1ll*n*n;
    while(le<ri){
    	int mid=(le+ri)/2;
    	if(go(mid,0)>k){
    		le=mid+1;
		} else{
			ri=mid;
		}
	}
	return -le*k+go(le,1);
}
/*
5 7 2          
0 4 4 4 4                                                
3 4 6 5 6
*/
