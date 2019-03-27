#include "funcoes_auxiliares.h"

bool idebug = 1;
#define prin(a) if(idebug) cout << #a << " = " << (a) << endl
#define ppal(a)  if(idebug) cout << #a << endl
#define cendl if(idebug) cout << endl
#define prinpar(p) if(idebug) cout << #p << ".fi=" << (p).fi << " " << #p << ".se=" << (p).se << endl
#define prinv(v) if(idebug){ cout << #v << ":" << endl; for(auto it = (v).begin(); it!=(v).end();it++){ cout << (int)(*it) << " ";} cout << endl;}

#define pb push_back
#define all(a) a.begin(),a.end()
#define fi first
#define se second
#define fr(i,n) for(int i=0;i<n;i++)
#define frr(i,a,b) for(int i =a;i<=b;i++)

#define BYTE unsigned char
#define DOIS_BYTES unsigned short int

int oposto_checksum = 0;

void erro(string mnsgm){
	cout << mnsgm << endl;
	exit(0);
}

int toVal(string s){
	if(s.size()==0) return 0;
	int base = 10;
	int i = 0;
	if(s[0]=='/') i++, base = 16;
	else if(s[0]=='&') i++, base = 2;

	int ans = 0;
	for(;i!=s.size();i++){
		ans*=base;
		if(isdigit(s[i])) ans+=s[i]-'0';
		else{
			s[i] = tolower(s[i]);
			if(s[i]<'a' or s[i]>'f') return 0;
			ans+=s[i]-'a'+10;
		}
	}
	return ans;
}

char letraHexa(BYTE val){
	assert(val<16);
	if(val<10) return '0'+val;
	return 'A'+val-10;
}

string byteToHexa(BYTE val){
	string ans;
	ans+=letraHexa(val>>4);
	ans+=letraHexa(val%(1<<4));
	return ans;
}

bool isnum(string s){
	if(s.size()==0) return 0;
	fr(i,s.size()) if(isalpha(s[i])) s[i] = tolower(s[i]);
	if(s[0]!='/' and s[0]!='&' and !isxdigit(s[0])) return 0;
	frr(i,1,s.size()-1) if(!isxdigit(s[i])) return 0;
	return 1;
}

string tiraExtencao(string s){
	int ext = 0;
	fr(i,s.size()) if(s[i]=='.') ext = 1;
	if(!ext) return s;

	while(s.size()){
		char c = s.back();
		s.erase(--s.end());
		if(c=='.') break;
	}

	return s;
}
