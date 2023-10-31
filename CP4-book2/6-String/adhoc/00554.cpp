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

char valueToChar[400];
int charToValue[400];

void solve(){

	charToValue[' '] = 0;
	valueToChar[0] = ' ';
	for(int a='A';a<='Z';a++){
		charToValue[a] = a-'A' + 1;
		valueToChar[a-'A' + 1] = a;
	}

	vector<string> dic;
	while(1){
		string s;
		cin >> s;
		if(s[0] == '#') break;
		dic.push_back(s);
	}

	string line;
	getline(cin, line);
	getline(cin, line);

	string bestAns;
	int error = -1;
	for(int k=0;k<=27;k++){

		string cp = line;
		for(char &w: cp){
			int val = charToValue[w];
			val = (val - k)%27;
			while(val < 0) val = (val+27)%27;
			w = valueToChar[val];
		}
		int points = 0;
		for(string word: dic){
			for(int i=0;i<cp.size();i++){
				if(word.compare(cp.substr(i, word.size()))==0)
					points++;
			}
		}
		if(points > error){
			error = points;
			bestAns = cp;
		}
	}
	vector<string> separ;
	string buff = "";
	bestAns += " ";
	for(char w: bestAns){
		if(w==' '){
			if(buff.size()){
				separ.push_back(buff);
				buff = "";
			}
			continue;
		}
		buff+=w;
	}

	int currentLine = 0;
	bool shouldSpace = false;
	for(string word: separ){
		int nextSize = currentLine + word.size();
		if(shouldSpace) nextSize++;
		if(nextSize<=60){
			if(shouldSpace) cout << " ";
			cout << word;
			currentLine = nextSize;
			shouldSpace = true;
			continue;
		}
		cout << "\n";
		currentLine = word.size();
		shouldSpace = true;
		cout << word;
	}
	cout << "\n";
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
