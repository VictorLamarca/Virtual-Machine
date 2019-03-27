#ifndef MAQUINA_VIRTUAL_H_
#define MAQUINA_VIRTUAL_H_

#include "funcoes_auxiliares.h"
using namespace std;

#define BYTE unsigned char
#define DOIS_BYTES unsigned short int

void maquina_virtual(string arquivo);

void simuladorDeExecucao(FILE *pObjetoRead, FILE *pObjetoWrite);

BYTE leByte(FILE *pObjeto);

void escreveByte(FILE *pObjeto);

#endif /* MAQUINA_VIRTUAL_H_ */
