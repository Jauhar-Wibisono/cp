#include<bits/stdc++.h>
using namespace std;

long long n, m, cnt[26], ans=0;
string s;

int main(){
	memset(cnt,0,sizeof cnt);
	cin >> n >> m >> s;
	for (char c : s) cnt[c-'A']++;
	for (int i=0;i<m;i++){
		char c;
		string t;
		cin >> c >> t;
		long long tmp=cnt[c-'A'];
		cnt[c-'A']=0;
		for (char d : t) cnt[d-'A']+=tmp;
	}
	for (int i=0;i<26;i++) ans+=cnt[i];
	cout << ans << "\n";
}
