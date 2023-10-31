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


/*
012345678
TNM AEIOU

001 0 1
011 000 111
010 00 10 01 11
011 001 111
000
 */

string buff;

vector<int> keys;
struct Segment{
	string head = "";
	int headValue = 0;
	string currentKeyBuff = "";
	int keyValue = 0;
	bool ended = false;

}seg;

bool push(char c){
	if(c!='0' && c!='1') return true;
	if(seg.ended){
		seg = Segment();
	}
	if(seg.head.size()<3){
		seg.head += c;
		seg.headValue *= 2;
		seg.headValue += c-'0';
		if(seg.head.size()==3){
			if(seg.headValue == 0) {
				return false;
			}
		}
		seg.keyValue = 0;
		return true;
	}
	seg.currentKeyBuff += c;
	seg.keyValue = (seg.keyValue*2) + c-'0';

	if(seg.currentKeyBuff.size() == seg.headValue){
		bool any = false;
		for(char w: seg.currentKeyBuff) if(w == '0') any = true;
		if(!any){
			seg = Segment();
			return true;
		}
		int off = 0;
		for(int i=1;i<seg.headValue;i++){
			off += (1<<i) -1;
		}
		keys.push_back(off + seg.keyValue);
		seg.keyValue = 0;
		seg.currentKeyBuff.clear();
	}
	return true;
}

void solve(){
	string header;
	if(cin.eof()) exit(0);
	getline(cin, header);
	if(header.size()==0) getline(cin, header);
	if(cin.eof()) exit(0);

	while(1){
		char c;
		cin >> c;
		if(!push(c)) break;
	}
	for(auto k: keys) cout << header[k];
	keys.clear();
	cout << "\n";
	seg = Segment();
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
