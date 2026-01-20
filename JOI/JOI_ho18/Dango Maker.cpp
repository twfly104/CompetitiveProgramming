/*
tmwilliamlin168 orz
https://www2.ioi-jp.org/joi/2017/2018-ho/2018-ho-t3-review.pdf

you should notice the diagonal line!
*/
#include<bits/stdc++.h>
using namespace std;

#define ll long long

const int mxN=3e3;

char c[mxN][mxN];
int n, m;
int ans=0, dp[mxN][3];

bool check(int x, int y) {
	return (x>=0&&x<n&&y>=0&&y<m);
}

bool ok(int x, int y) {//vertical
	if(!(check(x-1, y)&&check(x+1, y))) {
		return 0;
	} else {
		return (c[x-1][y]=='R'&&c[x][y]=='G'&&c[x+1][y]=='W');	
	}
}

bool ok1(int x, int y) {//horizon
	if(!(check(x, y-1)&&check(x, y+1))) {
		return 0;
	} else {
		return (c[x][y-1]=='R'&&c[x][y]=='G'&&c[x][y+1]=='W');	
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>m;
	for(int i=0; i<n; i++)
		for(int j=0; j<m; j++)
			cin>>c[i][j];
	for(int i=0; i<n+m-1; i++) {
		int t=min({i+1, n+m-1-i, n, m}), j=0;
		int shift=max(0, i-m+1);
        for(int j=0; j<min(n, m); j++)
            dp[j][0]=dp[j][1]=dp[j][2]=0;
		while(t--) {
			int x=j+shift, y=i-j-shift;
			if(j!=0)	
				dp[j][0]=max({dp[j-1][0], dp[j-1][1], dp[j-1][2]});
			if(j==0)
				dp[j][1]=(ok(x, y)?1:0);
			else if(ok(x, y)) 
				dp[j][1]=max(dp[j-1][1], dp[j-1][0])+1;	
			if(j==0)
				dp[j][2]=(ok1(x, y)?1:0);
			else if(ok1(x, y))
				dp[j][2]=max(dp[j-1][2], dp[j-1][0])+1;
			if(t==0)
                ans+=max({dp[j][0], dp[j][1], dp[j][2]});
                j++;
			//cout<<j<<' '<<x<<' '<<y<<' '<<ok(x, y)<<' '<<ok1(x, y)<<' '<<dp[j][0]<<' '<<dp[j][1]<<' '<<dp[j][2]<<endl;
		}
        //cout<<ans<<endl;
	}
	cout<<ans;
	return 0;
}
