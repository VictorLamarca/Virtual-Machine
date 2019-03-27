#include "interpretador_de_comandos.h"

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

void imprime_arquivios_no_diretorio(){
	vector<string> arquivosDoUsuario, arquivosDoSistema;
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (".")) != NULL) {
	  while ((ent = readdir (dir)) != NULL) {
	  	string cur = string(ent->d_name);
	  	if(cur.size()<5) continue;
	  	string stxt = ".txt", sobj = ".obj", sdump = "dump";
	  	fr(i,4) if(cur[cur.size()-4+i]!=stxt[i] and cur[cur.size()-4+i]!=sobj[i] and cur[cur.size()-4+i]!=sdump[i]) goto prox;
	  	if(cur=="loader.txt" or cur=="dumper.txt" or cur=="loader.obj" or cur=="dumper.obj") arquivosDoSistema.pb(cur);
	  	else arquivosDoUsuario.pb(cur);
	  	prox: continue;
	  }
	  closedir (dir);
	} else {
	  cout << "Nao foi possivel acessar arquivos" << endl;
	  exit(0);
	}

	cout << "arquivos do usuario:" << endl;
	for(auto &it : arquivosDoUsuario) cout << " " << it << endl;
	cout << endl;
	cout << "arquivos do sistema:" << endl;
	for(auto &it : arquivosDoSistema) cout << " " << it << endl;
	cout << endl;
}

void interpretadorDeComandos(){
	char c;
	while(1){
		string login, senha;
		cout << "Insira o login: ";
		while(scanf("%c", &c)!=EOF and c!='\n') login+=c;
		cout << "Insira a senha: ";
		while(scanf("%c", &c)!=EOF and c!='\n') senha+=c;
		if(login=="admin" and senha=="admin") break;
		cout << "Login ou senha invalidos!" << endl;
	}
	cout << "Login efetuado com sucesso" << endl;
	while(1){
		cout << "$";
		string linha;

		while(scanf("%c", &c)!=EOF and c!='\n') linha+=c;
		vector<string> comandos;
		{
			int i = 0;
			while(i<linha.size()){
				string cur;
				while(i<linha.size() and isspace(linha[i])) i++;
				while(i<linha.size() and !isspace(linha[i])) cur+=linha[i++];
				comandos.pb(cur);
			}
		}
		if(!comandos.size()) continue;

		if(comandos[0]=="MD"){
			if(comandos.size()==2){
				fr(i,10) cout << byteToHexa(memoria_principal[toVal(comandos[1])+i]) << " ";
				cout << endl;
			} else if(comandos.size()==3){
				fr(i,toVal(comandos[2])) cout << byteToHexa(memoria_principal[toVal(comandos[1])+i]) << " ";
				cout << endl;
			} else {
				cout << "numero errado de parametros" << endl;
			}
		} else if(comandos[0]=="DIR"){
			imprime_arquivios_no_diretorio();
		} else if(comandos[0]=="RUN"){
			if(comandos.size()==1){
				cout << "Falta parametros" << endl;
			} else{
				comandos[1] = tiraExtencao(comandos[1]);
				if(comandos[1]=="loader" or comandos[1]=="dumper"){
					cout << "Nao e possivel executar programas dos sistema diretamente" << endl;
				} else{
					if(access( (comandos[1]+".txt").c_str(), F_OK )==-1){
						cout << "Arquivo nao encontrado" << endl;
					} else{
						maquina_virtual(comandos[1]);
					}
				}
			}
		} else if(comandos[0]=="END"){
			return;
		} else if(comandos[0]=="DEL"){
			if(comandos.size()==1){
				cout << "Falta parametros" << endl;
			} else{
				if(access( (comandos[1]).c_str(), F_OK )==-1){
					cout << "Arquivo nao encontrado" << endl;
				} else{
					remove( comandos[1].c_str() );
				}
			}
		} else{
			cout << "Comando nao identificado" << endl;
		}
	}

	return;
}
