#include <algorithm>
#include <bits/stdc++.h>
#include <cctype>
#include <cstdio>
#include <sstream>
#include <string>
#include <thread>
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
const int maxn = 2*112;
const int maxm = 31234;


ll fib[100];
map<ll, int>  fibToPos;
string text;
void solve(){
	int n;
	cin >> n;
	vector<ll> v(n);
	for(ll &w: v) cin >> w;

	string line;
	getline(cin, line);
	getline(cin, line);


	text = "";
	for(int i=0;i<200;i++) text += " ";
	int id = 0;
	int maxi = -1;
	int mini = -1;
	for(char w: line){
		if(w<'A' || w>'Z') continue;
		if(id >= v.size()) break; // Condição que não esta no statment :(
		ll value = v[id++];
		int position = fibToPos[value];
		text[position] = w;
		if(mini == -1){
			mini = maxi = position;
		}
		maxi = max(maxi, position);
		mini = min(mini, position);
	}
	if(mini!=-1 && maxi!=-1){
		cout << text.substr(0, maxi+1);
	}
	cout << "\n";
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	ll f = 1;
	ll s = 2;
	fib[0] = f;
	fib[1] = s;
	fibToPos[f] = 0;
	fibToPos[s] = 1;
	for(int i=2;i<=90;i++){
		f+=s;
		swap(f,s);
		fib[i] = s;
		fibToPos[s] = i;
	}

	int t = 1;
	cin >> t;
	for(int caso=1;caso<=t;caso++){
		solve();
	}
	return 0;
}
