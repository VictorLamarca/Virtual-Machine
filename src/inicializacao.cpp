#include "inicializacao.h"

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

void preLoader(){
	{
		FILE *pObjeto = fopen("loader.obj","r");

		int tamanho;

		string aux = "00";
		fr(i,3) fscanf(pObjeto," %c%c", &aux[0], &aux[1]);
		tamanho =  toVal('/'+aux);

		fr(i,tamanho){
			fscanf(pObjeto," %c%c", &aux[0], &aux[1]);
			memoria_principal[i] = toVal('/'+aux);
		}
	}
	{
			FILE *pObjeto = fopen("dumper.obj","r");

			int tamanho;

			string aux = "00";
			fr(i,3) fscanf(pObjeto," %c%c", &aux[0], &aux[1]);
			tamanho =  toVal('/'+aux);

			fr(i,tamanho){
				fscanf(pObjeto," %c%c", &aux[0], &aux[1]);
				memoria_principal[50+i] = toVal('/'+aux);
			}
	}

	return;
}

int main (int argc, char *argv[]){

	montador("loader");
	montador("dumper");
	preLoader();

	//chamda da interface
	interpretadorDeComandos();

	cout << "Sistema desligando" << endl;
}
