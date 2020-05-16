#include<bits/stdc++.h>
using namespace std;

int n, m, ans=0;
vector<int>adjl[100002];
bool visit[100002];

void dfs(int now, int prev, int dist){
	if (visit[now]){
		ans+=dist/2;
		return;
	}
	visit[now]=1;
	for (int next : adjl[now]){
		if (next==prev) continue;
		dfs(next,now,dist+1);
	}
}

int main(){
	cin >> n >> m;
	for (int i=0;i<m;i++){
		int u, v;
		cin >> u >> v;
		adjl[u].push_back(v);
		adjl[v].push_back(u);
	}
	memset(visit,0,sizeof visit);
	for (int i=1;i<=n;i++){
		if (visit[i]) continue;
		dfs(i,0,0);
	}
	cout << ans << "\n";
}
