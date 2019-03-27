#include "funcoes_auxiliares.h"

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

bool poeArquivo(int val, int tam, FILE *pfile){
	vector<BYTE> v;
	while(val){
		v.pb(val%(1<<8));
		val>>=8;
	}
	reverse(all(v));
	if(v.size()<tam){
		reverse(all(v));
		while(v.size()<tam) v.pb(0);
		reverse(all(v));
	}
	assert(v.size()==tam);

	fr(i,v.size()){
		fprintf(pfile, "%c", letraHexa(v[i]>>4));
		fprintf(pfile, "%c ", letraHexa(v[i]%(1<<4)));
		oposto_checksum+=v[i];
	}
	return 1;
}

bool montador(string arquivo){
	//tabela de rótulos para correspondência com endereços
	map<string,int> tabela;

	arquivo = tiraExtencao(arquivo);

	//checa se arquivo existe
	assert(access( (arquivo+".txt").c_str(), F_OK )!=-1);

	//ponteiro para arquivos txt (mnemonico) e .obj
	FILE *pfile, *pObjeto;
	pfile = fopen((arquivo+".txt").c_str(),"r");
	pObjeto = fopen((arquivo+".obj").c_str(),"w");

	set<string> pseudo = {"@","#","$","K"};
	set<string> instrucao_2BYTE = {"JP", "JZ", "JN", "+", "-", "*", "/", "LD", "MM","SC"};
	set<string> instrucao_1BYTE = {"CN", "OS", "IO"};

	vector<string> vin = {"JP","JZ","JN","CN","+","-","*","/","LD","MM","SC","OS","IO"};
	vector<string> vesp = {"HM", "RI", "IN"};

	map<string,int> codigo_instrucao;
	int cnt = 0;
	for(auto &it : vin){
		codigo_instrucao[it] = cnt++;
	}

	map<string,int> operandos_especiais;

	cnt = 0;
	for(auto &it : vesp) operandos_especiais[it] = cnt++;
	operandos_especiais["GD"] = 1;
	operandos_especiais["PD"] = 5;

	DOIS_BYTES Endereco_inicial, Endereco_de_execucao;

	//passo 1
	while(1){
		char c;
		string rotulo, instrucao, operando, linha;
		while(fscanf(pfile,"%c", &c)!=EOF and c!='\n') linha+=c;

		fr(i,linha.size()) if(linha[i]==';'){
			while(1){
				linha.erase(--linha.end());
				if(linha.size()==i) goto sai;
			}
		}
		sai:
		if(linha.size()==0) continue;

		int i = 0;
		while(i<linha.size() and !isspace(linha[i])) rotulo+=linha[i++];
		while(i<linha.size() and isspace(linha[i])) i++;
		while(i<linha.size() and !isspace(linha[i])) instrucao+=linha[i++];
		while(i<linha.size() and isspace(linha[i])) i++;
		while(i<linha.size() and !isspace(linha[i])) operando+=linha[i++];
		while(i<linha.size() and isspace(linha[i])) i++;

		if(rotulo.size() and rotulo.back()==':'){ rotulo.erase(--rotulo.end());}
		if(rotulo.size()) tabela[rotulo] = ci;

		if(instrucao.size()==0) continue;

		if(instrucao=="@") ci = toVal(operando), Endereco_inicial = ci;
		else if(instrucao=="#"){ break;}
		else if(instrucao=="$") ci = ci + toVal(operando);
		else if(instrucao=="K") ci = ci + 1;
		else if(instrucao_2BYTE.count(instrucao)) ci = ci + 2;
		else if(instrucao_1BYTE.count(instrucao)) ci = ci + 1;
		else{
			cout << "Erro: mnemonico indefinido\n";
			cout << instrucao << endl;
			exit(0);
		}
	}
	rewind(pfile);

	BYTE tamanho = ci-Endereco_inicial;

	poeArquivo(Endereco_inicial,2,pObjeto);
	poeArquivo(tamanho,1,pObjeto);

	oposto_checksum = 0;
	//passo 2
	while(1){
		char c;
		string rotulo, instrucao, operando, linha;
		while(fscanf(pfile,"%c", &c)!=EOF and c!='\n') linha+=c;

		fr(i,linha.size()) if(linha[i]==';'){
			while(1){
				linha.erase(--linha.end());
				if(linha.size()==i) goto sai2;
			}
		}
		sai2:
		if(linha.size()==0) continue;

		int i = 0;
		while(i<linha.size() and !isspace(linha[i])) rotulo+=linha[i++];
		while(i<linha.size() and isspace(linha[i])) i++;
		while(i<linha.size() and !isspace(linha[i])) instrucao+=linha[i++];
		while(i<linha.size() and isspace(linha[i])) i++;
		while(i<linha.size() and !isspace(linha[i])) operando+=linha[i++];
		while(i<linha.size() and isspace(linha[i])) i++;

		DOIS_BYTES valOperando;
		if(tabela.count(operando)) valOperando = tabela[operando];
		else if(isnum(operando)) valOperando = toVal(operando);
		else if(operandos_especiais.count(operando)) valOperando = operandos_especiais[operando];
		else if(operando.size()!=0){
			cout << "Operando não definido\n";
			prin(operando.size());
			cout << operando << endl;
			exit(0);
		}

		if(instrucao.size()==0) continue;

		if(instrucao=="@"){
			ci = valOperando;
		} else if(instrucao=="#"){ Endereco_de_execucao = valOperando; break;}
		else if(instrucao=="$") poeArquivo(0,valOperando,pObjeto), ci = ci + valOperando;
		else if(instrucao=="K") poeArquivo(valOperando,1,pObjeto), ci = ci + 1;
		else if(codigo_instrucao.count(instrucao)){
			if(instrucao_2BYTE.count(instrucao))
				poeArquivo(codigo_instrucao[instrucao]*(1<<12)+valOperando,2,pObjeto), ci+=2;
			else if(instrucao_1BYTE.count(instrucao))
			    poeArquivo(codigo_instrucao[instrucao]*(1<<4)+valOperando,1,pObjeto), ci++;
		}
		else{
			cout << "Erro: mnemonico indefinido\n";
			cout << instrucao << endl;
			exit(0);
		}
	}

	poeArquivo(Endereco_de_execucao,2,pObjeto);

	assert(ci-Endereco_inicial==tamanho);
	int check_sum = ((1<<8)-oposto_checksum%(1<<8))%(1<<8);
	poeArquivo(check_sum,1,pObjeto);

	fclose(pfile);
	fclose(pObjeto);

	return 1;
}
