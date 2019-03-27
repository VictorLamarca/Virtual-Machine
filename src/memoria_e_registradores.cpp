#include "memoria_e_registradores.h"

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

BYTE memoria_principal[1<<16];

DOIS_BYTES ci; //contador de instruções
DOIS_BYTES ac;
