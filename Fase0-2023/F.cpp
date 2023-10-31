#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<ll> vll;
#define INF (1<<30)
#define LINF (1LL<<61)
#define x first
#define y second
#define pb push_back
#define mp make_pair
#define lsb(i) (i&(-i))
#define all(z) begin(z), end(z)
#define EPS ((double)(1e-9))
#define MOD 998244353
const int maxn = 412345;
const int maxm = 31234;

vi makeSa(const string &s){
	int n = s.size();
	int N = max(n,300);
	vi sa(n), ra(n);
	for(int i=0;i<n;i++){
		sa[i] = i;
		ra[i] = s[i];
	}
	vi cnt(N,0);
	vi nsa(sa), nra(n);
	for(int k=0;k<n;k=(k?k*2:k+1)){
		fill(all(cnt), 0);
		for(int i=0;i<n;i++){
			nsa[i] = (sa[i] - k + n)%n;
			cnt[ra[i]]++;
		}
		for(int i=1;i<N;i++) cnt[i] += cnt[i-1];
		for(int i=n-1;i>=0;i--) sa[--cnt[ra[nsa[i]]]] = nsa[i];
 
		int r = 0;
		nra[sa[0]] = r;
		for(int i=1;i<n;i++){
			nra[sa[i]] = r += ra[sa[i]] != ra[sa[i-1]] or ra[(sa[i]+k)%n] != ra[(sa[i-1]+k)%n];
		}
		swap(nra, ra);
		if(ra[sa[n-1]]==n-1) break;
	}
	return sa;
}
 
vi kasai(const string &s, const vi &sa){
	int n = s.size();
	vi lcp(n,0), ra(n);
	for(int i = 0;i<n;i++) ra[sa[i]] = i;
	int k = 0;
	for(int i=0;i<n;i++, k -= !!k){
		if(ra[i]==n-1){
			k = 0;
			continue;
		}
		int j = sa[ra[i]+1];
		while(i+k < n  and j+k < n  and s[i+k]==s[j+k]) k++;
		lcp[ra[i]] = k;
	}
	return lcp;
}

template<int maxp, int maxn>
struct dSparse{
	int n;
	int st[maxp][maxn];
	int nSiz;
	int nLog;
	int *v;

	dSparse(){
	}
	dSparse(int n, int *v){
		init(n,v);
	}
	void init(int n, int *v){
		this->v = v;
		this->n = n;
		memset(this->st, 0, sizeof(this->st));
	}
	 
	void build(){
		nSiz = 1;
		nLog = 0;
		while(nSiz<n){
			nLog++;
			nSiz*=2;
		}
		for(int h=0;h<nLog;h++){
			int blockSiz = nLog - h;
			for(int block=0;block<(1<<h);block++){
				int ini = block<<blockSiz;
				int fin = (block+1)<<blockSiz;
				int mid = (ini+fin)/2;
				st[h][mid] = v[mid];
				st[h][mid-1] = v[mid-1];
				for(int i=mid+1;i<fin;i++) st[h][i] = min(st[h][i-1],v[i]);
				for(int i=mid-2;i>=ini;i--) st[h][i] = min(st[h][i+1], v[i]);
			}
	 
		}
	}
	 
	int query(int l, int r){
		if(l==r) return st[nLog-1][l];
		int lev = nLog - 32 + __builtin_clz(l^r);
		return min(st[lev][l], st[lev][r]);
	}
};


int prefixSum[maxn];

int where[maxn];
auto rm = dSparse<30, maxn>();

void solve(){
	int n,m;
	cin >> n >> m;
	string s;
	string t;
	cin >> s;
	cin >> t;
	string combo = s + "$" + t + "$$"; // Why $$ in the end?
	auto sa = makeSa(combo);
	auto lcp = kasai(combo, sa);

	rm.init(lcp.size(), lcp.data());
	rm.build();
	for(int i=0;i<sa.size();i++){
		//cout << i << " ";
		//cout << lcp[i] << " ";
		//cout << combo.substr(sa[i]) << endl;
		prefixSum[i] = 0;
		if(sa[i] > s.size()) where[sa[i] - s.size() - 1] = i;
		else prefixSum[i] = 1;
		if(i)
			prefixSum[i] += prefixSum[i-1];
	}
	int q;
	cin >> q;
	for(int i=0;i<q;i++){
		int a,b;
		cin >> a >> b;
		a--; b--;
		int len = b-a+1;

		int position = where[a];

		int right = -1;
		int left = -1;
		{ // Find the first sa[j] j > position and rmq[position, j] < lenrmq[position, j] < len
			int l = position;
			int r = sa.size()-1;
			while(l<=r){
				int m = (l+r)/2;
				if(rm.query(position, m) < len){
					if(right == -1) right = m;
					right = min(right, m);
					r = m-1;
				}
				else l = m+1;
			}
		}
		{ // Find the first sa[j] j < position and rmq[j, position] < lenrmq[position, j] < len
			int l = 0;
			int r = position-1;
			while(l<=r){
				int m = (l+r)/2;
				if(rm.query(m, position-1) < len){
					if(left == -1) left = m;
					left = max(left, m);
					l = m+1;
				}
				else r = m-1;
			}
		}

		//cout << "found on " <<position <<" ("<<left <<", "<<right<<") ";
		int qnt = prefixSum[right] - prefixSum[left];
		cout << qnt << "\n";
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	for(int caso=1;caso<=t;caso++){
		solve();
	}
	return 0;
}
