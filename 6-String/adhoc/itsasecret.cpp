#include <bits/stdc++.h>
#include <cctype>
#include <cstdio>
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
#define MOD 1000000007
const int maxn = 2*112;
const int maxm = 31234;


char mapp[10][10];
bool used['Z'+100];

ii get_idx(char a){
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			if(mapp[i][j] == a) return {i,j};
		}
	}
	return {0,0};
}
string encode(char a, char b){
	if(a=='X' && b == 'X') return "YY";
	ii idA = get_idx(a);
	ii idB = get_idx(b);
	if(idA.x != idB.x && idA.y != idB.y) 
		return string("") + mapp[idA.x][idB.y] + mapp[idB.x][idA.y];
	if(idA.x == idB.x)
		return string("") + mapp[idA.x][(idA.y+1)%5] + mapp[idB.x][(idB.y+1)%5];
	return string("") + mapp[(idA.x + 1)%5][idA.y] + mapp[(idB.x+1)%5][idB.y];
}

void solve(){
	static bool flag = false;
	int n;
	cin >> n;
	if(n==0) exit(0);

	if(flag) cout << "\n";
	flag = true;
	string key;
	getline(cin, key); // Empty after n
	getline(cin, key);

	int id = 0;
	memset(used, 0, sizeof(used));

	for(int i=0;i<key.size();i++){
		key[i] = toupper(key[i]);
		if(key[i] == ' ') continue;
		if(key[i] == 'J') key[i] = 'I';
		if(used[key[i]]) continue;
		used[key[i]] = 1;
		mapp[id/5][id%5] = key[i];
		id++;
	}
	char test = 'A';
	while(id<25){
		while(used[test] || test=='J') {
			test++;
		}
		used[test] = 1;
		mapp[id/5][id%5] = test;
		test++;
		id++;
	}

	for(int i=0;i<n;i++){
		string s;
		getline(cin, s);
		char last;
		bool used = false;
		for(int j=0;j<s.size();j++){
			if(s[j] == ' ') continue;
			s[j] = toupper(s[j]);
			if(s[j] == 'J') s[j] = 'I';
			if(!used){
				last = s[j];
				used = true;
				continue;
			}
			if(s[j] == last){
				cout << encode(last, 'X');
				continue;
			}
			cout << encode(last, s[j]);
			used = false;
		}
		if(used){
			cout << encode(last, 'X');
		}
		cout << '\n';
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	for(int caso=1;;caso++){
		solve();
	}
	return 0;
}
