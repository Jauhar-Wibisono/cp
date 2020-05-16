#include<bits/stdc++.h>
using namespace std;

const int maxn=100002, loga=30;
int n, q, a[maxn], pref[maxn], tree[loga][4*maxn];
bool lazy[loga][4*maxn];

// yey ac
// query(l,r)=sum of xor of all prefix pairs [l-1,r]
// tree: segtree of count1
// sama kayak penyisihan SCPC B

void build(int l, int r, int v, int bit){
	if (l==r){
		long long tmp=pref[l];
		if (tmp&(1<<bit)) tree[bit][v]=1;
		else tree[bit][v]=0;
	}
	else{
		int mid=(l+r)/2;
		build(l,mid,v*2,bit);
		build(mid+1,r,v*2+1,bit);
		tree[bit][v]=tree[bit][v*2]+tree[bit][v*2+1];
	}
}

void push(int l, int r, int v, int bit){
	if (lazy[bit][v]){
		int mid=(l+r)/2;
		tree[bit][v*2]=(mid-l+1-tree[bit][v*2]);
		tree[bit][v*2+1]=(r-mid-tree[bit][v*2+1]);
		lazy[bit][v*2]^=lazy[bit][v];
		lazy[bit][v*2+1]^=lazy[bit][v];
		lazy[bit][v]=0;
	}
}

// flip
void update(int l, int r, int v, int lb, int rb, int bit){
	if (r<lb || l>rb) return;
	if (l>=lb && r<=rb) tree[bit][v]=(r-l+1-tree[bit][v]), lazy[bit][v]^=1;
	else{
		push(l,r,v,bit);
		int mid=(l+r)/2;
		update(l,mid,v*2,lb,rb,bit);
		update(mid+1,r,v*2+1,lb,rb,bit);
		tree[bit][v]=tree[bit][v*2]+tree[bit][v*2+1];
	}
}

long long query(int l, int r, int v, int lb, int rb, int bit){
	if (r<lb || l>rb) return 0;
	if (l>=lb && r<=rb) return tree[bit][v];
	push(l,r,v,bit);
	int mid=(l+r)/2;
	return query(l,mid,v*2,lb,rb,bit)+query(mid+1,r,v*2+1,lb,rb,bit);
}


int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);
	cin >> n >> q;
	for (int i=0;i<n;i++) cin >> a[i];
	pref[0]=0;
	for (int i=1;i<=n;i++) pref[i]=pref[i-1]^a[i-1];
	memset(lazy,0,sizeof lazy);
	for (int i=0;i<loga;i++) build(0,n,1,i);
	while (q--){
		int type;
		cin >> type;
		if (type==1){
			int x, v;
			cin >> x >> v;
			for (int i=0;i<loga;i++){
				bool ba=0, bv=0;
				if (a[x-1]&(1<<i)) ba=1;
				if (v&(1<<i)) bv=1;
				if (ba^bv) update(0,n,1,x,n,i);
			}
			a[x-1]=v;
		}
		else{
			int l, r;
			cin >> l >> r;
			long long ans=0;
			for (int i=0;i<loga;i++){
				int cnt1=query(0,n,1,l-1,r,i);
				ans+=((long long)cnt1)*((long long)(r-l+2-cnt1))*((long long)(1<<i));
			}
			cout << ans << "\n";
		}
	}
}
