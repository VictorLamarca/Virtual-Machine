/*
 * memoria_e_registradores.cpp
 *
 *  Created on: 30 de jun de 2018
 *      Author: vlamarca
 */

#ifndef MEMORIA_E_REGISTRADORES_H_
#define MEMORIA_E_REGISTRADORES_H_

#define BYTE unsigned char
#define DOIS_BYTES unsigned short int

#include "funcoes_auxiliares.h"

//memória principal é composta por 2^16 BYTES
extern BYTE memoria_principal[1<<16];

extern DOIS_BYTES ci; //contador de instruções
extern DOIS_BYTES ac;

#endif /* MEMORIA_E_REGISTRADORES_H_ */
