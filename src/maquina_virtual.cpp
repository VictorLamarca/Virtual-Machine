#include "maquina_virtual.h"

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


void maquina_virtual(string arquivo){
	FILE *pObjetoRead, *pObjetoWrite;

	arquivo = tiraExtencao(arquivo);

	montador(arquivo);

	pObjetoRead = fopen((arquivo+".obj").c_str(),"r");
	pObjetoWrite = fopen((arquivo+".dump").c_str(),"w");

	ci = 0;
	simuladorDeExecucao(pObjetoRead,pObjetoWrite);

	//rodar dumper
	ci = 50;
	simuladorDeExecucao(pObjetoRead,pObjetoWrite);
	
	fclose(pObjetoRead);
	fclose(pObjetoWrite);

	return;
}

void simuladorDeExecucao(FILE *pObjetoRead, FILE *pObjetoWrite){
	int opcode, operando;
	bool indireto = 0;

	while(1){
		BYTE cur = memoria_principal[ci];
		opcode = cur>>4;
		operando = cur%(1<<4);

		if(opcode==0){        // JP
			operando<<=8;
			operando+=memoria_principal[ci+1];
			if(indireto) operando = (memoria_principal[operando]<<8) + memoria_principal[operando+1];
			ci = operando;
		} else if(opcode==1){ // JZ
			operando<<=8;
			operando+=memoria_principal[ci+1];
			if(indireto) operando = (memoria_principal[operando]<<8) + memoria_principal[operando+1];
			if(ac==0) ci = operando;
			else ci=ci+2;
		} else if(opcode==2){ // JN
			operando<<=8;
			operando+=memoria_principal[ci+1];
			if(indireto) operando = (memoria_principal[operando]<<8) + memoria_principal[operando+1];
			if(ac<0) ci = operando;
			else ci=ci+2;
		} else if(opcode==3){ // CN
			if(operando==0) return;
			else if(operando==2) indireto = 1;
			else erro("Operando indefinido");
			ci++;
		} else if(opcode==4){ // +
			operando<<=8;
			operando+=memoria_principal[ci+1];
			ac+=memoria_principal[operando];
			ci+=2;
		} else if(opcode==5){ // -
			operando<<=8;
			operando+=memoria_principal[ci+1];
			ac-=memoria_principal[operando];
			ci+=2;
		} else if(opcode==6){ // *
			operando<<=8;
			operando+=memoria_principal[ci+1];
			ac*=memoria_principal[operando];
			ci+=2;
		} else if(opcode==7){ // /
			operando<<=8;
			operando+=memoria_principal[ci+1];
			ac/=memoria_principal[operando];
			ci+=2;
		} else if(opcode==8){ // LD
			operando<<=8;
			operando+=memoria_principal[ci+1];
			if(indireto) operando = (memoria_principal[operando]<<8) + memoria_principal[operando+1];
			ac=memoria_principal[operando];
			ci+=2;
		} else if(opcode==9){ // MM
			operando<<=8;
			operando+=memoria_principal[ci+1];
			if(indireto) operando = (memoria_principal[operando]<<8) + memoria_principal[operando+1];
			memoria_principal[operando]=ac;
			ci+=2;
		} else if(opcode==10){ // SC
			ci+=2;
		} else if(opcode==11){ // OS
			ci++;
		} else if(opcode==12){ // IO
			int xy = operando>>2;
			int zt = operando%(1<<2);
			if(xy==0 and zt==1){
				ac = leByte(pObjetoRead);
			} else if(xy==1 and zt==1){
				escreveByte(pObjetoWrite);
			} else erro("Operando IO não identificado");
			ci++;
		} else erro("opcode nao identificado");

		if(!(opcode==3 and operando==2)) indireto = 0;
	}
}

BYTE leByte(FILE *pObjeto){
	string ans = "00";
	fscanf(pObjeto," %c%c", &ans[0], &ans[1]);
	return toVal('/'+ans);
}

void escreveByte(FILE *pObjeto){
	BYTE cur = ac%(1<<8);
	fprintf(pObjeto,"%s ", byteToHexa(cur).c_str());
	return;
}

